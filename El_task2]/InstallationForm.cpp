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
        QThread::sleep(2);
    }

    void SampleThreadToTestWith(IInstallationObserver* pObserver) // this interface can be changed
    {
        for(int i = 0; i < 10; ++i)
        {
            if (QThread::currentThread()->isInterruptionRequested())
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
    QMainWindow(parent),
    m_ui(new Ui::InstallationForm),
    m_observer(new InstallationObserver)
{
    m_ui->setupUi(this);
    connect(m_observer.get(), &InstallationObserver::UpdateProgress, this, &InstallationForm::OnProgress, Qt::QueuedConnection);
}

InstallationForm::~InstallationForm()
{

}

void InstallationForm::OnStartInstallationClick()
{
    QThread* work_thread = QThread::create([this]()
    {
        SampleThreadToTestWith(m_observer.get());
    });

    connect(work_thread, &QThread::finished, work_thread, &QThread::deleteLater);
    connect(this, &InstallationForm::UserHasCancelledOperation, work_thread, [this, work_thread]
    {
        this->OnProgress(100);
        work_thread->requestInterruption();
    }, Qt::DirectConnection);

    work_thread->start();
}

void InstallationForm::OnProgress(int percents)
{
    m_ui->progressBar->setValue(percents);
}

void InstallationForm::closeEvent(QCloseEvent* event)
{
    emit UserHasCancelledOperation();
    QMainWindow::closeEvent(event);
}
