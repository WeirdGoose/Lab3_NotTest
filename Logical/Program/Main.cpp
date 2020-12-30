
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// amount of memory to be allocated for heap storage must be specified for every ANSI C++ program with the bur_heap_size variable
unsigned long bur_heap_size = 0xFFFF; 

void _INIT ProgramInit(void)
{
	// Insert code here 
	Axis_X_HW.EncIf1_Typ = ncSDC_ENC16;
	Axis_X_HW.DiDoIf_Typ = ncSDC_DIDO;
	Axis_X_HW.DrvIf_Typ = ncSDC_DRVSERVO16;
	//strcpy(Axis_X_HW.EncIf1_Name, "Axis_X_EncIf");
	//strcpy(Axis_X_HW.DrvIf_Name, "Axis_X_DrvIf");
	//strcpy(Axis_X_HW.DiDoIf_Name, "Axis_X_DiDoIf");

	Axis_X_ModuleOk = 1;
	Axis_X_EncIf.iEncOK = 1;
	Axis_X_DrvIf.iDrvOK = 1;
	Axis_X_DrvIf.iStatusEnable = 1;
	Axis_X_DiDoIf.iDriveReady = 1;
	
	axis_X.last_counter = 0;
	axis_X.counter = axis_X.last_counter;
	pwm_period = 0.05;
	axis_X.pwm_period = pwm_period;
	
	
	axis_X.fb_controller.dt = 0.002;
	axis_X.fb_controller.integrator.dt = 0.002;
	axis_X.fb_controller.k_i = 0.0072;
	axis_X.fb_controller.k_p = 0.0072;
	axis_X.fb_controller.max_abs_value = 40.0;
	
	fb_motor.dt = 0.01;
	fb_motor.ke = 1;
	fb_motor.Tm = 0.1;
	fb_motor.u = 0;
	fb_motor.phi = 0;
	fb_motor.integrator.dt = 0.01;
	
}

void _CYCLIC ProgramCyclic(void)
{
	// Insert code here 
	Axis_X_EncIf.iLifeCnt++;
	Axis_X_EncIf.iActTime = (INT)AsIOTimeCyclicStart();
	Axis_X_DrvIf.iLifeCnt++;
	Axis_X_DrvIf.oSetPos = Axis_X.monitor.v;
	Axis_X_DiDoIf.iLifeCntDriveEnable++;
	Axis_X_DiDoIf.iLifeCntDriveReady++;
	Axis_X_DiDoIf.iLifeCntNegHwEnd++;
	Axis_X_DiDoIf.iLifeCntPosHwEnd++;
	Axis_X_DiDoIf.iLifeCntReference++;
	
	axis_X.iActPos = Axis_X_EncIf.iActPos;
	axis_X.iLifeCnt = Axis_X_EncIf.iLifeCnt;
	axis_X.iNegHwEnd = Axis_X_DiDoIf.iNegHwEnd;
	axis_X.iPosHwEnd = Axis_X_DiDoIf.iPosHwEnd;
	axis_X.oSetPos = Axis_X_DrvIf.oSetPos;
	
	FB_Axis(&axis_X);
	
	Axis_X_EncIf.iActPos = axis_X.iActPos;
	Axis_X_EncIf.iLifeCnt = axis_X.iLifeCnt;
	Axis_X_DiDoIf.iNegHwEnd = axis_X.iNegHwEnd;
	Axis_X_DiDoIf.iPosHwEnd = axis_X.iPosHwEnd;
	Axis_X_DrvIf.oSetPos = axis_X.oSetPos;
	
	if(Axis_X_DrvIf.oSetPos != 0)
	{
		fb_motor.u = axis_X.pwm_value / axis_X.pwm_period * 32767;
		FB_Motor(&fb_motor);
		axis_X.counter = fb_motor.phi;
		
		axis_X.endswitch_a_reached = axis_X.counter <= -3000 ? 1 : 0;
		axis_X.endswitch_b_reached = axis_X.counter >= 3000 ? 1 : 0;
	}

}

void _EXIT ProgramExit(void)
{
	// Insert code here 
	
}
