#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct _list{
	int value;
	struct _list * next;
}List;

int push(Stack * stack, int value){
	List * list = (List *) malloc(sizeof(List));
	if(list ==NULL){
		fprintf(stderr,"Not enougth memory\n");
		return 0;	
	}
	list->value=value;
	list->next=NULL;
	if(stack->head==NULL){
		stack->head=list;
	}else{
		list->next=stack->head;
		stack->head=list;
	}
	return 1;
}
int is_empty(Stack * stack){
	return (stack->head==NULL);
}
int pop(Stack * stack){
	int ret;
	List * tmp;
	if(is_empty(stack)){
		fprintf(stderr,"Fifo is empty\n");
		return -1;
	}
	ret=(stack->head->value); 
	tmp=stack->head;
	stack->head=stack->head->next;
	free(tmp);
	return ret;
}

Stack * new_stack(){
	Stack * stack = (Stack *) calloc ( sizeof(Stack),1);
	if(stack==NULL){
		fprintf(stderr,"Not enougth memory\n");
		return NULL;	
	}
	stack->head=NULL;
	return stack;
}
