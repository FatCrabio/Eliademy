#pragma once
#include <QObject>

class IInstallationObserver : public QObject
{
    Q_OBJECT
public:
    IInstallationObserver(QObject* parent = nullptr) : QObject(parent) {}

    virtual ~IInstallationObserver() = default;
    virtual void OnProgress(int percents) = 0;
};
