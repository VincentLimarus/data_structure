#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int global = 0;
char id[15];
char shoeLaces[15];
char shoeName[25];
int shoeSize;
char shoeType[25];
char shoeBrand[25];
char shoeColor[25];

struct data{
    int height;
    struct data *left;
    struct data *right;
    char id[15];

    char shoeLaces[15];
    char shoeName[25];
    int shoeSize;
    char shoeType[25];
    char shoeBrand[25];
    char shoeColor[25];
}*root = NULL;

void typeValidation(char shoeType[]){    // 65 - 90 Besar  97 - 122 Kecil
    for(int i = 0; i < strlen(shoeType); i++){
        if(shoeType[0] >= 97 && shoeType[0] <= 122 && i == 0){
            shoeType[0] -= 32;
        }
        else if(shoeType[i] >= 65 && shoeType[i] <= 90 && i != 0){
            shoeType[i] += 32;
        }
    }
}

void colorValidation(char shoeColor[]){
    for(int i = 0; i < strlen(shoeColor); i++){
        if(shoeColor[0] >= 97 && shoeColor[0] <= 122 && i == 0){
            shoeColor[0] -= 32;
        }
        else if(shoeColor[i] >= 65 && shoeColor[i] <= 90 && i != 0){
            shoeColor[i] += 32;
        }
    }
}

struct data *newData(char shoeName[], int shoeSize, char shoeType[], char shoeBrand[], char shoeColor[]){
    struct data *node = (struct data*)malloc(sizeof(struct data));

    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    char genShoeLaces[2] = {'X'};   

    genShoeLaces[0] = '0' + rand() % 4 + 2;    // 2, 5(akhir - awal + 1) + awal

    char genId[15] = "SHXXX";
    strcpy(node->shoeName, shoeName);
    strcpy(node->shoeType, shoeType);
    strcpy(node->shoeBrand, shoeBrand);
    strcpy(node->shoeColor, shoeColor);
    node->shoeSize = shoeSize;

    for(int i = 2; i < 5; i++){
        genId[i] = '0' + rand()%10;
    }

    // sprintf(node->id, "%c%c%03d", genId[0], genId[1], rand()%10, rand()%10, rand()%10);

    strcpy(node->id, genId);
    strcpy(node->shoeLaces, genShoeLaces);

    return node;
}

int functionSearch(struct data *curr, char id[]){
    if(curr != NULL){
        if(strcmp(curr->id, id) > 0){
            return functionSearch(curr->left, id);
        }
        else if(strcmp(curr->id, id) < 0){
            return functionSearch(curr->right, id);
        }
        else{
            return 1;
        }
    }
    else{
        return 2;
    }
}
int getMax(int a, int b){
    return a > b ? a : b;
}

int getHeight(struct data *curr){
    if(curr == NULL) return 0;
    return curr->height;
}

int getBalanceFactor(struct data *curr){
    return getHeight(curr->left) - getHeight(curr->right);
}

struct data *rightRotate(struct data *curr){
    struct data *leftChild = curr->left;
    struct data *leftRightChild = leftChild->right;

    leftChild->right = curr;
    curr->left = leftRightChild;

    curr->height = 1 + getMax(getHeight(curr->left), getHeight(curr->right));

    leftChild->height = 1 + getMax(getHeight(leftChild->left), getHeight(leftChild->right));

    return leftChild;
}

struct data *leftRotate(struct data *curr){
    struct data *rightChild = curr->right;
    struct data *rightLeftChild = rightChild->left;

    rightChild->left = curr;
    curr->right = rightLeftChild;

    curr->height = 1 + getMax(getHeight(curr->left), getHeight(curr->right));

    rightChild->height = 1 + getMax(getHeight(rightChild->left), getHeight(rightChild->right));

    return rightChild;
}

struct data *balancing(struct data *curr){
    curr->height = 1 + getMax(getHeight(curr->left), getHeight(curr->right));

    if(getBalanceFactor(curr) > 1 && getBalanceFactor(curr->left) >= 0){
        return rightRotate(curr);
    }
    if(getBalanceFactor(curr) < -1 && getBalanceFactor(curr->right) <= 0){
        return leftRotate(curr);
    }
    if(getBalanceFactor(curr) > 1 && getBalanceFactor(curr->left) < 0){
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if(getBalanceFactor(curr) < -1 && getBalanceFactor(curr->right) > 0){
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

struct data *insert(struct data* curr, struct data *node){
    if(curr == NULL){
        global++;
        return node;
    }
    if(strcmp(curr->id, node->id) > 0){
        curr->left = insert(curr->left, node);
    }
    else if(strcmp(curr->id, node->id) < 0){
        curr->right = insert(curr->right, node);
    }
    return balancing(curr);
}

void inOrder(struct data *curr){
    if(curr != NULL){
        inOrder(curr->left);
        printf("| %s    | %s        | %d    | %s        | %s        | %s        | %s\n" , curr->id, curr->shoeName, curr->shoeSize, curr->shoeBrand, curr->shoeColor, curr->shoeType, curr->shoeLaces);
        inOrder(curr->right);
    }
}

void preOrder(struct data *curr){
    if(curr != NULL){
        printf("| %s    | %s        | %d    | %s        | %s        | %s        | %s\n" , curr->id, curr->shoeName, curr->shoeSize, curr->shoeBrand, curr->shoeColor, curr->shoeType, curr->shoeLaces);
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

void postOrder(struct data *curr){
    if(curr != NULL){
        postOrder(curr->left);
        postOrder(curr->right);
        printf("| %s    | %s        | %d    | %s        | %s        | %s        | %s\n" , curr->id, curr->shoeName, curr->shoeSize, curr->shoeBrand, curr->shoeColor, curr->shoeType, curr->shoeLaces);
    }
}

int search(struct data *curr, char id[]){
    if(curr != NULL){
        if(strcmp(curr->id, id) > 0){
            return search(curr->left, id);
        }
        else if(strcmp(curr->id, id) < 0){
            return search(curr->right, id);
        }
        else{
            puts("Shoe Found!");
        }
    }
    else{
        puts("Shoe not found!");
    }
}

struct data *predecessor(struct data *curr){
    struct data *temp = curr->left;

    while(temp->right != NULL){
        temp = temp->right;
    }
    return temp;
}

struct data *pop(struct data *curr, char id[]){
    if(curr == NULL){
        return curr;
    }
    if(strcmp(curr->id, id) > 0){
        curr->left = pop(curr->left, id);
    }
    else if(strcmp(curr->id, id) < 0){
        curr->right = pop(curr->right, id);
    }
    else{
        if(curr->left == NULL && curr->right == NULL){
            free(curr);
            curr = NULL;
            global--;
            puts("Shoe deleted!");
            return curr;
        }
        else if(curr->left == NULL || curr->right == NULL){
            struct data *temp;

            if(curr->left != NULL){
                temp = curr->left;
            }
            else if(curr->right != NULL){
                temp = curr->right;
            }
            free(curr);
            curr = temp;
            global--;
            puts("Shoe deleted!");
        }
        else{
            struct data *pre = predecessor(curr);

            strcpy(curr->id,pre->id);
            strcpy(curr->shoeBrand, pre->shoeBrand);
            strcpy(curr->shoeColor, pre->shoeColor);
            strcpy(curr->shoeName, pre->shoeName);
            strcpy(curr->shoeType, pre->shoeType);
            strcpy(curr->shoeLaces, pre->shoeLaces);
            curr->shoeSize = pre->shoeSize;

            curr->left = pop(curr->left, pre->id);
            global--;
            puts("Shoe deleted!");
        }    
    }
    return balancing(curr);
}

struct data *popAll(struct data *curr){
    while(curr != NULL){
        curr = pop(curr, curr->id);
    }
    return NULL;
}

int main()
{  
    srand(time(0));

    int input = 0;

    do{ 
        system("cls");
        puts("+=====================+");
        puts("|     Shoe Shop       |");
        puts("+=====================+");
        puts("|  1. Insert Shoe     |");
        puts("|  2. View Shoes      |");
        puts("|  3. Search Shoe     |");
        puts("|  4. Delete Shoe     |");
        puts("|  5. Delete All Shoe |");
        puts("|  6. Exit            |");
        puts("+=====================+");
        printf(">> ");
        scanf("%d", &input);
        getchar();

        if(input == 1){
            do{
                printf("Input shoe name [5 - 20 characters] : ");
                scanf("%[^\n]", shoeName);
                getchar();
            }while(strlen(shoeName) < 5 || strlen(shoeName) > 20);

            do{
                printf("Input shoe size [30-50]: ");
                scanf("%d", &shoeSize);
                getchar();
            }while(shoeSize < 30 || shoeSize > 50);

            do{
                printf("Input shoe type [Walking | Running] (Case insensitive): ");
                scanf("%[^\n]", shoeType);
                getchar();

                typeValidation(shoeType);
            }while(strcmp(shoeType, "Walking") != 00 && strcmp(shoeType, "Running") != 0);

            do{
                printf("Input shoe brand [Airwalk | Diadora] (Case sensitive): ");
                scanf("%[^\n]", shoeBrand);
                getchar();
            }while(strcmp(shoeBrand, "Airwalk") != 0 && strcmp(shoeBrand, "Diadora"));

            do{
                printf("Input shoe color [Red | Green | Blue | Yellow] (Case Sensitive): ");
                scanf("%[^\n]", shoeColor);
                getchar();

                colorValidation(shoeColor);
            }while(strcmp(shoeColor, "Red") != 0 && strcmp(shoeColor, "Green") != 0 && strcmp(shoeColor, "Blue") != 0 && strcmp(shoeColor, "Yellow") != 0);

            root = insert(root, newData(shoeName, shoeSize, shoeType, shoeBrand, shoeColor));
            printf("Shoe with ID : %s has been generated\n", root->id);
            puts("");

            printf("Press enter to continue..");
            getch();
        }
        else if(input == 2){
            if(global == 0){
                puts("There is no data!");
                printf("Press enter to continue..");
                getch();
            }
            else{
                int inputView = 0;
                do{
                    system("cls");
                    puts("View");
                    puts("1. In-Order");
                    puts("2. Post-Order");
                    puts("3. Pre-Order");
                    puts("4. Exit");
                    printf(">> ");
                    scanf("%d", &inputView);
                    getchar();

                    if(inputView == 1){
                        puts("+=========+=======================+===========+============+============+===========+============+");
                        puts("| Shoe ID |       Shoe Name       | Shoe Size | Shoe Brand | Shoe Color | Shoe Type | Shoe Laces |");
                        puts("+=========+=======================+===========+============+============+===========+============+");
                        inOrder(root);
                        puts("+=========+=======================+===========+============+============+===========+============+");

                        printf("Press enter to continue..");
                        getch();
                    }
                    else if(inputView == 2){
                        puts("+=========+=======================+===========+============+============+===========+============+");
                        puts("| Shoe ID |       Shoe Name       | Shoe Size | Shoe Brand | Shoe Color | Shoe Type | Shoe Laces |");
                        puts("+=========+=======================+===========+============+============+===========+============+");
                        postOrder(root);
                        puts("+=========+=======================+===========+============+============+===========+============+");

                        printf("Press enter to continue..");
                        getch();
                    }
                    else if(inputView == 3){
                        puts("+=========+=======================+===========+============+============+===========+============+");
                        puts("| Shoe ID |       Shoe Name       | Shoe Size | Shoe Brand | Shoe Color | Shoe Type | Shoe Laces |");
                        puts("+=========+=======================+===========+============+============+===========+============+");
                        preOrder(root);
                        puts("+=========+=======================+===========+============+============+===========+============+");

                        printf("Press enter to continue..");
                        getch();    
                    }
                }while(inputView == 4);
            }
        }
        else if(input == 3){
            char findId[15];

            if(global == 0){
                puts("There is no data!");
                printf("Press enter to continue..");
                getch();    
            }
            else{
                puts("+=========+=======================+===========+============+============+===========+============+");
                puts("| Shoe ID |       Shoe Name       | Shoe Size | Shoe Brand | Shoe Color | Shoe Type | Shoe Laces |");
                puts("+=========+=======================+===========+============+============+===========+============+");
                inOrder(root);
                puts("+=========+=======================+===========+============+============+===========+============+");

                puts("");
                printf("Input ShoeID to search: ");
                scanf("%s", findId);
                getchar();

                search(root, findId);
                puts("");

                printf("Press enter to continue..");
                getch();
            }
        }
        else if(input == 4){
            if(global == 0){
                puts("There is no data!");
                printf("Press enter to continue..");
                getch();
            }
            else{
                char deleteItem[15];
                puts("+=========+=======================+===========+============+============+===========+============+");
                puts("| Shoe ID |       Shoe Name       | Shoe Size | Shoe Brand | Shoe Color | Shoe Type | Shoe Laces |");
                puts("+=========+=======================+===========+============+============+===========+============+");
                inOrder(root);
                puts("+=========+=======================+===========+============+============+===========+============+");

                puts("");
                printf("Input ShoeID to delete: ");
                scanf("%s", deleteItem);
                getchar();

                if(functionSearch(root, deleteItem) == 1){
                    root = pop(root, deleteItem);

                    printf("Press enter to continue..");
                    getch();
                }
                else if(functionSearch(root, deleteItem) == 2){
                    puts("Shoe not found!");

                    printf("Press enter to continue..");
                    getch();
                }
            }
        }
        else if(input == 5){
            if(global == 0){
                puts("There is no data!");

                printf("Press enter to continue..");
                getch();
            }
            else{
                popAll(root);
                puts("Deleted all data successfully");

                printf("Press enter to continue..");
                getch();
            }
        }
    }while(input != 6);
    return 0;
}