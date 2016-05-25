#include "param.h"
#include "syscall.h"
#include "semaphore.h"

void CannibalArrives(void * arg_ptr);
void boat(void* arg_ptr);
void MissionaryArrives(void *arg_ptr);

semaphore b;
semaphore d;
semaphore p1;
semaphore p2;
semaphore m;
semaphore c;
int mc = 0;
int cc = 0;


int main(int argc, char *argv[]){

   initSemaphore(&b, 3);
   initSemaohore(&p1, 1);
   initSemaphore(&p2, 1);
   initSemaphore(&c, 1);
   initSemaphore(&m, 1);
   initSemaphore(&d, 0)

   void *tid = thread_create(test_func, 0);
   if(tid <= 0){
       printf(1,"wrong happen");
       exit();
   } 
   while(wait()>= 0)
   
   exit();
}

//void test_func(void *arg_ptr){
void CannibalArrives(void *arg_ptr){
    sem_acquire(&b);
    sem_acquire(&c);
    ++c;
    sem_signal(&c);
    sem_signal(&d);
    texit();
}

void MissionaryArrives(void *arg_ptr){
    sem_acquire(&b);
    sem_acquire(&m);
    ++m;
    sem_signal(&m);
    sem_signal(&d);
    texit();
}

void boat(void *arg_ptr){
    sem_acquire(&p2);
    sem_acquire(&d);
    sem_acquire(&d);
    sem_acquire(&d);
    sem_acquire(&m)
    while(mc == 1){
       sem_signal(&b);
       sem_signal(&m)
       sem_acquire(&m);
    }
    if(mc == 2){
      sem_acquire(&c);
      printf(1, "Two missionaires and one cannibal across \n");
      mc = mc-2;
      --cc;
      sem_signal(&c);
    }
    else if(mc ==3){
      printf(1, "Three missionaries across\n")
      mc = mc - 3;
    }
    else{
      sem_acquire(&c);
      printf(1, "Three cannibals across\n");
      cc = cc-3;
      sem_signal(&c);
    }
    acquire(&c);
    if(cc == 0 && mc ==0){
      sem_signal(&b);
    }
    sem_signal(&b);
    sem_signal(&b);
    sem_signal(&m);
    sem_signal(&c);
    texit();
}

