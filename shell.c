//******************************************** Header Files Inclusions ********************************************************************

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<dirent.h> //for directory related syscalls
#include<sys/syscall.h>
#include"wishparser.h"
#include"stack.h"

//******************************************************************************************************************************************


#define MAXBUFFERLEN 1000	//sufficient length
char* CMD[10];
char stream[MAXBUFFERLEN];


//******************************************** Function Declarations ********************************************************************

void shell_loop();
void get_stream();
void list_files(char *directory);
int w_tokenizer(char *stream,char **argv);
int scan0(char **argv);

//******************************************************************************************************************************************


int main()
{
    printf("Welcome to wish shell !\n");
    shell_loop();
}


void shell_loop(){

   
    // Retrieving hostname from /etc/hostaname file
  int MAXCMDSIZE = 100;
  int length;
   
    FILE *file = fopen("/etc/hostname","r");
    char *host_name;
    char* argv[MAXCMDSIZE];
    //argv=(char **)malloc(100*sizeof(char*));

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
    length = strlen(stream);
    stream[length-1] = '\0';
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
 
    if(!strcmp(argv[0],"ls")){
        list_files(argv[1]);       
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
	
	int i=0;
	for(;argv[i]!=NULL;i++)puts(argv[i]);
    
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