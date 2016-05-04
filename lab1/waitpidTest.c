#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc,char *argv[]){
  int i, pid;
  int mainpid = getpid();
  int status = -2;
  int status2 = -2;
  for(i = 0; (i <= 15 && getpid() == mainpid); ++i){
    pid = fork();
  }
  if(getpid() == 10){
    printf(1, "process 10 waiting on process 6 \n");
    if(waitpid(6, &status, 0) == 6){
      printf(1, "cleaning up process 6\n");
    }
  }
  else if(getpid() == 12)
  {
    printf(1, "process 12 waiting on process 6\n");
    if(waitpid(6, &status2, 0) == 6){
      printf(1, "cleaning up process 6\n");
    }
  }
  int j = 0;
  int k = 0;
  while(j < 2000000){
    ++j;
    while(k < 50){
      ++k;
    }
    k = 0;
  }
  if(pid != 0){
    int exiting;
    while((exiting = wait(0)) > 0){
      printf(1, "cleaning up process %d \n", exiting);
    }
  }
  printf(1, "process %d finished\n", getpid());
  exit(0);
}
