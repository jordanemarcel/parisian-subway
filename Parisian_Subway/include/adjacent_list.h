#ifndef ADJACENT_LIST_H
#define ADJACENT_LIST_H

#include "stack.h"
#include "hashmap.h"

enum linktype {direct_link=0,connecting_link=1};

typedef struct cell{
	int target;
	int linkvalue;
	struct cell * next;
}Cell;

typedef struct list_adj{
	Cell ** list;
	Station_map * station_map;
	char ** name;
	char ** line;
	int size;
}List_adj;

List_adj * new_list_adj( int size );
void print_list (Cell * list, List_adj * la);
void print_list_adj (List_adj * la);
Cell * create_cell(int target, int value);
int add_cell(Cell ** list, Cell * c);
int add_arc (List_adj * la, int from, int target , int value);
int remove_arc (List_adj * la, int from, int target);
int add_edge (List_adj * la, int vertex1, int vertex2, int value);
int remove_edge(List_adj * la, int vertex1, int vertex2);

Stack * get_path(List_adj * la, int from, int to);
#endif
