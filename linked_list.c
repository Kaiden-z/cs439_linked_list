#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node_t;

// Reference to first element of linked list
node_t* header = NULL;

/**
 * Insert new node into the list with data sorted in order of least to greatest
 */
void add(int data) {
    // Create new node
    node_t* newNode = (node_t*) malloc(sizeof(node_t));
    newNode->data = data;

    if (header == NULL) { /*Set as header if list is empty*/
        header = newNode;
    } else {  /*Place new node into approiate sorted order*/
        node_t* cur = header;
        while (cur != NULL) {
            // Stop if cur data is larger than new data
            if (cur->data > newNode->data) {
                newNode->next = cur;
                newNode->prev = cur->prev;
                // Keep prev null if cur = header
                if (header = cur) {
                    header = newNode;
                } else {
                    cur->prev->next = newNode;
                }
                cur->prev = newNode;
                return;

            // No larger data found, therefore data is last (largest)
            } else if (cur->next == NULL) {
                newNode->prev = cur;
                cur->next = newNode;
                return;
            }

            cur = cur->next;
        }
    }
    
    return;
}

/**
 * Create a linked list of size n with incrementing data from 1 to n
 * @pre: n >= 1
 */
void initiateLinkedList(int n) {
    if (n < 1) {
        printf("n must be <= 1");
        return;
    }

    for (int i = 1; i <= n; i++) {
        add(i);
    }

    return;
}

/**
 * Print all elements of the linked list
 */
void printList() {
    printf("[");
    node_t* cur = header;
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) {
            printf(", ");
        }
        cur = cur->next;
    }
    printf("]");

    return;
}

/**
 * Start of linked list tests
 */
void main() {
    int n = 5;
    initiateLinkedList(n);
    printList();

    return;
}