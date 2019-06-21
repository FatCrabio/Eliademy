#include "InstallationObserver.h"

InstallationObserver::InstallationObserver(QObject* parent)
    : IInstallationObserver(parent)
{
}

void InstallationObserver::OnProgress(int percents)
{
    emit UpdateProgress(percents);
}

