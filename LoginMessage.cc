#include "LoginMessage.h"

void LoginMessage::to_bin()
{
    int size = sizeof(int);
    alloc_data(size);
    memset(_data, 0, size);
    memcpy(_data, &a, sizeof(int));
}
int LoginMessage::from_bin(char *bobj)
{
    if (bobj == 0)
    {
        std::cout << "Error on deserialization, empty object received\n";
        return -1;
    }
    int size = sizeof(int);
    alloc_data(size);
    memcpy(static_cast<void *>(_data), bobj, size);

    char tmp;
    memcpy(&tmp,bobj,sizeof(int));
    a=tmp;
}
