#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <assert.h>

#define STACK_SIZE 10
#define LINE_SIZE 100

//struct SStack -> TStack
typedef struct SStack{
    float values[STACK_SIZE];
    int size;
}TStack;

void pushStack(TStack* stack, float value){
    //assert(stack->size < STACK_SIZE);
    if(stack->size >= STACK_SIZE){
        printf("full stack\n");
        exit(0);
    }
    stack->values[stack->size] = value;
    stack->size++;
}

float popStack(TStack* stack){
    //uvedomi nas ak bude stack->size <= 0
    assert(stack->size > 0);
    stack->size--;
    return stack->values[stack->size];
}

void printStack(TStack* stack){
    int i = 0;
    //printf(">");
    for(i = 0;i < stack->size;i++)
        printf("%.2f ", stack->values[i]);
    printf("\n");
}

int readLine(char* line){
    char* r = NULL;
    int length = 0;
    r = fgets(line, LINE_SIZE, stdin);
    if(r != NULL && line[1] != 0){
        length = strlen(line);
        //funkcia fgets pridava znak '\n' na konec retazca
        line[length - 1] = 0;
        return 1;
    }
    return 0;
}

int getCommand(char* line, TStack* stack){
    char operations[5] = "+-*/";
    int i, res;
    float num, result, x, y;
    i = res = 0;
    num = result = x = y = 0.0f;
    //cislo
    res = sscanf(line, "%f", &num);
    if( (res == 1) && (line[0] != '.') ){
        pushStack(stack, num);
        printStack(stack);
        return 1;
    }
    //operacii
    for(i = 0;i < 4;i++){
        //ak to je nejaka operacia a mame aspon 2 prvky
        if(line[0] == operations[i] && stack->size >= 2){
            x = popStack(stack);
            y = popStack(stack);
            if(i == 0)
                result = y + x;
            if(i == 1)
                result = y - x;
            if(i == 2)
                result = y * x;
            if(i == 3){
                //v menovatele nemozeme mat 0
                if(x == 0){
                    printf("division by zero\n");
                    return 0;
                }
                result = y / x;
            }
            pushStack(stack, result);
            printStack(stack);
            return 1;
        }else if(line[0] == operations[i] && stack->size < 2){
            //musime mat aspon dva prvky aby urobit nejaku operaciu
            printf("not enough operands\n");
            return 0;
        }
    }
    //ak nie je to cislo, ani operacia, tak je to "bad input"
    printf("bad input\n");
    return 0;
}

int main()
{
    TStack myStack;
    char line[LINE_SIZE];
    memset(&myStack, 0, sizeof(TStack));
    myStack.size = 0;
    do{
        memset(line, 0, LINE_SIZE);
        if(readLine(line) != 1){
            //fprintf(stderr, "INPUT LINE ERROR!\n");
            printf("no input\n");
            return 0;
        }
    }while(getCommand(line, &myStack) != 0);

    return 0;
}

