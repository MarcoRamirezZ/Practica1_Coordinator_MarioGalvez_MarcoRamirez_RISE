/*
 * MyNewTask.h
 *
 *  Created on: 27 oct. 2020
 *      Author: marco
 */

#ifndef MYNEWTASK_H_
#define MYNEWTASK_H_

/* Fwk*/
#include"TimersManager.h"
#include"FunctionLib.h"
#include"LED.h"

/* KSDK */
#include"fsl_common.h"
#include"EmbeddedTypes.h"
#include"fsl_os_abstraction.h"

/* Define the available Task's Events */
#define gMyNewTaskEvent1_c (1 << 0)
#define gMyNewTaskEvent2_c (1 << 1)
#define gMyNewTaskEvent3_c (1 << 2)

#define gMyTaskPriority_c 3
#define gMyTaskStackSize_c 400

void MyTaskTimer_Start(void);
void MyTaskTimer_Stop(void);
void MyTask_Init(void);



#endif /* MYNEWTASK_H_ */
