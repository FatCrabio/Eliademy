#pragma once

#include <QMainWindow>

class InstallationForm;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QPushButton* m_startOperation;
    std::unique_ptr<InstallationForm> m_installationForm;
};

