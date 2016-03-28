#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "protected_buffer.h"

#define MAXDURATION 5
#define MAXTHREADS 256
int last_thread = -1;
int first_thread = 0;
pthread_t threads_table[MAXTHREADS];
protected_buffer_t * protected_buffer;


// Terminate thread
void process_exit() {
  pthread_exit(NULL);
}

// Find a terminated child process and return its tid
pthread_t process_wait() {
  pthread_t thread = NULL;
  
  if (first_thread <= last_thread) {
    thread = threads_table[first_thread];
    pthread_join(threads_table[first_thread],NULL);
    first_thread++;
  }

  return thread;
}

// Main procedure for a child process
void thread_main(void){
  pthread_t self = pthread_self();
  int       duration = random()%MAXDURATION + MAXDURATION/2;

  printf("thread (%p) sleeping for %d s\n", (void *)self, duration);
  sleep(duration);
  protected_buffer_put(protected_buffer, (void*) pthread_self());
  process_exit();
}

int main(int argc, char *argv[]){
  struct timeval t;
  struct timeval s = {0, 0};
  protected_buffer = protected_buffer_init(MAXTHREADS);
  
  if (argc != 2){ 
    printf("Usage : %s <n_threads>\n", argv[0]);
    exit(1);
  } 

  srandom(time(NULL));
  gettimeofday(&s, NULL);
  last_thread = atoi(argv[1]) - 1;


  // Creer autant de threads que demandé en ligne de commande
  int n;
  for (n = 0; n <= last_thread; n++) {
    usleep(1000);
    pthread_create(&threads_table[n],NULL,thread_main,NULL);
  }

  // Attendre la terminaison des threads dans un certain ordre
  //Partie de la question, à commenter pour la question 3
  /*
  pthread_t thread;
  while ((thread = process_wait()) != NULL) {
    gettimeofday(&t, NULL);
    printf("thread (%p) join after %d s\n", thread, (int)(t.tv_sec -s.tv_sec));   
    }*/

  //Partie de la question 3 à décommenter au moment de la question 3
  
    void * thread;
    while(first_thread<=last_thread){
    thread = protected_buffer_get(protected_buffer);
    if(thread !=NULL){
    gettimeofday(&t, NULL);
    printf("thread (%p) join after %d s\n", thread, (int)(t.tv_sec -s.tv_sec));
    first_thread++;
    }
    }
  
  
  return 0;

}





