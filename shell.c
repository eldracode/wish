#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

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
    
    stream = get_stream();

}

char* get_stream(){

    
}