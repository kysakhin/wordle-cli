#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void clear_screen(void);
void get_todays_date(char* buffer, size_t size);
void clear_input_buffer(void);
size_t write_callback(void *ptr, size_t size, size_t nmemb, void* userdata);

#endif
