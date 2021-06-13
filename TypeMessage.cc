#include "TypeMessage.h"
void TypeMessage::to_bin()
{
    int size = sizeof(uint);
    alloc_data(size);
    uint aux = (uint)myType_;
    memset(_data, 0, size);
    memcpy(_data, &aux, sizeof(uint));
}
int TypeMessage::from_bin(char *bobj)
{
    if (bobj == 0)
    {
        std::cout << "Error on deserialization, empty object received\n";
        return -1;
    }
    int size = sizeof(uint);
    alloc_data(size);
    memcpy(static_cast<void *>(_data), bobj, size);
    uint aux;
    memcpy(&aux, bobj, sizeof(uint));
    myType_=(NetType)aux;
}
