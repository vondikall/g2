/*
 * tt_setup.cpp
 *
 * Created: 29.4.2018 21:00:00
 *  Author: Vondikall
 */ 
/*
C:\Users\Vondikall\Documents\GitHub\g2\g2core\canonical_machine.h Line 410 for tool hight offset
*/


#include "tt_setup.h"
#include "g2core.h"
#include "config.h"
#include "canonical_machine.h"

aTool T1;
aTool T2;
aTool T3;
aTool T4;
aTool T5;
void tt_make_tools(void){
	T1.position[0]=0.0; // x
	T1.position[1]=0.0; // y
	T1.position[2]=0.0; // z
	T1.number=1;
	T1.inTable=true;
	
	T2.position[0]=0.0;
	T2.position[1]=0.0;
	T2.position[2]=0.0;
	T2.number=2;
	T2.inTable=true;
	
	T3.position[0]=0.0;
	T3.position[1]=0.0;
	T3.position[2]=0.0;
	T3.number=3;
	T3.inTable=true;
	
	T4.position[0]=0.0;
	T4.position[1]=0.0;
	T4.position[2]=0.0;
	T4.number=4;
	T4.inTable=true;
	
	T5.position[0]=0.0;
	T5.position[1]=0.0;
	T5.position[2]=0.0;
	T5.number=5;
	T5.inTable=true;
}

ToolTable theTable;
void tt_make_table(void){
	theTable.tools[0]=T1;
	theTable.tools[1]=T2;
	theTable.tools[2]=T3;
	theTable.tools[3]=T4;
	theTable.tools[4]=T5;
}

bool tt_is_in_table(aTool T){
	return T.inTable;
}