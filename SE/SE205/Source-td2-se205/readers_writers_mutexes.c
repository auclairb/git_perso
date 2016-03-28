#include "readers_writers_mutexes.h"

void rw_mutex_init (r_mutex_t * r_mutex, w_mutex_t * w_mutex){
  w_mutex->writer = 1;
  r_mutex->n_readers = 0;
}

void rw_mutex_read_lock (r_mutex_t *r_mutex, w_mutex_t * w_mutex, thread_conf_t *conf){
  int i;
  while(w_mutex->writer <=0);
  r_mutex->n_readers = r_mutex->n_readers + 1;
    for (i=0; i < r_mutex->n_readers; i++) printf ("  ");
  printf ("reader (%ld) : enter r = %d v = %ld\n",
	  conf->identifier, r_mutex->n_readers, shared_variable);
}

void rw_mutex_read_unlock (r_mutex_t *r_mutex, thread_conf_t * conf){
  int i;
  for (i=0; i < r_mutex->n_readers; i++) printf ("  ");
  printf ("reader (%ld) : leave r = %d v = %ld\n",
	  conf->identifier, r_mutex->n_readers, shared_variable);
  r_mutex->n_readers = r_mutex->n_readers - 1;
}

void rw_mutex_writer_lock (r_mutex_t *r_mutex, w_mutex_t * w_mutex, thread_conf_t * conf){
  w_mutex->writer = w_mutex->writer - 1;
  while(r_mutex->n_readers > 0 || w_mutex->writer <0);
}

void rw_mutex_writer_unlock (w_mutex_t *w_mutex, thread_conf_t * conf){
  w_mutex->writer = w_mutex->writer + 1;
}
