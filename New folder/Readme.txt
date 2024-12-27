1.Write a program to represent sparse matrix using array and perform simple and fast transpose

#include <stdio.h>

 

#define MAX_ELEMENTS 100

 

// Structure to store a non-zero element of the matrix

typedef struct {

    int row;

    int col;

    int value;

} SparseElement;

 

// Function to perform sparse matrix transpose

void fastTranspose(SparseElement matrix[], int *numElements, SparseElement transposed[], int numRows, int numCols) {

    int count[MAX_ELEMENTS] = {0}; // Count the number of elements in each column

    int pos[MAX_ELEMENTS]; // Position of each element in the transposed matrix

   

    // Count non-zero elements in each column

    for (int i = 0; i < *numElements; i++) {

        count[matrix[i].col]++;

    }

   

    // Calculate position of each element in transposed matrix

    pos[0] = 0;

    for (int i = 1; i < numCols; i++) {

        pos[i] = pos[i - 1] + count[i - 1];

    }

   

    // Fill the transposed matrix using the calculated positions

    for (int i = 0; i < *numElements; i++) {

        int j = matrix[i].col;

        transposed[pos[j]].row = matrix[i].col;

        transposed[pos[j]].col = matrix[i].row;

        transposed[pos[j]].value = matrix[i].value;

        pos[j]++;

    }

}

 

// Function to display a sparse matrix

void displaySparseMatrix(SparseElement matrix[], int numElements) {

    for (int i = 0; i < numElements; i++) {

        printf("Row: %d, Col: %d, Value: %d\n", matrix[i].row, matrix[i].col, matrix[i].value);

    }

}

 

int main() {

    int numRows, numCols, numElements;

    SparseElement matrix[MAX_ELEMENTS];

    SparseElement transposed[MAX_ELEMENTS];

   

    // Input matrix dimensions and non-zero elements

    printf("Enter the number of rows and columns of the matrix: ");

    scanf("%d %d", &numRows, &numCols);

   

    printf("Enter the number of non-zero elements: ");

    scanf("%d", &numElements);

   

    printf("Enter the non-zero elements (row, column, value):\n");

    for (int i = 0; i < numElements; i++) {

        scanf("%d %d %d", &matrix[i].row, &matrix[i].col, &matrix[i].value);

    }

   

    printf("\nOriginal Sparse Matrix:\n");

    displaySparseMatrix(matrix, numElements);

   

    // Perform fast transpose

    fastTranspose(matrix, &numElements, transposed, numRows, numCols);

   

    printf("\nTransposed Sparse Matrix:\n");

    displaySparseMatrix(transposed, numElements);

   

    return 0;

}

 

 

 

2 Write a menu-driven program that utilizes a singly linked list to handle operations such as adding, removing, and displaying books, as well as searching for specific books and counting the total number of books available.

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

 

// Define structure for Book

typedef struct Book {

    char title[100];

    char author[100];

    struct Book* next;

} Book;

 

// Function to create a new book node

Book* createBook(char title[], char author[]) {

    Book* newBook = (Book*)malloc(sizeof(Book));

    strcpy(newBook->title, title);

    strcpy(newBook->author, author);

    newBook->next = NULL;

    return newBook;

}

 

// Function to add a book to the list

void addBook(Book** head, char title[], char author[]) {

    Book* newBook = createBook(title, author);

    if (*head == NULL) {

        *head = newBook;

    } else {

        Book* temp = *head;

        while (temp->next != NULL) {

            temp = temp->next;

        }

        temp->next = newBook;

    }

    printf("Book added successfully.\n");

}

 

// Function to remove a book by title

void removeBook(Book** head, char title[]) {

    if (*head == NULL) {

        printf("The list is empty.\n");

        return;

    }

    Book* temp = *head;

    Book* prev = NULL;

   

    // Check if the book is the first one

    if (strcmp(temp->title, title) == 0) {

        *head = temp->next;

        free(temp);

        printf("Book removed successfully.\n");

        return;

    }

   

    // Search for the book to remove

    while (temp != NULL && strcmp(temp->title, title) != 0) {

        prev = temp;

        temp = temp->next;

    }

 

    // If the book is not found

    if (temp == NULL) {

        printf("Book not found.\n");

        return;

    }

 

    prev->next = temp->next;

    free(temp);

    printf("Book removed successfully.\n");

}

 

// Function to display all books

void displayBooks(Book* head) {

    if (head == NULL) {

        printf("No books available.\n");

        return;

    }

    Book* temp = head;

    while (temp != NULL) {

        printf("Title: %s\n", temp->title);

        printf("Author: %s\n\n", temp->author);

        temp = temp->next;

    }

}

 

// Function to search for a book by title

void searchBook(Book* head, char title[]) {

    Book* temp = head;

    while (temp != NULL) {

        if (strcmp(temp->title, title) == 0) {

            printf("Book found!\n");

            printf("Title: %s\n", temp->title);

            printf("Author: %s\n\n", temp->author);

            return;

        }

        temp = temp->next;

    }

    printf("Book not found.\n");

}

 

// Function to count total number of books

int countBooks(Book* head) {

    int count = 0;

    Book* temp = head;

    while (temp != NULL) {

        count++;

        temp = temp->next;

    }

    return count;

}

 

int main() {

    Book* head = NULL; // Initialize the head of the linked list

    int choice;

    char title[100], author[100];

 

    do {

        printf("\nMenu:\n");

        printf("1. Add Book\n");

        printf("2. Remove Book\n");

        printf("3. Display All Books\n");

        printf("4. Search for a Book\n");

        printf("5. Count Total Books\n");

        printf("6. Exit\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);

        getchar(); // To consume the newline character left by scanf

       

        switch (choice) {

            case 1:

                printf("Enter book title: ");

                fgets(title, sizeof(title), stdin);

                title[strcspn(title, "\n")] = 0;  // Remove the newline character

                printf("Enter book author: ");

                fgets(author, sizeof(author), stdin);

                author[strcspn(author, "\n")] = 0;

                addBook(&head, title, author);

                break;

            case 2:

                printf("Enter book title to remove: ");

                fgets(title, sizeof(title), stdin);

                title[strcspn(title, "\n")] = 0;

                removeBook(&head, title);

                break;

            case 3:

                displayBooks(head);

                break;

            case 4:

                printf("Enter book title to search: ");

                fgets(title, sizeof(title), stdin);

                title[strcspn(title, "\n")] = 0;

                searchBook(head, title);

                break;

            case 5:

                printf("Total number of books: %d\n", countBooks(head));

                break;

            case 6:

                printf("Exiting...\n");

                break;

            default:

                printf("Invalid choice. Please try again.\n");

        }

    } while (choice != 6);

 

    return 0;

}

 

 

 

 

3 Write a menu driven program which will maintain a list of car models, their price, name of the manufacture, engine capacity etc. as a doubly linked list. The menu should make provisions for inserting information pertaining to new car models, delete obsolete models, update data such as price besides answering queries such as listing all car models within a price range specified by the client and listing all details given a car model

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

 

struct Car {

    char modelName[50];

    char manufacturer[50];

    float price;

    float engineCapacity;

    struct Car* next;

    struct Car* prev;

};

 

typedef struct Car Car;

 

Car* head = NULL;

 

void insertCar();

void deleteCar();

void updatePrice();

void listCarsInPriceRange();

void listCarDetails();

void displayCars();

Car* createCarNode();

 

int main() {

    int choice;

 

    while (1) {

        printf("\nMenu:\n");

        printf("1. Insert a new car model\n");

        printf("2. Delete a car model\n");

        printf("3. Update the price of a car model\n");

        printf("4. List car models within a price range\n");

        printf("5. List details of a car model\n");

        printf("6. Display all cars\n");

        printf("7. Exit\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);

 

        switch (choice) {

            case 1:

                insertCar();

                break;

            case 2:

                deleteCar();

                break;

            case 3:

                updatePrice();

                break;

            case 4:

                listCarsInPriceRange();

                break;

            case 5:

                listCarDetails();

                break;

            case 6:

                displayCars();

                break;

            case 7:

                exit(0);

            default:

                printf("Invalid choice, please try again.\n");

        }

    }

    return 0;

}

 

Car* createCarNode() {

    Car* newCar = (Car*)malloc(sizeof(Car));

    printf("Enter model name: ");

    getchar();  // to consume newline left by previous input

    fgets(newCar->modelName, sizeof(newCar->modelName), stdin);

    newCar->modelName[strcspn(newCar->modelName, "\n")] = 0;  // removing newline character

 

    printf("Enter manufacturer name: ");

    fgets(newCar->manufacturer, sizeof(newCar->manufacturer), stdin);

    newCar->manufacturer[strcspn(newCar->manufacturer, "\n")] = 0;

 

    printf("Enter price: ");

    scanf("%f", &newCar->price);

 

    printf("Enter engine capacity: ");

    scanf("%f", &newCar->engineCapacity);

 

    newCar->next = NULL;

    newCar->prev = NULL;

    return newCar;

}

 

void insertCar() {

    Car* newCar = createCarNode();

 

    if (head == NULL) {

        head = newCar;

    } else {

        Car* temp = head;

        while (temp->next != NULL) {

            temp = temp->next;

        }

        temp->next = newCar;

        newCar->prev = temp;

    }

 

    printf("Car model added successfully.\n");

}

 

void deleteCar() {

    char modelName[50];

    printf("Enter the model name of the car to delete: ");

    getchar();  // to consume newline left by previous input

    fgets(modelName, sizeof(modelName), stdin);

    modelName[strcspn(modelName, "\n")] = 0;

 

    Car* temp = head;

    while (temp != NULL) {

        if (strcmp(temp->modelName, modelName) == 0) {

            if (temp->prev != NULL) {

                temp->prev->next = temp->next;

            } else {

                head = temp->next;

            }

            if (temp->next != NULL) {

                temp->next->prev = temp->prev;

            }

            free(temp);

            printf("Car model deleted successfully.\n");

            return;

        }

        temp = temp->next;

    }

 

    printf("Car model not found.\n");

}

 

void updatePrice() {

    char modelName[50];

    printf("Enter the model name of the car to update price: ");

    getchar();  // to consume newline left by previous input

    fgets(modelName, sizeof(modelName), stdin);

    modelName[strcspn(modelName, "\n")] = 0;

 

    Car* temp = head;

    while (temp != NULL) {

        if (strcmp(temp->modelName, modelName) == 0) {

            printf("Enter new price for %s: ", temp->modelName);

            scanf("%f", &temp->price);

            printf("Price updated successfully.\n");

            return;

        }

        temp = temp->next;

    }

 

    printf("Car model not found.\n");

}

 

void listCarsInPriceRange() {

    float minPrice, maxPrice;

    printf("Enter the minimum price: ");

    scanf("%f", &minPrice);

    printf("Enter the maximum price: ");

    scanf("%f", &maxPrice);

 

    Car* temp = head;

    int found = 0;

    while (temp != NULL) {

        if (temp->price >= minPrice && temp->price <= maxPrice) {

            printf("\nModel: %s\n", temp->modelName);

            printf("Manufacturer: %s\n", temp->manufacturer);

            printf("Price: %.2f\n", temp->price);

            printf("Engine Capacity: %.2f\n", temp->engineCapacity);

            found = 1;

        }

        temp = temp->next;

    }

 

    if (!found) {

        printf("No cars found in the given price range.\n");

    }

}

 

void listCarDetails() {

    char modelName[50];

    printf("Enter the model name of the car to view details: ");

    getchar();  // to consume newline left by previous input

    fgets(modelName, sizeof(modelName), stdin);

    modelName[strcspn(modelName, "\n")] = 0;

 

    Car* temp = head;

    while (temp != NULL) {

        if (strcmp(temp->modelName, modelName) == 0) {

            printf("\nModel: %s\n", temp->modelName);

            printf("Manufacturer: %s\n", temp->manufacturer);

            printf("Price: %.2f\n", temp->price);

            printf("Engine Capacity: %.2f\n", temp->engineCapacity);

            return;

        }

        temp = temp->next;

    }

 

    printf("Car model not found.\n");

}

 

void displayCars() {

    if (head == NULL) {

        printf("No cars to display.\n");

        return;

    }

 

    Car* temp = head;

    while (temp != NULL) {

        printf("\nModel: %s\n", temp->modelName);

        printf("Manufacturer: %s\n", temp->manufacturer);

        printf("Price: %.2f\n", temp->price);

        printf("Engine Capacity: %.2f\n", temp->engineCapacity);

        temp = temp->next;

    }

}

 

 

4 Write a program to implement stack as an ADT. Use this ADT to perform expression conversion and evaluation. (Infix – Postfix)

#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <string.h>

 

#define MAX 100

 

// Stack structure

struct Stack {

    int arr[MAX];

    int top;

};

 

// Stack functions

void initStack(struct Stack* stack) {

    stack->top = -1;

}

 

int isFull(struct Stack* stack) {

    return stack->top == MAX - 1;

}

 

int isEmpty(struct Stack* stack) {

    return stack->top == -1;

}

 

void push(struct Stack* stack, int value) {

    if (isFull(stack)) {

        printf("Stack Overflow\n");

    } else {

        stack->arr[++(stack->top)] = value;

    }

}

 

int pop(struct Stack* stack) {

    if (isEmpty(stack)) {

        printf("Stack Underflow\n");

        return -1; // Error value

    } else {

        return stack->arr[(stack->top)--];

    }

}

 

int peek(struct Stack* stack) {

    if (isEmpty(stack)) {

        return -1; // Error value

    } else {

        return stack->arr[stack->top];

    }

}

 

// Function to check precedence of operators

int precedence(char c) {

    if (c == '+' || c == '-') return 1;

    if (c == '*' || c == '/') return 2;

    return 0;

}

 

// Infix to Postfix conversion

void infixToPostfix(char* infix, char* postfix) {

    struct Stack stack;

    initStack(&stack);

    int i, k = 0;

    for (i = 0; infix[i] != '\0'; i++) {

        char ch = infix[i];

 

        // If operand, add to postfix expression

        if (isalnum(ch)) {

            postfix[k++] = ch;

        }

        // If '(', push to stack

        else if (ch == '(') {

            push(&stack, ch);

        }

        // If ')', pop until '('

        else if (ch == ')') {

            while (!isEmpty(&stack) && peek(&stack) != '(') {

                postfix[k++] = pop(&stack);

            }

            pop(&stack); // Remove '('

        }

        // If operator, pop from stack based on precedence and push the current operator

        else {

            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(ch)) {

                postfix[k++] = pop(&stack);

            }

            push(&stack, ch);

        }

    }

 

    // Pop remaining operators from stack

    while (!isEmpty(&stack)) {

        postfix[k++] = pop(&stack);

    }

    postfix[k] = '\0'; // Null-terminate the string

}

 

// Postfix Evaluation

int evaluatePostfix(char* postfix) {

    struct Stack stack;

    initStack(&stack);

    int i;

    for (i = 0; postfix[i] != '\0'; i++) {

        char ch = postfix[i];

 

        // If operand, push to stack

        if (isalnum(ch)) {

            push(&stack, ch - '0'); // Convert char to int

        }

        // If operator, pop operands and perform operation

        else {

            int b = pop(&stack);

            int a = pop(&stack);

            int result;

 

            switch (ch) {

                case '+': result = a + b; break;

                case '-': result = a - b; break;

                case '*': result = a * b; break;

                case '/': result = a / b; break;

            }

 

            push(&stack, result);

        }

    }

 

    // The result will be the last element in the stack

    return pop(&stack);

}

 

int main() {

    char infix[MAX], postfix[MAX];

   

    // Input infix expression

    printf("Enter an infix expression: ");

    fgets(infix, MAX, stdin);

   

    // Remove newline character from input

    infix[strcspn(infix, "\n")] = '\0';

 

    // Convert infix to postfix

    infixToPostfix(infix, postfix);

    printf("Postfix Expression: %s\n", postfix);

 

    // Evaluate postfix expression

    int result = evaluatePostfix(postfix);

    printf("Evaluation Result: %d\n", result);

 

    return 0;

}

 

 

5 Write a program to manage customer support tickets. Utilize a circular queue implemented using arrays to handle incoming support requests. Each ticket represents a customer support request, ensuring memory-efficient management. Implement features for ticket submission, processing, and displaying the current queue status

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

 

#define MAX_SIZE 5  // Maximum number of tickets in the queue

 

// Structure to represent a support ticket

struct Ticket {

    int id;

    char description[100];

};

 

// Circular Queue structure

struct CircularQueue {

    struct Ticket tickets[MAX_SIZE];

    int front, rear;

};

 

// Function to initialize the queue

void initQueue(struct CircularQueue* queue) {

    queue->front = -1;

    queue->rear = -1;

}

 

// Function to check if the queue is full

int isFull(struct CircularQueue* queue) {

    return (queue->rear + 1) % MAX_SIZE == queue->front;

}

 

// Function to check if the queue is empty

int isEmpty(struct CircularQueue* queue) {

    return queue->front == -1;

}

 

// Function to submit a new support ticket

void submitTicket(struct CircularQueue* queue, int id, const char* description) {

    if (isFull(queue)) {

        printf("Queue is full! Cannot submit new ticket.\n");

        return;

    }

    if (isEmpty(queue)) {

        queue->front = 0;

    }

    queue->rear = (queue->rear + 1) % MAX_SIZE;

    queue->tickets[queue->rear].id = id;

    strncpy(queue->tickets[queue->rear].description, description, sizeof(queue->tickets[queue->rear].description) - 1);

    queue->tickets[queue->rear].description[sizeof(queue->tickets[queue->rear].description) - 1] = '\0';  // Ensure null-termination

    printf("Ticket %d submitted successfully.\n", id);

}

 

// Function to process the next ticket in the queue

void processTicket(struct CircularQueue* queue) {

    if (isEmpty(queue)) {

        printf("No tickets to process.\n");

        return;

    }

    printf("Processing ticket ID: %d\n", queue->tickets[queue->front].id);

    printf("Description: %s\n", queue->tickets[queue->front].description);

    if (queue->front == queue->rear) {

        // If there was only one ticket, reset the queue

        queue->front = queue->rear = -1;

    } else {

        queue->front = (queue->front + 1) % MAX_SIZE;

    }

}

 

// Function to display the current queue status

void displayQueue(struct CircularQueue* queue) {

    if (isEmpty(queue)) {

        printf("Queue is empty.\n");

        return;

    }

    printf("Current Tickets in Queue:\n");

    int i = queue->front;

    while (i != queue->rear) {

        printf("Ticket ID: %d, Description: %s\n", queue->tickets[i].id, queue->tickets[i].description);

        i = (i + 1) % MAX_SIZE;

    }

    printf("Ticket ID: %d, Description: %s\n", queue->tickets[queue->rear].id, queue->tickets[queue->rear].description);

}

 

// Main program

int main() {

    struct CircularQueue queue;

    initQueue(&queue);

 

    int choice, id;

    char description[100];

 

    while (1) {

        printf("\nCustomer Support Ticket System\n");

        printf("1. Submit Ticket\n");

        printf("2. Process Ticket\n");

        printf("3. Display Queue Status\n");

        printf("4. Exit\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);

 

        switch (choice) {

            case 1:

                // Submit Ticket

                printf("Enter Ticket ID: ");

                scanf("%d", &id);

                getchar();  // to consume the newline character left by scanf

                printf("Enter Ticket Description: ");

                fgets(description, sizeof(description), stdin);

                description[strcspn(description, "\n")] = '\0';  // Remove newline character

                submitTicket(&queue, id, description);

                break;

 

            case 2:

                // Process Ticket

                processTicket(&queue);

                break;

 

            case 3:

                // Display Queue Status

                displayQueue(&queue);

                break;

 

            case 4:

                // Exit

                printf("Exiting the program.\n");

                exit(0);

 

            default:

                printf("Invalid choice! Please try again.\n");

        }

    }

 

    return 0;

}

 

 

 

6 Write a program that reads a list of names and telephone numbers from user and insert into a BST tree. Once the tree has been built, present the user with a menu that allows him to search the list for a specified name, insert new name, delete an existing name or print the entire phone list.

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

 

// Define the structure for the node of the BST

typedef struct Node {

    char name[100];

    char phone[20];

    struct Node* left;

    struct Node* right;

} Node;

 

// Function to create a new node

Node* createNode(char name[], char phone[]) {

    Node* newNode = (Node*)malloc(sizeof(Node));

    strcpy(newNode->name, name);

    strcpy(newNode->phone, phone);

    newNode->left = NULL;

    newNode->right = NULL;

    return newNode;

}

 

// Function to insert a new node into the BST

Node* insertNode(Node* root, char name[], char phone[]) {

    if (root == NULL) {

        return createNode(name, phone);

    }

 

    if (strcmp(name, root->name) < 0) {

        root->left = insertNode(root->left, name, phone);

    } else if (strcmp(name, root->name) > 0) {

        root->right = insertNode(root->right, name, phone);

    } else {

        printf("Duplicate entry found. The name already exists.\n");

    }

    return root;

}

 

// Function to search for a name in the BST

Node* searchNode(Node* root, char name[]) {

    if (root == NULL || strcmp(root->name, name) == 0) {

        return root;

    }

 

    if (strcmp(name, root->name) < 0) {

        return searchNode(root->left, name);

    } else {

        return searchNode(root->right, name);

    }

}

 

// Function to find the minimum node in a BST

Node* findMin(Node* root) {

    while (root && root->left != NULL) {

        root = root->left;

    }

    return root;

}

 

// Function to delete a node from the BST

Node* deleteNode(Node* root, char name[]) {

    if (root == NULL) {

        return root;

    }

 

    // Find the node to delete

    if (strcmp(name, root->name) < 0) {

        root->left = deleteNode(root->left, name);

    } else if (strcmp(name, root->name) > 0) {

        root->right = deleteNode(root->right, name);

    } else {

        // Node found, perform deletion

        if (root->left == NULL) {

            Node* temp = root->right;

            free(root);

            return temp;

        } else if (root->right == NULL) {

            Node* temp = root->left;

            free(root);

            return temp;

        }

 

        // Node with two children, get the inorder successor

        Node* temp = findMin(root->right);

 

        // Copy the inorder successor's content to this node

        strcpy(root->name, temp->name);

        strcpy(root->phone, temp->phone);

 

        // Delete the inorder successor

        root->right = deleteNode(root->right, temp->name);

    }

    return root;

}

 

// Function to print the entire phone list (in-order traversal)

void printInOrder(Node* root) {

    if (root == NULL) {

        return;

    }

    printInOrder(root->left);

    printf("Name: %s, Phone: %s\n", root->name, root->phone);

    printInOrder(root->right);

}

 

// Main function to interact with the user

int main() {

    Node* root = NULL;

    int choice;

    char name[100], phone[20];

 

    while (1) {

        printf("\nPhone Directory Menu:\n");

        printf("1. Insert new name\n");

        printf("2. Search for a name\n");

        printf("3. Delete a name\n");

        printf("4. Print entire phone list\n");

        printf("5. Exit\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);

        getchar();  // To consume the newline character

 

        switch (choice) {

            case 1:

                // Insert a new name and phone number

                printf("Enter name: ");

                fgets(name, sizeof(name), stdin);

                name[strcspn(name, "\n")] = '\0';  // Remove newline character

 

                printf("Enter phone number: ");

                fgets(phone, sizeof(phone), stdin);

                phone[strcspn(phone, "\n")] = '\0';  // Remove newline character

 

                root = insertNode(root, name, phone);

                break;

 

            case 2:

                // Search for a name

                printf("Enter name to search: ");

                fgets(name, sizeof(name), stdin);

                name[strcspn(name, "\n")] = '\0';  // Remove newline character

 

                Node* result = searchNode(root, name);

                if (result) {

                    printf("Found: Name: %s, Phone: %s\n", result->name, result->phone);

                } else {

                    printf("Name not found.\n");

                }

                break;

 

            case 3:

                // Delete a name

                printf("Enter name to delete: ");

                fgets(name, sizeof(name), stdin);

                name[strcspn(name, "\n")] = '\0';  // Remove newline character

 

                root = deleteNode(root, name);

                printf("Name %s deleted successfully.\n", name);

                break;

 

            case 4:

                // Print the entire phone list

                printf("Phone Directory:\n");

                printInOrder(root);

                break;

 

            case 5:

                // Exit the program

                printf("Exiting program...\n");

                return 0;

 

            default:

                printf("Invalid choice. Please try again.\n");

        }

    }

 

    return 0;

}

 

 

7 Write a program to create graph, use the map of your city as the graph. Represent graph using adjacency list/adjacency matrix and perform Depth First Search and Breadth First Search.

#include <stdio.h>

#include <stdlib.h>

 

#define MAX_VERTICES 10

 

// Define the structure for an adjacency list node

typedef struct Node {

    int vertex;

    struct Node* next;

} Node;

 

// Define the structure for the graph

typedef struct Graph {

    int numVertices;

    Node* adjList[MAX_VERTICES];

} Graph;

 

// Function to create a new graph

Graph* createGraph(int vertices) {

    Graph* graph = (Graph*)malloc(sizeof(Graph));

    graph->numVertices = vertices;

 

    for (int i = 0; i < vertices; i++) {

        graph->adjList[i] = NULL;

    }

 

    return graph;

}

 

// Function to add an edge to the graph (undirected)

void addEdge(Graph* graph, int src, int dest) {

    // Add edge from src to dest

    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->vertex = dest;

    newNode->next = graph->adjList[src];

    graph->adjList[src] = newNode;

 

    // Add edge from dest to src (since it's undirected)

    newNode = (Node*)malloc(sizeof(Node));

    newNode->vertex = src;

    newNode->next = graph->adjList[dest];

    graph->adjList[dest] = newNode;

}

 

// Function to perform DFS

void DFS(Graph* graph, int startVertex, int visited[]) {

    printf("Visiting vertex %d\n", startVertex);

    visited[startVertex] = 1;

 

    // Traverse the adjacency list of the vertex

    Node* adjList = graph->adjList[startVertex];

    while (adjList != NULL) {

        int connectedVertex = adjList->vertex;

 

        if (!visited[connectedVertex]) {

            DFS(graph, connectedVertex, visited);

        }

        adjList = adjList->next;

    }

}

 

// Function to perform BFS

void BFS(Graph* graph, int startVertex) {

    int visited[MAX_VERTICES] = {0};

    int queue[MAX_VERTICES];

    int front = 0, rear = 0;

 

    // Mark the start vertex as visited and enqueue it

    visited[startVertex] = 1;

    queue[rear++] = startVertex;

 

    while (front < rear) {

        int currentVertex = queue[front++];

        printf("Visiting vertex %d\n", currentVertex);

 

        // Traverse the adjacency list of the current vertex

        Node* adjList = graph->adjList[currentVertex];

        while (adjList != NULL) {

            int connectedVertex = adjList->vertex;

 

            if (!visited[connectedVertex]) {

                visited[connectedVertex] = 1;

                queue[rear++] = connectedVertex;

            }

            adjList = adjList->next;

        }

    }

}

 

// Function to print the adjacency list representation of the graph

void printGraph(Graph* graph) {

    for (int i = 0; i < graph->numVertices; i++) {

        Node* temp = graph->adjList[i];

        printf("\nVertex %d: ", i);

        while (temp) {

            printf("%d -> ", temp->vertex);

            temp = temp->next;

        }

        printf("NULL");

    }

    printf("\n");

}

 

int main() {

    // Create a graph (example city map with 6 locations)

    Graph* graph = createGraph(6);

 

    // Add edges (undirected roads between locations)

    addEdge(graph, 0, 1); // Road between location 0 and 1

    addEdge(graph, 0, 2); // Road between location 0 and 2

    addEdge(graph, 1, 3); // Road between location 1 and 3

    addEdge(graph, 1, 4); // Road between location 1 and 4

    addEdge(graph, 2, 4); // Road between location 2 and 4

    addEdge(graph, 3, 5); // Road between location 3 and 5

    addEdge(graph, 4, 5); // Road between location 4 and 5

 

    // Print the graph

    printf("City Map (Graph Representation):\n");

    printGraph(graph);

 

    // Perform DFS from vertex 0

    printf("\nDepth First Search (DFS) starting from vertex 0:\n");

    int visited[MAX_VERTICES] = {0};

    DFS(graph, 0, visited);

 

    // Perform BFS from vertex 0

    printf("\nBreadth First Search (BFS) starting from vertex 0:\n");

    BFS(graph, 0);

 

    return 0;

}

 

8 Write a program to represent a graph of your city using adjacency matrix /adjacency list. Nodes should represent the various areas in the city and links should represent the distance between them. Find the shortest path of your college from your home using Dijkstra's algorithm

#include <stdio.h>

#include <stdlib.h>

#include <limits.h>

 

#define MAX_VERTICES 10

#define INF INT_MAX

 

// Define a structure for an adjacency list node

typedef struct Node {

    int vertex;

    int weight;

    struct Node* next;

} Node;

 

// Define a structure for the graph

typedef struct Graph {

    int numVertices;

    Node* adjList[MAX_VERTICES];

} Graph;

 

// Function to create a new graph

Graph* createGraph(int vertices) {

    Graph* graph = (Graph*)malloc(sizeof(Graph));

    graph->numVertices = vertices;

 

    for (int i = 0; i < vertices; i++) {

        graph->adjList[i] = NULL;

    }

 

    return graph;

}

 

// Function to add an edge to the graph

void addEdge(Graph* graph, int src, int dest, int weight) {

    // Add edge from src to dest

    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->vertex = dest;

    newNode->weight = weight;

    newNode->next = graph->adjList[src];

    graph->adjList[src] = newNode;

 

    // Add edge from dest to src (since the graph is undirected)

    newNode = (Node*)malloc(sizeof(Node));

    newNode->vertex = src;

    newNode->weight = weight;

    newNode->next = graph->adjList[dest];

    graph->adjList[dest] = newNode;

}

 

// Function to find the vertex with the minimum distance that is not yet visited

int minDistance(int dist[], int visited[], int vertices) {

    int min = INF, minIndex;

 

    for (int v = 0; v < vertices; v++) {

        if (!visited[v] && dist[v] <= min) {

            min = dist[v];

            minIndex = v;

        }

    }

 

    return minIndex;

}

 

// Dijkstra's algorithm to find the shortest path from the source vertex

void dijkstra(Graph* graph, int startVertex, int dist[], int prev[]) {

    int visited[MAX_VERTICES] = {0};

 

    for (int i = 0; i < graph->numVertices; i++) {

        dist[i] = INF;

        prev[i] = -1;

    }

 

    dist[startVertex] = 0;

 

    for (int count = 0; count < graph->numVertices - 1; count++) {

        int u = minDistance(dist, visited, graph->numVertices);

        visited[u] = 1;

 

        // Update the distance value of the adjacent vertices of the picked vertex

        Node* adjList = graph->adjList[u];

        while (adjList != NULL) {

            int v = adjList->vertex;

            if (!visited[v] && dist[u] != INF && dist[u] + adjList->weight < dist[v]) {

                dist[v] = dist[u] + adjList->weight;

                prev[v] = u;

            }

            adjList = adjList->next;

        }

    }

}

 

// Function to print the shortest path from source to destination

void printPath(int prev[], int j) {

    if (prev[j] == -1) {

        printf("%d ", j);

        return;

    }

    printPath(prev, prev[j]);

    printf("-> %d ", j);

}

 

// Function to print the shortest distance and path

void printSolution(int dist[], int prev[], int vertices, int startVertex, int endVertex) {

    printf("Shortest distance from %d to %d is: %d\n", startVertex, endVertex, dist[endVertex]);

    printf("Shortest path: ");

    printPath(prev, endVertex);

    printf("\n");

}

 

int main() {

    Graph* graph = createGraph(6); // Let's assume 6 areas in the city

 

    // Add roads (edges) with distances

    addEdge(graph, 0, 1, 10); // Home -> Area 1

    addEdge(graph, 0, 2, 15); // Home -> Area 2

    addEdge(graph, 1, 2, 5);  // Area 1 -> Area 2

    addEdge(graph, 1, 3, 20); // Area 1 -> College

    addEdge(graph, 2, 3, 10); // Area 2 -> College

    addEdge(graph, 3, 4, 30); // College -> Area 4

    addEdge(graph, 4, 5, 5);  // Area 4 -> Area 5

    addEdge(graph, 3, 5, 10); // College -> Area 5

 

    int dist[MAX_VERTICES];

    int prev[MAX_VERTICES];

 

    // Perform Dijkstra's algorithm from Home (0) to College (3)

    dijkstra(graph, 0, dist, prev);

 

    // Print the shortest path and distance

    printSolution(dist, prev, graph->numVertices, 0, 3);

 

    return 0;

}

 

 

9 Write a program to create student database. Database contains different fields of student like Roll No, Name and percentage. Search a particular student according to roll number using binary search.

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

 

#define MAX_STUDENTS 100

 

// Define a structure to store student information

typedef struct {

    int rollNo;

    char name[50];

    float percentage;

} Student;

 

// Comparison function for sorting students by roll number

int compare(const void *a, const void *b) {

    return ((Student*)a)->rollNo - ((Student*)b)->rollNo;

}

 

// Binary search function to find a student by roll number

int binarySearch(Student students[], int n, int rollNo) {

    int left = 0, right = n - 1;

 

    // Perform binary search

    while (left <= right) {

        int mid = left + (right - left) / 2;

 

        if (students[mid].rollNo == rollNo) {

            return mid;  // Found the student at index mid

        }

        else if (students[mid].rollNo < rollNo) {

            left = mid + 1;  // Move right

        }

        else {

            right = mid - 1;  // Move left

        }

    }

    return -1;  // Return -1 if the student is not found

}

 

int main() {

    int n, rollNo, result;

    Student students[MAX_STUDENTS];

 

    // Input the number of students

    printf("Enter number of students: ");

    scanf("%d", &n);

 

    // Input student data

    for (int i = 0; i < n; i++) {

        printf("\nEnter details for student %d:\n", i + 1);

        printf("Roll No: ");

        scanf("%d", &students[i].rollNo);

        getchar();  // Consume the newline character left by scanf

        printf("Name: ");

        fgets(students[i].name, 50, stdin);

        students[i].name[strcspn(students[i].name, "\n")] = '\0';  // Remove the trailing newline

        printf("Percentage: ");

        scanf("%f", &students[i].percentage);

    }

 

    // Sort the students by Roll No using qsort

    qsort(students, n, sizeof(Student), compare);

 

    // Input the roll number to search for

    printf("\nEnter Roll No to search for: ");

    scanf("%d", &rollNo);

 

    // Perform binary search

    result = binarySearch(students, n, rollNo);

 

    // Display the result of the search

    if (result != -1) {

        printf("\nStudent found!\n");

        printf("Roll No: %d\n", students[result].rollNo);

        printf("Name: %s\n", students[result].name);

        printf("Percentage: %.2f\n", students[result].percentage);

    } else {

        printf("\nStudent with Roll No %d not found.\n", rollNo);

    }

 

    return 0;

}

 

 

10 Write a program to arrange list of students to find out first ten toppers from a class using Bubble sort. (refer the student database given in assignment 10)

#include <stdio.h>

#include <string.h>

 

#define MAX_STUDENTS 100

 

// Define a structure to store student information

typedef struct {

    int rollNo;

    char name[50];

    float percentage;

} Student;

 

// Function to swap two students

void swap(Student *a, Student *b) {

    Student temp = *a;

    *a = *b;

    *b = temp;

}

 

// Bubble sort function to sort students based on percentage in descending order

void bubbleSort(Student students[], int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - 1 - i; j++) {

            if (students[j].percentage < students[j + 1].percentage) {

                swap(&students[j], &students[j + 1]);

            }

        }

    }

}

 

int main() {

    int n;

 

    // Input the number of students

    printf("Enter number of students: ");

    scanf("%d", &n);

 

    // Ensure there are enough students to find the top 10

    if (n < 10) {

        printf("There are fewer than 10 students. Please input at least 10 students.\n");

        return 1;

    }

 

    Student students[MAX_STUDENTS];

 

    // Input student data

    for (int i = 0; i < n; i++) {

        printf("\nEnter details for student %d:\n", i + 1);

        printf("Roll No: ");

        scanf("%d", &students[i].rollNo);

        getchar();  // Consume the newline character left by scanf

        printf("Name: ");

        fgets(students[i].name, 50, stdin);

        students[i].name[strcspn(students[i].name, "\n")] = '\0';  // Remove the trailing newl12ine

        printf("Percentage: ");

        scanf("%f", &students[i].percentage);

    }

 

    // Sort the students by percentage using Bubble Sort

    bubbleSort(students, n);

 

    // Display the top 10 students

    printf("\nTop 10 Toppers:\n");

    for (int i = 0; i < 10 && i < n; i++) {

        printf("\nRank %d:\n", i + 1);

        printf("Roll No: %d\n", students[i].rollNo);

        printf("Name: %s\n", students[i].name);

        printf("Percentage: %.2f\n", students[i].percentage);

    }

 

    return 0;

}

 

 

11 Write a program to sort a list of sales data for a retail company. Each record represents a sale and contains the following information: sales ID, customer name, product name, quantity sold, and total sale amount. sort the sales data based on the total sale amount in descending order using the Merge Sort algorithm. / Quick sort method

#include <stdio.h>

#include <string.h>

 

#define MAX_SALES 100

 

// Structure to represent sales data

typedef struct {

    int salesID;

    char customerName[50];

    char productName[50];

    int quantitySold;

    float totalSaleAmount;

} Sale;

 

// Function to merge two halves in Merge Sort

void merge(Sale sales[], int left, int mid, int right) {

    int n1 = mid - left + 1;

    int n2 = right - mid;

   

    // Temporary arrays

    Sale leftArray[n1], rightArray[n2];

   

    // Copy data to temporary arrays

    for (int i = 0; i < n1; i++)

        leftArray[i] = sales[left + i];

    for (int i = 0; i < n2; i++)

        rightArray[i] = sales[mid + 1 + i];

   

    int i = 0, j = 0, k = left;

   

    // Merge the two arrays

    while (i < n1 && j < n2) {

        if (leftArray[i].totalSaleAmount > rightArray[j].totalSaleAmount) {

            sales[k] = leftArray[i];

            i++;

        } else {

            sales[k] = rightArray[j];

            j++;

        }

        k++;

    }

 

    // Copy remaining elements from leftArray, if any

    while (i < n1) {

        sales[k] = leftArray[i];

        i++;

        k++;

    }

 

    // Copy remaining elements from rightArray, if any

    while (j < n2) {

        sales[k] = rightArray[j];

        j++;

        k++;

    }

}

 

// Merge Sort function to sort sales by total sale amount in descending order

void mergeSort(Sale sales[], int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;

       

        // Recursively sort the two halves

        mergeSort(sales, left, mid);

        mergeSort(sales, mid + 1, right);

       

        // Merge the sorted halves

        merge(sales, left, mid, right);

    }

}

 

// Function to perform partitioning for Quick Sort

int partition(Sale sales[], int low, int high) {

    float pivot = sales[high].totalSaleAmount;

    int i = low - 1;

   

    for (int j = low; j < high; j++) {

        if (sales[j].totalSaleAmount > pivot) {

            i++;

            Sale temp = sales[i];

            sales[i] = sales[j];

            sales[j] = temp;

        }

    }

   

    Sale temp = sales[i + 1];

    sales[i + 1] = sales[high];

    sales[high] = temp;

   

    return (i + 1);

}

 

// Quick Sort function to sort sales by total sale amount in descending order

void quickSort(Sale sales[], int low, int high) {

    if (low < high) {

        int pi = partition(sales, low, high);

       

        // Recursively sort the two parts

        quickSort(sales, low, pi - 1);

        quickSort(sales, pi + 1, high);

    }

}

 

// Function to display the sales data

void displaySales(Sale sales[], int n) {

    printf("\nSales ID\tCustomer Name\tProduct Name\tQuantity Sold\tTotal Sale Amount\n");

    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {

        printf("%d\t\t%s\t\t%s\t\t%d\t\t%.2f\n",

            sales[i].salesID,

            sales[i].customerName,

            sales[i].productName,

            sales[i].quantitySold,

            sales[i].totalSaleAmount);

    }

}

 

int main() {

    int n;

   

    // Input the number of sales records

    printf("Enter number of sales records: ");

    scanf("%d", &n);

 

    Sale sales[MAX_SALES];

 

    // Input sales data

    for (int i = 0; i < n; i++) {

        printf("\nEnter details for sale %d:\n", i + 1);

        printf("Sales ID: ");

        scanf("%d", &sales[i].salesID);

        getchar();  // Consume the newline character left by scanf

        printf("Customer Name: ");

        fgets(sales[i].customerName, 50, stdin);

        sales[i].customerName[strcspn(sales[i].customerName, "\n")] = '\0';  // Remove newline character

        printf("Product Name: ");

        fgets(sales[i].productName, 50, stdin);

        sales[i].productName[strcspn(sales[i].productName, "\n")] = '\0';  // Remove newline character

        printf("Quantity Sold: ");

        scanf("%d", &sales[i].quantitySold);

        printf("Total Sale Amount: ");

        scanf("%f", &sales[i].totalSaleAmount);

    }

 

    // Sort using Merge Sort

    printf("\nSorting sales data using Merge Sort...\n");

    mergeSort(sales, 0, n - 1);

    displaySales(sales, n);

 

    // Sort using Quick Sort

    printf("\nSorting sales data using Quick Sort...\n");

    quickSort(sales, 0, n - 1);

    displaySales(sales, n);

 

    return 0;

}

 