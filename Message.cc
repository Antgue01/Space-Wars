#include "Message.h"
#include <memory.h>
void Message::send(Socket src, Socket dest)
{
    src.send(*_obj, dest);
}
void CountMessage::to_bin()
{
    int size = sizeof(int);
    alloc_data(size);
    memset(_data, 0, size);
    memcpy(_data, &_numMessages, sizeof(int));
}
int CountMessage::from_bin(char *bobj)
{
    if (bobj == 0)
    {
        std::cout << "Error on deserialization, empty object received\n";
        return -1;
    }
    int size = sizeof(int);
    alloc_data(size);
    memcpy(static_cast<void *>(_data), bobj, size);
    memcpy(&_numMessages, _data, sizeof(int));
}

