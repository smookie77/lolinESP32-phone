/**
 * @file display_handlers.h
 * @author smookie77 
 * @brief Display handler functions for the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-04
 * 
 * Provides functions for handling different display modes.
 */
#ifndef DISPLAY_HANDLERS_H_
#define DISPLAY_HANDLERS_H_

#include <display.h>
#include <phone_defines.h>
#include <battery.h>
#include <serialH.h>
#include <icons.h>
#include <wifi.h>
#include <gsm.h>

/**
 * @brief Handle the display boot mode.
 */
void display_handleMode_boot();
void display_handleMode_main();
Icon_t get_wifi_icon(int signalStrength);
Icon_t get_cellular_icon(int signalStrength);
void display_handleMenuNavigation();
void display_print_statusBar();

void display_handleMode_app_discord();
void display_handleMode_app_phone();
void display_handleMode_app_settings();
void settings_load_from_flash();
void settings_save_to_flash();
void display_handleMode_incoming_call();

#endif //DISPLAY_HANDLERS_H_