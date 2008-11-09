#ifndef HASHMAP_H
#define HASHMAP_H
#include "station.h"
typedef struct _stationmap{
	Station ** station_list;
	int size;
}Station_map;

Station_map * new_station_map(int size);
Station * get_station(Station_map * map, const char * station_name);
void add_station(Station_map * map, Station * new_station);

#endif
