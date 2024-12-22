#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the doubly linked list
struct Car {
    char model[50];
    char manufacturer[50];
    float price;
    float engine_capacity;
    struct Car* prev;
    struct Car* next;
};

// Function to create a new car node
struct Car* createCar(char* model, char* manufacturer, float price, float engine_capacity) {
    struct Car* newCar = (struct Car*)malloc(sizeof(struct Car));
    strcpy(newCar->model, model);
    strcpy(newCar->manufacturer, manufacturer);
    newCar->price = price;
    newCar->engine_capacity = engine_capacity;
    newCar->prev = NULL;
    newCar->next = NULL;
    return newCar;
}

// Function to insert a car at the end of the list
void insertCar(struct Car** head, char* model, char* manufacturer, float price, float engine_capacity) {
    struct Car* newCar = createCar(model, manufacturer, price, engine_capacity);
    if (*head == NULL) {
        *head = newCar;
        return;
    }
    struct Car* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newCar;
    newCar->prev = temp;
}

// Function to delete a car by model
void deleteCar(struct Car** head, char* model) {
    struct Car* temp = *head;
    while (temp != NULL && strcmp(temp->model, model) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Car model '%s' not found.\n", model);
        return;
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
    printf("Car model '%s' deleted successfully.\n", model);
}

// Function to update the price of a car
void updatePrice(struct Car* head, char* model, float newPrice) {
    struct Car* temp = head;
    while (temp != NULL && strcmp(temp->model, model) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Car model '%s' not found.\n", model);
        return;
    }
    temp->price = newPrice;
    printf("Price of car model '%s' updated to %.2f.\n", model, newPrice);
}

// Function to list all cars within a specified price range
void listCarsByPriceRange(struct Car* head, float minPrice, float maxPrice) {
    struct Car* temp = head;
    int found = 0;
    printf("\nCars within price range %.2f to %.2f:\n", minPrice, maxPrice);
    while (temp != NULL) {
        if (temp->price >= minPrice && temp->price <= maxPrice) {
            printf("Model: %s, Manufacturer: %s, Price: %.2f, Engine Capacity: %.2fL\n", 
                temp->model, temp->manufacturer, temp->price, temp->engine_capacity);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No cars found in the specified price range.\n");
    }
}

// Function to display details of a car given its model
void displayCarDetails(struct Car* head, char* model) {
    struct Car* temp = head;
    while (temp != NULL && strcmp(temp->model, model) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Car model '%s' not found.\n", model);
        return;
    }
    printf("\nDetails of car model '%s':\n", model);
    printf("Model: %s\nManufacturer: %s\nPrice: %.2f\nEngine Capacity: %.2fL\n", 
        temp->model, temp->manufacturer, temp->price, temp->engine_capacity);
}

// Function to display all cars
void displayAllCars(struct Car* head) {
    if (head == NULL) {
        printf("No cars available.\n");
        return;
    }
    struct Car* temp = head;
    printf("\nAll Cars:\n");
    while (temp != NULL) {
        printf("Model: %s, Manufacturer: %s, Price: %.2f, Engine Capacity: %.2fL\n", 
            temp->model, temp->manufacturer, temp->price, temp->engine_capacity);
        temp = temp->next;
    }
}

int main() {
    struct Car* head = NULL;
    int choice;
    char model[50], manufacturer[50];
    float price, engine_capacity, minPrice, maxPrice;

    do {
        printf("\nMenu:\n");
        printf("1. Insert New Car\n");
        printf("2. Delete Obsolete Car\n");
        printf("3. Update Car Price\n");
        printf("4. List Cars by Price Range\n");
        printf("5. Display Car Details\n");
        printf("6. Display All Cars\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Model: ");
                scanf("%s", model);
                printf("Enter Manufacturer: ");
                scanf("%s", manufacturer);
                printf("Enter Price: ");
                scanf("%f", &price);
                printf("Enter Engine Capacity (in L): ");
                scanf("%f", &engine_capacity);
                insertCar(&head, model, manufacturer, price, engine_capacity);
                break;

            case 2:
                printf("Enter Model to Delete: ");
                scanf("%s", model);
                deleteCar(&head, model);
                break;

            case 3:
                printf("Enter Model to Update Price: ");
                scanf("%s", model);
                printf("Enter New Price: ");
                scanf("%f", &price);
                updatePrice(head, model, price);
                break;

            case 4:
                printf("Enter Minimum Price: ");
                scanf("%f", &minPrice);
                printf("Enter Maximum Price: ");
                scanf("%f", &maxPrice);
                listCarsByPriceRange(head, minPrice, maxPrice);
                break;

            case 5:
                printf("Enter Model to Display Details: ");
                scanf("%s", model);
                displayCarDetails(head, model);
                break;

            case 6:
                displayAllCars(head);
                break;

            case 7:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    // Free memory
    while (head != NULL) {
        struct Car* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
