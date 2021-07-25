/*
 * File: main.c
 *
 * Real-Time Workshop code generated for Simulink model pid.
 *
 * Model version                        : 1.18
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Fri Sep 30 17:01:27 2016
 * TLC version                          : 7.4 (Jul 14 2009)
 * C/C++ source code generated on       : Fri Sep 30 17:01:28 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "main.h"
static boolean_T OverrunFlag = 0;

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(void)
{
  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag++) 
	{
    rtmSetErrorStatus(pid_M, "Overrun");
    return;
  }

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  pid_step();
  /* Get model outputs here */
	
  /* Indicate task complete */
  OverrunFlag--;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustates how you do this relative to initializing the model.
 */
int16_t udk, i;

void main(void)
{
	
	/* Enable SysTick at 5ms interrupt */
  SysTick_Config(SystemCoreClock/200);
  
  delay_01ms(1000);
  init_main();
	PWM0_Set_Freq(1000);
	PWM0_Set_Duty(0);

  /* Initialize model */
  pid_initialize();

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.005 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   */

  while(1)
	{			  
		if(tick_flag) 
		{ 
			tick_flag = 0;
			
			In2 = (double)ENC0_GetPos()/4000.0 *360.0;
			rt_OneStep();
			Out1 = Out1*1000/12;
			
			udk = (int)Out1;
			PWM0_Set_Duty(udk);
			
			if(tick_count>4000)		break;
		}
	}	

	PWM0_Set_Duty(0);
	while(1)
	{
	}
  /* Terminate model */
  pid_terminate();
}

