#ifndef STACK_H
#define STACK_H

typedef struct _stack{
	struct _list * head;
}Stack;

int push(Stack * stack, int value);
int is_empty(Stack * stack);
int pop(Stack * stack);
Stack * new_stack();

#endif
