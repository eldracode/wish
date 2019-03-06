#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// #include<sys/syscall.h>
#include"wishparser.h"
#include"stack.h"
#define MAXBUFFERLEN 1000	//sufficient length
#define MAXCMDSIZE 100 	//can be changed

char* CMD[10];

    char *stream;

void shell_loop();
void get_stream();
int scan0(char **argv);

int main()
{
    printf("Welcome to wish shell !\n");
    shell_loop();
}

int w_tokenizer(char *stream,char **argv);


void shell_loop(){

   
    // Retrieving hostname from /etc/hostaname file

    FILE *file = fopen("/etc/hostname","r");
    char *host_name;
    char* argv[MAXCMDSIZE];
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
    
    while(1){
        /* code */
    printf("%s [ %s ]  =>  ",user_name,host_name);

    get_stream();
    
    w_tokenizer(stream,argv);
    if(scan0(argv)==-1)
    {
        printf("LEVEL0_SYNTAX_ERR");
    }

    if(!strcmp(argv[0],"exit"))
    {
        printf("Die another day!!!\n");
        exit(0);
    }




    }
    
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

void get_stream(){
	//this function would read the string buffer 
	//will check if buffer has not exceeded the MAXBUFFERLEN that is 200 characters
	//if not exceeded it will return the char pointer
	//else it would return NULL pointer
    stream=(char*)malloc(sizeof(char)*MAXBUFFERLEN);

    fgets(stream,MAXBUFFERLEN,stdin);
    
}


int w_tokenizer(char* stream,char** argv)
{
    int i=1;
    char* temp=NULL;
    argv[0]=strtok(stream," ");
    puts(argv[0]);
    while((temp=strtok(NULL," "))!=NULL)
    {
        if(strcmp(temp,"\n"))argv[i]=temp;
        puts(argv[i]);
        i++;
        
    }
 
    if(i!=1)return i-1;
    else return -1;

}