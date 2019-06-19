#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Communication/socket-tool-server.h"
#include <QQmlContext>
#include "ConstVars/xml-config-reader.h"
#include "userdata.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
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



    qmlRegisterType<SocketsToolServer>("SocketsToolServer", 0, 1, "SocketsToolServer");
    engine.rootContext()->setContextProperty("socketServer", &socketToolServer);
    engine.rootContext()->setContextProperty("xml_user_data", xml_user_data);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
