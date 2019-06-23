#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>

class UserData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int qml_textFormat MEMBER textFormat NOTIFY textFormatChanged)

public:
    static UserData* getInstance();

    enum TextFormat
    {
        TEXT__FORMAT_SIMPLE,
        TEXT__FORMAT_IP,
        TEXT__FORMAT_HANDLER,
        TEXT__FORMAT_IP_HANDLER
    };
    Q_ENUMS(TextFormat)


    struct{
        QString text;
        bool isEnabled;
    }newClientWelcome;

    int textFormat;

    //This classe is supossed to be a singleton, the bellow functions are public just because the qml engine wants this constructors to be public!
    //Check for memory leak here
    UserData()= default;
    ~UserData()= default;


signals:
    void textFormatChanged();





private:    
    UserData(const UserData&)= delete;
    UserData& operator=(const UserData&)= delete;
};

#endif // USERDATA_H
