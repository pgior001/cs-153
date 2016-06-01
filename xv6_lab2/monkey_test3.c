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
  int i;
  for(i = 0; i < 7; i++)
  {
    int j = nrand(1000) % 10;
    //int j = 0;
    // while(j < 100000)
    //  j++;
     printf(1, "Monkey is spawning \n", i);
     tid = thread_create(monkey, (void *)j);
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

void monkey(void * arg_ptr)
{
  if((int)arg_ptr % 7 == 0)
  {
    sem_acquire(&d_Lock);
    dominant++;
    sem_signal(&d_Lock);
    printf(1,"Dominant monkey is waiting \n", (int)arg_ptr);
  }
  else
  {
    printf(1,"Normal monkey is waiting \n", (int)arg_ptr);
    while(dominant != 0){}
  }
  sem_acquire(&tree);
  if((int)arg_ptr % 7 == 0)
  {
    sem_acquire(&d_Lock);
    dominant--;
    sem_signal(&d_Lock);
    printf(1,"Dominant monkey up the tree \n", (int)arg_ptr);
  }
  else
  {
    printf(1, "Normal monkey up the tree \n", (int)arg_ptr);
  }

  int j = 0;                                                                
   while(j < 1000000)                                                        
    j++;  

  sem_signal(&tree);
  exit();
}
