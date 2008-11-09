#include <stdio.h>
#include <stdlib.h>
#include "adjacent_list.h"
#include "stack.h"
#include "hashmap.h"

enum {unvisit=0, vistiting, visited};

List_adj * new_list_adj( int size ){
	List_adj * la = ( List_adj* ) calloc (1, sizeof (List_adj));
	la->list = (Cell **) calloc (size, sizeof( Cell *));
	la->station_map = new_station_map(size);
	la->name = (char **) calloc (sizeof (char*),size);
	la->line = (char **) calloc (sizeof (char*),size);
	la->size = size;
	return la;
}

void print_list (Cell * list, List_adj * la){
	if (list == NULL)
		return;
	while(list != NULL){
		printf("->(%s %s),",la->name[list->target], la->line[list->target]);
		list = list->next;
	}
}

void print_list_adj (List_adj * la) {
	int i;
	if (la == NULL)
		return;
	for ( i = 0; i < la->size; i++) {
		printf("\n%d %s %s",i,la->name[i],la->line[i]);
		print_list(la->list[i], la);
	}
}


Cell * create_cell(int target, int linkvalue){
	Cell * c = (Cell *) calloc (sizeof (Cell),1);
	c->target =target;
	c->linkvalue = linkvalue;
	c->next = NULL;
	return c;
}
int add_cell(Cell ** list, Cell * c){
	if (*list==NULL){
		*list=c;
		return 1;
	}
	while ((*list)->next!=NULL){
		list = &((*list)->next);
	}
	(*list)->next = c;
	return 1;
}

int add_arc (List_adj * la, int from, int target , int linkvalue){
	Cell ** tmp;
	if (la == NULL)
		return 0;
	if ( from >= la->size || target >= la->size)
		return 0;
	tmp = &(la->list[from]);
	while (*tmp != NULL){ 
		tmp = &((*tmp)->next);
	}
	*tmp = create_cell(target, linkvalue);
	return 1;
}

int remove_arc (List_adj * la, int from, int target) {
	Cell ** tmp;
	if (la == NULL)
		return 0;
	if (from >= la->size || target >= la->size)
		return 0;
	tmp = &(la->list[from]);
	while((*tmp)!=NULL){
		if( (*tmp)->target == target)
			la->list[from]=(*tmp)->next;
		if((*tmp)->next != NULL)
			if(((*tmp)->next->target)== target)
				(*tmp)->next= (*tmp)->next->next;
		tmp = &((*tmp)->next);
	}
	return 1;
}
int add_edge (List_adj * la, int vertex1, int vertex2,int linkvalue){
	return add_arc(la,vertex1,vertex2,linkvalue) &&	add_arc(la,vertex2,vertex1,linkvalue);
}
int remove_edge(List_adj * la, int vertex1, int vertex2){
	return remove_arc(la,vertex1,vertex2) && remove_arc(la,vertex2,vertex1);
}

int _get_path(List_adj * la, int from, int to,int * stateArray,Stack * stack){
	Cell * current = la->list[from];
	stateArray[from]=visited;
	while (current!=NULL){
		if(current->target==to){
			push(stack,from);
			return 1;
		}
		if(stateArray[current->target]==unvisit)
			if(_get_path(la,current->target,to,stateArray,stack)){
				push(stack,from);
				return 1;
			}
		current = current->next;
	}
	return 0;
}

Stack * get_path(List_adj * la, int from, int to){
	int i;
	Stack * stack = new_stack();
	int * stateArray = (int*)calloc (sizeof(int),la->size);
	for(i=0;i<la->size;i++){
		stateArray[i]=unvisit;
	}
	push(stack,to);
	 _get_path(la,from,to,stateArray,stack);
	return stack;
}
