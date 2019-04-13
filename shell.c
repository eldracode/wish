//******************************************** Header Files Inclusions ********************************************************************

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<dirent.h> //for directory related syscalls
#include<sys/syscall.h>
#include<sys/types.h>
#include<sys/wait.h>
//#include"wishparser.h"
//#include"stack.h"
//#include"queue.h"

//******************************************************************************************************************************************


#define MAXBUFFERLEN 1000//sufficient length
#define MAXCMDSIZE 100	//sufficient size of cmd queue array

char *host_name;
char *user_name;
extern char** environ;
//char* envp[]={"/bin:/usr/bin/"};
char** CMD[10];//command queue array basically array of argv[]
char stream[MAXBUFFERLEN];
pid_t shell_PID;
int EXIT_STAT;


//******************************************** Function Declarations ********************************************************************

void shell_loop();
void get_stream();
void list_files(char *directory);
int w_tokenizer(char *stream,char **argv);
int scan0(char **argv);

//******************************************************************************************************************************************

void getprompt()
{
    // Retrieving hostname from /etc/hostaname file
    FILE *file = fopen("/etc/hostname","r");
    host_name=(char *)malloc(15*sizeof(char));
    if(!file)
    exit(0);
    fscanf(file,"%s",host_name);
    fclose(file);

    // Retrieving username using getlogin() fron <unistd.h>
    user_name=(char *)malloc(10*sizeof(char));
    user_name=getlogin();
}



int main()
{
  //  printf("Welcome to wish shell !\n");
    //a function to retreive hostname and user 
    getprompt();
    shell_loop();
}


void shell_loop(){

   
    
    int length;
   
    
    
    char* argv[MAXCMDSIZE];
    //argv=(char **)malloc(100*sizeof(char*));

    
    // Printing promp which contains usename and hostname 
    
    while(1){
        /* code */
    printf("\033[0;31m"); 
    printf("\033[1m");
    printf("%s  ➜  ",host_name);
    printf("\033[0m");
    printf("\033[0m"); 
    //getting user input 
    get_stream();
    length = strlen(stream);
    stream[length-1] = '\0';
    
    
    //converting user input to tokens
    w_tokenizer(stream,argv);
    
    //checking syntax: a trivial check indeed
    if(scan0(argv)==-1)
    {
        printf("LEVEL0_SYNTAX_ERR");
    }

    //executing the COMMAND if it's syntactically correct
    
    
    else{
        
    //below are the INTERNAL SHELL COMMANDS******************************************************************************************
        if(!strcmp(argv[0],"exit")){
            printf("Yippikaya Mr Falcon\n");
            exit(0);
        }
 
        else if(!strcmp(argv[0],"ls")){
            list_files(argv[1]);       
        }
    
    
    //below are the EXTERNAL COMMANDS aka THE BINARIES*******************************************************************************
        else {
    	    shell_PID=fork();

            if(shell_PID==0){//CHILD PROCESS:THE BINARY OR THE COMMAND
                execvp(argv[0],argv);
                exit(0);
            }
            else if(shell_PID>0){//PARENT PROCESS:WISH SHELL
                do{
                    waitpid(shell_PID,&EXIT_STAT,WUNTRACED);
                    }while(!WIFEXITED(EXIT_STAT)&&WIFSIGNALED(EXIT_STAT));
            }
            else{
                printf("forking error!\n");
            }
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
}
void get_stream(){
	//this function would read the string buffer 
	//will check if buffer has not exceeded the MAXBUFFERLEN that is 200 characters
	//if not exceeded it will return the char pointer
	//else it would return NULL pointer
    //stream=(char*)malloc(sizeof(char)*MAXBUFFERLEN);

    fgets(stream,MAXBUFFERLEN,stdin);
    
}


int w_tokenizer(char* stream,char** argv)
{
    
	int length =strlen(stream);
	char* curr=stream;
	char* temp;
	char* tok;

	char* del=" ";

	int index=-1;
	int err=-1;

	do
	{
		while(*(curr) == ' '){
			curr++;
		}
		
		if(*(curr)!='\"'){
			if(index==-1)tok=strtok_r(stream,del,&curr);
			else tok=strtok_r(NULL,del,&curr);
			index++;
			argv[index]=tok;
		}
		//else curr++;

		else
		{
			//int i = 0;
			temp=curr+1;
			do{
				curr++;
				
			}while((*curr)!='\"'&&(*curr)!='\0');

			index++;
			if(*curr=='\"'){
				*curr='\0';
				//index++;
				argv[index]=temp;
				curr++;
			}
			else {
				err++;
				argv[index]=NULL;
			}
			
		}
	}while(argv[index]!=NULL);
	
	//int i=0;
	//for(;argv[i]!=NULL;i++)puts(argv[i]);
    
        return 0;
}

int isCMDseparator(char ch){
    
    if(ch != ';' && ch != '|' && ch != '>' && ch != '<'){
        return 0;
    }
    return 1;

}

int scan0(char **argv){

    /*
    
    argv[0] = . / _ / alphabet /  
    
    */
   int i = 0 ;
   if(argv[0][0] != '.' && argv[0][0] != '_' && !isalpha(argv[0][0]) ){
       return -1;
   }
   while(argv[i] != NULL && isCMDseparator(argv[i][0])){
       
   }
   
   
}


void list_files(char *directory){

    struct dirent *di;
    
    // if(directory != NULL){
    //     if(*directory == '~'){
    //         directory = strcat("/home/eldraco",(directory+1));
    //     }
    // }

    DIR *dr = directory==NULL  ? opendir(".") : opendir(directory);

    if(dr == NULL){
    printf("could not open the directory / directory not present");
    return;
    }


    while((di = readdir(dr)) != NULL){
        puts(di->d_name);
    }
    
    


}