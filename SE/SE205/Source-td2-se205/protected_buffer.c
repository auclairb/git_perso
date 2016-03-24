#include <pthread.h>
#include <stdlib.h>
#include "circular_buffer.h"
#include "protected_buffer.h"

protected_buffer_t * protected_buffer_init(int length) {
  protected_buffer_t * b;
  b = (protected_buffer_t *)malloc(sizeof(protected_buffer_t));
  b->buffer = circular_buffer_init(length);
  b->length = length;
  return b;
}

void * protected_buffer_get(protected_buffer_t * b){
  while( circular_buffer_size(b->buffer) < 1);
  pthread_mutex_lock(&(b->mutex));
  void * d = circular_buffer_get(b->buffer);
  pthread_mutex_unlock(&(b->mutex));
  return d;
}

int protected_buffer_put(protected_buffer_t * b, void * d){
  while (b->length == circular_buffer_size(b->buffer));
  pthread_mutex_lock(&(b->mutex));
  circular_buffer_put(b->buffer, d);
  pthread_mutex_unlock(&(b->mutex));
  return 1;
}
   
