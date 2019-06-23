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
    read_textFormat(&xmlReader);
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

void XMLConfigReader::read_textFormat(QDomDocument *xmlReader)
{
    QDomNodeList nodes = xmlReader->firstChildElement().childNodes();
        qDebug() << "NODES COUNT: " <<  nodes.count() ;

    for (int var = 0; var < nodes.count(); var++) {
        if(!nodes.at(var).toElement().tagName().compare("textFormat")){
            qDebug() << "NODE TEXT: " <<  nodes.at(var).toElement().text() ;
            if( nodes.at(var).toElement().text() == "TEXT__FORMAT_SIMPLE"){
                xml_user_config->textFormat = UserData::TEXT__FORMAT_SIMPLE;
            }else if( nodes.at(var).toElement().text() == "TEXT__FORMAT_IP"){
                xml_user_config->textFormat = UserData::TEXT__FORMAT_IP;
            }else if( nodes.at(var).toElement().text() == "TEXT__FORMAT_HANDLER"){
                xml_user_config->textFormat = UserData::TEXT__FORMAT_HANDLER;
            }else if( nodes.at(var).toElement().text() == "TEXT__FORMAT_IP_HANDLER"){
                xml_user_config->textFormat = UserData::TEXT__FORMAT_IP_HANDLER;
            }
            break;
        }
    }
    qDebug() << "TIPO FORMATACAO TEXTO: " <<  xml_user_config->textFormat ;
}
