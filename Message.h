#pragma once
#include "Socket.h"
#include "Serializable.h"
enum type
{
    Count,
    NetVesselMovement
};
class Message
{
public:
    Message(Serializable *obj, type t) : _obj(obj), _myType(t) {}
    void send(Socket sock);

private:
    type _myType;
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
    int getNumMessages() { return _numMessages; }
};