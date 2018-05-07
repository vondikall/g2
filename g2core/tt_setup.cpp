/*
 * tt_setup.cpp
 *
 * Created: 29.4.2018 21:00:00
 *  Author: Vondikall
 */ 
/*
C:\Users\Vondikall\Documents\GitHub\g2\g2core\canonical_machine.h (Line 410 for tool hight offset)
*/


#include "tt_setup.h"
#include "g2core.h"
#include "config.h"
#include "canonical_machine.h"
#include "spindle.h"
#include "coolant.h"
#include "planner.h"
#include "user_pins.h"

aTool T1; aTool T2; aTool T3; aTool T4; aTool T5;
void th_make_tools(void){
	T1.position[0]=0.0; // x
	T1.position[1]=0.0; // y
	T1.position[2]=0.0; // z
	T1.number=1;
	T1.inHolder = IN_HOLDER;
	
	T2.position[0]=0.0;
	T2.position[1]=0.0;
	T2.position[2]=0.0;
	T2.number=2;
	T2.inHolder = IN_HOLDER;
	
	T3.position[0]=0.0;
	T3.position[1]=0.0;
	T3.position[2]=0.0;
	T3.number=3;
	T3.inHolder = IN_HOLDER;
	
	T4.position[0]=0.0;
	T4.position[1]=0.0;
	T4.position[2]=0.0;
	T4.number=4;
	T4.inHolder = IN_HOLDER;
	
	T5.position[0]=0.0;
	T5.position[1]=0.0;
	T5.position[2]=0.0;
	T5.number=5;
	T5.inHolder = IN_HOLDER;
}


void th_make_holder(void){
	cm.th.tools[0]=T1;
	cm.th.tools[1]=T2;
	cm.th.tools[2]=T3;
	cm.th.tools[3]=T4;
	cm.th.tools[4]=T5;
	cm.th.toolPins[0]=tool1_pin;
	cm.th.toolPins[1]=tool2_pin;
	cm.th.toolPins[2]=tool3_pin;
	cm.th.toolPins[3]=tool4_pin;
	cm.th.toolPins[4]=tool5_pin;
}

void tool_holder_init(void){
	th_make_tools();
	th_make_holder();
}

/***********************************************************************************
 **** CODE *************************************************************************
 ***********************************************************************************/

// Get functions
toolState th_get_tool_state(aTool T){ return T.inHolder; }
thlidState th_get_lid_state(void){ return cm.th.lid_state; }

stat_t th_set_valve_state(bool state){
	bool flags[] = {state,0,0,0,0,0};
	float value[] = {0,0,0,0,0,0};
	mp_queue_command(_exec_set_valve_state,&value[0],&flags[0]);
	return STAT_OK;
}
void _exec_set_valve_state(float target[], bool flags[]){
	atc_pin=flags[0];
}

stat_t th_set_lid_state(thlidState th_lid_state){
	cm.th.lid_state=th_lid_state;
	bool flags[] = {cm.th.lid_state,0,0,0,0,0};
	float value[] = {0,0,0,0,0,0};
	mp_queue_command(_exec_set_lid_state,&value[0],&flags[0]);
	return STAT_OK;
}
void _exec_set_lid_state(float target[], bool flags[]){
	lid_on_pin = flags[0];
	lid_off_pin = !flags[0];
}


stat_t set_air_flow(bool state){
	bool flags[] = {state,0,0,0,0,0};
	float value[] = {0,0,0,0,0,0};
	mp_queue_command(_exec_set_air_flow,&value[0],&flags[0]);
	return STAT_OK;
}
void _exec_set_air_flow(float value[], bool flags[]){
	cleanair_pin=flags[0];
}

// General functions
stat_t th_primeTable(void){
	bool flagsXY[] = {1,1,0,0,0,0};
	bool flagsZ[] = {0,0,1,0,0,0};
	float safe[] = {0,0,SAFE_HEIGHT,0,0,0};
			
	cm_spindle_off_immediate();
	cm_coolant_off_immediate();
	ritorno(cm_straight_traverse(&safe[0], &flagsZ[0]));
	ritorno(cm_straight_traverse(&cm.th.position1[0], &flagsXY[0]));
	ritorno(cm_straight_traverse(&cm.th.travelHeight[0], &flagsZ[0]));
	ritorno(set_air_flow(true));
	ritorno(cm_straight_traverse(&cm.th.position2[0], &flagsXY[0]));
	ritorno(set_air_flow(false));
	ritorno(cm_straight_traverse(&safe[0], &flagsZ[0]));
	ritorno(th_set_lid_state(OPEN));
	return STAT_OK;
}
stat_t th_toolReturn(aTool theTool){
	bool flagsXY[] = {1,1,0,0,0,0};
	bool flagsZ[] = {0,0,1,0,0,0};
			
	ritorno(cm_straight_traverse(&theTool.position[0], &flagsXY[0]));
	ritorno(cm_straight_traverse(&theTool.position[0], &flagsZ[0]));
	ritorno(th_set_valve_state((bool)RELEASE));
	ritorno(cm_straight_traverse(&cm.th.travelHeight[0], &flagsZ[0]));
	ritorno(th_toolPinsQuiry(ALL_IN));
	theTool.inHolder=IN_HOLDER;
	return STAT_OK;
}

stat_t th_toolPickup(aTool theTool){
	bool flagsXY[] = {1,1,0,0,0,0};
	bool flagsZ[] = {0,0,1,0,0,0};
	
	ritorno(cm_straight_traverse(&theTool.position[0], &flagsXY[0]));
	ritorno(cm_straight_traverse(&theTool.position[0], &flagsZ[0]));
	ritorno(th_set_valve_state((bool)HOLD));
	ritorno(cm_straight_traverse(&cm.th.travelHeight[0], &flagsZ[0]))
	ritorno(th_toolPinsQuiry(ONE_MISSING));
	theTool.inHolder=IN_SPINDLE;
	return STAT_OK;
}

stat_t th_toolPinsQuiry(thtoolPinStatus quiry){
	int i=0; int count=0;
	while (i<TOOLS){
		if (cm.th.toolPins[i]==IN_SPINDLE){ count++; }
	}
	if(count==0){cm.th.toolPins_status=ALL_IN;}
	if(count==1){cm.th.toolPins_status=ONE_MISSING;}
	else{ cm.th.toolPins_status=INVALID_STATUS; }
	if(quiry==cm.th.toolPins_status){return STAT_OK;}
	else{ return STAT_ERROR;}
}
