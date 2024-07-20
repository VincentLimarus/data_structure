#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 50

struct mahasiswa{
    char name[101];
    int score;
    struct mahasiswa *next;
    struct mahasiswa *prev;
}*head[SIZE], *tail[SIZE];

struct mahasiswa *newMahasiswa(char name[], int score){
    struct mahasiswa *node = (struct mahasiswa*)malloc(sizeof(struct mahasiswa));

    strcpy(node->name, name);
    node->score = score;
    node->next = NULL;
    node->prev = NULL;

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

    struct mahasiswa *node = newMahasiswa(name,score);

    if(head[index] == NULL){
        head[index] = tail[index] = node;
    }
    else{
        tail[index]->next = node;
        node->prev = tail[index];
        tail[index] = node;
    }
}

void update(char name[], int score){
    int index = hash(name);

    if(head[index] == NULL){
        puts("Data not Found!");
        return;
    }
    else{
        struct mahasiswa *curr = head[index];

        while(!curr && strcmp(curr->name, name) != 0){
            curr = curr->next;
        }
        if(curr == NULL){
            puts("Data not Found!");
            return;
        }
        strcpy(curr->name, name);
        curr->score = score;
    }
}

void removes(char name[]){
    int hashkey = hash(name);
    struct mahasiswa *curr, *temp;

    if(head[hashkey] == NULL){
        printf("Data not found!\n");
        return;
    }
    else{
        if(strcmp(head[hashkey]->name, name) == 0){
            if(head[hashkey] == tail[hashkey]){
                free(head[hashkey]);
                head[hashkey] = tail[hashkey] = NULL;
            }
            else{
                temp = head[hashkey];
                head[hashkey] = head[hashkey]->next;
                free(temp);
            }
        }
        else if(strcmp(tail[hashkey]->name, name) == 0){
            temp = tail[hashkey];
            tail[hashkey] = tail[hashkey]->prev;
            free(temp);
            tail[hashkey]->next = NULL;
        }
        else{
            curr = head[hashkey];
            while(curr){
                if(strcmp(curr->name, name) == 0){
                    temp = curr->next;
                    temp->prev = curr->prev;
                    curr->prev->next = temp;
                    free(curr);
                    break;
                }
                curr = curr->next;
            }
        }
    }
}

void view(){
    struct mahasiswa *curr;

    for(int i = 0; i < SIZE; i++){
        if(head[i] != NULL){
            curr = head[i];
            while(curr){
                printf("Name : %s, Score: %d\n", curr->name, curr->score);
                curr = curr->next;
            }
        }
    }
}
int main()
{
    // Test ur Code here!
    // insert("Gaby", 90);
    // insert("Gabriella", 95);
    // insert("Tes", 50);
    // insert("Sen", 50);
    // insert("Jordy", 80);
    // update("Nes", 99);
    // view();
    // puts("After Delete");
    // removes("Jordy");
    // view();
    return 0;
}