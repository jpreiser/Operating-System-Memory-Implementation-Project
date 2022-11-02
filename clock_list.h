struct ClockNode  {
	int data;
    int ref;
	struct ClockNode* next;
	struct ClockNode* prev;
};

struct ClockNode* cl_new_node(int data, int ref);
struct ClockNode* cl_insert_head(struct ClockNode *head, int data, int ref);
struct ClockNode* cl_insert_tail(struct ClockNode *head, int data, int ref);
struct ClockNode* cl_remove_head(struct ClockNode *head);
struct ClockNode* cl_remove_tail(struct ClockNode *head);
struct ClockNode* cl_remove(struct ClockNode *head, int data);
struct ClockNode* cl_update_ref(struct ClockNode *head, int data, int ref);
int cl_check(struct ClockNode *head);
int cl_find(struct ClockNode *head, int x);
void cl_print(struct ClockNode *head);
void cl_reverse_print(struct ClockNode* head);