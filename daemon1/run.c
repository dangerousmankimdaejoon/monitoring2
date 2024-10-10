#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <alloca.h>
#include <errno.h>
#include <sqlca.h>

#include "common.h"
#include "prm.h"
#include "reactor.h"

LinkedList l_shm;

void interruptHandler(int sig) {
   printf("this program will be exited in 1 seconds..\n");
   sleep(1);
   exit(0);
}

int main(int argc, char** argv) {
   
   signal(SIGINT, interruptHandler);

   getShmFileList(&l_shm, 0);
   fmaps();

   connDB();

   inqueryProc();

   pthread_t threadStat, threadUser, threadReactor;
   
   StatQueue queue;

   initQueue(&queue);

   if(pthread_create(&threadStat, NULL, s_Ksusga, (void *)&queue) != 0) {
      perror("s_Ksusga error");
      exit(EXIT_FAILURE);
   }
   
   if(pthread_create(&threadUser, NULL, s_Ksuse, (void *)&queue) != 0) {
      perror("s_Ksuse error");
      exit(EXIT_FAILURE);
   }
   
   if(pthread_create(&threadReactor, NULL, reactor, (void *)&queue) != 0) {
      perror("reactor error");
      exit(EXIT_FAILURE);
   }
   
   pthread_join(threadStat, NULL);
   pthread_join(threadUser, NULL);
   pthread_join(threadReactor, NULL);

   return 0;
}