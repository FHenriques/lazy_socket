#ifndef XMLCONFIG_H
#define XMLCONFIG_H

#include <QObject>
#include <QFile>
#include <QDomDocument>
#include "userdata.h"

class XMLConfigReader
{
public:
    XMLConfigReader();

    void read_initXML(void);
    void read_newClientWelcome(QDomDocument *xmlReader);
    void read_scripts(QDomDocument *xmlReader);

private:
    UserData* xml_user_config;
};

#endif // XMLCONFIG_H
