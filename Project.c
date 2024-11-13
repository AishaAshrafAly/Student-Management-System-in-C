/*
 * Project.c
 *
 *  Created on: Aug 8, 2024
 *      Author: aisha
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure representing a student
struct student {
    int id;
    char name[50];
    int age;
    float GPA;
};

// Structure representing a node in the linked list
struct node {
    struct student data;
    struct node* next;
};

struct node *head = NULL;  // Head of the linked list

void addStudent(const struct student *const ptr) {
    struct node *current = head;

    // Check if the student ID already exists
    while (current != NULL) {
        if (current->data.id == ptr->id) {
            printf("Error: Student with ID %d already exists.\n", ptr->id);
            return;
        }
        current = current->next;
    }

    struct node *link = (struct node*)malloc(sizeof(struct node));
    if (!link) {
        printf("Error: DMA failed.\n");
        return;
    }

    link->data = *ptr;
    link->next = NULL;

    // Insert the new node into the linked list
    if (head == NULL) {
        head = link; // If the list is empty, make the new node the head
    } else {
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = link;
    }

    printf("Student %d was added successfully.\n", ptr->id);
}

void displayStudents(void) {
    struct node *ptr = head;
    printf("[head] => ");

    while (ptr != NULL) {
        printf("ID: %d, Name: %s, Age: %d, GPA: %f => ", ptr->data.id, ptr->data.name, ptr->data.age, ptr->data.GPA);
        ptr = ptr->next;
    }

    printf("[null]\n");
}

void searchStudentByID(int id) {
    struct node *ptr = head;
    // Check if the student ID exists
    while (ptr != NULL) {
        if (ptr->data.id == id) {
        	printf("ID: %d, Name: %s, Age: %d, GPA: %f => \n", ptr->data.id, ptr->data.name, ptr->data.age, ptr->data.GPA);
            return;
        }
        ptr = ptr->next;
    }
        printf("Does not exist \n");
}

void updateStudent(int id) {
    struct node *ptr = head;
    while (ptr != NULL) {
            if (ptr->data.id == id) {
            	printf("Enter new name: ");
				scanf("%s", ptr->data.name);
				printf("Enter new age: ");
				scanf("%d", &ptr->data.age);
				printf("Enter new GPA: ");
				scanf("%f", &ptr->data.GPA);
				printf("Student details updated.\n");
				return;
            }
            ptr = ptr->next;
        }
            printf("Not Found :( \n");
    }

float calculateAverageGPA(void){
	struct node *ptr = head;
	int counter = 0;
	float average = 0;
	while( ptr != NULL){
		average += ptr -> data.GPA;
		counter++;
		ptr = ptr-> next;
	}
	average/=counter;
	return average;
}

void searchHighestGPA(void){
	if (head == NULL) {
        printf("The list is empty. No students to display :(.\n");
        return;
    }
	struct node *ptr = head;
	struct node *high = head;
	while( ptr != NULL){
		if(ptr->data.GPA > high ->data.GPA){
			high = ptr;
		}
		ptr = ptr -> next;
	}
	printf("Student with the highest GPA:\n");
	printf("ID: %d\n", high->data.id);
	printf("Name: %s\n", high->data.name);
	printf("Age: %d\n", high->data.age);
	printf("GPA: %.2f\n", high->data.GPA);
}


void deleteStudent(int id) {
    if (head == NULL) {
        printf("No students found.\n");
        return;
    }

    struct node *ptr = head;

    if (ptr->data.id == id) {
        head = ptr->next;
        free(ptr);
        printf("Student with ID %d deleted.\n", id);
        return;
    }

    while (ptr->next != NULL && ptr->next->data.id != id) {
        ptr = ptr->next;
    }

    // If the student was not found in the list
    if (ptr->next == NULL) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    // Student found, now delete it
    struct node *temp = ptr->next;
    ptr->next = temp->next;
    free(temp);
    printf("Student with ID %d deleted.\n", id);
}


int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
    int choice;
    struct student s1 = {1, "Aisha", 20, 3.7};
    struct student s2 = {2, "Mohamed", 21, 3.6};
    struct student s3 = {3, "Ahmed", 22, 3.5};


    while (1) {
        printf("Please choose:\n");
        printf("1. Add a student.\n");
        printf("2. Display all students.\n");
        printf("3. Search for a student by ID.\n");
        printf("4. Update Student Information.\n");
        printf("5. Delete a student.\n");
        printf("6. Calculate average GPA.\n");
        printf("7. Find student with highest GPA.\n");
        printf("8. Exit.\n");
        fflush(stdout);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(&s1);
                addStudent(&s2);
                addStudent(&s1);
                break;
            case 2:
            	displayStudents();
                break;
            case 3:
            	searchStudentByID(2);
            	searchStudentByID(3);
                break;
            case 4:
            	updateStudent(1);
                break;
            case 5:
            	deleteStudent(1);
                break;
            case 6:
            	printf("%f \n", calculateAverageGPA());
                break;
            case 7:
            	searchHighestGPA();
                break;
            case 8:
                return 0;
            default:
                printf("Invalid Input\n");
                break;
        }
    }

    return 0;
}
