#include "edl/edlconfigdialog.h"
#include "ui_edlconfigdialog.h"

EDLConfigDialog::EDLConfigDialog(QWidget *parent) :
    AlgorithmConfigDialog(parent),
    ui(new Ui::EDLConfigDialog)
{
    ui->setupUi(this);
}

EDLConfigDialog::~EDLConfigDialog()
{
    delete ui;
}

Algorithm* EDLConfigDialog::createAlgorithm()
{
    return new EDL(
                ui->sobelKernelSize->value(),
                ui->sobelScale->value(),
                ui->sobelDelta->value(),
                ui->gaussianKernelSize->value(),
                ui->anchorThreshold->value(),
                ui->angleTolerance->value() * M_PI / 180.0
    );
}

void EDLConfigDialog::on_sobelKernelSize_valueChanged(int sobelKernelSize)
{
    emit configChanged();
}

void EDLConfigDialog::on_sobelScale_valueChanged(double sobelScale)
{
    emit configChanged();
}

void EDLConfigDialog::on_sobelDelta_valueChanged(double sobelDelta)
{
    emit configChanged();
}

void EDLConfigDialog::on_gaussianKernelSize_valueChanged(int gaussianKernelSize)
{
    emit configChanged();
}

void EDLConfigDialog::on_anchorThreshold_valueChanged(int anchorThreshold)
{
    emit configChanged();
}

void EDLConfigDialog::on_angleTolerance_valueChanged(double angleTolerance)
{
    emit configChanged();
}
