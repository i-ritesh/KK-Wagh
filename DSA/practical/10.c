#include <stdio.h>
#include <string.h>

#define MAX 15  // Maximum number of students in the database

// Define a structure for storing student details
struct Student {
    int roll_no;
    char name[50];
    float percentage;
};

// Function to perform Bubble Sort on the student list based on percentage
void bubbleSort(struct Student students[], int n) {
    struct Student temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Sort in descending order based on percentage
            if (students[j].percentage < students[j + 1].percentage) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
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
        {105, "Charlie Davis", 90.1},
        {106, "Eve White", 91.5},
        {107, "Tom Black", 79.8},
        {108, "Lucy Green", 87.6},
        {109, "Jack Blue", 82.4},
        {110, "Sophie Gray", 93.2},
        {111, "Paul King", 76.8},
        {112, "Mia Queen", 94.1},
        {113, "Liam Prince", 89.5},
        {114, "Emma Knight", 81.3},
        {115, "Oliver Tiger", 80.7}
    };

    // Sort students based on their percentage
    bubbleSort(students, MAX);

    // Display the top 10 students
    printf("Top 10 Students based on Percentage:\n");
    printf("------------------------------------\n");
    for (int i = 0; i < 10 && i < MAX; i++) {
        displayStudent(students[i]);
    }

    return 0;
}
