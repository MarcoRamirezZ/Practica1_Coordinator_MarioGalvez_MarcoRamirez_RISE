/*
 * MyNewTask.c
 *
 *  Created on: 27 oct. 2020
 *      Author: Marco Antonio Ramírez Zepeda IE708370
 */

#include "MyNewTask.h"

void My_Task( osaTaskParam_t argument );
static void myTaskTimerCallback( void *param );

osaEventId_t mMyEvents;

/*Global variable to store our TimerID*/
tmrTimerID_t myTimerID = gTmrInvalidTimerID_c;

/*Handler ID for task*/
osaTaskId_t gMyTaskHandlerID = 0;

/*Local variable to store the current state of the LEDs*/
//static uint8_t ledsState = 0;

/*OSA Task Definition*/
OSA_TASK_DEFINE(My_Task, gMyTaskPriority_c, 1, gMyTaskStackSize_c, FALSE);

uint8_t gSwitch3Pressed = 0;
uint8_t gSwitch4Pressed = 0;


/*Main custom Task*/
void My_Task( osaTaskParam_t argument )
{
	osaEventFlags_t customEvent;
	myTimerID = TMR_AllocateTimer();

	while(1)
	{
		OSA_EventWait( mMyEvents, osaEventFlagsAll_c, FALSE, osaWaitForever_c, &customEvent );

		if( !gUseRtos_c && !customEvent )
		{
			break;
		}

		/*Depending on the received event */
		switch(customEvent)
		{
			case gMyNewTaskEvent1_c:  //Start timer to count 3 seconds and change the LEDs
				TMR_StartIntervalTimer(myTimerID, /*myTimerID*/3000, /* Timer's Timeout */myTaskTimerCallback, /* pointer to myTaskTimerCallback function */NULL);
				TurnOffLeds(); /* Ensure all LEDs are turned off */
				break;

			case gMyNewTaskEvent2_c: /* Event called from myTaskTimerCallback */
				//Evento usado para la recepción del switch 2 y 3
				if ( gSwitch3Pressed )
				{
					gSwitch3Pressed = 0; //reset to 0 to wait for next button press
					//gCounter = 1;   //Cuando se presione SW3 ponemos el counter de colores en 1
					//LED_Operate( void ); //Description: Basic LED operation: ON, OFF, TOGGLE. in LED.h

				}
				else if ( gSwitch4Pressed )
				{
					gSwitch4Pressed = 0; //reset to 0 to wait for next button press
					//gCounter = 2;   //Cuando se presione SW4 ponemos el counter de colores en 2
					//LED_Operate( void ); //Description: Basic LED operation: ON, OFF, TOGGLE. in LED.h
				}
				else
				{
					PRINTF("Switch indication not received, Try again.");
				}
				if(!ledsState)
//				{
//					TurnOnLeds();
//					ledsState = 1;
//				}
//				else
//				{
//					TurnOffLeds();
//					ledsState = 0;
//				}
				break;

			case gMyNewTaskEvent3_c: /* Event to stop the timer */
				ledsState = 0;
				TurnOffLeds();
				TMR_StopTimer(myTimerID);
				break;

			default:
				break;
		}
	}
}

/* Function to init the task */
void MyTask_Init(void)
{
	mMyEvents = OSA_EventCreate(TRUE);/* The instance of the MAC is passed at task creaton*/
	gMyTaskHandlerID = OSA_TaskCreate(OSA_TASK(My_Task), NULL);
}

/* Public function to send an event to start the timer */
void MyTaskTimer_Start(void)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent1_c);
}

/* This is the function called by the Timer each time it expires */
static void myTaskTimerCallback( void *param )
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent2_c);
}

/* Public function to send an event to stop the timer */
void MyTaskTimer_Stop(void)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent3_c);
}















