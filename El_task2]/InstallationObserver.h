#pragma once
#include "IInstallationObserver.h"

class InstallationObserver: public IInstallationObserver
{
    Q_OBJECT
public:
    explicit InstallationObserver(QObject* parent = nullptr);
    virtual ~InstallationObserver() = default;

    virtual void OnProgress(int percents) override;

signals:
    void UpdateProgress(int percents);
};
