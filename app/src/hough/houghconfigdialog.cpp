#include "hough/houghconfigdialog.h"
#include "ui_houghconfigdialog.h"

HoughConfigDialog::HoughConfigDialog(QWidget *parent) :
    AlgorithmConfigDialog(parent),
    ui(new Ui::HoughConfigDialog)
{
    ui->setupUi(this);
}

HoughConfigDialog::~HoughConfigDialog()
{
    delete ui;
}

Algorithm* HoughConfigDialog::createAlgorithm()
{
    return new Hough(
                ui->checkEnvironmentSize->value(),
                ui->maximalLineGap->value(),
                ui->minimumLineSize->value()
    );
}

void HoughConfigDialog::on_checkEnvironmentSize_valueChanged(int houghMinimumLineSize)
{
    emit configChanged();
}

void HoughConfigDialog::on_maximalLineGap_valueChanged(int houghMinimumLineSize)
{
    emit configChanged();
}

void HoughConfigDialog::on_minimumLineSize_valueChanged(int minimumLineSize)
{
    emit configChanged();
}
