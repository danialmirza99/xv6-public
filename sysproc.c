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
  return fork();
}

int
sys_exit(void)
{
  int status;
  argint(0, &status); //check this later
  exit(status);
  return 0;  // not reached
}

int
sys_wait(void)
{
  int *status;
  argptr(0,(char **) &status, sizeof(int*));
  return wait(status);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
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
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_hello(void){
  hello();
  return 0;
}
/*
int
sys_waitpid() {
  argint(0, &pid);
  argptr(0,(char **) &status, sizeof(int*));
  argint(0, &options);
  return 0;
}
*/

void
sys_set_prior(void)
{
  int prior_val = 10;
  return set_prior(prior_val);
}

int
sys_updating_prior_val(void){
  int pid, prior_val;
  if (argint(0,&pid) < 0){
    return -1;
  }
  if (argint(1,&prior_val) < 0){
    return -1;
  }
  return updating_prior_val(pid, prior_val);
}
