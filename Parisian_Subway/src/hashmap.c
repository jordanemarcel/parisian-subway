#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hashmap.h"

Station_map * new_station_map(int size) {
  Station_map * map=(Station_map*)calloc(size,sizeof(Station_map));
  memset(map, (int)NULL, size);
  map->station_list=(Station**)calloc(size,sizeof(Station*));
  map->size=size;
  return map;
}

unsigned int hash_string(const char *str,const int size){
   unsigned int hash = 5381;
   const char *s;
   for (s = str; *s; s++)
      hash = ((hash << 5) + hash) + tolower(*s);
   return (hash & 0x7FFFFFFF)%size;
}

/**
 * Search a name in a Station_map and return the Station if found NULL otherwise.
 * @param map: the Station_map that you want search in.
 * @param station_name: the name that you look for in the map
 * @return the station corresponding to the name give in param or NULL if not found
 */
Station * get_station(Station_map * map, const char * station_name) {
  Station * position;
  for ( position = map->station_list[hash_string(station_name,map->size)];
   (position!=NULL) && (strncmp(station_name,position->name,24));
   position = position->next );
  return position;
}
/**
 * Add a Station to a hash map
 * @param map: the station will be add into this map
 * @param 
 */
void add_station(Station_map * map, Station * new_station) {
  Station ** position;
  if(new_station==NULL)
  	return;
  /*compute hashcode and get the station in the map*/
  position = &(map->station_list[hash_string(new_station->name,map->size)]);
  /*scan the list of station with the same hashcode*/
  while(*position!=NULL)
 	 position = &((*position)->next);
  *position = new_station;
}


