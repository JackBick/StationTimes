#include "timetable.h"

#define MAX_CHAR 4096

int split_time(char time[],char hour[], char minute[], char second[]){
    int i=0;
    int j=0;
    while (time[i]!=*":"){
        hour[j]=time[i];
        i++;
        j++;
    }
    j=0;
    i++;
    while (time[i]!=*":"){
        minute[j]=time[i];
        i++;
        j++;
    }
    j=0;
    i++;
    while (time[i]!=*"\0"){
        second[j]=time[i];
        i++;
        j++;
    }
    return 0;
}

int check_line(char line[]){
    //check the line is acceptable, return 1 if its bad, -1 if good
    int k=0;
    int l=0;
    int line_length=0;
    int colons_counter=0;
    while (line[l]!=*"\0"){
        line_length++;
        l++;
    }
    if (line_length>=4095){
        return 1;
    }
    while (line[k]!=*"\0"){
        if (line[k]==*":"){
            colons_counter++;
        }
    k++;
    }
    if (colons_counter!=6){
        return 1;
    }
    return -1;
}

int split_csv(char source[],char destination[],char hour[],char minutes[],char seconds[],char string[]){
    if (check_line(string)==1){
        return -1;
    }
    int j=0;
    int i=0;
    while (string[i]!=*":"){
        source[j]=string[i];
        i++;
        j++;
    }
    i+=2;
    j=0;
    while (string[i]!=*":"){
        destination[j]=string[i];
        i++;
        j++;
    }
    i+=2;
    j=0;
    while (string[i]!=*":"){  
        hour[j]=string[i];
        i++;
        j++;
    }
    i++;
    j=0;
    while (string[i]!=*":"){
        minutes[j]=string[i];
        i++;
        j++;
    }
    i++;
    j=0;
    while (string[i]!=*"\0"){
        seconds[j]=string[i];
        i++;
        j++;
    }
    return 1;
}

int compare_lower_time(int time1[],int time2[]){ //return 1 if time1 < time2, return -1 if same or time2 > time1
    if (time2[0]-time1[0]<0){
        return 1;
    }
    else if (time2[0]-time1[0]>0){
        return -1;
    }
    else if (time2[0]-time1[0]==0){
        if (time2[1]-time1[1]<0){
            return 1;
        }
        else if (time2[1]-time1[1]>0){
            return -1;
        }
        else if (time2[1]-time1[1]==0){
            if (time2[2]-time1[2]<0){
                return 1;
            }
            else if (time2[2]-time1[2]>=0){
                return -1;
            }
        }
    }
    return -1;
}

int my_strlen(char *s){
    int counter =0;
    while (*s)
    {
        s++;
        counter++;
    }
    return counter;
    
}

int string_compare(char string1[],char string2[]){
    int i=0;
    int j=0;
    while (string1[i]!=*"\0" && string2[i]!=*"\0"){
        if (j==my_strlen(string1)-1){
            return 1;
        }
        if (string1[i]!=string2[i]){
            return 0;
        }
        else{
            i++;
            j++;
        }
    }
    return 0;
}

int check_route(char* source,char* destination,char* new_source,char* new_destination){
    if (string_compare(source,new_source) && string_compare(destination,new_destination)){
        return 1;
    }
    else {
        return 0;
    }
}

int make_time1_equal_time2(int time1[],int time2[]){
    time1[0]=time2[0];
    time1[1]=time2[1];
    time1[2]=time2[2];
    return 0;
}

int main(int argc,char**argv) {
    if (argc!=4){
        printf("Please provide <source> <destination> <time> as command line arguments\n");
        return 0;
    }
    char base_h[5];
    char base_m[5];
    char base_s[5];
    int base_time[3];

    split_time(argv[3],base_h,base_m,base_s);
    base_time[0]=atoi(base_h);
    base_time[1]=atoi(base_m);
    base_time[2]=atoi(base_s);

    char timetable[MAX_CHAR];
    int soonest_time[3]; //soonest time following arrival
    int first_time_of_day[3]; //this is the earliest train of the day
    int first_check=0;
    int second_check=0;
    int timetable_check=0;
    while (fgets(timetable,MAX_CHAR,stdin)!=NULL){
        timetable_check=1;
        char new_source[MAX_CHAR];
        char new_destination[MAX_CHAR];
        char temp_hour[5];
        char temp_minute[5];
        char temp_second[5];
        int new_time[3];

        if (split_csv(new_source,new_destination,temp_hour,temp_minute,temp_second,timetable)==1){
            new_time[0]=atoi(temp_hour);
            new_time[1]=atoi(temp_minute);
            new_time[2]=atoi(temp_second);

            if (check_route(argv[1],argv[2],new_source,new_destination)==1){
                if (compare_lower_time(base_time,new_time)==-1){
                    if (first_check==0){
                        first_check=1;
                        make_time1_equal_time2(soonest_time,new_time);
                    }
                    else if (compare_lower_time(new_time,soonest_time)==-1){
                        make_time1_equal_time2(soonest_time,new_time);
                    }
                }
                if (second_check==0){
                    second_check=1;
                    make_time1_equal_time2(first_time_of_day,new_time);
                    continue;
                }
                else if (compare_lower_time(new_time,first_time_of_day)==-1){
                    make_time1_equal_time2(first_time_of_day,new_time);
                }
            }
        }
    }
    if (timetable_check==0){
        fprintf(stderr,"%s\n","No timetable to process.");
        return 0;
    }
    if (second_check==0){
        printf("No suitable trains can be found\n");
    }
    else if (first_check==0){
        printf("The next train to %s from %s departs at %02d:%02d:%02d\n",argv[2],argv[1],first_time_of_day[0],first_time_of_day[1],first_time_of_day[2]);
    }
    else {
        printf("The next train to %s from %s departs at %02d:%02d:%02d\n",argv[2],argv[1],soonest_time[0],soonest_time[1],soonest_time[2]);
    }
}

