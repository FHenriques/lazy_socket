#include "xml-config-reader.h"
#include <QDebug>
#include <QCoreApplication>

XMLConfigReader::XMLConfigReader()
{
    xml_user_config = UserData::getInstance();
}

void XMLConfigReader::read_initXML()
{
    QString appPath(QCoreApplication::applicationDirPath());
    qDebug() << appPath;
    QFile xmlReaderFile(appPath + "/lazy_ini.xml");

    if(!xmlReaderFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Cannot read file" << xmlReaderFile.errorString();
        exit(0);
    }

    QDomDocument xmlReader("xml_initializer");

    if (!xmlReader.setContent(&xmlReaderFile)) {
        xmlReaderFile.close();
        return;
    }
    xmlReaderFile.close();
    read_newClientWelcome(&xmlReader);
    read_scripts(&xmlReader);
}

void XMLConfigReader::read_newClientWelcome(QDomDocument *xmlReader)
{
    QDomNodeList nodes = xmlReader->firstChildElement().childNodes();
    for (int var = 0; var < nodes.count(); var++) {
        if(!nodes.at(var).toElement().tagName().compare("newClientWelcome")){
            nodes = nodes.at(var).toElement().childNodes();
            for (int var = 0; var < nodes.count(); var++) {
                if(!nodes.at(var).toElement().tagName().compare("text")){
                    xml_user_config->newClientWelcome.text = nodes.at(var).toElement().text();
                }else if(!nodes.at(var).toElement().tagName().compare("isEnabled")){
                    xml_user_config->newClientWelcome.isEnabled = nodes.at(var).toElement().text().toInt();
                }
            }
            break;
        }
    }
}

void XMLConfigReader::read_scripts(QDomDocument *xmlReader)
{

}
