#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adjacent_list.h"
#include "hashmap.h"
#define STATION_FILE "/home/jordane/workspace/Parisian_Subway/station_list"

List_adj * load_station(){
	char buffer_reader[100];
	char line_name[10];
	int nb_line = 0;
	int nb_station=0;
	List_adj * la;
	FILE * file = fopen(STATION_FILE,"r");
	if(file==NULL){
		fprintf(stderr,"Error: file %s cannot be open !",STATION_FILE);
		return NULL;
	}
	while(1){
		if(fscanf(file,"%s",buffer_reader)==EOF)
			break;
		if(buffer_reader[0]>='0' && buffer_reader[0]<='9'){
			nb_line++;
		}else{
			nb_station++;
		}
	}
	la = new_list_adj(nb_station);
	nb_station = 0;
	fseek(file,0,SEEK_SET);
	while(1){
		if(fscanf(file,"%s",buffer_reader)==EOF)
			break;
		if(buffer_reader[0]>='0' && buffer_reader[0]<='9'){
			strcpy(line_name,buffer_reader);
		}else{
			char * name = (char *) calloc(sizeof (char),50);
			char * line = (char *) calloc(sizeof (char),10);
			sprintf(name ,"%s",buffer_reader);
			sprintf(line ,"%s",line_name);
			add_station(la->station_map,new_station(name,line,nb_station));
			la->name[nb_station] = name;
			la->line[nb_station++] = line;
		}
	}
	fclose(file);
	return la;
}
int create_link(List_adj * la){
	int i,j;
	for(i=0;i<la->size-1;i++){
		if( strcmp(la->line[i],la->line[i+1]) == 0 ){
			add_edge(la,i,i+1,direct_link);
		}
		for(j=0;j<la->size;j++){
			if(i!=j){
				if( strcmp(la->name[i],la->name[j]) == 0){
					add_arc(la,i,j,connecting_link);
				}
			}
		}
	}
	return 1;
}

List_adj * get_subway(){
	List_adj * la = load_station();
	create_link(la);
	return la;
}
