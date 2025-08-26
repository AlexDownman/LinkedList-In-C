#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ------------------------ Structs ------------------------
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node *head;

    // Insertion functions
    Node* (*createNodeAtBeginning)(struct LinkedList *list, int data);
    Node* (*createNodeAtEnd)(struct LinkedList *list, int data);
    Node* (*createNodeAtIndex)(struct LinkedList *list, int index, int data);

    // Search functions
    Node* (*findNodeByValue)(struct LinkedList *list, int targetData);
    Node* (*findNodeByIndex)(struct LinkedList *list, int tarIndex);

    // Utility functions
    void (*deleteNode)(struct LinkedList *list, int targetData);
    void (*deleteNodeByIndex)(struct LinkedList *list, int index);
    void (*printLinkedList)(struct LinkedList *list);

} LinkedList;

// ------------------------ Insertion Functions ------------------------
Node* createNodeAtBeginning(LinkedList *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) { perror("malloc error"); exit(1); }

    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;

    return newNode;
}

Node* createNodeAtEnd(LinkedList *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) { perror("malloc error"); exit(1); }

    newNode->data = data;
    newNode->next = NULL;

    if (!list->head) list->head = newNode;
    else {
        Node *current = list->head;
        while (current->next) current = current->next;
        current->next = newNode;
    }

    return newNode;
}

Node* createNodeAtIndex(LinkedList *list, int index, int data) {
    if (index < 0) { fprintf(stderr, "Index cannot be negative\n"); return NULL; }
    if (index == 0) return createNodeAtBeginning(list, data);

    Node *current = list->head;
    for (int i = 0; i < index - 1 && current != NULL; i++) current = current->next;

    if (!current) {
        fprintf(stderr, "Index %d out of bounds\n", index);
        return NULL;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) { perror("malloc error"); exit(1); }

    newNode->data = data;
    newNode->next = current->next;
    current->next = newNode;

    return newNode;
}

// Optional: insert after a node
Node* createAfterNode(LinkedList *list, Node *node, int data) {
    if (!node) { fprintf(stderr, "Node cannot be NULL\n"); return NULL; }

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) { perror("malloc error"); exit(1); }

    newNode->data = data;
    newNode->next = node->next;
    node->next = newNode;

    return newNode;
}

// Optional: insert before a node
Node* createBeforeNode(LinkedList *list, Node *node, int data) {
    if (!node) { fprintf(stderr, "Node cannot be NULL\n"); return NULL; }

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) { perror("malloc error"); exit(1); }

    if (list->head == node) {
        newNode->next = list->head;
        list->head = newNode;
        return newNode;
    }

    Node *current = list->head;
    Node *previous = NULL;
    while (current && current != node) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        fprintf(stderr, "Node not found in the list\n");
        free(newNode);
        return NULL;
    }

    previous->next = newNode;
    newNode->next = node;

    return newNode;
}

// ------------------------ Search Functions ------------------------
Node* findNodeByValueRec(const Node *node, int targetData) {
    if (!node) return NULL;
    if (node->data == targetData) return (Node*)node;
    return findNodeByValueRec(node->next, targetData);
}

Node* findNodeByValue(LinkedList *list, int targetData) {
    return findNodeByValueRec(list->head, targetData);
}

Node* findNodeByIndexRec(const Node *node, int curIndex, int tarIndex) {
    if (!node) return NULL;
    if (curIndex == tarIndex) return (Node*)node;
    return findNodeByIndexRec(node->next, curIndex + 1, tarIndex);
}

Node* findNodeByIndex(LinkedList *list, int tarIndex) {
    if (tarIndex < 0) return NULL;
    return findNodeByIndexRec(list->head, 0, tarIndex);
}

// ------------------------ Deletion Functions ------------------------
void deleteNode(LinkedList *list, int targetData) {
    Node *current = list->head;
    Node *previous = NULL;

    while (current && current->data != targetData) {
        previous = current;
        current = current->next;
    }

    if (!current) return;

    if (!previous) list->head = current->next;
    else previous->next = current->next;

    free(current);
}

void deleteNodeByIndex(LinkedList *list, int index) {
    if (index < 0 || !list->head) return;

    Node *current = list->head;
    Node *previous = NULL;

    if (index == 0) {
        list->head = current->next;
        free(current);
        return;
    }

    for (int i = 0; i < index && current; i++) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        fprintf(stderr, "Index %d out of bounds\n", index);
        return;
    }

    previous->next = current->next;
    free(current);
}

// ------------------------ Utility Functions ------------------------
void printLinkedListRec(const Node *node) {
    if (!node) return;
    printf("%d -> ", node->data);
    if (!node->next) printf("END\n");
    printLinkedListRec(node->next);
}

void printLinkedList(const LinkedList *list) {
    printLinkedListRec(list->head);
}

void freeLinkedList(LinkedList *list) {
    Node *current = list->head;
    while (current) {
        Node *tmp = current;
        current = current->next;
        free(tmp);
    }
    list->head = NULL;
}

int getLengthOfList(LinkedList *list) {
    int lengthCount = 0;
    Node *current = list->head;
    while (current) {
        lengthCount++;
        current = current->next;
    }
    return lengthCount;
}

void isEmpty(LinkedList *list) {
    if (!list->head) printf("List Is Empty");
    else printf("List Is Not Empty");
}

void reverseList(LinkedList *list) {
    Node *prev = NULL;
    Node *current = list->head;
    Node *next = NULL;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev;
}

// ------------------------ LinkedList Constructor ------------------------
LinkedList createLinkedList() {
    LinkedList list;
    list.head = NULL;

    list.createNodeAtBeginning = createNodeAtBeginning;
    list.createNodeAtEnd = createNodeAtEnd;
    list.createNodeAtIndex = createNodeAtIndex;

    list.findNodeByValue = findNodeByValue;
    list.findNodeByIndex = findNodeByIndex;

    list.deleteNode = deleteNode;
    list.deleteNodeByIndex = deleteNodeByIndex;
    list.printLinkedList = printLinkedList;

    return list;
}

// ------------------------ Main ------------------------
int main(void) {
    LinkedList list = createLinkedList();
    LinkedList *pList = &list;

    // Insert nodes
    pList->createNodeAtEnd(pList, 1);
    pList->createNodeAtEnd(pList, 2);
    pList->createNodeAtEnd(pList, 3);
    pList->createNodeAtEnd(pList, 4);
    pList->createNodeAtEnd(pList, 5);

    // Print list
    pList->printLinkedList(pList);

    // Reverse list
    reverseList(pList);

    // Print reversed list
    pList->printLinkedList(pList);

    // Free memory
    freeLinkedList(pList);

    return 0;
}
