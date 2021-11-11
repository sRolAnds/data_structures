#include "a_station.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <assert.h>

struct station* create_station(){
    struct station* new_station = (struct station*)calloc(1, sizeof(struct station));
    assert(new_station);
    new_station->track_count = STATION_SIZE;
    new_station->tracks = (struct car**)calloc(new_station->track_count, sizeof(struct car*));
    assert(new_station->tracks);
    return new_station;  
}

void destroy_station(struct station* station){
    if(station == NULL){
        fprintf(stderr, "ERROR THE STATION IS EMPTY\n");
        exit(-1);
    }
    int i = 0;
    for(i = 0;i < station->track_count;i++){
        struct car* list = station->tracks[i];
        while(list != NULL){
            struct car* tmp = list;
            list = list->next;
            free(tmp);
        }
    }
    free(station->tracks);
    free(station);    
}

unsigned int hash_string(const char* word);

int select_track(struct station* station, const char* target){
    if(station == NULL){
        fprintf(stderr, "ERROR THE STATION IS EMPTY\n");
        exit(-1);
    }
    unsigned int hash = hash_string(target);
    int station_slot = hash % station->track_count;
    return station_slot;    
}

void add_target_capacity(struct station* station,const char* target, int capacity){
    if(station == NULL){
        fprintf(stderr, "ERROR THE STATION IS EMPTY\n");
        exit(-1);
    }
    int station_slot = select_track(station, target);
    struct car* list = station->tracks[station_slot];
    struct car* new_list = (struct car*)calloc(1, sizeof(struct car));
    assert(new_list);
    strcpy(new_list->value, target);
    new_list->capacity = capacity;
    if(list == NULL){
        new_list->next = NULL;
    }else{
        while(list != NULL){
            if(strcmp(list->value, target) == 0){
                list->capacity += capacity;
                free(new_list);
                return;
            }
            list = list->next;
        }
        new_list->next = station->tracks[station_slot];
    }
    station->tracks[station_slot] = new_list;    
}

int get_target_capacity(struct station* station,const char* target){
    if(station == NULL){
        return 0;
    }
    int station_slot = select_track(station, target);
    struct car* list = station->tracks[station_slot];
    while(list != NULL){
        if(strcmp(list->value, target) == 0){
            return list->capacity;
        }
        list = list->next;
    }
    return 0;    
}

int count_targets(struct station* station){
    if(station == NULL){
        return 0;
    }
    int cnt_targets = 0;
    int i = 0;
    for(i = 0;i < station->track_count;i++){
        struct car* list = station->tracks[i];
        while(list != NULL){
            cnt_targets++;
            list = list->next;
        }
    }
    return cnt_targets;    
}

int count_capacity(struct station* station){
    if(station == NULL){
        return 0;
    }
    int cnt_capacity = 0;
    int i = 0;
    for(i = 0;i < station->track_count;i++){
        struct car* list = station->tracks[i];
        while(list != NULL){
            cnt_capacity += list->capacity;
            list = list->next;
        }
    }
    return cnt_capacity;    
}

unsigned int hash_string(const char* word){
    int cnt = 0;
    unsigned int hash = 0;
    for(cnt = 0;word[cnt] != 0;cnt++){
        hash = word[cnt] + (hash << 6) + (hash << 16) - hash;
    }
    return hash;    
}

