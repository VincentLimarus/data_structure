#include <stdio.h>
#include <string.h>
#include <stdlib.h> // STACK - LIFO -> push head, pop head  
                   // QUEUE - FIFO -> push tail, pop head

struct user{
    char name[51];
    int age;
    struct user *next;
    struct user *prev;
}*head = NULL, *tail = NULL;

struct user *newUser(char name[51], int age){
    struct user *node = (struct user*)malloc(sizeof(struct user));

    strcpy(node->name, name);
    node->age = age;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

void pushHead(char name[], int age){
    struct user *node = newUser(name, age);

    if(head == NULL){
        head = tail = node;
    }
    else{
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void pushTail(char name[], int age){
    struct user *node = newUser(name, age);

    if(head == NULL){
        head = tail = node;
    }
    else{
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

void pushMid(char name[], int age){
    struct user *node = newUser(name, age);

    if(head == NULL){
        head = tail = node;
        // return;
    }
    if(strcmp(node->name, head->name) < 0){
        pushHead(name, age);
    }   
    else if(strcmp(node->name, tail->name) > 0){
        pushTail(name , age);
    }
    else{
        struct user *curr = head;

        while(strcmp(curr->next->name, node->name) < 0){
            curr = curr->next;
        }
        struct user *afterCurr = curr->next;
        afterCurr->prev = node;
        node->next = afterCurr;

        curr->next = node;
        node->prev = curr;
    }
}

void popHead(){
    struct user *curr = head;

    if(head == NULL){
        return;
    }
    else if(head == tail){
        head = tail = NULL;
        free(head);
        return;
    }
    else{
        head = head->next; 
        free(curr);
        head->prev = NULL;
        curr->next = NULL;
    }
}

void popTail()
{
    struct user *curr = tail;

    if(head == NULL){
        return;
    }
    else if(head == tail)
    {
        free(head);
        head = tail = NULL;
        return;
    }
    else{
        tail = curr->prev;
        tail->next = NULL;

        free(curr);
        curr = NULL;
    }

}

void popMid(char name[]){
    struct user *curr = head;

    if(head == NULL){
        return;
    }
    else if(head == tail)
    {
        free(head);
        head = tail = NULL;
        return;
    }
    else if(strcmp(head->name, name) == 0){
        popHead();
        return;
    }
    else if(strcmp(tail->name, name) == 0){
        popTail();
        return;
    }
    else{

        while(curr != NULL && strcmp(curr->name, name) != 0){
            curr = curr->next;
        }
        if(curr == NULL){
            printf("Data not found\n");
            return;
    }

    struct user *before = curr->prev;
    struct user *after = curr->next;

    before->next = after;
    after->prev = before;

    curr->prev = NULL;
    curr->next = NULL;

    free(curr);
    curr = NULL;
    }
}
void printData(){
    struct user *curr = head;

    while(curr){
        printf("Name : %s, Age : %d\n", curr->name, curr->age);
        curr = curr->next;
    }
}
int main()
{
    // Test ur Code here!
    // pushHead("Jordy", 12);
    // pushTail("Titi", 11);
    // popTail();
    // popHead();
    // pushMid("Budi", 15);
    // printData();
    // popMid("Bryan");
    // printData();    
    return 0;
}