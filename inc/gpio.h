/*
 * gpio.h
 *
 *  Created on: Mar 17, 2025
 *      Author: patry
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

void leds_init(void);
void leds_update(uint8_t led_state);
void buttons_init(void);

#endif /* INC_GPIO_H_ */
