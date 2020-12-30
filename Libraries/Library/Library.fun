
{REDUND_ERROR} FUNCTION_BLOCK FB_Axis (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		reset_error : BOOL;
		endswitch_a_reached : BOOL;
		endswitch_b_reached : BOOL;
		u : INT;
	END_VAR
	VAR_OUTPUT
		pwm_value : INT;
		counter : INT;
		speed : REAL;
	END_VAR
	VAR
		reset_counter : BOOL;
		last_counter : INT;
		counter_memory : INT;
		speed_d : REAL;
		fb_controller : FB_controller;
		pwm_period : UINT;
		iLifeCnt : SINT;
		iPosHwEnd : USINT;
		iNegHwEnd : BOOL;
		iActPos : INT;
		oSetPos : INT;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_controller (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		e : {REDUND_UNREPLICABLE} REAL;
	END_VAR
	VAR_OUTPUT
		u : {REDUND_UNREPLICABLE} REAL;
	END_VAR
	VAR
		k_p : {REDUND_UNREPLICABLE} REAL;
		k_i : {REDUND_UNREPLICABLE} REAL;
		integrator : {REDUND_UNREPLICABLE} FB_Integrator;
		iyOld : {REDUND_UNREPLICABLE} REAL;
		max_abs_value : REAL;
		dt : REAL;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_Integrator (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		in : REAL;
	END_VAR
	VAR_OUTPUT
		out : REAL;
	END_VAR
	VAR
		dt : REAL;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} FUNCTION_BLOCK FB_Motor (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		u : REAL;
	END_VAR
	VAR_OUTPUT
		w : REAL;
		phi : REAL;
	END_VAR
	VAR
		integrator : FB_Integrator;
		Tm : REAL;
		ke : REAL;
		dt : REAL;
	END_VAR
END_FUNCTION_BLOCK
