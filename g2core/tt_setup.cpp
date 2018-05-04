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

ToolHolder th;
void th_make_holder(void){
	th.tools[0]=T1;
	th.tools[1]=T2;
	th.tools[2]=T3;
	th.tools[3]=T4;
	th.tools[4]=T5;
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
thlidState th_get_lid_state(void){ return th.lid_state; }

// Set functions //NOTE:missing physical pin change
// need to change both pins when changing state
//void tt_set_tool_offest(aTool T){} // I'm missing offset definition
void th_set_lid_state(const thlidState th_lid_state){
	th.lid_state=th_lid_state;
}

// General functions
stat_t th_primeTable(void){
	bool flagsXY[] = {1,1,0,0,0,0};
	stat_t NSWYAOSB = STAT_OK; //NotSureWhatYouAreOrShouldBe
	cm_spindle_off_immediate();
	cm_coolant_off_immediate();
	// spindle fan thing
	NSWYAOSB = th_goToHeight(SAFE_HEIGHT);
	NSWYAOSB = cm_straight_traverse(&th.position1[0], &flagsXY[0]);
	NSWYAOSB = th_goToHeight(TH_HEIGHT);
	// blow clean air
	NSWYAOSB = cm_straight_traverse(&th.position2[0], &flagsXY[0]);
	// clean air of
	NSWYAOSB = th_goToHeight(SAFE_HEIGHT);
	return STAT_OK;
}
void th_toolReturn(aTool theTool){
	bool flagsXY[] = {1,1,0,0,0,0};
	bool flagsZ[] = {0,0,1,0,0,0};
	stat_t NSWYAOSB = STAT_OK; //NotSureWhatYouAreOrShouldBe
	NSWYAOSB = cm_straight_traverse(theTool.position, &flagsXY[0]);
	NSWYAOSB = cm_straight_traverse(theTool.position, &flagsZ[0]);
	// valve command
	NSWYAOSB=th_goToHeight(TH_HEIGHT);
	// check switch feedback
	theTool.inHolder=IN_HOLDER;
}

void th_toolPickup(aTool theTool){
	bool flagsXY[] = {1,1,0,0,0,0};
	bool flagsZ[] = {0,0,1,0,0,0};
	bool* flagsXY_ptr =flagsXY;
	bool* flagsZ_ptr =flagsZ;
	stat_t NSWYAOSB = STAT_OK; //NotSureWhatYouAreOrShouldBe
	NSWYAOSB = cm_straight_traverse(theTool.position, flagsXY_ptr);
	NSWYAOSB = cm_straight_traverse(theTool.position, flagsZ_ptr);
	// valve command
	NSWYAOSB = th_goToHeight(TH_HEIGHT);
	// check switch feedback
	theTool.inHolder=IN_SPINDLE;
}

stat_t th_goToHeight(float height){
	bool flags[]  = { 0,0,1,0,0,0 };
	float value[] = {0,0,height,0,0,0};
	return(cm_straight_traverse(&value[0], &flags[0]));
}

