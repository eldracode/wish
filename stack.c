typedef struct STACK{ int top; int SIZE; char** data;}STACK;

void push(STACK* s,char* b){
if (s->top==(s->SIZE)-1){
printf("Pudding Brain");
}
s->data[top++]=b;
}

char* pop(STACK* s){
if(s->top==-1){
	printf("Brave Heart User")
}
top--;
return s->data[top+1];
}