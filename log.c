#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "log.h"

typedef struct list_struct{
  data_t item;
  struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

char *datparse(data_t data){
  char *time = ctime(&data.time);
  removeNewline(time);
  char *out = calloc(strlen(time)+strlen(data.string)+10, sizeof(char));
  strcat(out, time);
  strcat(out, "   --   ");
  strcat(out, data.string);
  strcat(out, "\n");

  return out;
}

int logprntstr(char* string){
  return logstr(string, 1);
}

int logprntdat(data_t data){
  return logdat(data, 1);
}

int logstr(char* string, int p){
  return logdat((data_t){.time = time(NULL), .string = string}, p);
}

int logdat(data_t data, int p){
  if(p == 1){
    char* dpar = datparse(data);
    fprintf(stdout, "%s", dpar);
    free(dpar);
  }
  
  if(tailptr == NULL){
    headptr = malloc(sizeof(log_t));
    tailptr = headptr;
  }
  else{
    tailptr->next = malloc(sizeof(log_t)); 
    tailptr = tailptr->next;
  }

  tailptr->item = data;
  tailptr->next = NULL;

  return 0;
}

void clearlog(void){
  log_t *next;
  while(headptr != NULL){
    next = headptr->next;
    free(headptr);
    headptr = next;
  }

  return;
}

void removeNewline(char *str) {
  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
      str[len - 1] = '\0';
  }
}

char *getlog(void){
  log_t *current = headptr;
  char* buf = NULL; // = realloc(buf, 0);
  char *time_string;
  int last = 0;

  while(current != NULL){
    if(buf == NULL){
      buf = calloc(sizeof(char)*(strlen(current->item.string) + strlen(ctime(&(current->item.time))) + 9) + last, sizeof(char));
    }
    else{
      buf = realloc(buf, sizeof(char)*(strlen(current->item.string) + strlen(ctime(&(current->item.time))) + 9) + last);
    }   
    last += sizeof(char)*(strlen(current->item.string) + strlen(ctime(&(current->item.time))) + 9) + sizeof(buf);

    time_string = ctime(&current->item.time);
    removeNewline(time_string);

    strcat(buf, time_string);
    strcat(buf, "   --   ");
    strcat(buf, current->item.string);
    strcat(buf, "\n");

    current = current->next;
  }

  return buf;
}

int savelog(char* filename){ 
  FILE* fp = (filename == NULL) ? stdout : fopen(filename, "w+");
  
  char *buf = getlog();
  fprintf(fp, "%s", buf);
  if(fp != stdout){
    fclose(fp);
  }
  
  free(buf);
  return 0;
}

// int main(){
//   time_t currentTime;
//   time(&currentTime);

//   data_t d;
//   d.string = "yay";
//   d.time = currentTime;

//   data_t b;
//   b.string = "uhoh";
//   b.time = currentTime;

//   logprntdat(d);
//   logprntstr("test");

//   savelog(NULL);
//   clearlog();

//   return 0;
// }
