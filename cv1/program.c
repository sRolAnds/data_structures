#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#define LINE_SIZE 100
#define POCET_JEDAL 100

typedef struct SPizza{
    float price;
    char name[LINE_SIZE];
}TPizza;

int read_line(char* line){
    char *r = NULL;
    int l = 0;
    r = fgets(line, LINE_SIZE, stdin);
    if(r != NULL && line[1] != 0){
	l = strlen(line);
	//funkcia fgets pridava znak '\n' na konec retazca
        line[l - 1] = 0;
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
//prototyp funkcie hacker_script
char hacker_script(char c);

int search_string(const char* heap, const char* needle){
    int M, N, i, j, cnt;
    M = strlen(heap), N = strlen(needle);
    i = j = cnt = 0;
    for(i = 0;i < M - N + 1;i++){
        for(j = 0;j < N;j++){
            if( hacker_script(heap[i + cnt]) == hacker_script(needle[j]) )
                cnt++;
            else{
                cnt = 0;
                break;
            }
        }
        if(cnt == N)
            return i;
    }
    return -1;
}

char hacker_script(char c){
    char numbers[] = "0123456789";
    char letters[] = "oizeasbtbq";
    int i = 0;
    for(i = 0;i < 10;i++){
        if(c == numbers[i])
       	    return letters[i];
        if(isupper(c)){
	    //A -> a
	    c = tolower(c);
            return c;
        }
    }
    return c;
}

int read_pizza_list(TPizza* list){
    TPizza item;
    int res, i, cnt;
    res = i = cnt = 0;
    for(i = 0;i < POCET_JEDAL;i++){
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

int main()
{
    char line[LINE_SIZE];
    memset(line, 0, LINE_SIZE);
    TPizza jedalny_listok[POCET_JEDAL];
    memset(jedalny_listok, 0, sizeof(TPizza) * POCET_JEDAL);
    int i, cnt;
    i = cnt = 0;
    printf("Zadaj hladanu surovinu:\n");
    if(read_line(line) != 1){
        fprintf(stderr, "INPUT LINE ERROR!\n");
        return -1;
    }
    printf("Zadaj jedalny listok:\n");
    cnt = read_pizza_list(jedalny_listok);
    for(i = 0;i < cnt;i++){
        if(search_string(jedalny_listok[i].name, line) != -1)
            printf("%s\n%.2f\n", jedalny_listok[i].name, jedalny_listok[i].price);
    }
    printf("Nacitanych %d poloziek.\n", cnt);
    return 0;
}

