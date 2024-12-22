#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[100];
    char phone[20];
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(char* name, char* phone) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the BST
Node* insertNode(Node* root, char* name, char* phone) {
    if (root == NULL) {
        return createNode(name, phone);
    }

    if (strcmp(name, root->name) < 0) {
        root->left = insertNode(root->left, name, phone);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insertNode(root->right, name, phone);
    }

    return root;
}

// Function to search for a node by name
Node* searchNode(Node* root, char* name) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        return searchNode(root->left, name);
    } else {
        return searchNode(root->right, name);
    }
}

// Function to find the minimum value node in the BST (used for deletion)
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the BST
Node* deleteNode(Node* root, char* name) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        root->left = deleteNode(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = deleteNode(root->right, name);
    } else {
        // Node to be deleted found
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node has two children, get the inorder successor (smallest in the right subtree)
        Node* temp = findMin(root->right);
        strcpy(root->name, temp->name);
        strcpy(root->phone, temp->phone);
        root->right = deleteNode(root->right, temp->name);
    }
    return root;
}

// Function to print the BST in-order (sorted order)
void printInOrder(Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("Name: %s, Phone: %s\n", root->name, root->phone);
        printInOrder(root->right);
    }
}

// Main menu function to interact with the user
void menu(Node** root) {
    int choice;
    char name[100], phone[20];
    Node* result;

    while (1) {
        printf("\nPhone Directory Menu:\n");
        printf("1. Insert a new entry\n");
        printf("2. Search for a name\n");
        printf("3. Delete an entry\n");
        printf("4. Print entire phone list\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // to consume the newline left by scanf

        switch (choice) {
            case 1: // Insert a new entry
                printf("Enter the name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline

                printf("Enter the phone number: ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = '\0';  // Remove newline

                *root = insertNode(*root, name, phone);
                printf("Entry inserted successfully.\n");
                break;

            case 2: // Search for a name
                printf("Enter the name to search for: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline

                result = searchNode(*root, name);
                if (result != NULL) {
                    printf("Name: %s, Phone: %s\n", result->name, result->phone);
                } else {
                    printf("Name not found in the directory.\n");
                }
                break;

            case 3: // Delete an entry
                printf("Enter the name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline

                *root = deleteNode(*root, name);
                printf("Entry deleted successfully (if it existed).\n");
                break;

            case 4: // Print entire phone list
                if (*root == NULL) {
                    printf("The directory is empty.\n");
                } else {
                    printf("Phone Directory:\n");
                    printInOrder(*root);
                }
                break;

            case 5: // Exit
                printf("Exiting program.\n");
                return;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

int main() {
    Node* root = NULL;

    printf("Welcome to the Phone Directory Management System!\n");
    menu(&root);

    return 0;
}
