// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#include "Submarine.h"

#if CLI_ENABLED == ENABLED

// Command/function table for the setup menu
static const struct Menu::command setup_menu_commands[] PROGMEM = {
	// command			function called
	// =======        	===============
	{"erase",			MENU_FUNC(setup_erase)}
};

// Create the setup menu object.
MENU(setup_menu, "setup", setup_menu_commands);

// Called from the top-level menu to run the setup menu.
int8_t Submarine::setup_mode(uint8_t argc, const Menu::arg *argv)
{
	// Give the user some guidance
	cliSerial->printf_P(PSTR("Setup Mode\n"
						 "\n"
						 "IMPORTANT: if you have not previously set this system up, use the\n"
						 "'reset' command to initialize the EEPROM to sensible default values\n"
						 "and then the 'radio' command to configure for your radio.\n"
						 "\n"));

	// Run the setup menu.  When the menu exits, we will return to the main menu.
	setup_menu.run();
    return 0;
}

int8_t Submarine::setup_erase(uint8_t argc, const Menu::arg *argv)
{
	int			c;

	cliSerial->printf_P(PSTR("\nType 'Y' and hit Enter to erase all waypoint and parameter data, any other key to abort: "));

	do {
		c = cliSerial->read();
	} while (-1 == c);

	if (('y' != c) && ('Y' != c))
		return(-1);
	zero_eeprom();
	return 0;
}

void Submarine::zero_eeprom(void)
{
	cliSerial->printf_P(PSTR("\nErasing EEPROM\n"));
    StorageManager::erase();
	cliSerial->printf_P(PSTR("done\n"));
}

#endif // CLI_ENABLED
