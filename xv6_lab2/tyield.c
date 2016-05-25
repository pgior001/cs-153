#include "semaphore.h"

int threadCount = 0;
semaphore lock;

void test_func(void * arg_ptr);
void long_thread(void *arg_ptr);

int main(int argc, char *argv[]){

   initSemaphore(&lock, 1);
   int i = 0;
   for(i = 0; i < 10; ++i){
      void *tid = thread_create(long_thread, 0);
      if(tid <= 0){
          printf(1,"wrong happen");
          exit();
      } 
   }
   void *tid = thread_create(test_func, 0);
   if(tid <= 0){
       printf(1,"wrong happen");
       exit();
   }
   i = 0;
   for(i= 0; i < 10; ++i){
      void *tid = thread_create(long_thread, 0);
      if(tid <= 0){
          printf(1,"wrong happen");
          exit();
      }
   }


   while(wait()>= 0);
   
   exit();
}

//void test_func(void *arg_ptr){
void test_func(void *arg_ptr){
  sem_acquire(&lock);
  ++threadCount;
  sem_signal(&lock);
  while(threadCount > 1){
   thread_yield();
  }
  sem_acquire(&lock);
  --threadCount;
  printf(1, "last thread finishing\n");
  sem_signal(&lock);
  texit();
}

void long_thread(void *arg_ptr){
  int i = 0;
  sem_acquire(&lock);
  ++threadCount;
  sem_signal(&lock);
  while(i < 2000000){
   ++i;
  }
  sem_acquire(&lock);
  --threadCount;
  printf(1, "thread count: %d\n", threadCount);
  sem_signal(&lock);
  texit();
}


