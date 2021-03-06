//created by Lochana on 17/07/2016
//This is the serial implementation

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct list_node
{
	int data;
	struct list_node* next;
};

class LinkedList {
	
public:
	list_node* head;

	LinkedList() {
		head = NULL;
	}

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

	//Print the list
	void PrintList(list_node *head) {
		list_node *current_p = head;
		int count = 0;

		while (current_p != NULL) {
			printf("%d: %d\n", ++count, current_p->data);
			current_p = current_p->next;
		}
	}


};






int main() {

	unsigned seed = time(NULL);
	srand(seed);

	LinkedList list;
	int n;
	int m;
	float insert_ratio, member_ratio, del_ratio;
	int insert = 0, member = 0, del = 0;
	double start, finish, elapsed;

	printf("Enter the number of values to be added to the linked list:");
	scanf_s("%d", &n);
	printf("You are adding %d values\n", n);
	printf("Enter the number of operations to be performed on the linked list:");
	scanf_s("%d", &m);
	printf("You are gonna do %d operations\n", m);
	printf("Enter the member ratio:\n");
	scanf_s("%f", &member_ratio);
	printf("Enter the insert ratio:\n");
	scanf_s("%f", &insert_ratio);
	printf("Enter the delete ratio:\n");
	scanf_s("%f", &del_ratio);

	//Populate the list with n random numbers 
	for (int i = 0; i < n; i++) {
		//We need the numbers to be generated to be between 0 and 65535
		//Since the RAND_MAX is normally 32767 the below calculation of generates two random numbers
		//where the first one (msb) will set the Most Significant Bit of the second ( msb | rand() )
		//finally generating a random number between 0 and 65535 
		int msb = (rand() % 2) << 15;
		list.Insert(msb | rand(), &(list.head));
	}

	

	start = clock();
	while (true) {

		int msb = (rand() % 2) << 15;
		int val = msb | rand();
		switch (rand() % 3) {
		case 0:
			if (insert < (int)(insert_ratio*m)) {
				list.Insert(val, &(list.head));
				insert++;
				printf("adding %d\n", val);
			}
			break;
		case 1:
			if (member < (int)(member_ratio*m)) {
				list.Member(val, list.head);
				member++;
				printf("searching %d\n", val);
			}
			break;
		case 2:
			if (del < (int)(del_ratio*m)) {
				list.Delete(val, &(list.head));
				del++;
				printf("deleting %d\n", val);
			}
			break;
		}
		if (insert >= (int)(insert_ratio*m) && member >= (int)(member_ratio*m) && del >= (int)(del_ratio*m))
			break;
	}

	finish = clock();
	elapsed = (finish - start) / CLOCKS_PER_SEC;

	printf("Elapsed time = %.10f seconds\n", elapsed);

	
	printf("Member operation count = %d\n",member);
	printf("Insert operation count = %d\n",insert);
	printf("Delete operation count = %d\n",del);

	//list.PrintList(list.head);

		
	
}