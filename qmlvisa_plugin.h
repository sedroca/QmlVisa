#ifndef QMLVISA_PLUGIN_H
#define QMLVISA_PLUGIN_H

#include <QQmlExtensionPlugin>

class QMLVisaPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // QMLVISA_PLUGIN_H

