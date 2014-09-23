#ifndef TCPIP_H
#define TCPIP_H

#ifndef NIVISA_H
#define NIVISA_H
#define NIVISA_USB
#include "C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h"
#endif

//#include "qmlvisa.h"

#include <QQuickItem>

class Tcpip : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString addr     READ addr       NOTIFY addrChanged) // read only
    Q_PROPERTY(QString hostname READ hostname   NOTIFY hostnameChanged)  // read only
    Q_PROPERTY(QString port     READ port       NOTIFY portChanged)  // read only

public:
    explicit Tcpip(QQuickItem *parent = 0);

    QString addr();        // Read only
    QString hostname();    // Read only
    QString port();        // Read only

    void setAddr(QString addr);
    void setHostname(QString hostname);
    void setPort (QString port);

signals:
    void addrChanged();
    void hostnameChanged();
    void portChanged();

    void updateVisaAttributes();


public slots:

protected:
    QString _addr;
    QString _hostname;
    QString _port;


};

#endif // TCPIP_H
