#include <stdio.h>
#include <stdlib.h>
#include "adjacent_list.h"

enum state { white = 1, black =2};
enum dijkstra_mode{fewest_stations=0,fewest_connections,least_time};
typedef struct dijkstra_s{
	int * visited;
	int * distance;
	int * parent;
	int size;
	int parent_pos;
}dijkstra_t; 

dijkstra_t * new_dijkstra_s(int size){
	dijkstra_t * dij = (dijkstra_t *) calloc (1,sizeof(dijkstra_t));
	dij->visited = (int *) calloc (size, sizeof(int));
	dij->parent = (int *) calloc ( sizeof( int ), size);
	dij->distance = (int *) calloc ( sizeof( int ), size);
	dij->size = size;
	dij->parent_pos = 0;
	
	return dij;
}

int min_distance(dijkstra_t * dij){
	int i,min=10000000,min_pos=-1;
	for (i=0;i<dij->size;i++){
		if ( dij->visited[i]==white && dij->distance[i] <= min){
			min=dij->distance[i];
			min_pos = i;
		}
	}
	/*printf("(%d %d)",min_pos,min);*/
	return min_pos;
}

Stack * dijkstra(List_adj * la,int source,int target,enum dijkstra_mode mode){
	Stack * stack = new_stack();
	int i,current;
	Cell * tmp_list;
	int link_value[3][3]= {{1,1},{1,100},{1,3}};
	int tmp;
	dijkstra_t * dij = new_dijkstra_s(la->size);
	if(mode>3 || mode<0)mode=0;
	if(source>la->size || source<0)return NULL;
	if(target>la->size || target<0)return NULL;
	if(la==NULL)return NULL;
	for (i=0;i<dij->size;i++){
		dij->visited[i] = white;
		dij->parent[i] = -2;
		dij->distance[i] = 1000000;
	}
	dij->distance[source] = 0;
	dij->parent[source] = -1;
	/*printf("dij->size %d\n",dij->size);*/
	for (i=0;i<dij->size;i++){
		if(dij->visited[i]==white){
			/*printf("non visiter= %d\n",i);*/
			current = min_distance(dij);
			dij->visited[current] = black;
			tmp_list = la->list[current];
			while (tmp_list != NULL){
				/*printf("a visiter current=%d,target=%d\n",current,tmp_list->target);*/
				if ( dij->visited[tmp_list->target] == white){
					if (dij->distance[tmp_list->target] > dij->distance[current] + link_value[mode][tmp_list->linkvalue]){
						
						dij->distance[tmp_list->target]	= dij->distance[current] + link_value[mode][tmp_list->linkvalue];
						dij->parent[tmp_list->target] = current;
					}
				}
				tmp_list = tmp_list->next;
			}
		}
	}
	
	tmp=target;
	while(dij->parent[tmp] != -1){
		push(stack,tmp);
		tmp=dij->parent[tmp];
	}
	push(stack,source);
	return stack;
}
