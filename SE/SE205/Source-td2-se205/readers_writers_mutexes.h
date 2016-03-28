#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
  int n_readers;
} r_mutex_t;

typedef struct {
  int writer;
} w_mutex_t;


typedef struct {
  w_mutex_t * w_mutex;
  r_mutex_t * r_mutex;
  long offset;
  long exec_time;
  long rest_time;
  long increment;
  long identifier;
} thread_conf_t;

extern long shared_variable;

void rw_mutex_init(r_mutex_t * r_mutex, w_mutex_t * w_mutex);
void rw_mutex_read_lock (r_mutex_t * r_mutex, w_mutex_t * w_mutex, thread_conf_t * conf);
void rw_mutex_read_unlock (r_mutex_t * r_mutex, thread_conf_t * conf);
void rw_mutex_writer_lock (r_mutex_t * r_mutex, w_mutex_t * w_mutex, thread_conf_t * conf);
void rw_mutex_writer_unlock (w_mutex_t * w_mutex, thread_conf_t * conf);
