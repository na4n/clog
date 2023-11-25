#include <time.h>

typedef struct data_struct{
  time_t time;
  char* string;
} data_t;

char *datparse(data_t data);
int logprntstr(char* string);
int logprntdat(data_t data);
int logstr(char* string, int p);
int logdat(data_t data, int p);
void clearlog(void);
void removeNewline(char *str) ;
char *getlog(void);
int savelog(char* filename);