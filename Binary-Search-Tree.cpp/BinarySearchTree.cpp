#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user{
    int key;
    char name[101];
    struct user* left;
    struct user* right;
};

struct user *createUser(int key, char name[]){
    struct user *newUser = (struct user*)malloc(sizeof(struct user));

    newUser->key = key;
    strcpy(newUser->name, name);
    newUser->left = NULL;
    newUser->right = NULL;

    return newUser;
}

struct user* insertBST(struct user* root, struct user* newUser){

    if(root == NULL){
        root = newUser;
    }
    else if(newUser->key < root->key){
        root->left = insertBST(root->left, newUser);
    }
    else if(newUser->key > root->key){
        root->right = insertBST(root->right, newUser);
    }
    else{
        return root;
    }
}

struct user *updateBST(struct user* root, int key, char updateName[]){

    if(root == NULL){
        return root;
    }
    else if(key > root->key){
        root->right = updateBST(root->right,key, updateName);
    }
    else if(key < root->key){
        root->left = updateBST(root->left, key, updateName);
    }
    else if(key == root->key){
        strcpy(root->name, updateName);
    }
    return root;
}

struct data *searchBST(struct user* curr, int key){
    if(curr){
        if(key > curr->key){
            return searchBST(curr->right, key);
        }
        else if(key < curr->key){
            return searchBST(curr->left, key);
        }
        else{
            printf("Found Key : %d, Name : %s\n", curr->key, curr->name);
            
        }
    }
    else{
        printf("Not Found!\n");
    }
}
struct user* predecessor(struct user* root){
    struct user* curr = root->left;

    while(curr->right != NULL){
        curr = curr->right;
    }

    return curr;
}

struct user* deleteBST(struct user* root, int key){
    if(root == NULL){
        return root;
    }
    else if(key < root->key){
        root->left = deleteBST(root->left, key);
    }
    else if(key > root->key){
        root->right = deleteBST(root->right, key);
    }
    else{
        if(root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
        }
        else if(root->left == NULL || root->right == NULL){
            struct user* temp;
            if(root->left != NULL){
                temp = root->left;
            }
            else{
                temp = root->right;
            }

            free(root);
            root = temp;
        }
        else{
            struct user* pre = predecessor(root);

            root->key = pre->key;
            strcpy(root->name, pre->name);

            root->left = deleteBST(root->left, pre->key);
        }
    }
    return root;

}

void preOrder(struct user* root){
    if(root != NULL){
        printf("Name : %s, Key : %d\n", root->name, root->key);
        preOrder(root->left);
        preOrder(root->right);
        
    }
}

void inOrder(struct user* root){
    if(root != NULL){
        inOrder(root->left);
        printf("Name : %s, Key : %d\n", root->name, root->key);
        inOrder(root->right);
    }
}

void postOrder(struct user *root){
    if(root != NULL){
        postOrder(root->left);
        postOrder(root->right);
        printf("Name : %s, Key : %d\n", root->name, root->key);
    }
}

struct user* deleteAll(struct user* root){
    while(root != NULL){
        root = deleteBST(root, root->key);
    }
    return NULL;
}

int minValue(struct user *node){
    if(node == NULL){
        return -1;
    }
    else{
        struct user *curr = node->left;

        while(curr->left != NULL){
            curr = curr->left;
        }
        return curr->key;
    }
}

int maxValue(struct user *node){
    if(node == NULL){
        return -1;
    }
    else{
        struct user *curr = node->right;

        while(curr->right != NULL){
            curr = curr->right;
        }
        return curr->key;
    }
}

int count(struct user* node){
    if(node == NULL){
        return 0;
    }
    else{
        int leftcounter = count(node->left);
        int rightcounter = count(node->right);

        return (leftcounter + rightcounter + 1);
    }
}

int heightBST(struct user *node){
    if(node == NULL){
        return 0;
    }
    else{
        int leftHeight = heightBST(node->left);
        int rightHeight = heightBST(node->right);

        if(leftHeight > rightHeight){
            return (leftHeight + 1);
        }
        else return (rightHeight + 1);
    }
}

int main()
{
    // Test ur Code here!
    // struct user* root = NULL;

    // root = insertBST(root, createUser(5, "Jordy"));
    // root = insertBST(root, createUser(10, "Budi"));
    // root = insertBST(root, createUser(16, "Susi"));
    // root = insertBST(root, createUser(4, "Joko"));

    // root = updateBST(root, 12, "Gaby");
    // inOrder(root);
    // puts("After Delete");
    // root = deleteBST(root, 5);
    // inOrder(root);

    // root = deleteAll(root);
    // inOrder(root);
    // postOrder(root);
    // puts("");
    // preOrder(root);
    // puts("");    
    // inOrder(root);
    // searchBST(root, 10);
    // inOrder(root);
    return 0;
}
