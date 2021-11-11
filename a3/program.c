#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <assert.h>

#define SIZE 100
#define HEAP_SIZE 100

//MIN HEAP
struct heap {
    //pole cisel
    int* array;
    //aktualna velkost
    int size;
    //
    int capacity;
};

struct heap* createHeap() {
    struct heap* heap = (struct heap*)calloc(1, sizeof(struct heap));
    assert(heap);
    heap->size = HEAP_SIZE;
    heap->capacity = HEAP_SIZE; 
    heap->array = (int*)calloc(HEAP_SIZE, sizeof(int));
    assert(heap->array);
    return heap;
}

char* readLine() {
    char* line = NULL;
    line = (char*)calloc(SIZE, sizeof(char));
    assert(line);
    char* r = NULL;
    r = fgets(line, SIZE, stdin);
    if(r != NULL && line[1] != 0) {
        int length = strlen(line);
        line[length - 1] = 0;
        return line;
    }
    free(line);
    return NULL;
}

int parent(int i) {
    return (i - 1) / 2;
}

//Vypocet laveho syna
int left_child(int i) {
    return (i * 2) + 1;
}

//Vypocet praveho syna
int right_child(int i) {
    return (i * 2) + 2;
}

void convertToNum(char* line, int* array, int* size) {
    int i, arr_index;
    char* end = NULL;
    i = arr_index = 0;
    for(i = 0;line[i] != 0;i++) {
        if(line[i] == ' ') {
            continue;
        }
        if(i == 0) {
            array[arr_index] = (int)strtol(line, &end, 10);
            arr_index++;
            continue;
        }
        if(line[i - 1] == ' ') {
            array[arr_index] = (int)strtol(line + i, &end, 10);
            arr_index++;
            continue;
        }
    }
    *size = arr_index;
}

//pre-order
//1. vizit node
//2. vizit node->left
//3. vizit node->right
void display(struct heap* heap, int index, int level) {
    if(index > heap->size - 1) {
        return;
    }
    if(index == 0)
        printf("%d\n", heap->array[index]);
    else {
        for(int i = 0;i < level;i++)
            printf(" ");
        printf("%d\n", heap->array[index]);
    }
    display(heap, left_child(index), level + 1);
    display(heap, right_child(index), level + 1);
}

void destroyHeap(struct heap** heap) {
    free((*heap)->array);
    free(*heap);
    *heap = NULL;
}

int checkHeapProperty(struct heap* heap) {
    if(heap == NULL) {
        return 0;
    }
    int i = 0;
    for(i = 0;i < heap->size;i++) {
        int l_child = left_child(i);
        int r_child = right_child(i);
        if( (l_child >= heap->size) || (r_child >= heap->size) ) {
            break;
        }
        if( (heap->array[i] >= heap->array[l_child]) || (heap->array[i] >= heap->array[r_child]) ) {
            return 0;
        }
    }   
    return 1;
}

int main()
{
    struct heap* heap = NULL;
    heap = createHeap();
    char* line = NULL;
    line = readLine();
    if(line == NULL) {
        fprintf(stderr, "bad input\n");
        return 0;
    }
    convertToNum(line, heap->array, &heap->size);
    if(checkHeapProperty(heap) != 1) {
        printf("Nie je kopa.\n");
        free(line);
        destroyHeap(&heap);
        return 0;
    }
    printf("Je to taka kopa:\n");
    display(heap, 0, 0);
    free(line);
    destroyHeap(&heap);
   
    return 0;
}
