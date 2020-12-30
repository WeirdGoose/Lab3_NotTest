
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_Axis(struct FB_Axis* inst)
{
	/*TODO: Add your code here*/
	/*if (!(inst->endswitch_a_reached || inst->endswitch_b_reached))
	{
		inst->pwm_value=inst->u/24.0*32767;
		inst->reset_error=0;
		inst->speed=inst->u/24.0*6500.0;
	}
	else
	{
		if(inst->endswitch_a_reached)
		{
			inst->speed=inst->u/24.0*6500.0;
			inst->pwm_value=inst->u/24.0*32767;
		}
		if(inst->endswitch_b_reached)
		{
			inst->speed=inst->u/24.0*(-6500.0);
			inst->pwm_value=inst->u/24.0*(-32767);
		}
	}*/

	
	inst->counter_memory += inst->counter - inst->last_counter;
	inst->last_counter = inst->counter;
	inst->iActPos = inst->counter;
	if((inst->iLifeCnt) % 6000 == 0)
	{
		inst->speed = (inst->counter) / (0.002 * 6000); // cycle = 2 ms
		inst->counter = 0;
	}
	
	inst->iNegHwEnd = inst->endswitch_a_reached;
	inst->iPosHwEnd = inst->endswitch_b_reached;
	
	inst->speed_d = inst->oSetPos * 24 / 32767;
	inst->fb_controller.e = inst->speed_d - inst->speed;
	FB_controller(&(inst->fb_controller));
	inst->pwm_value = (inst->fb_controller.u) / (inst->fb_controller.max_abs_value) * (inst->pwm_period);
	
}
