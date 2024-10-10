typedef unsigned long long int t_uint64;

/*******************************************
 * linked list  
 *******************************************/
typedef struct _node{
    void *data;
    struct _node *next;
} Node;


typedef struct _linkedList{
    Node *head;
    Node *tail;
    Node *current;
} LinkedList;

typedef struct _ammInfo AmmInfo;

typedef void(*DISPLAY)(void*);
typedef void(*REMOVE)(void*);
typedef int(*COMPARE)(void*, void*);
typedef void(*UPDATE)(void*);


void addHead(LinkedList *list, void *data);

void initList(LinkedList *list);

void displayAllLinkedList(LinkedList *list, DISPLAY display);

int deleteAllNodesInList(LinkedList *list, REMOVE remove);

int CrosscheckPmonAddy(LinkedList *ksuseList, LinkedList *pmonMapslist);

int removeNoneMatchedNodes(LinkedList *list) ;

void releaseNode(LinkedList *list, Node *node);

Node* getNode(LinkedList *list, void* data);

int addMapstoAddySpace(LinkedList *list);


/*******************************************
 * common function
 *******************************************/
char *ltrim(char *str);
char *rtrim(char *str);

void h_str(char *str, unsigned int hexval);
void p_str(char *s_str, char *t_str);

void setBase32(char *s_str, unsigned long long int t_int);
void getDate(char *s_str, int t_int);
void getLTM(char *s_str, unsigned long long int t_int);
void escapeJsonString(char *input, char *output, size_t max_len);