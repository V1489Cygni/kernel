#include "../input/input.h"
#include "../output/output.h"
#include "../shell/shell.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"
#include "../isr/isr.h"
#include "../irq/irq.h"
#include "../pit/pit.h"
#include "../rtc/rtc.h"

void show_time() {
    print((unsigned char*)"Current time is: ");
    unsigned char h, m, s;
    read_rtc(&h, &m, &s);
    if(h < 10) print_char('0');
    print_int_10(h);
    print_char(':');
    if(m < 10) print_char('0');
    print_int_10(m);
    print_char(':');
    if(s < 10) print_char('0');
    print_int_10(s);
    print_char('\n');
}

void process_cmd(unsigned char* cmd) {
    int length = 0;
    for(;; length++)
        if(!cmd[length])
            break;
    length--;
    if(length < 0) {
        print((unsigned char*)"Unknown command!\n");
        return;
    }
    while(cmd[length] == ' ' && length > 0) {
        length--;
    }
    length++; 
    if(length > 5 && cmd[0] == 'e' && cmd[1] == 'c' && cmd[2] == 'h' && cmd[3] == 'o' && cmd[4] == ' ') {
        print(cmd + 5);
        print_char('\n');
        return;
    } else if (length == 3 && cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == 's') {
        cls();
        return;
    } else if (length == 4 && cmd[0] == 't' && cmd[1] == 'i' && cmd[2] == 'm' && cmd[3] == 'e') {
        show_time();
        return;
    }
	print((unsigned char*)"Unknown command!\n");
}

int kernel_main() {
    init_output();
    print((unsigned char*)"Video memory is set up into text mode\nInstalling GDT...                  ");
    gdt_install();
    print((unsigned char*)"OK\nInstalling IDT...                  ");
    idt_install();
    print((unsigned char*)"OK\nInstalling ISRs...                 ");
    isr_install();
    print((unsigned char*)"OK\nInstalling IRQs...                 ");
    irq_install();
    print((unsigned char*)"OK\nInstalling keyboard input...       ");
    init_input();
    print((unsigned char*)"OK\nInstalling timer...                ");
    timer_install();
    print((unsigned char*)"OK\nEnableing interrupts...            ");
    __asm__ __volatile__ ("sti");
    print((unsigned char*)"OK\nMain is loaded at: ");
    print_int((int)kernel_main);
    print_char('\n');
    show_time();
    while(1) {
        print((unsigned char*)"> ");
        process_cmd(next_cmd());
    }
}
    
