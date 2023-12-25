#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "log.h"

struct log_linked_list {
  char *strdat;
  struct log_linked_list *next;
} typedef log_t;


log_t *HEAD = NULL;
log_t *curr_log = NULL;

// int init(){
//   HEAD = malloc(sizeof(log_t));
//   if(HEAD != NULL){
//     *HEAD = (log_t){"", NULL};
//   }

//   return 0;
// }

// int add_log(char *txt){
//   curr_log->strdat = txt;
//   curr_log->next = malloc(sizeof(log_t));
//   curr_log = curr_log->next;

//   return 0;
// }

log_t *getlog(){
  if(HEAD == NULL){
    HEAD = malloc(sizeof(log_t));
    curr_log = HEAD;
  }
  return curr_log;
}

int ltrace(){   //make all logs variadic 
  return 1;
}

int ldebug(){
  return 1;
}

int linfo(){
  return 1;
}

int lerror(){
  return 1;
}

int lfatal(){
  return 1;
}

int free_log(log_t *head){
  while(head != NULL){
    log_t *n = head->next;
    free(head);
    head = n;
  }

  return 0;
}

int display_log(log_t *head){
  while(head != NULL){
    printf("%s\n", head->strdat);
  }

  return 0;
}

int main(){
  display_log(HEAD);
  
  free_log(HEAD);

  return 1;
}
