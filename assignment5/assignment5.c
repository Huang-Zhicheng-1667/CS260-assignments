#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a node in the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the correct position in the linked list
void insertNode(Node** head, int value) {
    Node* newNode = createNode(value);
    if (*head == NULL || (*head)->data >= newNode->data) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL && current->next->data < newNode->data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to search for a value in the linked list (linear search)
Node* search(Node* head, int value) {
    Node* current = head;
    while (current != NULL && current->data != value) {
        current = current->next;
    }
    return current;
}

// Function to print the linked list
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    // Create a linked list
    Node* head = NULL;
    
    // Insert elements into the linked list
    insertNode(&head, 5);
    insertNode(&head, 2);
    insertNode(&head, 8);
    insertNode(&head, 1);
    insertNode(&head, 9);
    
    // Print the linked list
    printf("Linked List: ");
    printList(head);
    
    // Search for elements in the linked list
    int searchValue = 8;
    Node* result = search(head, searchValue);
    if (result != NULL) {
        printf("%d found in the linked list.\n", searchValue);
    } else {
        printf("%d not found in the linked list.\n", searchValue);
    }

    return 0;
}
