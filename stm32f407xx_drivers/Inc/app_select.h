/*
 * app_select.h
 *
 *  Created on: May 3, 2026
 *      Author: Bilal Laiadi
 */

#ifndef APP_SELECT_H
#define APP_SELECT_H

#define APP_NONE                    0U
#define APP_LED_TOGGLE              1U
#define APP_LED_TOGGLE_BUTTON       2U
#define APP_LED_TOGGLE_BUTTON_IT    3U
#define APP_SPI_HALF_DUPLEX_TX      4U
#define APP_SPI_FULL_DUPLEX_TX      5U


/* Select exactly one application */
#define APP_SELECTED APP_SPI_FULL_DUPLEX_TX

#endif /* APP_SELECT_H */
