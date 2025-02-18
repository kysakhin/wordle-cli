#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/utils.h"

void clear_screen()
{
  system("clear");
}

void get_todays_date(char *buffer, size_t size)
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  snprintf(buffer, size, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void clear_input_buffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
  strncat((char*)userdata, (char*)ptr, size*nmemb);
  return size*nmemb;
}
