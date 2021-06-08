#pragma once
#include "Socket.h"
#include "Serializable.h"
#include "Component.h"

class Message
{
public:
    Message(Serializable *obj, netType t) : _obj(obj), _myType(t) {}
    void send(Socket src, Socket dest);
    inline Serializable *getObj() { return _obj; }
    inline void setObj(Serializable *s) { _obj = s; }

private:
    netType _myType;
    Serializable *_obj;
};

class CountMessage : public Serializable
{
private:
    int _numMessages;

public:
    CountMessage(int num) : _numMessages(num) {}
    virtual void to_bin();
    virtual int from_bin(char *bobj);
    virtual void deserialize(char *data) {}
    int getNumMessages() { return _numMessages; }
};