#include<stdio.h>
#include<stdlib.h>
#include "clock_list.h"

struct ClockNode* cl_new_node(int x, int ref) 
{
		struct ClockNode* newClockNode 
                = (struct ClockNode*)malloc(sizeof(struct ClockNode));
		newClockNode->data = x;
        newClockNode->ref = ref;
		newClockNode->prev = NULL;
		newClockNode->next = NULL;
		return newClockNode;
}

struct ClockNode* cl_remove_tail(struct ClockNode *head)
{
		if(head == NULL) return NULL;
		
		struct ClockNode *rem = head;
		
		while(rem->next != NULL) rem = rem->next;
		rem->prev->next = NULL;
		return head;
}

struct ClockNode* cl_remove_head(struct ClockNode *head)
{
		if(head == NULL) return NULL;
		
		struct ClockNode *temp = head;
		head = head->next;
		if(head != NULL) head->prev = NULL;
		
		return head;
}

struct ClockNode *cl_remove(struct ClockNode *head, int data)
{
		if(head == NULL) return NULL;

		struct ClockNode *ret = head;

		while(ret != NULL) {
				if(data == ret->data) {
						if(ret == head) return cl_remove_head(head);
						if(ret->next == NULL) return cl_remove_tail(head);
						if(ret->prev) ret->prev->next = ret->next;
						if(ret->next) ret->next->prev = ret->prev;
						return head;
				}
				ret = ret->next;
		}
		return head;
}

struct ClockNode *cl_insert_head(struct ClockNode *head, int x, int ref) {
		struct ClockNode* newClockNode = cl_new_node(x, ref);
		if(head == NULL) 
        {
				head = newClockNode;
				return head;
		}
		head->prev = newClockNode;
		newClockNode->next = head; 
		head = newClockNode;

		return head;
}

struct ClockNode *cl_insert_tail(struct ClockNode *head, int x, int ref) {
		struct ClockNode* temp = head;
		struct ClockNode* newClockNode = cl_new_node(x, ref);
		if(head == NULL) 
        {
				head = newClockNode;
				return head;
		}
		while(temp->next != NULL) temp = temp->next; // Go To last ClockNode
		temp->next = newClockNode;
		newClockNode->prev = temp;

		return head;
}

struct ClockNode *cl_update_ref(struct ClockNode *head, int data, int ref) {
    struct ClockNode* temp = head;
    while (temp != NULL) {
      if (temp->data == data) 
      {
        temp->ref = ref;

        return head;
      }
      temp = temp->next;
    }

    return head;
}

int cl_find(struct ClockNode *head, int x) {
		struct ClockNode* temp = head;
		while (temp != NULL) 
        {
			if (temp->data == x) 
            {
				return temp->ref;
			}

			temp = temp->next;
		}

		return -1;
}

int clock_list_check(struct ClockNode *head) {
  return head->ref;
}

void cl_print(struct ClockNode *head) {
		struct ClockNode* temp = head;
		printf("Forward: ");
		while(temp != NULL) {
				printf("[%d, %d] ",temp->data, temp->ref);
				temp = temp->next;
		}
		printf("\n");
}

void cl_reverse_print(struct ClockNode *head) {
		struct ClockNode* temp = head;
		if(temp == NULL) return;
		while(temp->next != NULL) {
				temp = temp->next;
		}
		printf("Reverse: ");
		while(temp != NULL) {
				printf("[%d, %d] ",temp->data, temp->ref);
				temp = temp->prev;
		}
		printf("\n");
}