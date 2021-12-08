#ifndef __TASKS_H__
#define __TASKS_H__
// Task struct
typedef struct task_t{
  unsigned long period;
  unsigned long elaspedTime;
  int state;
  int (*TickFct)(int);
} task_t;


#endif
