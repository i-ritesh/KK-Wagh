#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5  // Maximum number of tickets in the queue

// Queue structure to represent the circular queue
typedef struct Queue {
    int front, rear;
    char tickets[MAX][100];  // Array to hold tickets (strings)
} Queue;

// Function to initialize the queue
void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

// Function to check if the queue is full
int isFull(Queue* q) {
    return (q->rear + 1) % MAX == q->front;
}

// Function to check if the queue is empty
int isEmpty(Queue* q) {
    return q->front == -1;
}

// Function to add a ticket to the queue
void submitTicket(Queue* q, char* ticket) {
    if (isFull(q)) {
        printf("Queue is full! Cannot submit new ticket.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    strcpy(q->tickets[q->rear], ticket);
    printf("Ticket submitted: %s\n", ticket);
}

// Function to process (serve) a ticket from the queue
void processTicket(Queue* q) {
    if (isEmpty(q)) {
        printf("No tickets to process.\n");
        return;
    }
    printf("Processing ticket: %s\n", q->tickets[q->front]);
    if (q->front == q->rear) {  // If there's only one ticket left
        q->front = q->rear = -1;  // Reset the queue
    } else {
        q->front = (q->front + 1) % MAX;
    }
}

// Function to display the current status of the queue
void displayQueueStatus(Queue* q) {
    if (isEmpty(q)) {
        printf("No tickets in the queue.\n");
        return;
    }
    printf("Current tickets in the queue:\n");
    int i = q->front;
    while (i != q->rear) {
        printf("%s\n", q->tickets[i]);
        i = (i + 1) % MAX;
    }
    printf("%s\n", q->tickets[q->rear]);  // Print the last ticket
}

int main() {
    Queue q;
    initQueue(&q);

    int choice;
    char ticket[100];

    while (1) {
        printf("\nCustomer Support Ticket Management\n");
        printf("1. Submit Ticket\n");
        printf("2. Process Ticket\n");
        printf("3. Display Queue Status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline character after entering the choice

        switch (choice) {
            case 1:
                printf("Enter the ticket description: ");
                fgets(ticket, sizeof(ticket), stdin);
                ticket[strcspn(ticket, "\n")] = '\0';  // Remove the newline character
                submitTicket(&q, ticket);
                break;
            case 2:
                processTicket(&q);
                break;
            case 3:
                displayQueueStatus(&q);
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
