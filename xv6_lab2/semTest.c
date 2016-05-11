#include "param.h"
#include "syscall.h"
#include "semaphore.h"

void test_func(void * arg_ptr);

semaphore sem1;

int main(int argc, char ** argv)
{
  initSemaphore(&sem1, 1);
  void *tid;
  int i;
  for(i = 0; i < 10; i++)
  {
     tid = thread_create(test_func, (void *)0);
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

void test_func(void * arg_ptr)
{
  sem_acquire(&sem1);
  int j = 0;
  while(j < 1000000)
  {
    j++;
  }
  printf(1, "Process %d has semaphore 1\n", getpid());
  sem_signal(&sem1);
  exit();
}
