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
  int i;
  for(i = 0; i < 10; i++)
  {
     tid = thread_create(H, (void *)0);
     if(tid == 0)
     {
       printf(1, "Thread Creation Failed!");
       exit();
     }
  }
  for(i = 0; i < 10; i++)
  {
     tid = thread_create(O, (void *)0);
     if(tid == 0)
     {
       printf(1, "Thread Creation Failed!");
       exit();
     }
  }
  for(i = 0; i < 10; i++)
  {
     tid = thread_create(H, (void *)0);
     if(tid == 0)
     {
       printf(1, "Thread Creation Failed!");
       exit();
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
