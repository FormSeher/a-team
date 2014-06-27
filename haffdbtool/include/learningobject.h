#ifndef LEARNINGOBJECT_H
#define LEARNINGOBJECT_H

// Database tool
#include "imagemode.h"

// Formseher project
#include "line.h"
#include "linedetection/linedetectionalgorithm.h"
#include "objectdetection/databaseutils.h"

// OpenCV
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Qt
#include <QColor>
#include <QObject>
#include <QString>

class LearningObject : public QObject
{
    Q_OBJECT

public:
    LearningObject(QString imagePath);
    ~LearningObject();

    void setDatabase(QString databasePath);

    std::vector<formseher::Model> getDatabaseModels() const;

    cv::Mat getImage() const;

    QString getImagePath() const;

    QString getDatabasePath() const;

    std::pair<std::vector<formseher::Line>, std::vector<formseher::Line> > getLines() const;

    QString getName() const;

    cv::Mat getOriginalImage() const;

    void saveToDatabase(QString name);

    void addChosenLine(formseher::Line line);

    void addChosenLines(std::vector<formseher::Line> lines);


public slots:
    void slot_getImage(ImageMode mode, int possibleIndex = -1, int chosenIndex = -1);
    void slot_setSettings(formseher::LineDetectionAlgorithm* lineDetectionAlgorithm, std::pair<QColor, QColor> lineColors, int thickness);
    void slot_doubleClicked(std::pair<int, int> clickedLines);
    void slot_deleteFromDataBase(QString name);

signals:
    void signal_newImage(cv::Mat);
    void signal_settingsChanged();
    void signal_linesChanged(std::pair<std::vector<formseher::Line>, std::vector<formseher::Line>>);
    void signal_newDatabase(std::vector<formseher::Model>);


private:
    cv::Mat image;

    QString imagePath;
    QString databasePath;

    std::vector<formseher::Line> possibleLines;
    std::vector<formseher::Line> chosenLines;

    formseher::DatabaseUtils* databaseUtils;

    QString objectName;

    formseher::LineDetectionAlgorithm* lineDetectionAlgorithm;

    std::pair<QColor, QColor> lineColors;

    int thickness = 2;
};

#endif // LEARNINGOBJECT_H
