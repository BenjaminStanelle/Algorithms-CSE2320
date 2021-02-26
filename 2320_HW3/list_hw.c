#include <stdio.h>
#include <stdlib.h>

#include "list_hw.h"

// ------------- Node functions

/* Creates a new link, that contains the value specified in the argument, 
 * and that points to next_in. 
 */
struct node * new_node(int value_in,  struct node * next_in) {
    struct node * result = (struct node *) malloc(sizeof (struct node));
    result->data = value_in;
    result->next = next_in;
    return result;
}

/*    --------  LIST functions    */
// List implementation uses a DUMMY NODE

/* Creates and returns an empty list with a dummy node. */
struct node * new_list() {
	struct node * dummy = new_node(0,NULL);
    return dummy;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroy_list(struct node * Ld) {
    struct node * next;
	struct node * current = Ld;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }    
}

// Inserts new_node after the node called "previous". 
void insert_node(struct node * previous, struct node * new_node) {
    if (previous == NULL) {
        printf("\n Cannot insert after a NULL node. No action taken.");        		
    } else {
        new_node->next = previous->next;
        previous->next = new_node;
    }    
}

// Returns 0 for empty lists (that have just one dummy node) and NULL lists 
int compute_length(struct node * Ld) {
    if (Ld == NULL) {
        return 0;
    }

    int counter = 0;
    struct node * curr;
    for (curr = Ld->next; curr != NULL; curr = curr->next) {
        counter++;
    }
    return counter;
}


void print_list_vert(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list> : list is NULL\n");    
        return;
    }
    int i = 0;    
    struct node * curr;
    printf("\n List items:\n");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("item %d: %d\n", i, curr->data);
        i++;
    }
	printf(" Length of above list = %d\n", i);    
}

void print_list_horiz(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_horiz> : List is NULL\n");    
        return;		
    }
    int i = 0;    
    struct node * curr;

    printf("\n List items: ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%5d    ", curr->data);
        i++;
    }
	printf("\n Length of above list = %d\n", i);    
}

void print_list_pointer(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_pointer> : List is NULL\n");    
        return;
    }

    int i = 0;    
    struct node * curr;	
    printf("\n List items:    ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%-11d ", curr->data);
        i++;
    }    
    printf("\n List pointers: ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%p ", curr);
        i++;
    }
	printf("\n Length of above list = %d\n", i);    	
}


/*----------------------------------------------------------------
 New functions.
 * Finish their implementation below. 
 * If you need to use helper functions you can define them and use them in this file.
 *** You should not change the behavior of any of the functions defined above.***
 *** You should only write code in this file. DO not modify the client file in any way. You will NOT submit the client file. 
 
 NOTE: that the functions:
 link array_2_list(int arr[], int sz)
 link build_list_of_ints()
 are implemented and used in the instructor_client.c file, 
 BUT YOU CAN ALSO CALL THEM AND USE THEM IN YOUR student_test_sublist function.
 */
				//Allocates a new list of ints in position (pos_list) of A and puts them into new list
struct node * sublist(struct node * A, struct node * pos_list) {
	int j;
		struct node * test;
		test=pos_list;
			//testing: pos_list is empty, pos_list is NULL;
		if(compute_length(pos_list)<1|| pos_list==NULL){
			return NULL;
		}
		while(test!= NULL){
				//testing: index out of bounds, A is NULL, A is empty.
			if((compute_length(A)<test->data) || (test->data<0) || (compute_length(A)<1) || (A==NULL)){
				return NULL;
				
			}
		test=test->next;
		}
	
	struct node* temp_A, *temp_pos, *result, *temp_result;	
		
	temp_A=A->next;		//skip the first dummy nodes in the lists.
	temp_pos= pos_list->next;
	
	
	temp_result= new_list();   //temp_result points to the new list with the dummy node
	result= temp_result;   //result pointers to the first node in the temp_result list;

	int i;
	while(temp_pos != NULL){	//while our position list and A list are not NULL traverse through A until 
		for(i=0; i< temp_pos->data; i++){		//you get to the pos->data
			if(temp_A != NULL){
				temp_A=temp_A->next;
			}
		}
		insert_node(temp_result,new_node(temp_A->data,NULL));	//insert new node into result list
		temp_A=A->next;		//traverse all three lists.
		temp_result=temp_result->next;
		temp_pos=temp_pos->next;
	}
	
	
    return result;
}
						//swaps the first and third node in the list skipping the dummy node
void swap_first_third(struct node * A) {
	struct node * first, *third, *temp, *second;
		first= A->next;	//setting pointers to the first 3 nodes in A list
		second=first->next;
		third=second->next;
												//for understanding swap
		if(compute_length(A)>=3){		//if list A is greater or equal to 3
			temp=third->next;			//temp to pointer to 4th node
			third->next=second;			//third node points to second node
			A->next=third;				//dummy node points to old 3rd node
			first->next=temp;				//old first node points to 4th node
			second->next=first;			//second node points to old first, finishing the swap
		}
		else if(compute_length(A)==2){ 		//if only two nodes in the list besides dummy node
				first->next=second->next;
				second->next=first;
				temp=second;
				second=first;
				first=temp;
			
		}
		
		else {
			printf("The list has only one or no nodes");
			
		}
    return;
}
 				//takes in dynamically allocated list A and deletes occurrences of int V in it
void delete_occurrences(struct node * A, int V) {
	struct node* temp_result;
	struct node* current;
	struct node* prev;
	
	temp_result= A->next;	//points to second node in list
	prev= A;					// points to first node in list 
	
	while(temp_result!= NULL){		//while list A is not empty look for data in A that is equal to int v
		if(temp_result->data == V){
			current=temp_result;	//link the other nodes to leave out the occurence we want to delete
			prev->next=temp_result->next;
			temp_result= temp_result->next;
			free(current);				//free the node that is not linked to anything
		
		}
		else {
			prev= prev->next;		//else traverse both pointers which are both in list a
			temp_result = temp_result->next;
		}
	

	}
	
    return;
}

// Tests the sublist function.
int student_test_sublist() {
	printf("\n Running function student_test_sublist.\n ");    

	//index out of bounds 
		int arr_A[] = {10, 10, 40, 20};
		 struct node * A_list_test=NULL;
		A_list_test= array_2_list(arr_A, 4);	//building list 10, 10, 40, 20 
		int arr_pos[] = {-7, 3};	
		 struct node * pos_list_test =NULL;
		pos_list_test= array_2_list(arr_pos, 2);  //building list -7, 3 position list
		struct node * res_test=sublist(A_list_test, pos_list_test); 		//calling sublist to test case 1
		print_list_pointer(res_test);
		destroy_list(res_test);
		destroy_list(A_list_test);
		destroy_list(pos_list_test);
	
	//A is NULL
		struct node * A_list_test1=NULL;
		int arr_pos1[] = {0,0};	
		 struct node * pos_list_test1 =NULL;
		pos_list_test1= array_2_list(arr_pos1, 2);  
		struct node * res_test1=sublist(A_list_test1, pos_list_test1); 		//calling sublist to test case 2
		print_list_pointer(res_test1);
		destroy_list(res_test1);
		destroy_list(A_list_test1);
		destroy_list(pos_list_test1);

	//A is empty
		int arr_A2[] = {};
		struct node * A_list_test2=NULL;
		A_list_test2= array_2_list(arr_A2, 0);
		int arr_pos2[] = {0};	
		 struct node * pos_list_test2 =NULL;
		pos_list_test2= array_2_list(arr_pos2, 2);  
		struct node * res_test2=sublist(A_list_test2, pos_list_test2); 		//calling sublist to test case 3
		print_list_pointer(res_test2);
		destroy_list(res_test2);
		destroy_list(A_list_test2);
		destroy_list(pos_list_test2);

	//pos_list is empty
		int arr_A3[] = {1,2};
		struct node * A_list_test3=NULL;
		A_list_test3= array_2_list(arr_A3, 2);
		int arr_pos3[] = {};	
		 struct node * pos_list_test3 =NULL;
		pos_list_test3= array_2_list(arr_pos3, 0);  
		struct node * res_test3=sublist(A_list_test3, pos_list_test3); 		//calling sublist to test case 4
		print_list_pointer(res_test3);
		destroy_list(res_test3);
		destroy_list(A_list_test3);
		destroy_list(pos_list_test3);
	//pos_list is NULL
		int arr_A4[] = {1,2};
		struct node * A_list_test4=NULL;
		A_list_test4= array_2_list(arr_A4, 2);
		
		 struct node * pos_list_test4 =NULL;
		struct node * res_test4=sublist(A_list_test4, pos_list_test4); 		//calling sublist to test case 5
		print_list_pointer(res_test4);
		destroy_list(res_test4);
		destroy_list(A_list_test4);
		destroy_list(pos_list_test4);

	//A is not modified by sublist()
		int arr_A5[] = {15,100,7,5,100};
		struct node * A_list_test5=NULL;
		A_list_test5= array_2_list(arr_A5, 5);
		int arr_pos5[] = {3,0,2};	
		 struct node * pos_list_test5 =NULL;
		pos_list_test5= array_2_list(arr_pos5, 3);  
		struct node * res_test5=sublist(A_list_test5, pos_list_test5); 		//calling sublist to test case 5
		print_list_pointer(A_list_test5);
		destroy_list(res_test5);
		destroy_list(A_list_test5);
		destroy_list(pos_list_test5);
	//Repeated position
		int arr_A6[] = {5};
		struct node * A_list_test6=NULL;
		A_list_test6= array_2_list(arr_A6, 1);
		int arr_pos6[] = {0,0,0};	
		 struct node * pos_list_test6 =NULL;
		pos_list_test6= array_2_list(arr_pos6, 3);  
		struct node * res_test6=sublist(A_list_test6, pos_list_test6); 		//calling sublist to test case 5
		print_list_pointer(res_test6);
		destroy_list(res_test6);
		destroy_list(A_list_test6);
		destroy_list(pos_list_test6);
    return 0; 													
}
