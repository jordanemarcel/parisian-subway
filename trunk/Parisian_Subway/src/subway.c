#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adjacent_list.h"
#include "station_loader.h"
#include "stack.h"
#include "dijkstra.h"

#include "station.h"
#include "hashmap.h"

/**
 * Find station number from its name
 * @param subway: the adjacency list witch contains all station
 * @param name: the name of the station that you are looking for.
 * @param station_num: if the station can be found its number will be store here
 * @return 1 if the sation can be found 0 otherwise
 */
int find_station(List_adj * subway, char * name, int * station_num){
	Station * station = get_station(subway->station_map,source);
	if(station==NULL)
		return 0;
	*station_num = station->vertex_nb;
	return 1;
}
/**
 * Find a path in the graph subway for go to target from source
 * @param source: the start station
 * @param target: the destination station
 * @param subway: the adjacency list witch contains all station
 */
void find_path(char * source, char * target, List_adj * subway){
	int from, to;
	Stack * result;
	if(!find_station(subway,source,&from) && !find_station(subway,target,&to)){
		printf("Station can not be found, check them spell");
		return;
	}		
	printf("Looking for a path from %s to %s\n",subway->name[from],subway->name[to]);
	result = get_path(subway,from,to);
	if(result==NULL){
		printf("Path not found.\n");
		return;
	}
	printf("Path found :\n");
	
	while(!is_empty(result)){
		int tmp = pop(result);
		printf("%s-%s ",subway->name[tmp],subway->line[tmp]);
 	}
 	printf("\n");
}
/**
 * Find the shortest path in the graph subway for go to target from source.
 * you can choose how to calculate the shortest way by giving the desired mode:
 * 0 -> fewest stations
 * 1 -> fewest connections
 * 2 -> least time
 * @param source: the start station
 * @param target: the destination station
 * @param subway: the adjacency list witch contains all station
 */

void find_shortest_path(char * source, char * target, List_adj * subway,int mode){
	int from, to;
	Stack * result;
	char modename[3][20]={{"station"},{"correspondance"},{"time"}};
	if(!find_station(subway,source,&from) && !find_station(subway,target,&to)){
		printf("Station can not be found, check them spell");
		return;
	}
	printf("Looking for the shortest path in %s from %s to %s\n",modename[mode],subway->name[from],subway->name[to]);
	result = dijkstra(subway,from,to,mode);
	if(result==NULL){
		printf("Path not found.\n");
		return;
	}
	printf("Path found :\n");
	
	while(!is_empty(result)){
		int tmp = pop(result);
		printf("%s-%s ",subway->name[tmp],subway->line[tmp]);
 	}
 	printf("\n");
}

int main (int argc, char* argv[]){
	List_adj * la = get_subway();
	char from[50];
	char to[50];
	char impl;
	/* cas qui bug */
	/*
	Stack * result= dijkstra(la,80,103,0);
	while(!is_empty(result)){
		int tmp = pop(result);
		printf("%s-%s ",la->name[tmp],la->line[tmp]);
 	}
 	*/
	while (1){
		printf("choose the implementation:(type corresponding number)\n1)-matrix\n2)-list\n3)-quit\n");
		fscanf(stdin,"%c",&impl);
		if(impl=='3')
			break;
		if(impl=='2')
			while(1){
				fflush(stdin);
				printf("Enter the source station:\n");
				fscanf(stdin,"%s",from);
				printf("Enter the destination station:\n");
				fflush(stdin);
				fscanf(stdin,"%s",to);
				find_path(from,to,la);
				find_shortest_path(from,to,la,0);
				find_shortest_path(from,to,la,1);
				find_shortest_path(from,to,la,2);
			}
	}
	return 0;
}
