/*
 * game.h
 *
 *  Created on: Mar 17, 2025
 *      Author: patry
 */

#ifndef INC_GAME_H_
#define INC_GAME_H_

#include "stdint.h"

uint8_t check_win_condition(uint8_t led_state);
void adder_button(uint8_t *led_state);
void toggler_button(uint8_t *led_state);
void shifter_button(uint8_t *led_state);

#endif /* INC_GAME_H_ */
