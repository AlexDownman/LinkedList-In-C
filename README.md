# Singly Linked List Features

| Feature | Description | Function Declaration |
|---------|-------------|--------------------|
| **Add at Beginning** | Insert a new node at the start of the list. | `Node* createNodeAtBeginning(LinkedList *list, int data);` |
| **Add at End** | Insert a new node at the end of the list. | `Node* createNodeAtEnd(LinkedList *list, int data);` |
| **Add at Specific Index** | Insert a new node at a given index in the list. | `Node* createNodeAtIndex(LinkedList *list, int index, int data);` |
| **Insert After a Node** *(Optional)* | Insert a new node immediately after a specified node. | `Node* createAfterNode(LinkedList *list, Node *node, int data);` |
| **Insert Before a Node** *(Optional)* | Insert a new node immediately before a specified node. | `Node* createBeforeNode(LinkedList *list, Node *node, int data);` |
| **Find Node by Value** | Retrieve the first node in the list with a specific value. | `Node* findNodeByValue(LinkedList *list, int targetData);` |
| **Find Node by Index** | Retrieve the node at a specific index in the list. | `Node* findNodeByIndex(LinkedList *list, int tarIndex);` |
| **Find Node by Next Node** *(Optional)* | Retrieve the node that points to a specific node. | `Node* findNodeByNextNode(LinkedList *list, Node *targetNode);` |
| **Delete Node by Value** | Remove the first node in the list that matches a given value. | `void deleteNode(LinkedList *list, int targetData);` |
| **Delete Node by Index** | Remove the node at a specific index in the list. | `void deleteNodeByIndex(LinkedList *list, int index);` |
| **Print List** | Display all nodes in order. | `void printLinkedList(const LinkedList *list);` |
| **Check if List is Empty** | Determine whether the list has any nodes. | `void isEmpty(LinkedList *list);` |
| **Get Length of List** | Count the number of nodes in the list. | `int getLengthOfList(LinkedList *list);` |
| **Reverse List** | Reverse the order of nodes in the list. | `void reverseList(LinkedList *list);` |
| **Free List** | Release all memory used by the list. | `void freeLinkedList(LinkedList *list);` |
