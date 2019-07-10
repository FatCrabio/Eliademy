#include "pch.h"
#include "MainWindow.h"
#include "QPushButton"
#include "InstallationForm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_startOperation = new QPushButton(this);
    this->layout()->addWidget(m_startOperation);

    connect(m_startOperation, &QPushButton::clicked, [this]()
    {
        m_installationForm = std::unique_ptr<InstallationForm>(new InstallationForm(nullptr));

        m_installationForm->show();
        m_installationForm->OnStartInstallationClick();
    });
}

MainWindow::~MainWindow()
{

}
