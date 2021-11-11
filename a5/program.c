#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define LINE_SIZE 1500
#define SIZE 500
#define CNT_OF_LINES 2

#define MULTIPLIER 2
#define SUCCESS 1
#define FAIL 0

//Letters in morse code (from A to Z)
char* alpha_morseCode[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                         "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-",
                         "...-", ".--", "-..-", "-.--", "--.."};
//Numbers in morse code (from 0 to 9)
char* num_morseCode[] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

// data strukture for binary tree
struct b_tree {
    //dekodovane morse slovo = symbol
    char c;
    //lavy syn
    struct b_tree* left;
    //pravy syn
    struct b_tree* right;
};

struct s_lines {
    char** array;
    int top;
    int capacity;
};

struct b_tree* createNewNode(char c) {
    struct b_tree* node = (struct b_tree*)calloc(1, sizeof(struct b_tree));
    if(node == NULL) {
        return NULL;
    }
    node->c = c;
    node->left = node->right = NULL;
    return node;
}

struct b_tree* readTree(struct b_tree* tree, char* line, char c) {
    int i = 0;
    struct b_tree* root = tree;
    for(i = 0;i < strlen(line);i++) {
        if(line[i] == '.') {
            if(root->left && root->left->c != ' ') {
                root = root->left;
                continue;
            }else if( (root->left) && ( (root->left->c == ' ') && (i == strlen(line) - 1) ) ) {
                root->left->c = c;
                break;
            }else if( (root->left) && (root->left->c == ' ') ) {
                root = root->left;
                continue;
            }else {
                if(!root->left && i == strlen(line) - 1) {
                    root->left = createNewNode(c);
                    break;
                }else{
                    root->left = createNewNode(' ');
                    root = root->left;
                    continue;
                }
            }   
        }
        if(line[i] == '-') {
            if( (root->right) && (root->right->c != ' ') ) {                
                root = root->right;
                continue;
            }else if( (root->right) && ( (root->right->c == ' ') && (i == strlen(line) - 1) ) ) {
                root->right->c = c;
                break;
            }else if( (root->right) && (root->right->c == ' ') ) {
                root = root->right;
                continue;
            }else {
                if(!root->right && i == strlen(line) - 1) {
                    root->right = createNewNode(c);
                    break;
                }else{
                    root->right = createNewNode(' ');
                    root = root->right;
                    continue;
                }
            }   
        }
    }
    return tree;
}

struct b_tree* createWholeTree() {
    struct b_tree* tree = createNewNode('*');
    if(tree == NULL)
        return NULL;
    int i = 0;
    //add letters to tree
    char c = 'A';
    for(i = 0;i < 26;i++) {
        tree = readTree(tree, alpha_morseCode[i], c);
        c += 1;
    }
    //add numbers to tree
    c = '0';
    for(i = 0;i < 10;i++) {
        tree = readTree(tree, num_morseCode[i], c);
        c += 1;
    }
    return tree;
}

// inorder print tree
void displayTree(struct b_tree* root) {
    if(root == NULL) 
        return;
    displayTree(root->left);
    printf("%c\n", root->c);
    displayTree(root->right);
}

void destroyTree(struct b_tree* root) {
    if(root == NULL) 
        return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

int readLine(char* line) {
    memset(line, 0, LINE_SIZE);
    char* r = NULL;
    r = fgets(line, LINE_SIZE, stdin);
    if(r != NULL && line[1] != 0) {
        int length = strlen(line);
        line[length - 1] = 0;
        return SUCCESS;
    }
    return FAIL;
}

void initInputLines(struct s_lines* input_lines) {
    memset(input_lines, 0, sizeof(struct s_lines));
    input_lines->capacity = CNT_OF_LINES;
    input_lines->top = 0;
    input_lines->array = (char**)calloc(input_lines->capacity, sizeof(char*));
    int i = 0;
    for(i = 0;i < input_lines->capacity;i++) {
        input_lines->array[i] = (char*)calloc(LINE_SIZE, sizeof(char));
    }
}

void initLines(struct s_lines* lines) {
    memset(lines, 0, sizeof(struct s_lines));
    lines->capacity = CNT_OF_LINES;
    lines->top = 0;
    lines->array = (char**)calloc(lines->capacity, sizeof(char*));
    int i = 0;
    for(i = 0;i < lines->capacity;i++) {
        lines->array[i] = (char*)calloc(LINE_SIZE, sizeof(char));
    }
}

void destroyLines(struct s_lines* lines) {
    int i = 0;
    for(i = 0;i < lines->capacity;i++) {
        free(lines->array[i]);
    }
    free(lines->array);
}

void resizeInputLines(struct s_lines* input_lines);

void inputLines(char* line, struct s_lines* input_lines) {
    while(readLine(line) != FAIL) {
        if(input_lines->top >= input_lines->capacity) {
            resizeInputLines(input_lines);
        }
        memcpy(input_lines->array[input_lines->top], line, LINE_SIZE);
        input_lines->top += 1;
    }
}

void resizeInputLines(struct s_lines* input_lines) {
    int i = 0;
    input_lines->capacity *= MULTIPLIER;  
    input_lines->array = (char**)realloc(input_lines->array, input_lines->capacity * sizeof(char*));
    for(i = input_lines->top;i < input_lines->capacity;i++) {
        input_lines->array[i] = (char*)calloc(LINE_SIZE, sizeof(char));
    }
}

void resizeLines(struct s_lines* lines) {
    int i = 0;
    lines->capacity *= MULTIPLIER;  
    lines->array = (char**)realloc(lines->array, lines->capacity * sizeof(char*));
    for(i = lines->top;i < lines->capacity;i++) {
        lines->array[i] = (char*)calloc(SIZE, sizeof(char));
    }
}

void createMorseCodeLines(struct s_lines* morse_lines, char* input_line) {
    char tmp[SIZE];
    memset(tmp, 0, SIZE);
    int i, tmp_index, length;
    i = tmp_index = 0;
    length = strlen(input_line);
    for(i = 0;i <= length;i++) {
        if(input_line[i] == ' ')
            continue;
        if( (input_line[i] == 0) || (i != 0 && (input_line[i - 1] == ' ')) ) {
            if(morse_lines->top >= morse_lines->capacity) {
                resizeLines(morse_lines);
            }
            memcpy(morse_lines->array[morse_lines->top], tmp, SIZE);
            morse_lines->top += 1;
            memset(tmp, 0, SIZE);
            tmp_index = 0;
        }
        tmp[tmp_index] = input_line[i];
        tmp_index++;
    }
}   

char findSymbInTree(struct b_tree* root, char* morse_code_line, int* space_status) {
    int i = 0;
    //length of morse_code_line
    int length = strlen(morse_code_line);
    char c = '0';
    for(i = 0;i < length;i++) {
        if(morse_code_line[i] == '/')
            *space_status = 1;
        if(morse_code_line[i] == '.') {
            if( (root->left) && (i == length - 1) ) {
                c = root->left->c;
                break;
            }
            if(root->left) {
                root = root->left;
                continue;
            }
            if(!root->left) {
                c = '*';
                break;
            }   
        }else if(morse_code_line[i] == '-') {
            if( (root->right) && (i == length - 1) ) {
                c = root->right->c;
                break;
            }
            if(root->right) {
                root = root->right;
                continue;
            }
            if(!root->right) {
                c = '*';
                break;
            }   
        }
    }
    return c;
}

void decryptMorseCodeLines(struct b_tree* root, struct s_lines* morse_lines, struct s_lines* decrypt_lines) {
    int i, index, space_status;
    i = index = space_status = 0;
    for(i = 0;i < morse_lines->top;i++) {
        char c = findSymbInTree(root, morse_lines->array[i], &space_status);
        if(space_status == 1) {
            decrypt_lines->array[decrypt_lines->top][index] = ' ';
            index++;
            space_status = 0;
        }
        if(c != '0') {
            decrypt_lines->array[decrypt_lines->top][index] = c;
            index++;
        }
    }
}

void createDecryptMorseCodeLines(struct b_tree* root, struct s_lines* input_lines, struct s_lines* morse_lines, struct s_lines* decrypt_lines) {
    int i = 0;
    for(i = 0;i < input_lines->top;i++) {
        createMorseCodeLines(morse_lines, input_lines->array[i]);
        if(decrypt_lines->top >= decrypt_lines->capacity) {
            resizeLines(decrypt_lines);
        }
        decryptMorseCodeLines(root, morse_lines, decrypt_lines);
        decrypt_lines->top += 1;
        destroyLines(morse_lines);
        initLines(morse_lines);
    }
}

void printLines(struct s_lines lines) {
    int i = 0;
    for(i = 0;i < lines.top;i++) {
        printf("%s\n", lines.array[i]);
    }
    printf("\n");
}

int main()
{
    struct b_tree* tree = createWholeTree();
    char line[LINE_SIZE];
    struct s_lines input_lines;
    initInputLines(&input_lines);
    inputLines(line, &input_lines);
    //-------------------------
    struct s_lines morse_lines;
    initLines(&morse_lines);
    //----------------------------
    struct s_lines decrypt_lines;
    initLines(&decrypt_lines);
    //----------------------------
    createDecryptMorseCodeLines(tree, &input_lines, &morse_lines, &decrypt_lines);
    printLines(decrypt_lines);

    destroyTree(tree);
    destroyLines(&input_lines);
    destroyLines(&morse_lines);
    destroyLines(&decrypt_lines);

    return 0;
}
