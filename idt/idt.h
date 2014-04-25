#ifndef IDT_H
#define IDT_H

typedef struct {
    unsigned short base_lo;
    unsigned short sel;        
    unsigned char always0;    
    unsigned char flags;     
    unsigned short base_hi;
}__attribute__((packed)) idt_entry;

typedef struct {
    unsigned short limit;
    unsigned int base;
}__attribute__((packed)) idt_ptr;

extern void idt_load();
void idt_set_gate(unsigned char, unsigned long, unsigned short, unsigned char);
void idt_install();

#endif
