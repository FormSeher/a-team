/*
* This file is part of FormSeher.
*
* FormSeher is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* FormSeher is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright 2014 FormSeher
*/

// Database tool
#include "learningobject.h"

// Qt
#include <QFile>

LearningObject::LearningObject(QString imagePath)
    : imagePath(imagePath)
{
    if(QFile(imagePath).exists())
        this->image = cv::imread(imagePath.toStdString(), CV_LOAD_IMAGE_COLOR);
}

LearningObject::~LearningObject()
{
    image.release();

    possibleLines.clear();
    chosenLines.clear();
}

void LearningObject::setDatabase(QString databasePath)
{
    this->databasePath = databasePath;
    this->databaseUtils = new formseher::DatabaseUtils(databasePath.toStdString());

    emit signal_newDatabase(this->databaseUtils->read());
}

std::vector<formseher::Model> LearningObject::getDatabaseModels() const
{
    return this->databaseUtils->read();
}

cv::Mat LearningObject::getImage() const
{
    return this->image;
}

std::pair<std::vector<formseher::Line>, std::vector<formseher::Line> > LearningObject::getLines() const
{
    return std::pair<std::vector<formseher::Line>, std::vector<formseher::Line>>(this->possibleLines, this->chosenLines);
}

QString LearningObject::getImagePath() const
{
    return this->imagePath;
}

QString LearningObject::getDatabasePath() const
{
    return this->databasePath;
}

void LearningObject::slot_getImage(ImageMode mode, int possibleIndex, int chosenIndex)
{
    cv::Mat imageToReturn = image.clone();

    if(mode == ImageMode::MODE_IMG || mode == ImageMode::MODE_GREY)
    {
        if(mode == ImageMode::MODE_GREY)
        {
            cv::cvtColor(imageToReturn, imageToReturn, CV_BGR2GRAY);
            cv::cvtColor(imageToReturn, imageToReturn, CV_GRAY2RGB);
        }
        else
        {
            cv::cvtColor(imageToReturn, imageToReturn, CV_BGR2RGB);
        }
    }
    else
    {
        if(mode == ImageMode::MODE_IMG_LINES)
        {
            cv::cvtColor(imageToReturn, imageToReturn, CV_BGR2RGB);
        }
        else if(mode == ImageMode::MODE_GREY_LINES)
        {
            cv::cvtColor(imageToReturn, imageToReturn, CV_RGB2GRAY);
            cv::cvtColor(imageToReturn, imageToReturn, CV_GRAY2RGB);
        }
        else if(mode == ImageMode::MODE_LINES)
        {
            imageToReturn = cv::Mat::zeros(imageToReturn.rows, imageToReturn.cols, imageToReturn.type());
        }

        for(auto line: chosenLines)
        {
            cv::line(imageToReturn, line.getStart(), line.getEnd(),
                     cv::Scalar(lineColors.first.red(), lineColors.first.green(), lineColors.first.blue()), thickness);
        }

        if(possibleIndex >= 0 && possibleLines.size() > 0)
        {
            cv::line(imageToReturn, possibleLines.at(possibleIndex).getStart(), possibleLines.at(possibleIndex).getEnd(),
                     cv::Scalar(lineColors.second.red(), lineColors.second.green(), lineColors.second.blue()), thickness);
        }
        else if(chosenIndex >= 0 && chosenLines.size() > 0)
        {
            cv::line(imageToReturn, chosenLines.at(chosenIndex).getStart(), chosenLines.at(chosenIndex).getEnd(),
                     cv::Scalar(lineColors.second.red(), lineColors.second.green(), lineColors.second.blue()), thickness);
        }
    }

    emit signal_newImage(imageToReturn);
}

void LearningObject::slot_setSettings(formseher::LineDetectionAlgorithm* lineDetectionAlgorithm, std::pair<QColor, QColor> lineColors, int thickness)
{
    this->lineDetectionAlgorithm = lineDetectionAlgorithm;
    this->lineColors = lineColors;
    this->thickness = thickness;

    possibleLines = lineDetectionAlgorithm->calculate(image.clone());

    emit signal_linesChanged(std::pair<std::vector<formseher::Line>, std::vector<formseher::Line>>(possibleLines, chosenLines));

    emit signal_settingsChanged();
}

cv::Mat LearningObject::getOriginalImage() const
{
    return image.clone();
}

void LearningObject::slot_doubleClicked(std::pair<int, int> clickedLines)
{
    if(clickedLines.first >= 0)
    {
        chosenLines.push_back(possibleLines[clickedLines.first]);
        possibleLines.erase(possibleLines.begin() + clickedLines.first);
    }
    else if(clickedLines.second >= 0)
    {
        possibleLines.push_back(chosenLines[clickedLines.second]);
        chosenLines.erase(chosenLines.begin() + clickedLines.second);
    }

    emit signal_linesChanged(std::pair<std::vector<formseher::Line>, std::vector<formseher::Line>>(possibleLines, chosenLines));

}

void LearningObject::saveToDatabase(QString name)
{
    formseher::Object obj;
    obj.setName(name.toStdString());

    for(auto line : chosenLines)
    {
        obj.addLine(line);
    }

    databaseUtils->read();
    databaseUtils->addObject(obj);
    databaseUtils->write();

    emit signal_newDatabase(this->databaseUtils->read());
}

void LearningObject::slot_deleteFromDataBase(QString name)
{
    formseher::Object obj;
    obj.fromString(name.toStdString());
    databaseUtils->removeObject(obj);
    databaseUtils->write();

    emit signal_newDatabase(this->databaseUtils->read());
}

void LearningObject::addChosenLine(formseher::Line line)
{
    if(imagePath != "")
    {
        chosenLines.push_back(line);
        emit signal_linesChanged(std::pair<std::vector<formseher::Line>, std::vector<formseher::Line>>(possibleLines, chosenLines));
    }
}

void LearningObject::addChosenLines(std::vector<formseher::Line> lines)
{
    if(imagePath != "")
    {
        for(formseher::Line line : lines)
            chosenLines.push_back(line);
        emit signal_linesChanged(std::pair<std::vector<formseher::Line>, std::vector<formseher::Line>>(possibleLines, chosenLines));
    }
}
