#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <assert.h>

#define SIZE 200

struct tree {
    //otazka alebo odpoved
    char value[SIZE];
    //odpoved ano
    struct tree* left;
    //odpoved nie
    struct tree* right;
};

void destroyNode(struct tree* root);

struct tree* read_tree(int* a_cnt){
    char buffer[SIZE];
    memset(buffer,0,SIZE);
    char* r = fgets(buffer,SIZE,stdin);
    //assert(r);
    if(r != NULL && buffer[1] != 0) {
        int length = strlen(buffer);
        buffer[length - 1] = 0;
    }else {
    	return NULL;
    }
    struct tree* node = calloc(1,sizeof(struct tree));
    memcpy(node->value,buffer,SIZE);
    // Ak je nacitany riadok listovy uzol ,tak netreba robit nic
    if(node->value[0] == '*') {
        *a_cnt += 1;
        return node;
    }else {
    // inak rekurzivne nacitanie laveho syna
        node->left = read_tree(a_cnt);
    // a rekurzivne nacitanie praveho syna
        node->right = read_tree(a_cnt);
    }
    return node;
}

//check
void display(struct tree* root) {
    if(root == NULL)
        return;
    display(root->left);
    printf("%s\n", root->value);
    display(root->right);
}


//display questions and answers
void displayQaA(struct tree* root) {
    struct tree* tree = root;
    char answer[30];
    memset(answer, 0, sizeof(char) * 30);
    char* r = NULL;
    printf("%s\n", root->value);
    while(root->value[0] != '*'){
        r = fgets(answer, 30, stdin);
        if(r != NULL && answer[1] != 0) {
            int length = strlen(answer);
            answer[length - 1] = 0;
        }else {
            printf("Koniec vstupu\n");
	    destroyNode(tree);
            exit(0);
        }
        //ak odpoved ano
        if(strcmp(answer, "a") == 0) {
            root = root->left;
        //ak odpoved nie
        }else if(strcmp(answer, "n") == 0) {
            root = root->right;
        //ak odpoved nieco ine
        }else {
            printf("Nerozumiem\n");
	    destroyNode(tree);
            exit(0);
        }
        printf("%s\n", root->value);
    }
}

void destroyNode(struct tree* root) {
    if(root == NULL)
        return;
    destroyNode(root->left);
    destroyNode(root->right);
    free(root);
}

int main()
{
    struct tree* tree = NULL;
    char str[SIZE];
    memset(str, 0, SIZE);
    //pocet listovych uzlov
    int a_cnt = 0;
    //create tree
    tree = read_tree(&a_cnt);
    //getchar();
    fgets(str, SIZE, stdin);
    printf("Expert z bufetu to vie.\n");
    if(tree == NULL || str[1] != 0) {
        printf("Chybna databaza\n");
        return 0;
    }
    printf("Pozna %d druhov ovocia a zeleniny.\n", a_cnt);
    printf("Odpovedajte 'a' pre prvu moznost alebo 'n' pre druhu moznost.\n");
    displayQaA(tree);
    printf("Koniec\n");
    destroyNode(tree);

    return 0;
}    
