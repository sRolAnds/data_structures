#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define LINE_SIZE 100
#define STACK_SIZE 10
#define MULTIPLIER 2

typedef struct tag_stack{
    char* array;
    int size;
    int top;
}t_stack;

t_stack* createStack(){
    t_stack* New = (t_stack*)calloc(1, sizeof(t_stack));
    if(New == NULL){
        fprintf(stderr, "FAIL IN MEMORY ALLOCATION\n");
        exit(-1);
    }
    New->size = STACK_SIZE;
    New->array = (char*)calloc(New->size, sizeof(char));
    if(New->array == NULL){
        fprintf(stderr, "FAIL IN MEMORY ALLOCATION\n");
        exit(-1);
    }
    New->top = 0;
    return New;
}

void resizeStack(t_stack* stack);

void pushStack(t_stack* stack, char c){
    if(stack->top >= stack->size){
        resizeStack(stack);
    }
    stack->array[stack->top] = c;
    stack->top++;
}

void freeStack(t_stack** stack);

void popStack(t_stack* stack){
    if(stack->top == 0){
        fprintf(stderr, "UNDERFLOW\n");
        freeStack(&stack);
        exit(-1);
    }
    stack->top--;
    //return stack->array[stack->top];
}

void resizeStack(t_stack* stack){
    stack->size *= MULTIPLIER;
    stack->array = (char*)realloc(stack->array, stack->size * sizeof(char));
    if(stack->array == NULL){
        fprintf(stderr, "FAIL IN MEMORY REALLOCATION\n");
        freeStack(&stack);
        exit(-1);
    }
}

void printStack(t_stack stack){
    int i = 0;
    printf(">");
    for(i = 0;i < stack.top;i++)
        printf(" %c", stack.array[i]);
    printf("\n");
}

void freeStack(t_stack** stack){
    free((*stack)->array);
    free(*stack);
    *stack = NULL;
}

int readLine(char* line){
    char* r = NULL;
    int length = 0;
    r = fgets(line, LINE_SIZE, stdin);
    if(r != NULL && line[1] != 0){
        length = strlen(line);
        line[length - 1] = 0;
        return 1;
    }
    return 0;
}

int findBracketState(t_stack* stack, char c, int index){
    char open_brackets[5] = "{[(<";
    char close_brackets[5] = "}])>";
    int i, j;
    i = j = 0;
    for(i = 0;i < 4;i++){
        if(c == open_brackets[i]){
            pushStack(stack, c);
            break;
        }
        if(c == close_brackets[i] && stack->array[stack->top - 1] == open_brackets[i]){
            popStack(stack);
            break;
        }
        if(c == close_brackets[i] && stack->array[stack->top - 1] != open_brackets[i]
           && stack->top > 1 && stack->array[stack->top - 1] != close_brackets[i]){
            for(j = 0;j < 4;j++)
                if(stack->array[stack->top - 1] == open_brackets[j])
                    break;
            printf("Crossed bracket %c in %d, expected %c \n", close_brackets[i], index, close_brackets[j]);
            return 1;
        }
        if(c ==  close_brackets[i]){
            pushStack(stack, c);
            break;
        }
    }
    return 0;
}

void check(t_stack* stack, char* line){
    char open_brackets[5] = "{[(<";
    char close_brackets[5] = "}])>";
    int i, j, k, temp;
    i = j = k = temp = 0;
    for(i = stack->top - 1;i >= 0;i--){
        for(j = 0;j < 4;j++){
            if(stack->array[i] == open_brackets[j]){
                if(temp == 0){
                    printf("Missing closing brackets: ");
                    temp++;
                }
                printf("%c", close_brackets[j]);
                continue;
            }
            if(stack->array[i] == close_brackets[j]){
                for(k = 0;k < strlen(line);k++)
                    if(line[k] == close_brackets[j])
                        break;
                printf("Unexpected closing bracket %c in %d", close_brackets[j], k);
               // return 0;
            }
        }
    }
    printf("\n");
   // return 1;
}


int main(){
    t_stack* myStack = NULL;
    myStack = createStack();
    char line[LINE_SIZE];
    memset(line, 0, LINE_SIZE);
    if(myStack == NULL){
        fprintf(stderr, "FAIL IN CREATING A DYNAMIC STACK\n");
        freeStack(&myStack);
        return -1;
    }
    if(readLine(line) != 1){
        fprintf(stderr, "INPUT LINE ERROR!\n");
        freeStack(&myStack);
        return -1;
    }
    printf("Read: %s\n", line);
    int i;
    i = 0;
    for(i = 0;i < strlen(line);i++)
        if(findBracketState(myStack, line[i], i) == 1){
            freeStack(&myStack);
            return 0;
        }
    if(myStack->top == 0){
        printf("All brackets OK\n");
        freeStack(&myStack);
        return 0;
    }
    check(myStack, line);
    //printStack(*myStack);
    freeStack(&myStack);

    return 0;
}

