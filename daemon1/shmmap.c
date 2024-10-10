#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <alloca.h>
#include <errno.h>
#include "shmmap.h"
#include "common.h"

char* getIpcInfo() {

  char buff[200];
  FILE *fp;
  
  fp = popen("echo \"set time off\n set sqlprompt \'\'\n oradebug setmypid\n oradebug ipc\n oradebug tracefile_name\n \"\|sqlplus \'\/ as sysdba\' \| grep \".trc\"", "r");

  if(fp == NULL) {
     printf("trc file open error\n");
     return(EXIT_FAILURE);
  }
  
  while(fgets(buff, 200, fp))
  
  pclose(fp);

  
  return buff;
}

void getShmFileList(LinkedList *list, int syn) {
 
   FILE *fd, *fp;
   char *line = NULL, *match = NULL;
   size_t len = 0;
   char* filename = NULL;
   unsigned long start, end;
   char read, write, exec, cow;
   int offset, dev_major, dev_minor, inode, count;
   Mmaps *maps = NULL;
   
   initList(list);

   char *name;

   name = getIpcInfo();

   const char* trcNm[strlen(name)+1];

   snprintf(trcNm, strlen(name), "%s", name);

   if ((fd = fopen(trcNm, "r")) == NULL ) {
      printf("trc file open error\n");
      return(EXIT_FAILURE);
   }

   while(getline(&line, &len, fd) != -1) {
      count = 0;
      filename = realloc(filename, len);

      count = sscanf(line, "%p-%p %c%c%c%c %x %x:%x %u %[^\n]", &start, &end, &read, 
                            &write, &exec, &cow, &offset, &dev_major, &dev_minor, &inode, filename);
      
      if(count != 11) continue;

      match = strstr(filename, "/ora_");
      
      if(match != NULL) {
         maps = (Mmaps*) malloc(sizeof(Mmaps));

         maps->fileName = malloc(strlen(filename));
         strcpy(maps->fileName, match);
         maps->lowAddr = start;
         maps->highAddr = end;
         maps->keep = 0;
         maps->length = 0;
         addHead(list, maps);
      }
   }

   if(fclose(fd) == -1) {
      printf("Failed to close\n");
      return(EXIT_FAILURE);
   }

   free(match);
   free(filename);
   free(line);

   Node *current = list->head;
   Mmaps *pmaps = NULL;
   
   if(syn) {
      while(current != NULL) {
         pmaps = current->data; 
         printf("lowAddr:%p, highAddr:%p and filename:%s\n"
                , pmaps->lowAddr, pmaps->highAddr, pmaps->fileName);
         current = current->next;
      }
   }  
}
