#include "service.h"

void memcpy(unsigned char *dest, const unsigned char *src, int count) {
    for (int i = 0; i < count; i++) {
        dest[i] = src[i];
    }
}

void memset(unsigned char *dest, unsigned char val, int count) {
    for (int i = 0; i < count; i++) {
        dest[i] = val;
    }
}

void memsetw(unsigned short *dest, unsigned short val, int count) {
    for (int i = 0; i < count; i++) {
        dest[i] = val;
    }
}

void memsetd(unsigned int *dest, unsigned int val, int count) {
    for (int i = 0; i < count; i++) {
        dest[i] = val;
    }
}

int strlen(const char *str) {
    for (int i = 0;; i++) {
        if (str[i] == '\0') {
            return i;
        }
    }
}

unsigned char inportb (unsigned short port) {
    unsigned char result;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void outportb (unsigned short port, unsigned char data) {
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}
