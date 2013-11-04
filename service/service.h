#ifndef SERVICE_H
#define SERVICE_H

void memcpy(unsigned char*, const unsigned char*, int);

void memset(unsigned char*, unsigned char, int);
void memsetw(unsigned short*, unsigned short, int);
void memsetd(unsigned int*, unsigned int, int);

int strlen(const char*);

unsigned char inportb (unsigned short);
void outportb (unsigned short, unsigned char);

#endif
