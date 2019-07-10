#pragma once
#include <QWidget>

namespace Ui {
    class InstallationForm;
}

class InstallationObserver;

class InstallationForm : public QWidget
{
    Q_OBJECT

public:
    explicit InstallationForm(QWidget* parent = nullptr);
    virtual ~InstallationForm();

    void OnProgress(int percents);
    void OnStartInstallationClick();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void UserHasCancelledOperation();

private:
    std::atomic<bool> m_operationCanceled;
    std::unique_ptr<QThread> m_processingThread;
    std::unique_ptr<Ui::InstallationForm> m_ui;
    std::unique_ptr<InstallationObserver> m_observer;
};

