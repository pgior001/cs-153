#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  ++proc->count;
  return fork();
}

int
sys_exit(void)
{

 int status;
 if(argint(0, &status) < 0)
    return -1;
  proc->count++;
  exit(status);
  return 0;  // not reached
}

int
sys_wait(void)
{
  char* tmp = 0;
  int size = 4;
  if(argptr(0, &tmp, size) < 0)
    return -1;
  proc->count++;
  return wait((int*)tmp);
}

int
sys_kill(void)
{
  proc->count++;
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  proc->count++;
  return proc->pid;
}

int
sys_sbrk(void)
{
  proc->count++;
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  proc->count++;
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  proc->count++;
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_count(void)
{
  ++proc->count;
  return proc->count;
}


int
sys_waitpid(void)
{
  char* tmp = 0;
  int size = 4;
  int pid = 0;
  int options = 0;
  if(argint(0, &pid) < 0 || argptr(1, &tmp, size) || argint(2, &options))
    return -1;
  proc->count++;
  return waitpid(pid, (int*)tmp, options);
}

int
sys_priority_chance(void)
{
  proc->count++;
  return proc->priority;
}

int
sys_priorityChange(void)
{
  proc->count++;
  int priority;
  if(argint(0, &priority) < 0)
    return -1;
  priorityChange(priority);
  return proc->priority;
}
