#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    int key;
    int height;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int key){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int getHeight(struct Node *curr){
    if(curr == NULL) return 0;
    return curr->height;
}

int getMax(int a, int b){
    return a > b ? a : b;
}

int getBalanceFactor(struct Node* curr){
    return getHeight(curr->left) - getHeight(curr->right);
}

struct Node* rightRotate(struct Node* curr){
    struct Node* childLeft = curr->left;        //  childLeft = 6
    struct Node* subChildLeft = childLeft->right; // subChildLeft = 8

    childLeft->right = curr;    
    curr->left = subChildLeft;
    
    curr->height = 1 + getMax(getHeight(curr->right), getHeight(curr->left));
    childLeft->height = 1 + getMax(getHeight(childLeft->right), getHeight(childLeft->left));

    return childLeft;
}

struct Node* leftRotate(struct Node* curr){
    struct Node* childRight = curr->right;
    struct Node* subChildright = childRight->left;

    childRight->left= curr;
    curr->right = subChildright;

    curr->height = 1 + getMax(getHeight(curr->left), getHeight(curr->right));
    childRight->height = 1 + getMax(getHeight(childRight->left), getHeight(childRight->right));

    return childRight;
}

struct Node *balancing(struct Node* curr){
    // Update Height
    curr->height = 1 + getMax(getHeight(curr->left), getHeight(curr->right));
    // Check Balancing 
    
    // Kondisi Left-Left
    if(getBalanceFactor(curr) > 1 && getBalanceFactor(curr->left) >= 0){
        // Right rotate
        return rightRotate(curr);
    }
    // Kondisi Right-Right
    if(getBalanceFactor(curr) < -1 && getBalanceFactor(curr->right) <= 0){
        // Left Rotate
        return leftRotate(curr);
    }
    // Kondisi Left-Right
    if(getBalanceFactor(curr) > 1 && getBalanceFactor(curr->left) < 0){
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    // Kondisi Right-Left
    if(getBalanceFactor(curr) < -1 && getBalanceFactor(curr->right) > 0){
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

struct Node* update(Node* curr, int key){
    if(curr == NULL){
        printf("Not Found!\n");
        return NULL;
    }
    if(key > curr->key){
       curr->right = update(curr->right, key);
    }
    else if(key < curr->key){
        curr->left = update(curr->left, key);
    }
    else if(key == curr->key){
        curr->key = key;
        return curr;
    }
}

struct Node* insert(Node* curr, Node* newNode){
    if(curr == NULL){
        return newNode;
    }
    
    if(newNode->key < curr->key){
        curr->left = insert(curr->left, newNode);
    }
    else if(newNode->key > curr->key){
        curr->right = insert(curr->right, newNode);
    }
    return balancing(curr);
}

struct Node* predecessor(struct Node* curr){
    struct Node* temp = curr->left;

    while(temp->right != NULL){
        temp = temp->right;
    }
    return temp;
}

struct Node *pop(struct Node* curr, int key){
    if(curr == NULL){
        printf("Data not Found!\n");
        return curr;
    }

    if(key < curr->key){
        curr->left = pop(curr->left, key);
    }
    else if(key > curr->key){
        curr->right = pop(curr->right, key);
    }
    else{
        if(curr->left == NULL && curr->right == NULL){
            free(curr);
            curr = NULL;
            return curr;
        }
        else if(curr->left == NULL || curr->right == NULL){
            struct Node* temp;
            if(curr->left != NULL){
                temp = curr->left;
            }
            else{
                temp = curr->right;
            }
            free(curr);
            curr = temp;
        }
        else{
            struct Node* pre = predecessor(curr);

            curr->key = pre->key;
            
            curr->left = pop(curr->left, pre->key);
        }
    }
    return balancing(curr);
}

struct Node* popAll(Node* curr){
    while(curr != NULL){
        curr = pop(curr, curr->key);
    }
    return NULL;
}

void preOrder(struct Node *curr){
    if(curr != NULL){
        printf("%d, %d\n", curr->key, curr->height);
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

int main()
{
    // Test ur Code here!
    // struct Node*root = NULL;

    // root = insert(root, createNode(10));
    // root = insert(root, createNode(8));
    // root = insert(root, createNode(7));
    // root = insert(root, createNode(12));
    // root = insert(root, createNode(11));
    // root = insert(root, createNode(14));
    // preOrder(root);

    // printf("\n\nAfter Delete\n\n");

    // root = pop(root, 10);
    // preOrder(root);

    // printf("\n\nAfter Pop All\n\n");
    // root = popAll(root);

    return 0;
}