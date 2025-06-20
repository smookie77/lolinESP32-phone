/**
 * @file display_handlers.cpp
 * @author smookie77
 * @brief Handlers for display modes in the lolinESP32 phone project.
 * @version 0.1
 * @date 2025-06-02
 * 
 * Implements handlers for different display modes.
 */
#include <display_handlers.h>
#include <keyboard.h>
#include <display_prints.h>
#include <serialH.h>
#include <string_utils.h>
#include <battery.h>
#include <Preferences.h>
#include <gsm.h> // Make sure this is included


// --- Settings menu state and variables: place here, after includes, before any function ---

enum SettingsMenuState {
    SETTINGS_MENU_MAIN,
    SETTINGS_MENU_EDIT_PIN,
    SETTINGS_MENU_EDIT_CONTRAST,
    SETTINGS_MENU_EDIT_SSID,
    SETTINGS_MENU_EDIT_PASS
};
static SettingsMenuState settings_state = SETTINGS_MENU_MAIN;
static int settings_selected = 0; // 0: SIM PIN, 1: Contrast, 2: SSID, 3: Password

char sim_pin[9] = "0000";
int contrast = LCD_CONTRAST;
char wifi_ssid[33] = "MotorolaGearSolid";
char wifi_pass[33] = "batpesho4";

static int edit_pos = 0;
static char edit_buffer[33] = {0};

static const char* settings_items[4] = {
    "SIM PIN",
    "Contrast",
    "WiFi SSID",
    "WiFi Pass"
};

extern Adafruit_PCD8544 display;
extern displayMode_e current_displayMode;

static int selected_app = 0; // 0: discord, 1: phone, 2: messages
static int entered_app = -1; // -1 means no app entered

// Helper for icon positions (left, center, right)
static const int app_icon_x[3] = {0, 42-12, 84-24};

Preferences prefs;

void settings_load_from_flash() {
    prefs.begin("settings", true); // read-only
    prefs.getString("sim_pin", sim_pin, sizeof(sim_pin));
    contrast = prefs.getInt("contrast", LCD_CONTRAST);
    prefs.getString("wifi_ssid", wifi_ssid, sizeof(wifi_ssid));
    prefs.getString("wifi_pass", wifi_pass, sizeof(wifi_pass));
    prefs.end();
}

void settings_save_to_flash() {
    prefs.begin("settings", false); // read-write
    prefs.putString("sim_pin", sim_pin);
    prefs.putInt("contrast", contrast);
    prefs.putString("wifi_ssid", wifi_ssid);
    prefs.putString("wifi_pass", wifi_pass);
    prefs.end();
}

/**
 * @brief Handle the display boot mode, showing system info and waiting for tasks.
 */
void display_handleMode_boot(){
	char bootText[128];
	snprintf(bootText, sizeof(bootText), 
		"SOP-PHONE %s\n"
		"BAT RAW: %d\n"
		"BAT V: %.2f\n"
		"KeyboardTask: \n"
		"GSMTask: \n"
		"BOOT: ",
		PHONE_VER,
		readBattery_raw(),
		readBattery_volts()
	);
	serial_buffer_write(SERIAL_TASK_DISPLAY, "Display: boot mode\n", 20);
	serial_buffer_write(SERIAL_TASK_DISPLAY, bootText, strlen(bootText));
	display_print_ScrollingMenu(1, 6, bootText);
	
	while(eTaskGetState(keyboard_Task) == eInvalid) {
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
	display_print("*", 1, 84-6, 24);
	while(eTaskGetState(keyboard_Task) == eInvalid) {
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
	display_print("*", 1, 84-6, 32);
	display_print("*", 1, 84-6, 40);
}


#define STATUS_ICONS_Y 0
#define BAT_ICON_X 76
#define CELLULAR_ICON_X 60
#define WIFI_ICON_X 52
#define APP_ICONS_Y 11

Icon_t get_wifi_icon(int signalStrength) {
    if (!wifi_isConnected) {
        return wifi_none;
    }
    // RSSI ranges typically from -100 dBm (weak) to -50 dBm (strong)
    if (signalStrength >= -65) {
        return wifi_full;
    } else if (signalStrength >= -75) {
        return wifi_med;
    } else {
        return wifi_low;
    }
}

Icon_t get_cellular_icon(int signalStrength) {
    if (!gsm_isConnected) {
        return cellular_none;
    }
    // GSM signal quality ranges from 0-31
    if (signalStrength > 24) {
        return cellular_full;
    } else if (signalStrength > 16) {
        return cellular_4;
    } else if (signalStrength > 8) {
        return cellular_3;
    } else if (signalStrength > 4) {
        return cellular_2;
    } else {
        return cellular_1;
    }
}

Icon_t get_battery_icon(float bat_vol){
    // Adjust thresholds as needed for your battery chemistry
    if (bat_vol > 4.0) {
        return battery_full;
    } else if (bat_vol > 3.6) {
        return battery_mid;
    } else {
        return battery_low;
    }
}

void display_print_statusBar(){
    display_print_icon(get_cellular_icon(gsm_signalStrength), CELLULAR_ICON_X, STATUS_ICONS_Y);
    display_print_icon(get_wifi_icon(wifi_signalStrength), WIFI_ICON_X, STATUS_ICONS_Y);
    display_print_icon(get_battery_icon(readBattery_volts()), BAT_ICON_X, STATUS_ICONS_Y);
    display.drawFastHLine(0, 7, 84, BLACK);

    // Parse datetime string from SIM800, expected format: "yy/MM/dd,hh:mm:ss+zz"
    int year, month, day, hours, minutes;
    hours = 0; minutes = 0;
    if (sscanf(datetime.c_str(), "%d/%d/%d,%d:%d", &year, &month, &day, &hours, &minutes) == 5) {
        char timeStr[6];
        snprintf(timeStr, sizeof(timeStr), "%02d:%02d", hours, minutes);
        display_print(timeStr, 1, 0);
    } else {
        display_print("??:??", 1, 0);
    }
}

void display_handleMode_main(){
    display_print_statusBar();

    // Determine icon order: center is selected_app, left/right are the others
    Icon_t* icons[3] = {&discord, &phone, &settings};
    int left = (selected_app + 2) % 3;
    int center = selected_app;
    int right = (selected_app + 1) % 3;

    display_print_icon(*icons[left],   app_icon_x[0], APP_ICONS_Y);
    display_print_icon(*icons[center], app_icon_x[1], APP_ICONS_Y);
    display_print_icon(*icons[right],  app_icon_x[2], APP_ICONS_Y);

    // Draw selector arrow under the center icon
    display_print("^", 1, app_icon_x[1] + 10, 35);

    display.drawFastHLine(0, 48-10, 84, BLACK);
    // display_print("APP NAME", 1, 5);
    switch (selected_app) {
        case 0: display_print("Discord", 1, 5); break;
        case 1: display_print("Phone", 1, 5); break;
        case 2: display_print("Settings", 1, 5); break;
        default: display.print("Unknown App"); break;
    }
}

// Add this function to handle menu navigation
void display_handleMenuNavigation() {
    char key = keyboard_getKey();
    if (key == '<') {
        selected_app = (selected_app + 2) % 3; // Move left, wrap around
    } else if (key == '>') {
        selected_app = (selected_app + 1) % 3; // Move right, wrap around
    } else if (key == 'X') {
        // Enter the selected app
        entered_app = selected_app;
        switch (entered_app) {
        case 0: current_displayMode = displayMode_app_discord; break;
        case 1: current_displayMode = displayMode_app_phone; break;
        case 2:  current_displayMode = displayMode_app_settings; break;
    }
    }
}

// Optionally, add a stub for the app display mode:
void display_handleMode_app() {
    display_print_statusBar();
    // Show which app is entered, for demonstration
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    switch (entered_app) {
        case 0: display.print("Discord App"); break;
        case 1: display.print("Phone App"); break;
        case 2: display.print("Settings App"); break;
        default: display.print("Unknown App"); break;
    }
    display.setCursor(0, 16);
    display.print("Press '*' to exit");
    // Handle exit
    char key = keyboard_getKey();
    if (key == '*') {
        current_displayMode = displayMode_main;
        entered_app = -1;
    }
}

void display_handleMode_app_discord(){
    display_handleMode_app();

    char key = keyboard_getKey();
    if (key == '*') {
        current_displayMode = displayMode_main;
        entered_app = -1;
    }
}


void display_handleMode_app_phone(){
    static char dial_number[17] = ""; // 16 digits max, plus null
    static int dial_pos = 0;
    display_print_statusBar();

    display.setCursor(0, 12);
    display.setTextSize(1);
    display.print("Dial: ");
    display.print(dial_number);

    display.setCursor(0, 28);
    display.print("<:Del X:Call *:Exit");

    char key = keyboard_getKey();
    if (key >= '0' && key <= '9' && dial_pos < 16) {
        dial_number[dial_pos++] = key;
        dial_number[dial_pos] = '\0';
    } else if (key == '<' && dial_pos > 0) {
        dial_number[--dial_pos] = '\0';
    } else if (key == 'X' && dial_pos > 0) {
        gsm_make_call(dial_number);
        // Optionally, clear number after dialing
        dial_number[0] = '\0';
        dial_pos = 0;
    } else if (key == '*') {
        current_displayMode = displayMode_main;
        dial_number[0] = '\0';
        dial_pos = 0;
    }
}


void display_handleMode_app_settings(){
    char key = keyboard_getKey();

    switch (settings_state) {
    case SETTINGS_MENU_MAIN:
        // Draw menu (only menu, not values)
        display_print("SETTINGS", 1, 0);
        display.drawFastHLine(0,8,84,BLACK);
        for (int i = 0; i < 4; ++i) {
            char line[20];
            if (i == settings_selected) {
                snprintf(line, sizeof(line), "> %s", settings_items[i]);
            } else {
                snprintf(line, sizeof(line), "  %s", settings_items[i]);
            }
            display_print(line, 1, 1, 12 + i*9);
        }
        // Navigation
        if (key == '<') {
            settings_selected = (settings_selected + 3) % 4;
        } else if (key == '>') {
            settings_selected = (settings_selected + 1) % 4;
        } else if (key == 'X') {
            edit_pos = 0;
            switch(settings_selected) {
                case 0: strncpy(edit_buffer, sim_pin, sizeof(sim_pin)); settings_state = SETTINGS_MENU_EDIT_PIN; break;
                case 1: settings_state = SETTINGS_MENU_EDIT_CONTRAST; break;
                case 2: strncpy(edit_buffer, wifi_ssid, sizeof(wifi_ssid)); settings_state = SETTINGS_MENU_EDIT_SSID; break;
                case 3: strncpy(edit_buffer, wifi_pass, sizeof(wifi_pass)); settings_state = SETTINGS_MENU_EDIT_PASS; break;
            }
        } else if (key == '*') {
            current_displayMode = displayMode_main;
        }
        break;

    case SETTINGS_MENU_EDIT_PIN:
        display_print("Edit SIM PIN:", 1, 0);
        display_print(edit_buffer, 1, 0, 12);
        display_print("^", 1, 0 + edit_pos*6, 20);
        display_print("X=OK  *=Back", 1, 0, 36);
        if (key >= '0' && key <= '9' && edit_pos < 8) {
            edit_buffer[edit_pos++] = key;
            edit_buffer[edit_pos] = '\0';
        } else if (key == '<' && edit_pos > 0) {
            --edit_pos;
        } else if (key == '>' && edit_pos < (int)strlen(edit_buffer)) {
            ++edit_pos;
        } else if (key == 'X') { // Confirm/save
            strncpy(sim_pin, edit_buffer, sizeof(sim_pin));
            settings_save_to_flash();
            settings_state = SETTINGS_MENU_MAIN;
        } else if (key == '*') { // Cancel/back
            settings_state = SETTINGS_MENU_MAIN;
        }
        break;

    case SETTINGS_MENU_EDIT_CONTRAST:
        {
        char contrast_line[20];
        snprintf(contrast_line, sizeof(contrast_line), "Contrast: %d", contrast);
        display_print(contrast_line, 1, 0, 12);
        display_print("< > to change", 1, 0, 22);
        display_print("X=OK  *=Back", 1, 0, 36);
        if (key == '<' && contrast > 0) {
            contrast--;
            display.setContrast(contrast);
        } else if (key == '>' && contrast < 127) {
            contrast++;
            display.setContrast(contrast);
        } else if (key == 'X') { // Confirm/save
            settings_save_to_flash();
            settings_state = SETTINGS_MENU_MAIN;
        } else if (key == '*') { // Cancel/back
            settings_state = SETTINGS_MENU_MAIN;
        }
        }
        break;

    case SETTINGS_MENU_EDIT_SSID:
        display_print("Edit SSID:", 1, 0);
        display_print(edit_buffer, 1, 0, 12);
        display_print("^", 1, 0 + edit_pos*6, 20);
        display_print("X=OK  *=Back", 1, 0, 36);
        // Accept all printable ASCII including '*' and 'X'
        if (key == 'X') { // Confirm/save
            strncpy(wifi_ssid, edit_buffer, sizeof(wifi_ssid));
            settings_save_to_flash();
            settings_state = SETTINGS_MENU_MAIN;
        } else if (key == '*') { // Cancel/back
            settings_state = SETTINGS_MENU_MAIN;
        } else if (key == '<' && edit_pos > 0) {
            --edit_pos;
        } else if (key == '>' && edit_pos < (int)strlen(edit_buffer)) {
            ++edit_pos;
        } else if (key >= 32 && key <= 126 && edit_pos < 32) {
            edit_buffer[edit_pos++] = key;
            edit_buffer[edit_pos] = '\0';
        } 
        break;

    case SETTINGS_MENU_EDIT_PASS:
        display_print("Edit WiFi Pass:", 1, 0);
        display_print(edit_buffer, 1, 0, 12);
        display_print("^", 1, 0 + edit_pos*6, 20);
        display_print("X=OK  *=Back", 1, 0, 36);
        // Accept all printable ASCII including '*' and 'X'
        if (key == 'X') { // Confirm/save
            strncpy(wifi_pass, edit_buffer, sizeof(wifi_pass));
            settings_save_to_flash();
            settings_state = SETTINGS_MENU_MAIN;
        } else if (key == '*') { // Cancel/back
            settings_state = SETTINGS_MENU_MAIN;
        } else if (key == '<' && edit_pos > 0) {
            --edit_pos;
        } else if (key == '>' && edit_pos < (int)strlen(edit_buffer)) {
            ++edit_pos;
        } else if (key >= 32 && key <= 126 && edit_pos < 32) {
            edit_buffer[edit_pos++] = key;
            edit_buffer[edit_pos] = '\0';
        } 
        break;
    }
}

void display_handleMode_incoming_call() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Incoming Call!");
    display.setCursor(0, 16);
    display.print("Press # to answer");
    display.setCursor(0, 24);
    display.print("Press * to reject");

    char key = keyboard_getKey();
    if (key == '#') {
        // Accept call logic here
        // e.g. gsm_answer_call();
        // Optionally switch to a "call in progress" mode
        current_displayMode = displayMode_main;
    } else if (key == '*') {
        // Reject call logic here
        gsm_hangup();
        current_displayMode = displayMode_main;
    }
}

