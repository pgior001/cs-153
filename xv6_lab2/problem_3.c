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
int bc = 0;
int mc = 0;
int cc = 0;


int main(int argc, char *argv[]){

   initSemaphore(&b, 3);
   initSemaphore(&c, 1);
   initSemaphore(&m, 1);
   initSemaphore(&d, 0);

   void *tid = thread_create(MissionaryArrives, 0);
 //  tid = thread_create(CannibalArrives, 0);
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
    ++cc;
    sem_acquire(&m);
    if(mc + cc == 3)
    {
      sem_signal(&m);
      sem_signal(&c);
      void *tid = thread_create(boat, 0);
      printf(1, "Cannibal starting boat crossing\n");
         if(tid <= 0){
           printf(1,"wrong happen");
           exit();
         }
    }
    else{
      sem_signal(&m);
      sem_signal(&c);
    }
    texit();
}

void MissionaryArrives(void *arg_ptr){
    sem_acquire(&b);
    sem_acquire(&c);
    sem_acquire(&m);
    ++mc;
    if(mc + cc == 3)
    {
      sem_signal(&c);
      sem_signal(&m);
      void *tid = thread_create(boat, 0);
      printf(1, "Missionary starting boat crossing\n");
         if(tid <= 0){
           printf(1,"wrong happen");
           exit();
         }
    }
    else{
      sem_signal(&c);
      sem_signal(&m);
    }
    texit();
}

void boat(void *arg_ptr){
    printf(1, "looking for passengers\n");
    sem_acquire(&c);
    sem_acquire(&m);
    printf(1, "%d\n", mc ==1);
    if(mc == 1){
       sem_signal(&b);
    }
    sem_signal(&m);
    sem_signal(&c);
    while(mc == 1 && cc != 3);
    sem_acquire(&c);
    sem_acquire(&m);
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

