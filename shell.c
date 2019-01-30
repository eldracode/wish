#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/syscall.h>
#include"wishparser.h"
#define MAXBUFFERLEN 200	//sufficient length
#define MAXCMDSTACKSIZE 10 	//can be changed

void shell_loop();
char* get_stream();
int main()
{
    printf("Welcome to wish shell !\n");
    shell_loop();
}

void shell_loop(){

    char *stream;
   
    // Retrieving hostname from /etc/hostaname file

    FILE *file = fopen("/etc/hostname","r");
    char *host_name;
    host_name=(char *)malloc(15*sizeof(char));
    if(!file)
    exit(0);
    fscanf(file,"%s",host_name);
    fclose(file);

    // Retrieving username using getlogin() fron <unistd.h>

    char *user_name;
    user_name=(char *)malloc(10*sizeof(char));
    user_name=getlogin();

    // Printing promp which contains usename and hostname 
    printf("%s(%s) =>  ",user_name,host_name);
    
    //stream = get_stream();
    //shell loops start here
    //Loop:(rough outline)
    //read string buffer to be parsed
    //parse the string buffer
    //parser code is in wishparser.c file
    //compilation would be like
    // gcc -o wishex wish.c wishparser.c
    //initialize the command stack
    //each command would be pushed after successful parsing 
    //after each successful execution of a command 
   	//command would be poped from command stack 
    //and next command would be set in execution

}

char* get_stream(){
	//this function would read the string buffer 
	//will check if buffer has not exceeded the MAXBUFFERLEN that is 200 characters
	//if not exceeded it will return the char pointer
	//else it would return NULL pointer
    
}


