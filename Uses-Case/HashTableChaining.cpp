#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define SIZE 50

int counter = 1;
int global = 0;

char propertyName[155];
char propertyType[155];
int room;
char owner[155];
char street[155];
char id[15];

char confirmation[15];

struct data{
    char propertyName[155];
    char propertyType[155];
    int room;
    char owner[155];
    char street[155];
    char id[15];
    struct data *next;
    struct data *prev;
}*head[SIZE], *tail[SIZE];

struct data *newData(char propertyName[], char propertyType[], int room, char owner[], char street[]){
    struct data *node = (struct data*)malloc(sizeof(struct data));

    node->room = room;
    node->next = NULL;
    node->prev = NULL;
    strcpy(node->propertyName, propertyName);
    strcpy(node->propertyType, propertyType);
    strcpy(node->owner, owner);
    strcpy(node->street, street);
    
    char genId[15] = "AAXXX";
    
    if(strcmp(propertyType, "Mansion") == 0){
        genId[0] = 'M';
        genId[1] = 'A';    
    }
    else if(strcmp(propertyType, "Bungalow") == 0){
        genId[0] = 'B';
        genId[1] = 'U';    
    }
    else if(strcmp(propertyType, "Cluster") == 0){
        genId[0] = 'C';
        genId[1] = 'L';    
    }

    sprintf(node->id, "%c%c%03d", genId[0], genId[1], counter);

    return node;
}

int validateOwner(char owner[]){
    if(owner[0] == 'M' && owner[1] == 'r' && owner[2] == '.'){
        return 1;
    }
    else if(owner[0] == 'M' && owner[1] == 'r' && owner[2] == 's' && owner[3] == '.'){
        return 1;
    }
    else{
        return 2;
    }
}
int hashKey(char id[]){
    int total = 0;

    for(int i = 2; i < 5; i++){
        total += id[i];
    }
    return total % SIZE;
}

void insert(struct data *node){
    int index = hashKey(node->id);

    if(head[index] == NULL){
        head[index] = tail[index] = node;
        counter++;
        global++;
    }
    else{
        tail[index]->next = node;
        node->prev = tail[index];
        tail[index] = node;
        counter++;
        global++;
    }
    
}

void view(){
    struct data *curr;

    for(int i = 0; i < SIZE; i++){
        if(head[i] == NULL){
            continue;
        }
        else{
            curr = head[i];

            while(curr != NULL){
                puts("LIST OF PROPERTY");
                puts("----------------");
                puts("");
                printf("Property ID     : [%s]\n", curr->id);
                printf("Property Name   : %s\n", curr->propertyName);
                printf("Property Type   : %s\n", curr->propertyType);
                printf("Room Quantity   : %d\n", curr->room);
                printf("Owner Name      : %s\n", curr->owner);
                printf("Property Street : %s\n", curr->street);
                curr = curr->next;
            }
        }
    }
}

void deleteHash(char id[]){
    int index = hashKey(id);

    if(head[index] == NULL){
        puts("Delete Property");
        puts("---------------");
        puts("");
        puts("No data !!!");
    }
    else if(head[index] == tail[index] && strcmp(head[index]->id, id) == 0){
        free(head[index]);
        head[index] = tail[index] = NULL;
        printf("%s - %s deleted !!!\nx", id, propertyName);
        counter--;
        global--;
    }
    else if(strcmp(head[index]->id, id) == 0){
        struct data *curr = head[index];
        head[index] = head[index]->next;
        head[index]->prev = NULL;
        curr->next = NULL;
        free(curr);
        curr = NULL;
        printf("%s - %s deleted !!!\n", id, propertyName);
        counter--;
        global--;
    }
    else if(strcmp(tail[index]->id, id) == 0){
        struct data *curr = tail[index];
        tail[index] = tail[index]->prev;
        tail[index]->next = NULL;
        curr->prev = NULL;
        free(curr);
        curr = NULL;
        printf("%s - %s deleted !!!\n", id, propertyName);
        counter--;
        global--;
    }
    else{
        struct data *curr = head[index]->next;

        if(!curr){
            puts("Property Not Found !!!");
        }
        while(curr != NULL && strcmp(curr->id, id) != 0){
            curr = curr->next;
        }
        struct data *after = curr->next;
        struct data *before = curr->prev;

        after->prev = before;
        before->next = after;

        curr->next = NULL;
        curr->prev = NULL;
        free(curr);
        curr = NULL;
        printf("%s - %s deleted !!!\n", id, propertyName);
        counter--;
        global--;
    }
}

int main()
{
    int input = 0;

    do{
        system("cls");
        puts("1. Add New Property");
        puts("2. View Property");
        puts("3. Delete Property");
        puts("4. Exit");
        printf("Choose [1 - 4] >> ");
        scanf("%d", &input);
        getchar();

        if(input == 1){
            do{
                printf("Input Property name [length 5..20]: ");
                scanf("%[^\n]", propertyName);
                getchar();
            }while(strlen(propertyName) > 20 || strlen(propertyName) < 5);

            do{
                printf("Input Property Type [Mansion | Bungalow | Cluster] (Case Sensitive) : ");
                scanf("%[^\n]", propertyType);
                getchar();
            }while(strcmp(propertyType, "Mansion") != 0 && strcmp(propertyType, "Bungalow") != 0 && strcmp(propertyType, "Cluster") != 0);

            do{
                printf("Input room quantity [1..8] : ");
                scanf("%d", &room);
                getchar();
            }while(room > 8 || room < 1);

            do{
                printf("Input owner name start with Mr. or Mrs. : ");
                scanf("%[^\n]", owner);
                getchar();
            }while(validateOwner(owner) != 1);

            do{
                printf("Input Street name of property endswith 'street' (case sensitive) : ");
                scanf("%[^\n]", street);
                getchar();
            }while(strcmp(&street[strlen(street) - 6], "street") != 0);

            do{
                printf("Are you sure to add this property [Y or N] (Case sensitive):\n");
                printf("> ");
                scanf("%[^\n]", confirmation);
                getchar();

            }while(strcmp(confirmation, "Y") != 0 && strcmp(confirmation, "N") != 0);

            if(strcmp(confirmation, "Y") == 0){
                puts("");
                puts("+========================+");
                insert(newData(propertyName, propertyType ,room, owner, street));
                puts("| Data has been insert ! |");
                puts("+========================+");
                puts("");
                printf("Press Enter to Continue..");
                getch();
            }
            else if(strcmp(confirmation, "N") == 0){
                puts("");
                printf("Press Enter to Continue..");
                getch();
            }
        }
        else if(input == 2){
            if(global == 0){
                puts("LIST OF PROPERTY");
                puts("----------------");
                puts("");
                puts("No data !!!");

                printf("Press enter to continue...");
                getch();
            }
            else{
                puts("");
                view();
                puts("");
                printf("Press enter to continue...");
                getch();
            }
        }
        else if(input == 3){
            if(global == 0){
                puts("LIST OF PROPERTY");
                puts("----------------");
                puts("");
                puts("No data !!!");

                printf("Press enter to continue...");
                getch();
            }
            else{
                puts("");
                view();
                puts("");

                printf("Chose the Property's' ID [MAXXX | BUXXX | CUXXX]");
                printf("> ");
                scanf("%[^\n]", id);
                getchar();
                deleteHash(id);

                printf("Press enter to continue...");
                getch();
            }
        }
    }while(input != 4);

    return 0;
}