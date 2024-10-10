#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common.h"

/*******************************************
 * list function
 *******************************************/

void addHead(LinkedList *list, void *data) {
   Node *node = (Node*) malloc(sizeof(Node));
   node->data = data;

   if ( list->head == NULL ) {
      list->tail = node;
      node->next = NULL;
   }
   else {
      node->next = list->head;
   }

   list->head = node;
}


void initList(LinkedList *list) {
   list->head = NULL;
   list->tail = NULL;
   list->current = NULL;
}

/*******************************************
 * common function
 *******************************************/

char *ltrim(char *str) {
   
   while(*str) {
      if(isspace(*str)) {
         str++;
      } else {
         break;
      }
   }
   return str;
}

char *rtrim(char *str) {

   int len = (int)strlen(str) - 1;
   
   while (len >= 0) {
      if(isspace(*(str + len))) {
         len--;
      } else {
      break;
      }
   }
   *(str + ++len) = '\0';
   return str;
}

void h_str(char *str, unsigned int hexval) {

   int len=0;

   while(1) {
      str[len] = *((char*)hexval+len);

      if(str[len] == '\0') return;
      len++;
   }
}

void h_str_l(char *str, unsigned int hexval, int len) {
   
   while(len--) {
      str[len] = *((char*)hexval+len);
   }
}

void p_str(char *s_str, char *t_str) {
   
   int len=0;

   while(len <= strlen(t_str)) {
      s_str[len] = t_str[len];
      len++;
   }
   
   *(s_str + ++len) = '\0';
}

void setBase32(char *s_str, t_uint64 t_int) {

   t_uint64 p_val = (t_uint64)pow(32.0,12.0);
   
   int slen;
   
   char tmpchar;

   for(slen=0 ; slen < 13 ; slen++) {

      switch((int)(t_int/p_val)) {
         case 0 :
            tmpchar = '0';
            break;
         case 1 :
            tmpchar = '1';
            break;
         case 2 :
            tmpchar = '2';
             break;
         case 3 :
            tmpchar = '3';
               break;
         case 4 :
            tmpchar = '4';
            break;
         case 5 :
            tmpchar = '5';
            break;
         case 6 :
            tmpchar = '6';
            break;
         case 7 :
            tmpchar = '7';
            break;
         case 8 :
            tmpchar = '8';
            break;
         case 9 :
            tmpchar = '9';
            break;
         case 10 :
            tmpchar = 'a';
            break;
         case 11 :
            tmpchar = 'b';
            break;
         case 12 :
            tmpchar = 'C';
            break;
         case 13 :
            tmpchar = 'd';
            break;
         case 14 :
            tmpchar = 'f';
            break;
         case 15 :
            tmpchar = 'g';
            break;
         case 16 :
            tmpchar = 'h';
            break;
         case 17 :
            tmpchar = 'j';
            break;
         case 18 :
            tmpchar = 'k';
            break;
         case 19 :
            tmpchar = 'm';
            break;
         case 20 :
            tmpchar = 'n';
            break;
         case 21 :
            tmpchar = 'p';
            break;
         case 22 :
            tmpchar = 'q';
            break;
         case 23 :
            tmpchar = 'r';
            break;
         case 24 :
            tmpchar = 's';
            break;
         case 25 :
            tmpchar = 't';
            break;
         case 26 :
            tmpchar = 'u';
            break;
         case 27 :
            tmpchar = 'v';
            break;
         case 28 :
            tmpchar = 'w';
            break;
         case 29 :
            tmpchar = 'x';
            break;
         case 30 :
            tmpchar = 'y';
            break;
         case 31 :
            tmpchar = 'z';
            break;
      }
      s_str[slen] = tmpchar;
      t_int = t_int % p_val;
      p_val /= 32;
    }
}

void getDate(char *s_str, int t_int) {

   struct tm* t;
   time_t base = t_int;

   t = localtime(&base);
   
   //printf("%d-%d-%d %d:%d:%d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
   if(t_int != 0)
      snprintf(s_str, 20, "%4d-%02d-%02d %02d:%02d:%02d", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	return;
}

void getLTM(char *s_str, t_uint64 t_int) {

   int cnt=0;

   snprintf(s_str, 20, "%2d%2d-%02d-%02d %02d:%02d:%02d",
    *(char*)(t_int)-100, *(char*)(t_int+1)-100, *(char*)(t_int+2), *(char*)(t_int+3), *(char*)(t_int+4)-1, *(char*)(t_int+5)-1, *(char*)(t_int+6)-1);
}

void escapeJsonString(char *input, char *output, size_t max_len) {
    size_t i = 0;
    size_t j = 0;
    for (i = 0; input[i] != '\0' && j < max_len - 1; i++) {
        switch (input[i]) {
            case '\n':
                if (j + 2 < max_len - 1) {
                    output[j++] = '\\';
                    output[j++] = 'n';
                }
                break;
            case '\r':
                if (j + 2 < max_len - 1) {
                    output[j++] = '\\';
                    output[j++] = 'r';
                }
                break;
            case '\t':
                if (j + 2 < max_len - 1) {
                    output[j++] = '\\';
                    output[j++] = 't';
                }
                break;
            case '\\':
                if (j + 2 < max_len - 1) {
                    output[j++] = '\\';
                    output[j++] = '\\';
                }
                break;
            case '\"':
                if (j + 2 < max_len - 1) {
                    output[j++] = '\\';
                    output[j++] = '\"';
                }
                break;
            default:
                if ((unsigned char)input[i] < 32) {
                    if (j + 6 < max_len - 1) {
                        j += snprintf(output + j, max_len - j, "\\u%04x", (unsigned char)input[i]);
                    }
                } else {
                    output[j++] = input[i];
                }
                break;
        }
    }
    output[j] = '\0';
}