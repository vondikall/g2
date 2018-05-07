/*
 * user_pins.h
 *
 * Created: 27-04-2018 14:11:46
 *  Author: sephi
 */ 


#ifndef USER_PINS_H_
#define USER_PINS_H_
 
#include "MotatePins.h"

static Motate::OutputPin<Motate::atc_pinNumber> atc_pin;
static Motate::OutputPin<Motate::lid_on_pinNumber> lid_on_pin;
static Motate::OutputPin<Motate::lid_off_pinNumber> lid_off_pin;
static Motate::OutputPin<Motate::cleanair_pinNumber> cleanair_pin;
static Motate::OutputPin<Motate::aux_pinNumber> aux_pin;

static Motate::OutputPin<Motate::tool1_pinNumber> tool1_pin;
static Motate::OutputPin<Motate::tool2_pinNumber> tool2_pin;
static Motate::OutputPin<Motate::tool3_pinNumber> tool3_pin;
static Motate::OutputPin<Motate::tool4_pinNumber> tool4_pin;
static Motate::OutputPin<Motate::tool5_pinNumber> tool5_pin;
static Motate::OutputPin<Motate::tool6_pinNumber> tool6_pin;

// uint8_t tool_sel; // What is this? [Steff]

#endif /* USER_PINS_H_ */