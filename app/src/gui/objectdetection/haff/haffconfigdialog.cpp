#include "gui/objectdetection/haff/haffconfigdialog.h"
#include "ui_haffconfigdialog.h"

#include "objectdetection/haff/haff.h"

namespace formseher
{

HaffConfigDialog::HaffConfigDialog(QWidget *parent) :
    ObjectDetectionAlgorithmConfigDialog(parent),
    ui(new Ui::HaffConfigDialog)
{
    ui->setupUi(this);
}

HaffConfigDialog::~HaffConfigDialog()
{
    delete ui;
}

ObjectDetectionAlgorithm* HaffConfigDialog::createAlgorithm()
{
    return new Haff(ui->numberOfBestHypotheses->value(),
                    ui->numberOfDetectedObjects->value(),
                    ui->minimalObjectRating->value(),
                    ui->coverWeight->value(),
                    ui->angleWeight->value(),
                    ui->positionWeight->value()
    );
}

void HaffConfigDialog::on_numberOfBestHypotheses_valueChanged(int)
{
    emit configChanged();
}

void HaffConfigDialog::on_numberOfDetectedObjects_valueChanged(int)
{
    emit configChanged();
}

void HaffConfigDialog::on_minimalObjectRating_valueChanged(double)
{
    emit configChanged();
}

void HaffConfigDialog::on_coverWeight_valueChanged(double)
{
    emit configChanged();
}

void HaffConfigDialog::on_angleWeight_valueChanged(double)
{
    emit configChanged();
}

void HaffConfigDialog::on_positionWeight_valueChanged(double)
{
    emit configChanged();
}

} // namespace formseher

