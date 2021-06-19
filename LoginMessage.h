#pragma once
#include <queue>
#include "Socket.h"
#include "Message.h"
#include "Entity.h"
#include "Serializable.h"

//Mensaje inicial para identificar al cliente por parte del servidor

class LoginMessage : public Serializable
{

public:
    LoginMessage(){}
    

    virtual void to_bin();
    virtual int from_bin(char *bobj);

};