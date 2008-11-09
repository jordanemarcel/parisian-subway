#ifndef STATION_H
#define STATION_H

typedef struct _station{
	char * name;
	char * line;
	int vertex_nb;
	struct _station * next;
}Station;
	
Station * new_station(char * name, char * line, int vertex_nb);

#endif
