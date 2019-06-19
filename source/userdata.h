#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>

class UserData : public QObject
{
    Q_OBJECT
public:
    static UserData* getInstance();

    struct{
        QString text;
        bool isEnabled;
    }newClientWelcome;

private:
    UserData()= default;
    ~UserData()= default;
    UserData(const UserData&)= delete;
    UserData& operator=(const UserData&)= delete;
};

#endif // USERDATA_H
