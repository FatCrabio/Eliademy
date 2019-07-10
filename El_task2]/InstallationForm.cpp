#include "pch.h"
#include <QThread>
#include "InstallationForm.h"
#include "InstallationObserver.h"
#include "ui_InstallationForm.h"

#include <QDebug>


namespace
{
    void CallSomeUglyAPI(int i) // this interface can’t be changed
    {
        QThread::sleep(100);
    }

    void SampleThreadToTestWith(IInstallationObserver* pObserver, std::atomic<bool>& operationCancelled) // this interface can be changed
    {
        for(int i = 0; i < 10; ++i)
        {
            if (operationCancelled)
            {
                return;
            }

            CallSomeUglyAPI(i);
            pObserver->OnProgress(i * 10);
        }
        pObserver->OnProgress(100);
    }
}

InstallationForm::InstallationForm(QWidget* parent) :
    QWidget(parent),
    m_operationCanceled(false),
    m_processingThread(nullptr),
    m_ui(new Ui::InstallationForm),
    m_observer(new InstallationObserver)
{
    m_ui->setupUi(this);
    connect(m_observer.get(), &InstallationObserver::UpdateProgress, this, &InstallationForm::OnProgress, Qt::QueuedConnection);
}

InstallationForm::~InstallationForm()
{
    if (m_processingThread)
    {
        qDebug() << "Closed";
        m_processingThread->wait();
    }
}

void InstallationForm::OnStartInstallationClick()
{
    m_processingThread.reset(QThread::create([this]()
    {
        SampleThreadToTestWith(m_observer.get(), m_operationCanceled);
    }));

    connect(this, &InstallationForm::UserHasCancelledOperation, m_processingThread.get(), [this]
    {
        m_operationCanceled = true;
        this->OnProgress(100);
    }, Qt::DirectConnection);

    m_processingThread->start();
}

void InstallationForm::OnProgress(int percents)
{
    m_ui->progressBar->setValue(percents);
}

void InstallationForm::closeEvent(QCloseEvent* event)
{
    emit UserHasCancelledOperation();

    QWidget::closeEvent(event);
}
