#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *top, int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = top->next;
    top->next = temp;
}

int pop(struct node *top) {
    if (top->next == NULL) {
        return -1;
	}
    struct node* temp = top->next;
    int data = temp->data;
    top->next = temp->next;
    free(temp);
    return data;
}

void printStack(struct node *top) {
    struct node *current = top->next; 
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    struct node* top = (struct node*)malloc(sizeof(struct node));
    top->next = NULL; 

    int num;
    while (1) {
        if (scanf("%d", &num) == 1 && num > 0) {
            push(top, num); 
        } else {
            printf("Print stack\n");
            printStack(top); 
            break; 
        }
    }

    while (top->next != NULL) {
        pop(top);
    }
    free(top); 

    return 0;
}

