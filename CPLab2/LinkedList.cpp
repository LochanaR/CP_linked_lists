//created by Lochana on 17/07/2016
#include <stdlib.h>
#include <stdio.h>

struct list_node
{
	int data;
	struct list_node* next;
};

//Member function to check if a given value is present in the list
int Member(int value, list_node* head_p) {

	list_node* current_p = head_p;

	while (current_p != NULL && current_p->data < value)
	{
		current_p = current_p->next;
	}

	if (current_p == NULL || current_p->data > value) {
		return 0;
	}
	else {
		return 1;
	}
}

//Insert function to insert a value in to the list preserving the order (ascending)
int Insert(int value, list_node** pointer_to_head_p) {

	list_node* current_p = *pointer_to_head_p;
	list_node* previous_p = NULL;
	list_node* temp_p;


	// Iterate to the end of the list or until the value to be inserted is greater than existing values
	while (current_p != NULL && current_p->data < value)
	{
		previous_p = current_p; //keep track of the previous node
		current_p = current_p->next;
	}

	//if end of the list is reached or list has been empty from the start
	//or the value at the current node is greater than
	//the value to be inserted
	if (current_p == NULL || current_p->data > value) {
		temp_p = (list_node*)malloc(sizeof(list_node));
		temp_p->data = value;
		temp_p->next = current_p;

		//if the list has been empty
		//create new first node
		if (previous_p == NULL) {
			*pointer_to_head_p = temp_p;
		}

		else
			previous_p->next = temp_p;
		return 1;
	}
	//the value is already in the list
	else {
		return 0;
	}
}

//Delete function to delete a value in to the linked list preserving the order
int Delete(int value, list_node** pointer_to_head_p) {

	list_node* current_p = *pointer_to_head_p;
	list_node* previous_p = NULL;

	//while the list is not empty and the value at current node
	//is less than the value to be deleted
	while (current_p != NULL && current_p->data < value)
	{
		previous_p = current_p; //keep track of the previous node
		current_p = current_p->next;
	}

	//if the value to be deleted is found at the beginning of the
	//list or at the middle of it
	if (current_p != NULL && current_p->data == value) {
		//if the deletion is to happen at the start of the list
		if (previous_p == NULL) {
			*pointer_to_head_p = current_p->next;
			free(current_p);
		}
		else {
			previous_p->next = current_p->next;
			free(current_p);
		}
		return 1;
	}
	// the value to be deleted is not in the list
	else {
		return 0;
	}
}



void PrintList(list_node *head) {
	list_node *current_p = head;

	while (current_p != NULL) {
		printf("%d\n", current_p->data);
		current_p = current_p->next;
	}
}


int main() {

	list_node* head;
	head = NULL;
	Insert(10, &head);
	Insert(20, &head);
	Insert(30, &head);
	Insert(40, &head);
	Insert(50, &head);
	PrintList(head);
	printf("\n");
	Insert(15, &head);
	Insert(25, &head);
	PrintList(head);
	//printf(" If 1 is o/p the value is in the list: %d\n",Member(1, head));
	//Delete(20, &head);

}