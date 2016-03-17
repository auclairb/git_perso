#include <stdio.h>
#include <pthread.h>


void * thread1(){
  printf("hello je suis thread 1 !\n");
  return NULL;
}

void * thread2(){
  printf("hello je suis thread 2 !\n");
  return NULL;
}

int main(){
  pthread_t th1,th2;

  pthread_create(&th1, NULL, thread1, NULL);
  pthread_create(&th2, NULL, thread2, NULL);

  pthread_join(th1,NULL);
  pthread_join(th2,NULL);

  return 0;
  

}
