#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include "Communication/socket-tool-server.h"
#include <QQmlContext>
#include "ConstVars/xml-config-reader.h"
#include "userdata.h"
#include "Communication/clients-monitor.h"

#include "Models/socket-clients-list.h"
#include "Models/socket-clients-model.h"


int main(int argc, char *argv[])
{
    qRegisterMetaType<ClientDataPacket>("ClientDataPacket");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("Digiwest");
    app.setOrganizationDomain("digiwest.pt");
    app.setApplicationName("SocketsTool");




    XMLConfigReader init_xml;
    init_xml.read_initXML();

    UserData* xml_user_data = UserData::getInstance();

    SocketsToolServer socketToolServer;
    socketToolServer.config__welcome_message(
                xml_user_data->newClientWelcome.text,
                xml_user_data->newClientWelcome.isEnabled
                );

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    SocketClientsList socketClientsList;

    QObject::connect(&socketToolServer,&SocketsToolServer::sig__new_connection,&socketClientsList,&SocketClientsList::appendItem);


    qmlRegisterType<ClientsModel>("SocketClientsModel", 1, 0, "SocketClientsModel");
    qmlRegisterUncreatableType<SocketClientsList>("SocketClients", 1, 0, "SocketClientsList",
        QStringLiteral("ToDoList should not be created in QML"));
    qmlRegisterType<SocketsToolServer>("SocketsToolServer", 0, 1, "SocketsToolServer");
    qmlRegisterType<UserData>("UserData", 0, 1, "UserData");
    engine.rootContext()->setContextProperty("socketServer", &socketToolServer);
    engine.rootContext()->setContextProperty("xml_user_data", xml_user_data);
    engine.rootContext()->setContextProperty("sockets_manager", SOCKET_CLIENTS_MONITOR);
    engine.rootContext()->setContextProperty(QStringLiteral("socketClientsList"), &socketClientsList);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
