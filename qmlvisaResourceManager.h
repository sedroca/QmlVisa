#ifndef QMLVISARESOURCEMANAGER_H
#define QMLVISARESOURCEMANAGER_H

#include <QQuickItem>
#include <QStringList>
#include <QString>

#include "asrl.h"
#include "tcpip.h"
#include "usbraw.h"




#ifndef NIVISA_H
#define NIVISA_USB
#define NIVISA_H
#include "C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h"

#endif

class VisaResourceManager : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(VisaResourceManager)

    Q_PROPERTY(QStringList resourceList READ resourceList NOTIFY resourceListChanged)
    Q_PROPERTY(QString expr READ expr WRITE setExpr NOTIFY exprChanged)
    Q_PROPERTY(QString statusMsg READ statusMsg NOTIFY statusMsgChanged)


public:
    VisaResourceManager(QQuickItem *parent = 0);
    ~VisaResourceManager();
    Q_INVOKABLE QStringList findResource();

    QStringList resourceList();
    QString expr();
    void setExpr(const QString &ex);
    QString statusMsg();

signals:
    void resourceListChanged();
    void exprChanged();
    void statusMsgChanged();

private:
    ViSession _defaultRM;
    QStringList _resourceList;
    QString _expr;
    QString _statusMsg;

};




#endif // QMLVISARESOURCEMANAGER_H
