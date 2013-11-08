#include "rtc.h"

#include "../service/service.h"

unsigned char cmos_address = 0x70;
unsigned char cmos_data = 0x71;
 
int get_update_in_progress_flag() {
    outportb(cmos_address, 0x0A);
    return (inportb(cmos_data) & 0x80);
} 
 
unsigned char get_RTC_register(int reg) {
    outportb(cmos_address, reg);
    return inportb(cmos_data);
} 
 
void read_rtc(unsigned char* hours, unsigned char* minutes, unsigned char* seconds) {
    while (get_update_in_progress_flag());
    unsigned char second = get_RTC_register(0x00);
    unsigned char minute = get_RTC_register(0x02);
    unsigned char hour = get_RTC_register(0x04);
    unsigned char register_b = get_RTC_register(0x0B);
    if (!(register_b & 0x04)) {
        second = (second & 0x0F) + ((second / 16) * 10);
        minute = (minute & 0x0F) + ((minute / 16) * 10);
        hour = ((hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
    }
    *hours = hour;
    *minutes = minute;
    *seconds = second;
}
