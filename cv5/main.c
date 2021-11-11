#include "a_train.h"
#include <stdio.h>

// Testovaci subor pre vlak
int main(){
    struct car* train = NULL;
    train = add_car(train, "Presov");
    train = add_car(train, "Bratislava");
    train = add_car(train, "Levoca");
    train = add_car(train, "Spiska Nova Ves");
    train = add_car(train, "Mukacevo");
    print_train(train);
    train = clear_train(train, "Presov"); 
    train = clear_train(train, "Levoca");
    train = clear_train(train, "Bratislava");
    train = clear_train(train, "Spiska Nova Ves");
    print_train(train);
    cancel_train(train);

    return 0;
}
