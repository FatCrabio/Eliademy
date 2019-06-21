#pragma once
#include <QMainWindow>

namespace Ui {
    class InstallationForm;
}

class InstallationObserver;

class InstallationForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit InstallationForm(QWidget* parent = nullptr);
    virtual ~InstallationForm() = default;

    void OnProgress(int percents);
    void OnStartInstallationClick();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void UserHasCancelledOperation();

private:
    Ui::InstallationForm* m_ui;
    InstallationObserver* m_observer;
};

