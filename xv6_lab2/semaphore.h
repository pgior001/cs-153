#include "types.h"
#include "user.h"

typedef struct{
  int maxHold;
  int queue[60];
  int queueSize;
  lock_t lock;
} semaphore;

void 
initSemaphore(semaphore *s, int size);

void
sem_acquire(semaphore* s);

void
  sem_signal(semaphore* s);

