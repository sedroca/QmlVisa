#include "qmlvisa_plugin.h"
#include "qmlvisa.h"
#include "qmlvisaResourceManager.h"

#include <qqml.h>

void QMLVisaPlugin::registerTypes(const char *uri)
{
    // @uri com.github.sedroca
    qmlRegisterType<Visa>(uri, 1, 0, "Visa");
    qmlRegisterType<VisaResourceManager>(uri, 1, 0, "VisaResourceManager");
    qmlRegisterType<Asrl>(uri, 1, 0, "Asrl");
    qmlRegisterType<Tcpip>(uri, 1, 0, "Tcpip");
}


