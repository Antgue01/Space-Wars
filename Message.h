#pragma once
#include "Socket.h"
#include "Serializable.h"

class Message
{
public:
enum type
{
    Count,
    NetVesselMovement
};

    Message(Serializable *obj, type t) : _obj(obj), _myType(t) {}
    void send(Socket src,Socket dest);
    inline Serializable* getObj(){return _obj;}
    inline void setObj(Serializable* s){_obj=s;}
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
    virtual void deserialize(char* data)override {}
    int getNumMessages() { return _numMessages; }
};