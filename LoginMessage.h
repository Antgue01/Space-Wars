#pragma once
#include <queue>
#include "Socket.h"
#include "Message.h"
#include "Entity.h"
#include "Serializable.h"

class LoginMessage : public Serializable
{

public:
    LoginMessage(){}
    

    virtual void to_bin();
    virtual int from_bin(char *bobj);
	virtual void deserialize(char* data) override;
private:
    int a=0;
};