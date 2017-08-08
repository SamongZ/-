#ifndef SHM_COM_H
#define SHM_COM_H
#define MAXSIZE 2048

struct shared_use_st
{
    int written;
    char text[MAXSIZE];
};

#endif // SHM_COM_H_INCLUDED
