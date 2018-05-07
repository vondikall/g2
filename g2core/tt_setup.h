/*
 * tt_setup.h
 *
 * Created: 29.4.2018 21:00:23
 *  Author: Vondikall
 */ 
#include "g2core.h"
#include "config.h"
#include "canonical_machine.h"
#include "settings.h"

#ifndef TH_SETUP_H_
#define TH_SETUP_H_

// Needs fixing. is in placeholder mode.
#define SAFE_HEIGHT		((float)1) //This probably exists somewhere in settings but i cant currently find it.
#define	TH_HEIGHT		((float)1) // travel height above tt. Should be safe travel height if the lid is closed
#define TH_POSITION1_X	((float)1)
#define TH_POSITION1_Y	((float)1)
#define TH_POSITION2_X	((float)1)
#define TH_POSITION2_Y	((float)1)
#define HOLD			true
#define RELEASE			false


typedef enum{
	ALL_IN = 0,
	ONE_MISSING,
	INVALID_STATUS
}thtoolPinStatus;

typedef enum{
	CLOSED = 0,
	OPEN
}thlidState;

typedef enum{
	IN_SPINDLE = 0,
	IN_HOLDER
}toolState;


typedef struct aTool {
	float position[AXES] = { 0,0,0,0,0,0 };
	uint8_t number = 0;
	toolState inHolder;
	// not sure what type the offset is
	// want to add a message with tool description if called
}aTool;

typedef struct ToolHolder {
	aTool tools[TOOLS];
	bool toolPins[TOOLS];
	thtoolPinStatus toolPins_status = ALL_IN;
	thlidState lid_state = CLOSED; // polarity not picked
	float position1[AXES] = { TH_POSITION1_X,TH_POSITION1_Y,0,0,0,0 };
	float position2[AXES] = { TH_POSITION2_X,TH_POSITION2_Y,0,0,0,0 };
	float travelHeight[AXES] = {TH_HEIGHT,0,0,0,0,0};
} ToolHolder;

/***********************************************************************************
 **** Functions ********************************************************************
 ***********************************************************************************/
// Make functions. Tools and table are defined by user in tt_setup.cpp
void th_make_tools(void);
void th_make_holder(void);
void tool_holder_init(void);

// Get and set functions
toolState th_get_tool_state(aTool T);
thlidState th_get_lid_state(void);
void th_set_tool_offest(aTool T);

stat_t th_set_valve_state(bool state);
void _exec_set_valve_state(float target[], bool flags[]);
stat_t th_set_lid_state(thlidState th_lid_state);
void _exec_set_lid_state(float target[], bool flags[]);
stat_t set_air_flow(bool state);
void _exec_set_air_flow(float target[], bool flags[]);

// Tool return and Tool pickup functions
stat_t th_primeTable(void);
stat_t th_toolReturn(aTool theTool);
stat_t th_toolPickup(aTool theTool);
stat_t th_toolPinsQuiry(thtoolPinStatus quiry);

#endif /* TT_SETUP_H_ */
