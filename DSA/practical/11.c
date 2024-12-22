#include <stdio.h>
#include <string.h>

#define MAX 5  // Number of sales records

// Define a structure for storing sales data
struct SalesData {
    int sales_id;
    char customer_name[50];
    char product_name[50];
    int quantity_sold;
    float total_sale_amount;
};

// Merge Sort function
void merge(struct SalesData arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct SalesData leftArr[n1], rightArr[n2];

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    // Merge the temp arrays back into the original array
    while (i < n1 && j < n2) {
        if (leftArr[i].total_sale_amount >= rightArr[j].total_sale_amount) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    // Copy the remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k++] = leftArr[i++];
    }

    // Copy the remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k++] = rightArr[j++];
    }
}

// Recursive function to sort the array using Merge Sort
void mergeSort(struct SalesData arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort the first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Quick Sort partition function
int partition(struct SalesData arr[], int low, int high) {
    float pivot = arr[high].total_sale_amount;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // If current element is greater than or equal to pivot
        if (arr[j].total_sale_amount >= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            struct SalesData temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swap arr[i + 1] and arr[high] (pivot)
    struct SalesData temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

// Quick Sort recursive function
void quickSort(struct SalesData arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to display sales data
void displaySales(struct SalesData s) {
    printf("Sales ID: %d\n", s.sales_id);
    printf("Customer Name: %s\n", s.customer_name);
    printf("Product Name: %s\n", s.product_name);
    printf("Quantity Sold: %d\n", s.quantity_sold);
    printf("Total Sale Amount: %.2f\n\n", s.total_sale_amount);
}

int main() {
    // Declare an array of sales records and initialize their details
    struct SalesData sales[MAX] = {
        {101, "John Doe", "Laptop", 2, 1500.50},
        {102, "Jane Smith", "Phone", 3, 1200.75},
        {103, "Alice Johnson", "Tablet", 5, 2200.60},
        {104, "Bob Brown", "Headphones", 1, 350.40},
        {105, "Charlie Davis", "Smartwatch", 4, 800.30}
    };

    // Choose the sorting method: Merge Sort or Quick Sort
    int choice;
    printf("Choose sorting method:\n1. Merge Sort\n2. Quick Sort\nEnter choice (1/2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Sort the sales data using Merge Sort
        mergeSort(sales, 0, MAX - 1);
        printf("\nSales Data sorted using Merge Sort (by total sale amount):\n");
    } else if (choice == 2) {
        // Sort the sales data using Quick Sort
        quickSort(sales, 0, MAX - 1);
        printf("\nSales Data sorted using Quick Sort (by total sale amount):\n");
    } else {
        printf("Invalid choice!\n");
        return 1;
    }

    // Display the sorted sales data
    for (int i = 0; i < MAX; i++) {
        displaySales(sales[i]);
    }

    return 0;
}
