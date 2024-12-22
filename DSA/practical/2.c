#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the singly linked list
struct Book {
    int id;
    char title[100];
    struct Book* next;
};

// Function to add a book to the list
void addBook(struct Book** head, int id, char* title) {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    newBook->next = NULL;

    if (*head == NULL) {
        *head = newBook;
    } else {
        struct Book* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
    printf("Book added successfully.\n");
}

// Function to remove a book by ID
void removeBook(struct Book** head, int id) {
    struct Book* temp = *head;
    struct Book* prev = NULL;

    if (temp != NULL && temp->id == id) {
        *head = temp->next;
        free(temp);
        printf("Book removed successfully.\n");
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Book with ID %d not found.\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Book removed successfully.\n");
}

// Function to display all books
void displayBooks(struct Book* head) {
    if (head == NULL) {
        printf("No books available.\n");
        return;
    }

    printf("\nBooks List:\n");
    while (head != NULL) {
        printf("ID: %d, Title: %s\n", head->id, head->title);
        head = head->next;
    }
}

// Function to search for a book by ID
void searchBook(struct Book* head, int id) {
    while (head != NULL) {
        if (head->id == id) {
            printf("Book found: ID: %d, Title: %s\n", head->id, head->title);
            return;
        }
        head = head->next;
    }
    printf("Book with ID %d not found.\n", id);
}

// Function to count total number of books
void countBooks(struct Book* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    printf("Total number of books: %d\n", count);
}

int main() {
    struct Book* head = NULL;
    int choice, id;
    char title[100];

    do {
        printf("\nMenu:\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Display Books\n");
        printf("4. Search Book\n");
        printf("5. Count Books\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Book ID: ");
                scanf("%d", &id);
                getchar(); // Consume newline
                printf("Enter Book Title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0'; // Remove trailing newline
                addBook(&head, id, title);
                break;
            case 2:
                printf("Enter Book ID to remove: ");
                scanf("%d", &id);
                removeBook(&head, id);
                break;
            case 3:
                displayBooks(head);
                break;
            case 4:
                printf("Enter Book ID to search: ");
                scanf("%d", &id);
                searchBook(head, id);
                break;
            case 5:
                countBooks(head);
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    // Clean up memory
    while (head != NULL) {
        struct Book* toDelete = head;
        head = head->next;
        free(toDelete);
    }

    return 0;
}
