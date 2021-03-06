#pragma once
#include "Socket.h"
#include "Serializable.h"
//clase para enviar un serializable
class Message
{
public:
    Message(Serializable *obj) : _obj(obj) {}
    void send(Socket* src, Socket* dest);
    inline Serializable *getObj() { return _obj; }
    inline void setObj(Serializable *s) { _obj = s; }

private:
    Serializable *_obj;
};
//Serializable que tiene el número de mensajes que se enviarán
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