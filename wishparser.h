#include<stdio.h>
#include<string.h>
int w_tokenizer(char* stream,char** argv,char regex)
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
		while(*(curr) == regex){
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