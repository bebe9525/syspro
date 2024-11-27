#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node* addq(struct node *head, struct node *tail, int data) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;

    if (head->next == NULL) {
        head->next = temp;
        tail = temp;  
    } else {
        tail->next = temp;
        tail = temp; 
    }

    return tail;  
}

int delete(struct node *head, struct node *tail) {
    if (head->next == NULL) {
        return -1;
    }

    struct node *temp = head->next;
    int data = temp->data;
    head->next = temp->next;

    if (head->next == NULL) {
        tail = NULL;
    }

    free(temp);  
    return data;
}

void printQueue(struct node *head) {
    struct node *current;
    for (current = head->next; current != NULL; current = current->next) {
        printf("%d\n", current->data);
    }
}

int main() {
    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *tail = (struct node *)malloc(sizeof(struct node));

    head->next = NULL;
    tail->next = NULL;

    int num;
    while (1) {
        if (scanf("%d", &num) == 1 && num > 0) {
            tail = addq(head, tail, num);  
        } else {
            printf("Print queue\n");
            printQueue(head);  
            break;
        }
    }

    while (head->next != NULL) {
        delete(head, tail);  
    }

    free(head);  

    return 0;
}

