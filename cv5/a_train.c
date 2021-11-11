#include "a_train.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <assert.h>

struct car* getLast(struct car* first);
struct car* getPrev(struct car* first, const char* target);

struct car* add_car(struct car* first,const char* target) {
    struct car* newcar = (struct car*)calloc(1, sizeof(struct car));
    assert(newcar);
    char* r = NULL;
    r = strcpy(newcar->value, target);
    assert(r);
    newcar->next = NULL;
    if(first == NULL){
        return newcar;
    }
    struct car* last = getLast(first);
    last->next = newcar;
    return first;
}

void print_train(struct car* first) {
    if(first == NULL)
        printf("The list is empty\n");
    while(first != NULL){
        printf("%s\n", first->value);
        first = first->next;
    }
}

void cancel_train(struct car* first) {
    while(first != NULL){
        struct car* next = first->next;
        free(first);
        first = next;
    }
}


struct car* clear_train(struct car* first, const char* target) {
//prazdny zoznam
    if(first == NULL)
        return NULL;
//jeden prvok
    if(first->next == NULL){
        if(strcmp(first->value, target) == 0){
            free(first);
            return NULL;
        }else{
            return first;
        }
    }
//ak prvy clen vyhovuje
    if(strcmp(first->value, target) == 0){
        struct car* tmp = first;
        first = first->next;
        free(tmp);
        return first;
    }
//ak > 1
    struct car* prev = getPrev(first, target);
    struct car* this_train = NULL;
    if(prev == NULL){
        return first;
    }else{
        this_train = prev->next;
        prev->next = this_train->next;
        free(this_train);
    }
    return first;
}

struct car* getLast(struct car* first){
    while(first->next != NULL){
        first = first->next;
    }
    return first;
}

struct car* getPrev(struct car* first, const char* target){
    while(first->next != NULL){
        if(strcmp(first->next->value, target) == 0){
            return first;
        }
        first = first->next;
    }
    return NULL;
}

