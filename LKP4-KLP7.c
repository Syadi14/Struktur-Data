#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
 
// Node Linked List  // <<< BERUBAH (sekarang dipakai untuk Queue)
typedef struct node {
    int data;
    struct node *next;
} Node;


// Queue dengan pointer front dan rear  // <<< BERUBAH
typedef struct {
    Node *front;   // <<< BERUBAH
    Node *rear;    // <<< BERUBAH
} Queue;


/* Function Prototypes */
void init(Queue *q);                // <<< BERUBAH
int is_empty(Queue *q);             // <<< BERUBAH
int enqueue(Queue *q, int x);       // <<< BERUBAH
int dequeue(Queue *q, int *value);  // <<< BERUBAH


int main() {
    Queue q;        // <<< BERUBAH
    int choice, value;

    init(&q);

    do {
        printf("\n===== QUEUE MENU =====\n");  // <<< BERUBAH
        printf("1. Enqueue\n"); // <<< BERUBAH
        printf("2. Dequeue\n"); // <<< BERUBAH
        printf("3. Exit\n"); // <<< BERUBAH
        printf("======================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                if(enqueue(&q, value)) // <<< BERUBAH
                    printf("Value inserted successfully.\n");
                else
                    printf("Memory Full!\n");
                break;

            case 2:
                if(dequeue(&q, &value)) 
                    printf("Removed value: %d\n", value);
                else
                    printf("Queue Underflow!\n");
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 3);

    return 0;
}


// INIT
void init(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}


// Cek Queue kosong 
int is_empty(Queue *q) {
    return (q->front == NULL);
}


// Enqueue (tambah di belakang) 
int enqueue(Queue *q, int x) {

    Node *newNode = (Node*) malloc(sizeof(Node)); 

    if(newNode == NULL)
        return FALSE;

    newNode->data = x;
    newNode->next = NULL;

    if(is_empty(q)) {
        q->front = newNode;  
        q->rear = newNode;    
    } else {
        q->rear->next = newNode;  
        q->rear = newNode;        
    }

    return TRUE;
}


// Dequeue (hapus dari depan) 
int dequeue(Queue *q, int *value) {

    if(is_empty(q))
        return FALSE;

    Node *temp = q->front;     
    *value = temp->data;

    q->front = temp->next;     

    if(q->front == NULL)
        q->rear = NULL;        

    free(temp);                

    return TRUE;
}