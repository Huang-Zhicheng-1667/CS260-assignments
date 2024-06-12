#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list implementation
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Queue structure
typedef struct {
    Node *front;
    Node *rear;
} Queue;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize a queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue an element to the queue
void enqueue(Queue* queue, int data) {
    Node* newNode = createNode(data);
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue an element from the queue
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty, cannot dequeue!\n");
        exit(1);
    }
    int data = queue->front->data;
    Node* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    return data;
}

// Function to peek the front element of the queue
int peek(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty, cannot peek!\n");
        exit(1);
    }
    return queue->front->data;
}

// Function to display the queue
void display(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    Node* temp = queue->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    // Test the linked list based queue
    Queue* queue = createQueue();
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    printf("Queue elements: ");
    display(queue);
    printf("Dequeued element: %d\n", dequeue(queue));
    printf("Peeked element: %d\n", peek(queue));
    printf("Queue elements after dequeue and peek: ");
    display(queue);

    // Test the array based queue (bonus)
    const int SIZE = 5;
    int arr[SIZE];
    int front = -1, rear = -1;

    // Enqueue elements
    arr[++rear] = 10;
    arr[++rear] = 20;
    arr[++rear] = 30;

    // Display elements
    printf("Array-based queue elements: ");
    for (int i = 0; i <= rear; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Dequeue an element
    int dequeued = arr[++front];
    printf("Dequeued element from array-based queue: %d\n", dequeued);

    // Peek an element
    printf("Peeked element from array-based queue: %d\n", arr[front+1]);

    return 0;
}
