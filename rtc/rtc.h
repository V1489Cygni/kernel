#ifndef RTC_H
#define RTC_H

int get_update_in_progress_flag(); 
unsigned char get_RTC_register(int); 
void read_rtc(unsigned char*, unsigned char*, unsigned char*);

#endif
