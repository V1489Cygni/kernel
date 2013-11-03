//////////////////////////////////////////////////////////////////////
// File: main.c
#include "system.h"

/* some convenient functions - as we don't ahve libc, we must do
   everything ourselves */

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
  int i;
  for (i=0; i<count;i++) dest[i]=src[i];
  return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
  int i;
  for (i=0; i<count;i++) dest[i]=val;
  return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
  int i;
  for (i=0; i<count;i++) dest[i]=val;
  return dest;
}

int strlen(const char *str)
{
  int i;
  for (i=0;;i++) if (str[i] == '\0') return i;
}

/* We can use this for reading from the I/O ports to get data from
*  devices such as the keyboard. We are using what is called 'inline
*  assembly' in these routines to actually do the work. [XXX I still
*  have to add devices to the tutorial] */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We can use this to write to I/O ports to send bytes to
*  devices. Again, we use some inline assembly for the stuff that
*  simply cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

/* This is a very simple main() function. All it does is print stuff
*  and then sit in an infinite loop. This will be like our 'idle'
*  loop */
//extern "C"
void cmain (/*unsigned long magic, unsigned long addr*/)
{

  init_video();
  puts ((unsigned char*)"hello world!");

    /* ...and leave this loop in. Note: there is an endless loop in
    *  'start.asm' also, if you accidentally delete this next line */
    for (;;);
}
//////////////////////////////////////////////////////////////////////
