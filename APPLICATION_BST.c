#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int accNo;
    char name[50];
    float balance;
    struct Node *left, *right;
};

struct Node* createNode(int accNo, char name[], float balance) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->accNo = accNo;
    strcpy(newNode->name, name);
    newNode->balance = balance;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int accNo, char name[], float balance) {
    if (root == NULL)
        return createNode(accNo, name, balance);

    if (accNo < root->accNo)
        root->left = insert(root->left, accNo, name, balance);
    else if (accNo > root->accNo)
        root->right = insert(root->right, accNo, name, balance);

    return root;
}

struct Node* search(struct Node* root, int accNo) {
    if (root == NULL || root->accNo == accNo)
        return root;

    if (accNo < root->accNo)
        return search(root->left, accNo);

    return search(root->right, accNo);
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("AccNo: %d | Name: %s | Balance: %.2f\n",
               root->accNo, root->name, root->balance);
        inorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, accNo;
    char name[50];
    float balance;

    while (1) {
        printf("\n1. Insert\n2. Search\n3. Display\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter Account No, Name, Balance: ");
            scanf("%d %s %f", &accNo, name, &balance);
            root = insert(root, accNo, name, balance);
            break;

        case 2:
            printf("Enter Account No to search: ");
            scanf("%d", &accNo);
            struct Node* result = search(root, accNo);
            if (result != NULL)
                printf("Found: %s | Balance: %.2f\n",
                       result->name, result->balance);
            else
                printf("Account not found\n");
            break;

        case 3:
            printf("\nBank Accounts (Sorted Order):\n");
            inorder(root);
            break;

        case 4:
            exit(0);

        default:
            printf("Invalid choice\n");
        }
    }
}
