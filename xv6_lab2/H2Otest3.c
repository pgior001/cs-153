#include "param.h"
#include "syscall.h"
#include "semaphore.h"

void H(void * arg_ptr);
void O(void * arg_ptr);

semaphore Hydrogen;
semaphore Oxygen;
//semaphore Water;
lock_t lock;
int water = 0;

int main(int argc, char ** argv)
{
  initSemaphore(&Hydrogen, 0);
  initSemaphore(&Oxygen, 0);
//  initSemaphore(&Water, 1);
  lock_init(&lock);
  void *tid;
  int h;
  int o;
  while(o < 5 && h < 10)
  {
    if(nrand(1000)% 2 == 0)
    {
      tid = thread_create(H, (void *)0);
      h++;
    }
    else
    {
      tid = thread_create(O, (void *)0);
      o++;
    }
  }
  if(h == 10)
  {
    while(o < 5)
    {
      tid = thread_create(O, (void *)0);
      o++;
    }
  }
  else
  {
    while(h < 10)
    {
      tid = thread_create(H, (void *)0);
      h++;
    }
  }
  while(wait() >= 0);

  exit();
  return 0;
}

void H(void * arg_ptr)
{
  sem_signal(&Hydrogen);
  sem_acquire(&Oxygen);
  printf(1, "hydrogen finished\n");
  texit();
}

void O(void * arg_ptr){
  sem_acquire(&Hydrogen);
  sem_acquire(&Hydrogen);
  sem_signal(&Oxygen);
  sem_signal(&Oxygen);
//  sem_acquire(&Water);
  lock_acquire(&lock);
  ++water;
  lock_release(&lock);
//  sem_signal(&Water);
  printf(1, "%d water molecules created\n", water);
  texit();
}
