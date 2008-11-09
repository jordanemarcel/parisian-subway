#include <stdio.h>
#include <stdlib.h>
#include "station.h"

Station * new_station(char * name, char * line, int vertex_nb){
	Station * new_station = malloc(sizeof(Station));
	new_station->name=name;
	new_station->line=line;
	new_station->vertex_nb=vertex_nb;
	new_station->next=NULL;
	return new_station;
}
