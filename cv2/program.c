#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#define LINE_SIZE 100
#define LIST_SIZE 100

typedef struct SPizza{
    float price;
    char name[LINE_SIZE];
}TPizza;

int read_line(char* line){
    char* r = NULL;
    int length;
    length = 0;
    r = fgets(line, LINE_SIZE, stdin);
    if(r != NULL && line[1] != 0){
        length = strlen(line);
        //funkcia fgets pridava znak '\n' na konec retazca
        line[length - 1] = 0;
	return 1;
    }else
        return 0;
}

int read_pizza(TPizza* item){
    //string for name
    char line[LINE_SIZE];
    //string for price
    char line2[LINE_SIZE];
    float f;
    int res;
    memset(line, 0, LINE_SIZE);
    memset(line2, 0, LINE_SIZE);
    f = 0.0f;
    res = 0;
    //ak sa nepodarilo nacitat retazce
    if(read_line(line) != 1)
        return 0;
    if(read_line(line2) != 1)
        return 0;
    else
        res = sscanf(line2, "%f", &f);
    if( (res != 1) && (f == 0.0f) )
        return 0;
    item->price = f;
    strcpy(item->name, line);
    return 1;
}

int read_pizza_list(TPizza* list){
    TPizza item;
    int res, i, cnt;
    res = i = cnt = 0;
    for(i = 0;i < LIST_SIZE;i++){
        memset(&item, 0, sizeof(TPizza));
        res = read_pizza(&item);
	//ak sa podarilo nacitat jednu polozku
        if(res == 1){
            memcpy(list + i, &item, sizeof(TPizza));
            ++cnt;
        }else
            break;
    }
    return cnt;
}
//prototypy funkcii
int compare_strings(char* line, char* line2);
void swapElements(TPizza* a, TPizza* b);

void sort_jedalny_listok(TPizza* array, int size){
    int i, j;
    i = j = 0;
    //BUBBLE SORT
    for(i = 0;i < size - 1;i++){
        for(j = i + 1;j < size;j++){
            if(array[i].price > array[j].price)
                swapElements(array + i, array + j);
            else if(array[i].price == array[j].price){
                if(compare_strings(array[i].name, array[j].name) == 1)
                    continue;
                else
                    swapElements(array + i, array + j);
            }
        }
    }
}

int compare_strings(char* line, char* line2){
    int M, N, i, n;
    M = strlen(line);
    N = strlen(line2);
    i = n = 0;
    //ak M > N tak n = N, inak n = M
    n = M > N ? N : M;
    for(i = 0;i < n;i++){
	// a < b
        if(tolower(line[i]) < tolower(line2[i]))
            return 1;
	// a == a
        else if(tolower(line[i]) == tolower(line2[i]))
            continue;
	// b > a
        else if(tolower(line[i]) > tolower(line2[i]))
            return 2;
    }
    return 1;
}

void swapElements(TPizza* a, TPizza* b){
    TPizza temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    TPizza jedalny_listok[LIST_SIZE];
    memset(jedalny_listok, 0, sizeof(TPizza) * LIST_SIZE);
    int cnt, i;
    cnt = i = 0;
    cnt = read_pizza_list(jedalny_listok);
    sort_jedalny_listok(jedalny_listok, cnt);
    for(i = 0;i < cnt;i++)
        printf("%s\n%f\n", jedalny_listok[i].name, jedalny_listok[i].price);

    return 0;
}

