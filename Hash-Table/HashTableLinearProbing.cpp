#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50

int count = 0;

struct mahasiswa{
    char name[101];
    int score;
}*array[SIZE];

struct mahasiswa *newMahasiswa(char name[], int score){
    struct mahasiswa *node = (struct mahasiswa*)malloc(sizeof(struct mahasiswa));

    strcpy(node->name,name);
    node->score = score;

    return node;
}

int hash(char name[]){
    int hashkey = 0;

    int len = strlen(name);

    for(int i = 0; i < len; i++){
        hashkey += name[i];
    }

    return hashkey % SIZE;
}

void insert(char name[], int score){
    int index = hash(name);

    // arraynya full
    if(count == SIZE){
        printf("Array Full\n");
        return;
    }
    // collision
    while(array[index] != NULL){
        index = (index + 1) % SIZE;
    }
    // lacinya kosong
    array[index] = newMahasiswa(name,score);
    count++;
}

void view()
{
    for(int i = 0; i < SIZE; i++){
        if(array[i] != NULL){
            printf("Name : %s - Score : %d - Key : %d\n", 
            array[i]->name, array[i]->score, hash(array[i]->name));
        }
        else{
            // puts("-");
            continue;
        }
    }
}

void removes(char name[]){
    int hashkey = hash(name);
    int index = hashkey;
        
    do{
        if(array[index] != NULL && strcmp(array[index]->name, name) == 0){
            free(array[index]);
            array[index] = NULL;
            return;
        }
        index = (index + 1) % SIZE;
    }
    while(index != hashkey);
    return;
}

struct mahasiswa *search(char name[]){
    int hashkey = hash(name);
    int index = hashkey;

    do{
        if(array[index] && strcmp(array[index]->name, name) == 0){
            
            return array[index];
        }
        index = (index + 1) % SIZE;
    }
    while(index != hashkey);
    return NULL;
}

int main()
{
    insert("Gaby", 60);
    insert("Jordy", 65);
    view();
    puts("After Remove");
    removes("Gaby");
    view();

    // if(search("Jordy")){
    //     printf("Found!\n");
    // }
    // else{
    //     printf("Not Found!\n");
    // }
    return 0;
}