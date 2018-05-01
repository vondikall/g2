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

#ifndef TT_SETUP_H_
#define TT_SETUP_H_

#define SAFE_HIGHT //This probably exists somewhere in settings but i cant currently find it.


typedef struct aTool {
	float position[AXES] = { 0,0,0,0,0,0 };
	uint8_t number = 0;
	bool inTable = true;
	// not sure what type the ofset is
	// want to add a message with tool description if called
} aTool;

typedef struct ToolTable {
	aTool tools[TOOLS];
	// lidstatus        
} ToolTable;

void tt_make_tools(void);
void tt_make_table(void);
bool tt_is_in_table(aTool T);
//void tt_set_tool_offest(aTool T);
//void tt_openLid(void);
//bool tt_is_lid_open(void);



#endif /* TT_SETUP_H_ */