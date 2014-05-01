#include "algorithmcontroller.hpp"

#include "algorithmworker.h"

#include <iostream>

AlgorithmController::AlgorithmController()
    : configDialog(0),
      queuedAlgorithm(0),
      scheduledAlgorithm(0)
{}

AlgorithmController::~AlgorithmController()
{
    if(queuedAlgorithm)
        delete queuedAlgorithm;
}

void AlgorithmController::setAlgorithmConfigDialog(AlgorithmConfigDialog *dialog)
{
    if(configDialog)
        disconnect(configChangedConnection);

    configDialog = dialog;
    configChangedConnection = connect(configDialog, &AlgorithmConfigDialog::configChanged,
                                      this, &AlgorithmController::enqueueAlgorithm);
}

void AlgorithmController::setImage(cv::InputArray image)
{
    queueMutex.lock();
    this->image = image.getMat();
    queueMutex.unlock();
}

std::vector<Line> AlgorithmController::getLatestResult()
{
    return latestResult;
}

void AlgorithmController::enqueueAlgorithm()
{
    Algorithm* newAlgorithm = configDialog->createAlgorithm();

    queueMutex.lock();
    if(queuedAlgorithm != 0)
        delete queuedAlgorithm;
    queuedAlgorithm = newAlgorithm;
    queueMutex.unlock();

    std::cout << "enqueued algorithm...." << std::endl;

    scheduleAlgorithm();
}

void AlgorithmController::scheduleAlgorithm()
{
    queueMutex.lock();

    if(scheduledAlgorithm != 0 || queuedAlgorithm == 0 || image.empty())
    {
        queueMutex.unlock();
        return;
    }

    worker = new AlgorithmWorker(queuedAlgorithm, image, this);
    scheduledAlgorithm = queuedAlgorithm;
    queuedAlgorithm = 0;
    connect(worker, &AlgorithmWorker::resultReady, this, &AlgorithmController::handleResult);
    connect(worker, &QThread::finished, worker, &QObject::deleteLater);
    worker->start();

    queueMutex.unlock();
}

void AlgorithmController::handleResult()
{
    queueMutex.lock();

    latestResult = worker->getResult();

    scheduledAlgorithm = 0;
    emit newResultAvailable();

    queueMutex.unlock();
}
