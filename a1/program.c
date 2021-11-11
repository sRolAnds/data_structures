#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define LINE_SIZE 100

int readLine(char* line){
    char* r = NULL;
    int length = 0;
    r = fgets(line, LINE_SIZE, stdin);
    if(r != NULL && line[1] != 0){
        length = strlen(line);
        line[length - 1] = 0;
        return 1;
    }else{
        return 0;
    }
}

int readNum(char* line, int* number);

int inputArray(int* array, int size){
    char line[LINE_SIZE];
    int i;
    i = 0;
    for(i = 0;i < size;i++){
        memset(line, 0, LINE_SIZE);
        printf("arr[%d] = ", i);
        if(readLine(line) != 1)
            return 0;
        else
            if(readNum(line, array + i) != 1)
                return 0;
    }
    return 1;
}

void showArray(int* array, int size){
    int i;
    for(i = 0;i < size;i++)
        printf("%d ", *(array + i));
}

void swapNums(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int findMaxNum(int* array, int size){
    int i;
    int maxNum = array[0];
    for(i = 1;i < size;i++)
        if(maxNum < array[i])
            maxNum = array[i];
    return maxNum;
}

void sortHeap(int* array, int arrSize){
    int i, j, maxNum, size, step;
    size = arrSize;
    i = j = maxNum = step = 0;
    while(size != 1){
        maxNum = findMaxNum(array, size);
        while(array[0] != maxNum){
            step = 1;
            for(i = 0;i < size/2;i++){
                for(j = i + step;j < i + step + 2;j++){
                    if(j > size - 1)
                        break;
                    if(array[i] < array[j])
                        swapNums(array + i, array + j);
                }
                step += 1;
            }
        }
        swapNums(array, array + size - 1);
        --size;
    }
}

int readNum(char* line, int* number){
    int num, result;
    num = result = 0;
    result = sscanf(line, "%d", &num);
    if( (result != 1) && (num == 0) )
        return 0;
    *number = num;
    return 1;
}

int main(){
    char line[LINE_SIZE];
    memset(line, 0, LINE_SIZE);
    int arraySize, resLine, res;
    arraySize = resLine = res = 0;
    printf("Enter the size of array:");
    resLine = readLine(line);
    if(resLine != 1){
        //fprintf(stderr, "INPUT LINE ERROR!\n");
        return 0;
    }
    if(readNum(line, &arraySize) != 1)
        return -1;
    int* array = (int*) malloc(sizeof(int) * arraySize);
    if(array == NULL){
	fprintf(stderr, "PROBLEM IN MEMORY ALLOCATION\n");
	return -1;
    }	
    memset(array, 0, sizeof(int) * arraySize);
    if(inputArray(array, arraySize) != 1){
        printf("Nacitanie pola sa nepodarilo\n");
	free(array);
        return -1;
    }
    sortHeap(array, arraySize);
    showArray(array, arraySize);
    printf("\n");
    free(array);

    return 0;
}

