#include "userdata.h"

UserData* UserData::getInstance(){
    static UserData* pSingleInstance = nullptr;
    if ( pSingleInstance == nullptr ){
        pSingleInstance= new UserData();
    }
    return pSingleInstance;
}

