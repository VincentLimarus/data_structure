#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user
{
    int age;
    char name[50];
    struct user *next;

}*head = NULL, *tail = NULL;

struct user *newUser(int age, char name[50])
{
    struct user *node = (struct user*)malloc(sizeof(struct user));
    node->age = age;
    strcpy(node->name, name);
    node->next = NULL;

    return node;
};

void pushHead(int age, char name[50])
{
    struct user *node = newUser(age, name);

    if(head == NULL){
        head = tail = node;
    }
    else{
        node->next = head;
        head = node;
    }
}

void printAll()
{
    if(head == NULL){
        printf("NO DATA EXIST\n");
    }
    struct user *curr = head;

    while(curr != NULL){
        printf("Age : %d, Name : %s\n", curr->age, curr->name);
        curr = curr->next;
    }
}

void pushTail(int age, char name[50])
{
    struct user *node = newUser(age, name);

    if(head == NULL){
        head = tail = node;
    }
    else{
        tail->next = node;
        tail = node;
    }
}

void pushMid(int age, char name[50])
{
    struct user *node = newUser(age, name);

    if(head == NULL){
        head = tail = node;
    }
    else if(age < head->age){
        pushHead(age, name);
    }
    else if(age >= tail->age){
        pushTail(age, name);
    }
    else{
        struct user *curr = head;
        while(curr != NULL && curr->next->age < age){
            curr = curr->next;
        }
        node->next = curr->next;
        curr->next = node;
    }
}

void popHead(){
    if(head == NULL){
        return;
    }
    else if(head == tail){
        free(head);
        head = tail = NULL;
    }
    else {
        struct user *temp = head;
        head = head->next;
        free(temp);
    }
}

void popTail(){
    if(head == NULL){
        return;
    }
    else if(head == tail){
        free(head);
        head = tail = NULL;
        return;
    }
    else{
        struct user *curr = head;
        while(curr->next != tail){
            curr = curr->next;
        }
        free(curr->next);
        curr->next = NULL;
        curr = tail;
    }
}

void popMid(int age){
    if(head == NULL){
        return;
    }
    else{
        if(head->age == age){
            popHead();
        }
        else if(tail->age == age){
            popTail();
        }
        else{
            struct user *curr = head;

            while(curr->next != NULL && curr->next->age != age){
                curr = curr->next;
            }
            if(curr->next == NULL){
                printf("Data doesnt Exist\n");
                return;
            }
            struct user *temp = curr->next;
            curr->next = temp->next;
            free(temp);
            
            return;
        }
    }
}
int main()
{
    // Test ur Code here!
    // pushMid(12, "Jordy");
    // pushMid(15, "Gabriella");
    // printAll();
    // popTail();
    // popHead();
    // printAll();
    // pushHead(12, "Jordy");
    // pushHead(9, "Gabriella");
    // pushTail(21, "Sen");
    // pushMid(1, "Lisa");
    // popMid(2);
    // printAll();

    return 0;
}