#include "syscall.h"
#include "param.h"
#include "semaphore.h"
//#include "types.h"
//#include "user.h"

void
initSemaphore(semaphore *s, int size)
{
  s->maxHold = size;
  s->queueSize = 0;
  lock_init(s->lock);
}

void
sem_acquire(semaphore* s)
{
  lock_acquire(s->lock);
  if(s->maxHold == 0)
  {
    if(s->queueSize == 60)
    {
      printf(1, "error acuireing semaphore");
      exit();
    }
    else
    {
      s->queue[s->queueSize] = getpid();
      s->queueSize++;
      lock_release(s->lock);
      tsleep();
      lock_acquire(s->lock);
    }
  }
  else
  {
    s->maxHold--;
  }
  lock_release(s->lock);
}

void
sem_signal(semaphore *s)
{
  lock_acquire(s->lock);
  if(s->queueSize == 0)
  {
    s->maxHold++;
  }
  else
  {
    int tmp = s->queue[0];
    int i;
    for(i = 1; i < s->queueSize; ++i)
    {
      s->queue[i - 1] = s->queue[i];
    }
    s->queueSize--;
    twakeup(tmp);
  }
  lock_release(s->lock);
}
