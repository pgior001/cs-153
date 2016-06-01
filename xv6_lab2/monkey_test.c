#include "param.h"
#include "syscall.h"
#include "semaphore.h"

void monkey(void * arg_ptr);

semaphore tree;
semaphore d_Lock;
int dominant = 0;

int main(int argc, char ** argv)
{
  initSemaphore(&tree, 3);
  initSemaphore(&d_Lock, 1);
  void *tid;
  printf(1, "Monkey is Spawning\n");
  tid = thread_create(monkey, (void *)1);
  tid = thread_create(monkey, (void *)2);
  tid = thread_create(monkey, (void *)3);
  tid = thread_create(monkey, (void *)4);
  tid = thread_create(monkey, (void *)0);

  while(wait() >= 0);

  exit();
  return 0;
}

void monkey(void * arg_ptr)
{
  if((int)arg_ptr % 7 == 0)
  {
    sem_acquire(&d_Lock);
    dominant++;
    sem_signal(&d_Lock);
    printf(1,"monkey %d is waiting \n", (int)arg_ptr);
  }
  else
  {
    printf(1,"monkey %d is waiting \n", (int)arg_ptr);
    while(dominant != 0){}
  }
  sem_acquire(&tree);
  if((int)arg_ptr % 7 == 0)
  {
    sem_acquire(&d_Lock);
    dominant--;
    sem_signal(&d_Lock);
    printf(1,"Dominant monkey %d up the tree \n", (int)arg_ptr);
  }
  else
  {
    printf(1, "Normal monkey %d up the tree \n", (int)arg_ptr);
  }

  int j = 0;                                                                
   while(j < 1000000)                                                        
    j++;  

  sem_signal(&tree);
  exit();
}
