#include <stdio.h>
#include <stdlib.h>

// Define a node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define the linked list structure
typedef struct {
    Node* head;
} LinkedList;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize a linked list
void initList(LinkedList* list) {
    list->head = NULL;
}

// Function to add a value to a given position in the list
void add(LinkedList* list, int value, int position) {
    Node* newNode = createNode(value);
    if (position == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* current = list->head;
        for (int i = 0; i < position - 1 && current != NULL; i++) {
            current = current->next;
        }
        if (current == NULL) {
            printf("Invalid position\n");
            return;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to remove a value from a given position and return it
int removeValue(LinkedList* list, int position) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    Node* temp;
    if (position == 0) {
        temp = list->head;
        list->head = list->head->next;
    } else {
        Node* current = list->head;
        for (int i = 0; i < position - 1 && current != NULL; i++) {
            current = current->next;
        }
        if (current == NULL || current->next == NULL) {
            printf("Invalid position\n");
            return -1;
        }
        temp = current->next;
        current->next = current->next->next;
    }
    int removedValue = temp->data;
    free(temp);
    return removedValue;
}

// Function to get a value from a given position without removing it
int getValue(LinkedList* list, int position) {
    Node* current = list->head;
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Invalid position\n");
        return -1;
    }
    return current->data;
}

// Function to test the add function
void testAdd() {
    LinkedList list;
    initList(&list);
    add(&list, 10, 0);
    add(&list, 20, 1);
    add(&list, 30, 1);
    // Expected: 10 -> 30 -> 20
    printf("After adding: %d -> %d -> %d\n", getValue(&list, 0), getValue(&list, 1), getValue(&list, 2));
}

// Function to test the remove function
void testRemove() {
    LinkedList list;
    initList(&list);
    add(&list, 10, 0);
    add(&list, 20, 1);
    add(&list, 30, 2);
    int removedValue = removeValue(&list, 1);
    // Expected: 20 (removed)
    printf("Removed value: %d\n", removedValue);
    // Expected: 10 -> 30
    printf("After removing: %d -> %d\n", getValue(&list, 0), getValue(&list, 1));
}

// Function to test the get function
void testGet() {
    LinkedList list;
    initList(&list);
    add(&list, 10, 0);
    add(&list, 20, 1);
    add(&list, 30, 2);
    int value = getValue(&list, 1);
    // Expected: 20
    printf("Value at position 1: %d\n", value);
}

int main() {
    testAdd();
    testRemove();
    testGet();
    return 0;
}
