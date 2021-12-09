#include <stdio.h>
#include <stdlib.h>

int split_time(char time[],char hour[], char minute[], char second[]);

int split_csv(char source[],char destination[],char hour[],char minutes[],char seconds[],char string[]);

int compare_lower_time(int time1[],int time2[]);

int my_strlen(char *s);

int string_compare(char string1[],char string2[]);

int string_compare(char string1[],char string2[]);

int check_route(char* source,char* destination,char* new_source,char* new_destination);

int make_time1_equal_time2(int time1[],int time2[]);

int check_line(char line[]);
