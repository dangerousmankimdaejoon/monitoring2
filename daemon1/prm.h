void sql_error();

int connDB();
void inqueryProc();
void get_userinfo();

void s_Ksusga();
void s_Ksuse();
void s_Kslei();

typedef unsigned long long int t_uint64;

#define DEF_OFF_SQLTEXT 448
#define DEF_OFF_SQLLENG 400
#define DEF_OFF_MODACT 3272

/* KSUSE */
typedef struct _ksuse {

   uint64_t INST_ID                     ;   /* INST_ID   0    */
   uint64_t SADDR                       ;   /* SADDR     0    */
   uint64_t SID                         ;   /* INDX      0    */
   uint64_t SERIAL_                     ;   /* KSUSESER  2172 */
   uint64_t AUDSID                      ;   /* KSUUDSES  56   */
   uint64_t PADDR                       ;   /* KSUSEPRO  8(ksspaown) -> +8 == 0 then 8 else 8(ksspaown) -> +8*/
							               
   uint64_t USERNUMBER                  ;   /* KSUUDLUI  64   */
   char     USERNAME[128+1]             ;   /* KSUUDLNA  197  */
   uint64_t COMMAND                     ;   /* KSUUDOCT  1494 */
   char     STATUS[8+1]                 ;   /* KSUSEFLG  2184 --decode(bitand(s.ksuseidl,11),1,'ACTIVE',0,decode(bitand(s.ksuseflg,4096),0,'INACTIVE','CACHED'),2,'SNIPED',3,'SNIPED', 'KILLED') */
   uint64_t SCHEMA_                     ;   /* KSUUDSID  1652 */
   char     SCHEMANAME[128+1]           ;   /* KSUUDSNA  1656 */
							               
   char     OSUSER[30+1]                ;   /* KSUSEUNM  2560 */
   char     PROCESS[24+1]               ;   /* KSUSEPID  2816 */
   char     MACHINE[64+1]               ;   /* KSUSEMNM  2696 */
   uint64_t PORT                        ;   /* KSUSEMNP  2768 */
   char     TERMINAL[16+1]              ;   /* KSUSETID  2772 */
   char     PROGRAM[64+1]               ;   /* KSUSEPNM  2912 */
   char     TYPE[10+1]                  ;   /* KSUSEFLG  2184 --decode(bitand(ksuseflg,19),17,'BACKGROUND',1,'USER',2,'RECURSIVE','?') */
								           
   uint64_t SQL_ADDRESS                 ;   /* KSUSESQL   2424 */
   uint64_t SQL_HASH_VALUE              ;   /* KSUSESQH   2436 */
   char     SQL_ID[13+1]                ;   /* KSUSESQI   2424(ksusesql) -> +368, +372 base32 */
   char     SQL_TEXT[2000]              ;   
   uint64_t SQL_CHILD_NUMBER            ;   /* KSUSESCH   2440 --decode(s.ksusesch, 65535, to_number(null), s.ksusesch)*/
   char     SQL_EXEC_START[19+1]        ;   /* KSUSESESTA 2456 */
   uint64_t SQL_EXEC_ID                 ;   /* KSUSESEID  2460 */
								           
   uint64_t PREV_SQL_ADDR               ;   /* KSUSEPSQ   2496 */
   uint64_t PREV_HASH_VALUE             ;   /* KSUSEPHA   2508 */
   char     PREV_SQL_ID[13+1]           ;   /* KSUSEPSI   2496(ksusepsq) -> +368, +372 base32 */
   char     PREV_SQL_TEXT[2000]         ;   
   uint64_t PREV_CHILD_NUMBER           ;   /* KSUSEPCH   2512 */
   char     PREV_EXEC_START[19+1]       ;   /* KSUSEPESTA 2520 */
   uint64_t PREV_EXEC_ID                ;   /* KSUSEPEID  2524 */
									       
   uint64_t PLSQL_ENTRY_OBJECT_ID       ;   /* 2472 KSUSEPEO decode(s.ksusepeo,0,to_number(null),s.ksusepeo) */
   uint64_t PLSQL_ENTRY_SUBPROGRAM_ID   ;   /* 2476 KSUSEPES decode(s.ksusepeo,0,to_number(null),s.ksusepes) */
   uint64_t PLSQL_OBJECT_ID             ;   /* 2484 KSUSEPCO decode(s.ksusepco, 0, to_number(null), decode(bitand(s.ksusstmbv, power(2,11)), power(2,11), s.ksusepco, to_number(null))) */
   uint64_t PLSQL_SUBPROGRAM_ID         ;   /* 2488 KSUSEPCS decode(s.ksusepcs, 0, to_number(null), decode(bitand(s.ksusstmbv, power(2,11)), power(2,11), s.ksusepcs, to_number(null))) */
									       
   //uint64_t MODULE_LEN                  ;   /* 3272 -> +64  */
   char     MODULE[48+1]                ;   /* 3272 -> +0   */
   uint64_t MODULE_HASH                 ;   /* 3272 -> +72  */
   //uint64_t ACTION_LEN                  ;   /* 3272 -> +144 */
   char     ACTION[32+1]                ;   /* 3272 -> +76  */
   uint64_t ACTION_HASH                 ;   /* 3272 -> +152 */
   
   char     CLIENT_INFO[64+1]           ;   /* KSUSECLI 3288 */
   uint64_t FIXED_TABLE_SEQUENCE        ;   /* KSUSEFIX 3280 */
									       
   uint64_t ROW_WAIT_OBJ_               ;   /* KSUSEOBJ 3264 */
   uint64_t ROW_WAIT_FILE_              ;   /* KSUSEFIL 3252 */
   uint64_t ROW_WAIT_BLOCK_             ;   /* KSUSEBLK 3256 */
   uint64_t ROW_WAIT_ROW_               ;   /* KSUSESLT 3260 */
									       
   uint64_t TOP_LEVEL_CALL_             ;   /* KSUSEORAFN 9624 */
   char     LOGON_TIME[19+1]            ;   /* KSUSELTM   3608 */
   uint64_t LAST_CALL_ET                ;   /* KSUSECTM   case ksusesesta, ksusepesta, ksuseltm*/
   
   //char     RESOURCE_CONSUMER_GROUP[32+1]  /* KSUSEGRP   */
   //uint64_t CURRENT_QUEUE_DURATION         /* KSUSECQD   */
   char     CLIENT_IDENTIFIER[64+1]     ;   /* KSUSECLID  4688*/
   
   uint64_t SEQ_                        ;   /* KSUSESEQ 2064 */
   uint64_t EVENT_                      ;   /* KSUSEOPC 2066 */
   char     EVNAME[64+1]                ;   /* KSUSEOPC 2066 */
   
   //++ p1, p2 ,p3, WAIT_TIME, SECONDS_IN_WAIT, STATE, STAT_VAL[MAX_STAT_CNT]
   uint64_t P1                          ;   /* KSUSEP1 2072 */
   char     P1TEXT[64+1]                ;   /*  */
   uint64_t P2                          ;   /* KSUSEP2 2080 */
   char     P2TEXT[64+1]                ;   /*  */
   uint64_t P3                          ;   /* KSUSEP3 2088 */
   char     P3TEXT[64+1]                ;   /*  */
   
   char     BLOCKING_SESSION_STATUS[11+1] ;  /*  */
   uint64_t BLOCKING_INSTANCE             ;  /*  */ 
   uint64_t BLOCKING_SESSION              ;  /*  */

   char     FINAL_BLOCKING_SESSION_STATUS[11+1] ; /*  */
   uint64_t FINAL_BLOCKING_INSTANCE             ; /*  */
   uint64_t FINAL_BLOCKING_SESSION              ; /*  */
   

} Ksuse;

/* KSUSE OFFSET */
typedef struct _off_ksuse {

   int OFF_INST_ID   ;
   int OFF_SADDR     ;
   int OFF_SID       ; /* 2160 (h) */
   int OFF_SERIAL_   ; /* KSUSESER  2172 */
   int OFF_AUDSID    ; /* KSUUDSES  56   */
   int OFF_PADDR     ; /* KSUSEPRO  8(ksspaown) -> +8 == 0 then 8 else 8(ksspaown) -> +8*/
   
   int OFF_USERNUMBER; /* KSUUDLUI  64   */
   int OFF_USERNAME  ; /* KSUUDLNA  197  */
   int OFF_COMMAND   ; /* KSUUDOCT  1494 */
   //int OFF_STATUS    ;
   int OFF_KSUSEFLG  ; /* KSUSEFLG  2184 */
   int OFF_KSUSEIDL  ; /* KSUSEIDL  2224 */
   int OFF_SCHEMA_   ; /* KSUUDSID  1652 */
   int OFF_SCHEMANAME; /* KSUUDSNA  1656 */
   
   int OFF_OSUSER    ; /* KSUSEUNM  2560 */
   int OFF_PROCESS   ; /* KSUSEPID  2816 */
   int OFF_MACHINE   ; /* KSUSEMNM  2696 */
   int OFF_PORT      ; /* KSUSEMNP  2768 */
   int OFF_TERMINAL  ; /* KSUSETID  2772 */
   int OFF_PROGRAM   ; /* KSUSEPNM  2912 */
   //int OFF_TYPE      ;
   
   int OFF_SQL_ADDRESS      ; /* KSUSESQL   2424 */
   int OFF_SQL_HASH_VALUE   ; /* KSUSESQH   2436 */
   //int OFF_SQL_ID           ; 
   int OFF_SQL_CHILD_NUMBER ; /* KSUSESCH   2440 */
   int OFF_SQL_EXEC_START   ; /* KSUSESESTA 2456 */
   int OFF_SQL_EXEC_ID      ; /* KSUSESEID  2460 */
   
   int OFF_PREV_SQL_ADDR    ; /* KSUSEPSQ   2496 */
   int OFF_PREV_HASH_VALUE  ; /* KSUSEPHA   2508 */
   //int OFF_PREV_SQL_ID      ;
   int OFF_PREV_CHILD_NUMBER; /* KSUSEPCH   2512 */
   int OFF_PREV_EXEC_START  ; /* KSUSEPESTA 2520 */
   int OFF_PREV_EXEC_ID     ; /* KSUSEPEID  2524 */
   
   int OFF_KSUSEPEO; /* 2472 KSUSEPEO */
   int OFF_KSUSEPES; /* 2476 KSUSEPES */
   int OFF_KSUSEPCO; /* 2484 KSUSEPCO */
   int OFF_KSUSEPCS; /* 2488 KSUSEPCS */
   int OFF_KSUSSTMBV; /* 2100 KSUSSTMBV */

   /*									
   int OFF_MODULE_LEN               ;
   int OFF_MODULE                   ;
   int OFF_MODULE_HASH              ;
   int OFF_ACTION_LEN               ;
   int OFF_ACTION                   ;
   int OFF_ACTION_HASH              ;
   */
   
   int OFF_MODACT; /* 3272 (HD) */
   
   int OFF_CLIENT_INFO              ; /* KSUSECLI 3288 */
   int OFF_FIXED_TABLE_SEQUENCE     ; /* KSUSEFIX 3280 */
									
   int OFF_ROW_WAIT_OBJ_            ; /* KSUSEOBJ 3264 */
   int OFF_ROW_WAIT_FILE_           ; /* KSUSEFIL 3252 */
   int OFF_ROW_WAIT_BLOCK_          ; /* KSUSEBLK 3256 */
   int OFF_ROW_WAIT_ROW_            ; /* KSUSESLT 3260 */
									
   int OFF_TOP_LEVEL_CALL_          ; /* KSUSEORAFN 9624 */
   int OFF_LOGON_TIME               ; /* KSUSELTM   3608 */
   //int OFF_LAST_CALL_ET             ;
   
   //char     RESOURCE_CONSUMER_GROUP[32+1]
   //uint64_t CURRENT_QUEUE_DURATION
   
   int OFF_CLIENT_IDENTIFIER; /* KSUSECLID  4688*/
   
   int OFF_SEQ_             ; /* KSUSESEQ 2064 */
   int OFF_EVENT_           ; /* KSUSEOPC 2066 */
   int OFF_EVNAME           ; /* KSUSEOPC 2066 */
   
   //++ p1, p2 ,p3, WAIT_TIME, SECONDS_IN_WAIT, STATE, STAT_VAL[MAX_STAT_CNT]
   int OFF_P1    ; /* KSUSEP1 2072 */
   int OFF_P2    ; /* KSUSEP2 2080 */
   int OFF_P3    ; /* KSUSEP3 2088 */

   int OFF_KSUSEBLOCKER;  /*  */
   int OFF_KSUSEFBLOCKER; /*  */

} OFF_ksuse;

/*

< SQL_ID >

0x66748738 : 6b af ce 99 00 00 00 00 0d 26 f2 ad ee 51 28 80
0x66748748 : ff 6a c5 76 6b af ce 99 4c 41 4e 41 78 7b 08 04

select LISTAGG(
       case when val1 < 10 then to_char(val1)
            when val1 = 10 then 'a'
            when val1 = 11 then 'b'
            when val1 = 12 then 'c'
            when val1 = 13 then 'd'
            when val1 = 14 then 'f'
            when val1 = 15 then 'g'
            when val1 = 16 then 'h'
            when val1 = 17 then 'j'
            when val1 = 18 then 'k'
            when val1 = 19 then 'm'
            when val1 = 20 then 'n'
            when val1 = 21 then 'p'
            when val1 = 22 then 'q'
            when val1 = 23 then 'r'
            when val1 = 24 then 's'
            when val1 = 25 then 't'
            when val1 = 26 then 'u'
            when val1 = 27 then 'v'
            when val1 = 28 then 'w'
            when val1 = 29 then 'x'
            when val1 = 30 then 'y'
            when val1 = 31 then 'z' end, '')
from
(
   select trunc(mod(t1.val,power(32, 13-level+1)) / power(32, 13-level)) as val1
      from (    
             select sum((instr('0123456789abcdef',substr(lower(trim('76c56aff99ceaf6b')),level,1))-1)*power(16,length(trim('76c56aff99ceaf6b'))-level)) as val
               from dual
            connect by
	          level <= length(trim('76c56aff99ceaf6b'))
	       ) t1
   connect by level <= 13
) t2
;
*/

/*

KSUSESESTA	2456
KSUSEPESTA	2520
KSUSEWTM    3604
KSUSELTM    3608

<KSUSELTM exam>

0x74d43358 / 2023-08-04 15:18:50

[sherpa@ora19_1 posix]$ ./p2 0x74d43358

0x74d43358 : 78 7b 08 04 10 13 33 00 80 c0 4a 68 00 00 00 00

78  7b   08  04   10   13   33
120 123  08  04   16   19   51
x20 x23  08  04   16-1 19-1 51-1

*/

/*
select to_char((to_number('74D42540', 'xxxxxxxx') +  3608), 'xxxxxxxx') from dual;

select (to_number('74881e3c', 'xxxxxxxx')-TO_NUMBER('74881028', 'xxxxxxxx'))  from dual;

-- fptr:0000000074881028 faddr:74881e3c fval:1691130424 fnam:
select ksusewtm
     , round((sysdate-to_date('197001010900','yyyymmddhh24mi'))*24*60*60,0)-ksusewtm as "t_ksusewtm" -- ksusewtm = round((sysdate-to_date('197001010900','yyyymmddhh24mi'))*24*60*60,0) - t_ksusewtm
     , round((KSUSELTM-to_date('197001010900','yyyymmddhh24mi'))*24*60*60,0) as         "t_ksuseltm"
     , round((KSUSESESTA-to_date('197001010900','yyyymmddhh24mi'))*24*60*60,0) as       "t_ksusesesta"
     , round((KSUSEPESTA-to_date('197001010900','yyyymmddhh24mi'))*24*60*60,0) as       "t_ksusepesta"
     , case when bitand(ksuseflg,19) = 1 then case when KSUSESESTA is null then round((sysdate-KSUSEPESTA)*24*60*60,0)
                                                   else round((sysdate-KSUSESESTA)*24*60*60,0) end
            else round((sysdate-KSUSELTM)*24*60*60,0) end as "t_ksusectm"
     , KSUSECTM
     , KSUSESESTA
     , KSUSELTM   as LOGIN
     , ksusesesta as EXEC
     , KSUSEPESTA as PRE_EXEC
     , ksuseflg
     , decode(                                  -- STATUS VARCHAR2(8)
       bitand(a.ksuseidl,11),1,'ACTIVE',0,decode(bitand(a.ksuseflg,4096),0,'INACTIVE','CACHED'),2,'SNIPED',3,'SNIPED', 'KILLED') as "STATUS"
     , decode(                                  -- TYPE VARCHAR2(10)
       bitand(ksuseflg,19),17,'BACKGROUND',1,'USER',2,'RECURSIVE','?') as TYPE
     , a.* from x$ksuse a where bitand(a.ksspaflg,1)!=0 and bitand(a.ksuseflg,1)!=0 and decode(bitand(ksuseflg,19),17,'BACKGROUND',1,'USER',2,'RECURSIVE','?') = 'USER';
*/

/*
<MODULE, ACTION>

select KSUSEAPP, KSUSEAPH, KSUSEACT, KSUSEACH, a.* from x$ksuse a where ksuseaph = 152940696;

select to_char((to_number('74D47510', 'xxxxxxxx') +  3272), 'xxxxxxxx') from dual;

Moduel = 0x6b90dd98 (+00) / len : 0x6b90ddd8 (+64)  / hash : 0x6b90dde0 (+72)
Action = 0x6b90dde4 (+76) / len : 0x6b90de28 (+144) / hash : 0x6b90de28 (+152)
;
select to_char((to_number('6B90DCF0', 'xxxxxxxx') +  0), 'xxxxxxxx') from dual;
select to_char((to_number('6B90DCF0', 'xxxxxxxx') +  64), 'xxxxxxxx') from dual;
select to_char((to_number('6B90DCF0', 'xxxxxxxx') +  76), 'xxxxxxxx') from dual;
select to_char((to_number('6B90DCF0', 'xxxxxxxx') +  144), 'xxxxxxxx') from dual;

*/

/*
<KSUSEBLOCKER, KSUSEFBLOCKER>

select * from x$ksmfsv where ksmfsnam = 'ksdhngsyst_';

72baad88 -> +128 -> +168
72baad88 -> +184 -> +168
*/


/*******************************
 *           EVENT
 *******************************/
#define SIZE_KSLEI 640

/* KSLEI */
typedef struct _kslei {
   int INDX;
   t_uint64 KSLESWTS_UN;
   t_uint64 KSLESTMO_UN;
   t_uint64 KSLESTIM_UN;
   t_uint64 KSLESMXT_UN;
   t_uint64 KSLESWTS_FG;
   t_uint64 KSLESTMO_FG;
   t_uint64 KSLESTIM_FG;
   t_uint64 KSLESMXT_FG;
   t_uint64 KSLESWTS_BG;
   t_uint64 KSLESTMO_BG;
   t_uint64 KSLESTIM_BG;
   t_uint64 KSLESMXT_BG;
} Kslei;

/* KSLEI OFFSET */
typedef struct _off_kslei {

   int OFF_KSLESWTS_UN;
   int OFF_KSLESTMO_UN;
   int OFF_KSLESTIM_UN;
   int OFF_KSLESMXT_UN;
   int OFF_KSLESWTS_FG;
   int OFF_KSLESTMO_FG;
   int OFF_KSLESTIM_FG;
   int OFF_KSLESMXT_FG;
   int OFF_KSLESWTS_BG;
   int OFF_KSLESTMO_BG;
   int OFF_KSLESTIM_BG;
   int OFF_KSLESMXT_BG;
} OFF_kslei;

/*******************************
 *           STAT           
 *******************************/
#define P_STAT 88
#define U_STAT 72
#define OFF_SESSTAT 2040
#define QUEUE_SIZE 60
#define DATA_INTERVAL 3

typedef struct _stat {
   int INDX;
   t_uint64 VALUE;
   t_uint64 SYS;
} Stat;

typedef struct _ustat {
   int INDX;
   t_uint64 ADDR;
} uStat;

typedef struct _ready {
   Stat  *data;
   Ksuse *user;
   int s_ready;
   int u_ready;
} ready;

typedef struct {
   Stat  *data[QUEUE_SIZE];
   Ksuse *user[QUEUE_SIZE];
   char  *time[QUEUE_SIZE];
   int data_count[2];
   int front;
   int rear;
   int count;
} StatQueue;

void initQueue(StatQueue *queue);
int isQueueEmpty(StatQueue *queue);
int isQueueFull(StatQueue *queue);

void enqueue(StatQueue *queue);
Stat* dequeue(StatQueue *queue);
void printQueue(StatQueue *queue);
void storeSnapshotInQueue(StatQueue *queue, void *input, int type);