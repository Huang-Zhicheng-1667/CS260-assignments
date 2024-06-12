Assignment 2 Design

initializeList():
    Create a list structure object.
    Set its head pointer to NULL, indicating that the linked list is empty.

insertAtPosition():
    Create a newNode and allocate memory for it.
    Sets the new node's data member to the value passed in data.
    If the insertion position is 0:
        Point the next pointer of the newNode of the current linked list.
        Update the head pointer of the linked list to the new node.
    Else traverse the list to find the previous node and the position you want to insert:
        Traverse the list starting from the head node until the 1st node is found or the end of the list is reached.
    If the end of the list is traversed, an error message is output and returned.
    Else, insert the newNode at the target position:
        Point the next pointer of the newNode to the node next to the target position.
        Point the next pointer of the target node to the newNode.

deleteAtPosition():
    If the linked list is empty, output error and return.
    If the delete position is 0:
        Point the head pointer to the next node of the head node.
        Free the memory for the orginal head node.
    Else traverse the list to find previous node at the target position to be deleted:
        Traverse the list starting from the head node to the target position.
    If the end of the list is traversed, but not found, output error and return.
    Else delete the target position node.
        Save the pointer of the node next to the target position node to the temporary pointer nextNode.
        Free the memory of the node at the target position.
        Point the next pointer of the previous node to nextNode and skip the target node.
    
printList():
    Traverse the list starting from the head node of the list.
        Initialize the head node with a temporary pointer.
    Traverse the list and print the data of each node.
        When the temp pointer is not NULL, print the data of the current node and upate the temp pinter to the next node.
