#include <stdio.h>
#include <pthread.h>
#include <time.h>

char *returnTime() {
   time_t rawtime;
   char *buffer = malloc(80);
   time(&rawtime);
   struct tm *timeinfo = localtime(&rawtime);
   strftime(buffer, 80, "%I:%M:%S", timeinfo);
   return buffer;
}

void threadFunction() {
   printf("Поток: pid=%d, id=%d, время %s\n", getpid(), pthread_self(), returnTime());
}

int main() {
   pthread_t thread1;
   pthread_t thread2;

   int err1;
   int err2;

   printf("Родительский процесс(поток): pid=%d, id=%d, время %s\n", getpid(), pthread_self(), returnTime());

   err1 = pthread_create(&thread1, NULL, threadFunction, NULL);

   if (err1)
   {
       printf("An error occured: %d", err1);
       return 1;
   }
   
   err2 = pthread_create(&thread2, NULL, threadFunction, NULL);

   if (err2)
   {
       printf("An error occured: %d", err2);
       return 1;
   }
  
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);

   return 0;
}
