#include "InstallationForm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InstallationForm w;
    w.show();
    w.OnStartInstallationClick();

    return a.exec();
}
