typedef struct _maps {
   char* fileName;
   unsigned long lowAddr;
   unsigned long highAddr;
   int keep;
   int length;
} Mmaps;

typedef struct _linkedList LinkedList;
char* getIpcInfo();
