#include <stdio.h>
#include <stdlib.h>

void foo(char source[],char destination[],char hour[],char minutes[],char seconds[],char string[]){
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
}
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
    
    while (time[i]!=*"\0"){
        second[j]=time[i];
        i++;
        j++;
    }
    return 0;
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
        printf("%c,%c\n",string1[i],string2[i]);
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


int main(){
    //char string[4096] = {"Sydney::Melbourne::12:00:00"};
    char string1[4096] = {"12:00:00"};
    char string3[4096] = {"12:00:00"};
    //char source[200];
    //char destination[200];
    char hour[200];
    char minutes[200];
    char seconds[200];
    //foo(source,destination,hour,minutes,seconds,string);
    //int hour1=atoi(hour);
    //int minutes1=atoi(minutes);
    //int seconds1=atoi(seconds);
    split_time(string1,hour,minutes,seconds);
    //printf("%s,%s,%s",hour,minutes,seconds);
    printf("%d\n",string_compare(string1,string3));
    //printf("%s,%s,%d:%d:%d\n",source,destination,hour1,minutes1,seconds1);
}