#include "tcpip.h"

Tcpip::Tcpip(QQuickItem *parent) :
    QQuickItem(parent)
{
}


// Tcpip Address
// (read only)
//
QString Tcpip::addr()
{
    return _addr;
}

void Tcpip::setAddr(QString addr)
{
    _addr = addr;
}


// Tcpip Hostname
// (read only)
//
QString Tcpip::hostname()
{
    return _hostname;
}

void Tcpip::setHostname(QString hostname)
{
    _hostname = hostname;
}

// Tcpip port
// (read only)
//
QString Tcpip::port()
{
    return _port;
}

void Tcpip::setPort(QString port)
{
    _port = port;
}


