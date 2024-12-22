#include <stdio.h>
#include <string.h>

#define MAX 5  // Maximum number of students in the database

// Define a structure for storing student details
struct Student {
    int roll_no;
    char name[50];
    float percentage;
};

// Function to perform binary search on the student database by roll number
int binarySearch(struct Student students[], int left, int right, int roll_no) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if roll_no is present at mid
        if (students[mid].roll_no == roll_no) {
            return mid;  // Return the index of the student
        }

        // If roll_no is greater, ignore the left half
        if (students[mid].roll_no < roll_no) {
            left = mid + 1;
        }
        // If roll_no is smaller, ignore the right half
        else {
            right = mid - 1;
        }
    }

    return -1;  // Return -1 if the student is not found
}

// Function to display student details
void displayStudent(struct Student s) {
    printf("Roll No: %d\n", s.roll_no);
    printf("Name: %s\n", s.name);
    printf("Percentage: %.2f\n\n", s.percentage);
}

int main() {
    // Declare an array of students and initialize their details
    struct Student students[MAX] = {
        {101, "John Doe", 85.5},
        {102, "Jane Smith", 92.3},
        {103, "Alice Johnson", 78.4},
        {104, "Bob Brown", 88.2},
        {105, "Charlie Davis", 90.1}
    };

    // Sort students based on their roll number using a simple bubble sort
    for (int i = 0; i < MAX - 1; i++) {
        for (int j = 0; j < MAX - i - 1; j++) {
            if (students[j].roll_no > students[j + 1].roll_no) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    int roll_no_to_search;
    printf("Enter roll number to search: ");
    scanf("%d", &roll_no_to_search);

    // Perform binary search
    int result = binarySearch(students, 0, MAX - 1, roll_no_to_search);

    if (result != -1) {
        printf("\nStudent found:\n");
        displayStudent(students[result]);
    } else {
        printf("Student with roll number %d not found.\n", roll_no_to_search);
    }

    return 0;
}
