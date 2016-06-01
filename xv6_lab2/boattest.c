#include "param.h"
#include "syscall.h"
#include "semaphore.h"

void CannibalArrives(void * arg_ptr);
void boat(void* arg_ptr);
void MissionaryArrives(void *arg_ptr);

semaphore b;
semaphore d;
semaphore m;
semaphore c;
semaphore passengers;
int bc = 0;
int mc = 0;
int cc = 0;
int extra = 0;


int main(int argc, char *argv[]){

   initSemaphore(&b, 3);
   initSemaphore(&passengers, 1);
   initSemaphore(&c, 1);
   initSemaphore(&m, 1);
   initSemaphore(&d, 0);

   void *tid = thread_create(boat,0);
   tid = thread_create(MissionaryArrives, 0);
   tid = thread_create(MissionaryArrives, 0);
   tid = thread_create(MissionaryArrives, 0);


   if(tid <= 0){
       printf(1,"wrong happen");
       exit();
   } 
   while(wait()>= 0);

   exit();
   return 0;
}

void CannibalArrives(void *arg_ptr){
    sem_acquire(&b);
    sem_acquire(&c);
    printf(1, "cannibal arrives\n");
    ++cc;
    sem_signal(&c);
    sem_signal(&d);
    texit();
}

void MissionaryArrives(void *arg_ptr){
    sem_acquire(&b);
    sem_acquire(&m);
    printf(1, "Missionary Arrives\n");
    ++mc;
    sem_signal(&m);
    sem_signal(&d);
    texit();
}

void boat(void *arg_ptr){
    sem_acquire(&passengers);
    sem_acquire(&d);
    sem_acquire(&d);
    printf(1, "got two passengers\n");
    sem_acquire(&d);
    printf(1, "got three passengers\n");
    sem_acquire(&c);
    sem_acquire(&m);
    if(mc == 1){
      sem_signal(&b);
      sem_signal(&m);
      sem_signal(&c);
      while(mc == 1 && cc != 3);
      sem_acquire(&c);
      sem_acquire(&m);
 
    }
    sem_signal(&passengers);
    if(mc == 2){
      printf(1, "Two missionaires and one cannibal across \n");
      mc = mc-2;
      --cc;
    }
    else if(mc ==3){
      printf(1, "Three missionaries across\n");
      mc = mc - 3;
    }
    else{
      printf(1, "Three cannibals across\n");
      cc = cc-3;
    }
    if(cc == 0 && mc ==0){
      sem_signal(&b);
    }
    sem_signal(&b);
    sem_signal(&b);
    sem_signal(&m);
    sem_signal(&c);
    texit();
}

