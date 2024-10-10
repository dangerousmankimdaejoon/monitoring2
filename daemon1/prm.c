
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[7];
};
static struct sqlcxp sqlfpn =
{
    6,
    "prm.pc"
};


static unsigned int sqlctx = 4899;


static struct sqlexd {
   unsigned long  sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
            short *cud;
   unsigned char  *sqlest;
            char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
   unsigned char  **sqphsv;
   unsigned long  *sqphsl;
            int   *sqphss;
            short **sqpind;
            int   *sqpins;
   unsigned long  *sqparm;
   unsigned long  **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
            int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
   unsigned int   sqlpfmem;
   unsigned char  *sqhstv[4];
   unsigned long  sqhstl[4];
            int   sqhsts[4];
            short *sqindv[4];
            int   sqinds[4];
   unsigned long  sqharm[4];
   unsigned long  *sqharc[4];
   unsigned short  sqadto[4];
   unsigned short  sqtdso[4];
} sqlstm = {13,4};

/* SQLLIB Prototypes */
extern sqlcxt (/*_ void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * _*/);
extern sqlcx2t(/*_ void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * _*/);
extern sqlbuft(/*_ void **, char * _*/);
extern sqlgs2t(/*_ void **, char * _*/);
extern sqlorat(/*_ void **, unsigned int *, void * _*/);

/* Forms Interface */
static int IAPSUCC = 0;
static int IAPFAIL = 1403;
static int IAPFTL  = 535;
extern void sqliem(/*_ unsigned char *, signed int * _*/);

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{13,4130,1,0,0,
5,0,0,0,0,0,27,72,0,0,4,4,0,1,0,1,9,0,0,1,9,0,0,1,10,0,0,1,10,0,0,
36,0,0,2,0,0,32,96,0,0,0,0,0,1,0,
51,0,0,3,84,0,4,188,0,0,2,0,0,1,0,2,97,0,0,2,3,0,0,
74,0,0,4,41,0,4,203,0,0,1,0,0,1,0,2,3,0,0,
93,0,0,5,64,0,4,209,0,0,1,0,0,1,0,2,3,0,0,
112,0,0,6,45,0,4,251,0,0,1,0,0,1,0,2,3,0,0,
};


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <alloca.h>
#include <errno.h>
#include <sqlca.h>

#include "common.h"
#include "shmmap.h"
#include "ksuse.h"
#include "prm.h"

/* EXEC SQL BEGIN DECLARE SECTION; */ 


/* CONNECT DB */
/* varchar id[20], pw[20]; */ 
struct { unsigned short len; unsigned char arr[20]; } id;

struct { unsigned short len; unsigned char arr[20]; } pw;


/* TEST VAL */
int fsiz[100];
unsigned char fptr[100][16+1];
unsigned char fnam[100][64];

/* SYSTEM EVENT */
int ksmchsiz[100];
unsigned char ksmchptr[100][16+1];

int evNum;
int evWaits;
int evWaitm;

char kqfconam[100][128];
int  kqfcooff[100];
int  ksleiCnt;

/* SYSTEM STAT */
int ksmfssiz;
unsigned char ksmfsadr[16+1];

int statCnt;
int ustatCnt;
int sesCnt;

/* USER SESSION */
int rs_ksuse;

int i, j, t_cnt, r_cnt;

/* EXEC SQL END DECLARE SECTION; */ 


LinkedList l_shm;
Mmaps *maps = NULL;
int shmlen = 0;
void* shmBase = NULL;

OFF_kslei off_kslei;
OFF_ksuse off_ksuse;

pthread_mutex_t queueMutex = PTHREAD_MUTEX_INITIALIZER;

int connDB() {
   /* EXEC SQL WHENEVER SQLERROR DO sql_error("Oracle error \n"); */ 

   get_userinfo(&id, &pw);
   /* EXEC SQL CONNECT :id IDENTIFIED BY :pw; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 13;
   sqlstm.arrsiz = 4;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )10;
   sqlstm.offset = (unsigned int  )5;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (unsigned char  *)&id;
   sqlstm.sqhstl[0] = (unsigned long )22;
   sqlstm.sqhsts[0] = (         int  )22;
   sqlstm.sqindv[0] = (         short *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned long )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (unsigned char  *)&pw;
   sqlstm.sqhstl[1] = (unsigned long )22;
   sqlstm.sqhsts[1] = (         int  )22;
   sqlstm.sqindv[1] = (         short *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned long )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlstm.sqlcmax = (unsigned int )100;
   sqlstm.sqlcmin = (unsigned int )2;
   sqlstm.sqlcincr = (unsigned int )1;
   sqlstm.sqlctimeout = (unsigned int )0;
   sqlstm.sqlcnowait = (unsigned int )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
   if (sqlca.sqlcode < 0) sql_error("Oracle error \n");
}


}

void get_userinfo(varchar *id, varchar *pw) {

   strcpy((char*)(id->arr), "sherpa");
   id->len = strlen((char*)(id->arr));

   strcpy((char*)(pw->arr), "sherpa");
   pw->len = strlen((char*)(pw->arr));
}

void sql_error(char *msg) {

   char err_msg[512];
   int buff_len, msg_len;

   /* EXEC SQL WHENEVER SQLERROR CONTINUE; */ 

   printf("\n%s\n",msg);

   buff_len = sizeof(err_msg);
   sqlglm(err_msg, &buff_len, &msg_len);
   printf("%.*s\n", msg_len, err_msg);

   /* EXEC SQL ROLLBACK RELEASE; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 13;
   sqlstm.arrsiz = 4;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )36;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


   exit(1);
}

void sqlerror_check(char *msg) {
   
   if(sqlca.sqlcode != 0) {
      if(sqlca.sqlcode == 1403) {
         printf("\n%s\n", msg);
         exit(1);
      }
      else {
         sql_error("Oracle error \n");
      }
   }
}

void initQueue(StatQueue *queue) {
   queue->front = 0;
   queue->rear = -1;
   queue->count = 0;
}

int isQueueEmpty(StatQueue *queue) {
   return queue->count == 0;
}

int isQueueFull(StatQueue *queue) {
   return queue->count == QUEUE_SIZE;
}

void enqueue(StatQueue *queue, Stat *snapshot) {
   //pthread_mutex_lock(&queueMutex);
   if (isQueueFull(queue)) {
      free(queue->data[queue->front]);
      queue->front = (queue->front + 1) % QUEUE_SIZE;
   } else {
      queue->count++;
   }
   queue->rear = (queue->rear + 1) % QUEUE_SIZE;
   queue->data[queue->rear] = snapshot;
   //pthread_mutex_unlock(&queueMutex);
}

Stat* dequeue(StatQueue *queue) {
   //pthread_mutex_lock(&queueMutex);
   if (queue->count == 0) {
       return NULL;
   }
   Stat *data = queue->data[queue->front];
   queue->front = (queue->front + 1) % QUEUE_SIZE;
   queue->count--;
   return data;
   //pthread_mutex_unlock(&queueMutex);
}

void printQueue(StatQueue *queue, int statCnt) {
    int i = queue->front;
    int j = 0;
   
   printf("queue count, front : %d\n", queue->count, queue->front);
   printf("=================================\n");
   while(j < queue->count) {
      printf("queue[%d] : %d %d %lx\n", j, queue->data[i][1].VALUE, queue->data[i][9].VALUE, queue->data[i]);
      i = (i + 1) % QUEUE_SIZE;
      j++;
   }
   printf("=================================\n\n");
}

void storeSnapshotInQueue(StatQueue *queue, Stat *arrStat, int statCnt) {

   Stat *snapshot = (Stat *)malloc(sizeof(Stat) * statCnt);

   if (snapshot == NULL) {
      perror("Failed to allocate memory for snapshot");
      exit(1);
   }

   int i;
   for(i = 0; i < statCnt; i++) {
      snapshot[i] = arrStat[i];
   }
   enqueue(queue, snapshot);
}

/*
 * sysstat
 */

void s_Ksusga(void *arg) {

   /* EXEC SQL
   select KSMFSADR, KSMFSSIZ INTO:ksmfsadr, :ksmfssiz
     from SYS.SPX$KSMFSV
    where KSMFSNAM='ksusga_'; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 13;
   sqlstm.arrsiz = 4;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select KSMFSADR ,KSMFSSIZ into :b0,:b1  from SYS.SPX$KSMFS\
V where KSMFSNAM='ksusga_'";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )51;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.sqlpfmem = (unsigned int  )0;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (unsigned char  *)ksmfsadr;
   sqlstm.sqhstl[0] = (unsigned long )17;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         short *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned long )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (unsigned char  *)&ksmfssiz;
   sqlstm.sqhstl[1] = (unsigned long )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         short *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned long )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   if(sqlca.sqlcode != 0) {
      if(sqlca.sqlcode == 1403) {
         printf("no result ksuga_");
         exit(1);
      }
      else {
         sql_error("Oracle error \n");        
      }
   }
 
   /* EXEC SQL
   select count(1) INTO:statCnt
     from v$sysstat; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 13;
   sqlstm.arrsiz = 4;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select count(1) into :b0  from v$sysstat ";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )74;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.sqlpfmem = (unsigned int  )0;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (unsigned char  *)&statCnt;
   sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         short *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned long )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   sqlerror_check("statCnt");
   
   /* EXEC SQL
   select min(statistic#) INTO:ustatCnt 
     from V$STATNAME 
    where CLASS>200; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 13;
   sqlstm.arrsiz = 4;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select min(statistic#) into :b0  from V$STATNAME where CLA\
SS>200";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )93;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.sqlpfmem = (unsigned int  )0;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (unsigned char  *)&ustatCnt;
   sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         short *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned long )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


   
   sqlerror_check("ustatCnt");
   
   struct _stat *arrStat = (struct _stat *)malloc(statCnt * sizeof(struct _stat));
   struct _ustat *ustatAddr = (struct _ustat *)malloc(statCnt * sizeof(struct _ustat));
  
   uint64_t addr, saddr, uaddr, useAddr;

   int scnt, ecnt, tstatCnt;

   StatQueue *queue = (StatQueue *)arg;
   
   addr = strtoul(ksmfsadr,NULL,16);

   /******************
    *  1. system stat 
    ******************/
   saddr = *((uint32_t*)(addr + P_STAT));
    
   //printf("1. sys pointer : 0x%lx\n", saddr);
   
   for(scnt=0 ; scnt < statCnt ; scnt ++) {
      
      arrStat[scnt].INDX  = scnt; 
      arrStat[scnt].VALUE = *((uint64_t*)(saddr + 8*scnt));
   }
   
   //printf("\n<SYSTEM>\n");
   
   /********************* 
    * 2. find x$ksusesta 
    *********************/
   uaddr = *((uint32_t*)(addr + U_STAT));
   
   //printf("\n2. ksuse pointer : 0x%lx", uaddr);
    
   //printf("\n2. ksuse first addr : 0x%lx\n", *((uint64_t*)uaddr));

   /* EXEC SQL
   select count(1) INTO :sesCnt 
     from SYS.SPX$KSUSE; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 13;
   sqlstm.arrsiz = 4;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select count(1) into :b0  from SYS.SPX$KSUSE ";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )112;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.sqlpfmem = (unsigned int  )0;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (unsigned char  *)&sesCnt;
   sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         short *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned long )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



   sqlerror_check("sesCnt");

   int t=0;
   
   while(1) {

      /* save array ksusesta addr */
      for(ecnt=0 ; ecnt < sesCnt ; ecnt++) {
         
         useAddr = *((uint64_t*)(uaddr + ecnt*8));

         ustatAddr[ecnt].INDX = ecnt+1;
         ustatAddr[ecnt].ADDR = *((uint64_t*)(useAddr + OFF_SESSTAT));
      }

      /**********************
       * 3. sum sys,ses stat 
       **********************/
      for(scnt=0 ; scnt < statCnt ; scnt++) {
         arrStat[scnt].INDX  = scnt;
         
         /* 2024.09.11 Add SYS */
         arrStat[scnt].SYS   = *((uint64_t*)(saddr + 8*scnt));

         /* process last non-idle time*/
         if(scnt==31 || scnt==32)
            arrStat[scnt].VALUE = 0;
         else
            arrStat[scnt].VALUE = *((uint64_t*)(saddr + 8*scnt));
      }
      
      for(ecnt=0 ; ecnt < sesCnt ; ecnt++) {
         
         useAddr = *((uint64_t*)(uaddr + ecnt*8));
         
         /* KSUSEFLG OFFSET 2184*/
         if((*((char*)useAddr)&1) != 0 && (*((short*)(useAddr + 2184))&1) != 0) {
            for(scnt=0 ; scnt < ustatCnt ; scnt++) {
               
              /**********************************
               * db block gets partition
               **********************************/
               /* db block gets from cache */
               if(scnt==160) {
                  arrStat[14].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[159].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* db block gets from cache (fastpath) */
               else if(scnt==161) {
                  arrStat[14].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[159].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[160].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* db block gets direct */
               else if(scnt==162) {
                  arrStat[14].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[159].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }

              /**********************************
               * consistent gets partition
               **********************************/
               /* consistent gets from cache */
               else if(scnt==164) {
                  arrStat[14].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[163].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* consistent gets pin */
               else if(scnt==165) {
                  arrStat[14].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[163].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[164].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* consistent gets pin (fastpath) */
               else if(scnt==166) {
                  arrStat[14].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[163].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[164].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[165].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* consistent gets examination */
               else if(scnt==167) {
                  arrStat[14].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[163].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[164].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* consistent gets examination (fastpath) */
               else if(scnt==168) {
                  arrStat[14].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[163].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[164].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[167].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* consistent gets direct */
               else if(scnt==169) {
                  arrStat[14].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[163].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }

              /**********************************
               * physical reads partition
               **********************************/
               /* physical reads cache */
               else if(scnt==173) {
                  arrStat[172].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* physical read flash cache hits */
               else if(scnt==174) {
                  arrStat[172].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  arrStat[173].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* physical reads direct */
               else if(scnt==175) {
                  arrStat[172].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               
              /**********************************
               * physical writes partition
               **********************************/
               /* physical writes direct */
               else if(scnt==184 ) {
                  arrStat[183].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* physical writes from cache */
               else if(scnt==185) {
                  arrStat[183].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               
              /**********************************
               * redo writes
               **********************************/
               else if(scnt>=321 && scnt<=328) {
                  arrStat[320].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
              /**********************************
               * redo blocks written
               **********************************/
               else if(scnt>=333 && scnt<=340) {
                  arrStat[332].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }

              /**********************************
               * commit batch/immediate requested
               **********************************/
               /* commit batch requested */
               else if(scnt==685) {
                  arrStat[684].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* commit immediate requested */
               else if(scnt==686) {
                  arrStat[684].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }

              /**********************************
               * commit batch/immediate performed
               **********************************/
               /* commit batch requested */
               else if(scnt==688) {
                  arrStat[687].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* commit immediate requested */
               else if(scnt==689) {
                  arrStat[687].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }

              /**********************************
               * commit wait/nowait requested
               **********************************/
               /* commit nowait requested */
               else if(scnt==691) {
                  arrStat[690].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* commit wait requested */
               else if(scnt==692) {
                  arrStat[690].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }

              /**********************************
               * commit wait/nowait performed
               **********************************/
               /* commit nowait performed */
               else if(scnt==694) {
                  arrStat[693].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }
               /* commit wait performed */
               else if(scnt==695) {
                  arrStat[693].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }

               /**********************************
                * db block gets, consistent gets
                **********************************/
               else if(scnt==159 || scnt==163) {
                  arrStat[14].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
               }

               /**********************************
                * process last non-idle time
                **********************************/
               else if(scnt==32) {
                  if(arrStat[scnt].VALUE < *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt))) {
                     arrStat[scnt].VALUE = *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  }
                  continue;
               }

               /**********************************
                * time (stat 23~30)
                **********************************/
               else if(scnt>=23 && scnt<=30) {
                  arrStat[scnt].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
                  continue;
               }

               arrStat[scnt].VALUE += *((uint64_t*)(ustatAddr[ecnt].ADDR + 8*scnt));
            }
         }
      }

      for(tstatCnt=23 ; tstatCnt<=30 ; tstatCnt++) {
         if(tstatCnt==29) continue;
         arrStat[tstatCnt].VALUE /= 10000;
      }

      storeSnapshotInQueue(queue, arrStat, statCnt);
      //printQueue(queue, statCnt);
      
      sleep(1);
   }
}

void fmaps() {
   
   Node *current = l_shm.head;
   
   struct stat sb;
   size_t flen = 0;
   int shmfd = 0;
   
   shmlen = 0;
   shmBase = NULL;
   
   while(current->next != NULL) {

      maps = current->data;

      if(strcmp(maps->fileName, ((Mmaps *)((Node *)current->next)->data)->fileName) == 0) {
               
         current = current->next;
         maps = current->data;
      }

      shmfd = shm_open(maps->fileName, O_RDONLY, 0666);

      if (shmfd == -1) {
         printf("Shared memory failed:\n");
         return (EXIT_FAILURE);
      }
      if (fstat(shmfd, &sb) == -1 ) {
         printf("fstat failed:\n");
         return (EXIT_FAILURE);
      }

      flen = sb.st_size;
      shmlen = flen;
      
      //printf("lowAddr:%p, highAddr:%p and filename:%s\n", maps->lowAddr, maps->highAddr, maps->fileName);

      shmBase = mmap(maps->lowAddr, shmlen, PROT_READ, MAP_SHARED | MAP_FIXED, shmfd, 0);
      
      /*
      if (shmBase == -1) {
         printf("Map failed\n");
         printf("%d,%s\n",errno,strerror(errno));
      }
      if (close(shmfd) == -1) {
         printf("Failed to close %s", shmfd);
      }
      */
      
      if(current->next != NULL) {
         current = current->next;
      }
   }
}
