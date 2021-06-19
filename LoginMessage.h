#pragma once
#include <queue>
#include "Socket.h"
#include "Message.h"
#include "Entity.h"
#include "Serializable.h"

class LoginMessage : public Serializable
{

public:
    LoginMessage(int b=0):a(b){}
    

    virtual void to_bin();
    virtual int from_bin(char *bobj);
    int a;
private:
};