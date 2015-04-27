/*
 * blueutil
 * Command-line utility to control Bluetooth.
 * Uses private API from IOBluetooth framework (i.e. IOBluetoothPreference*()).
 * http://www.frederikseiffert.de/blueutil
 * 
 * This software is public domain. It is provided without any warranty whatsoever,
 * and may be modified or used without attribution.
 *
 * Originally written by Frederik Seiffert <ego@frederikseiffert.de>
 *
 * Convert to C99 and add functions by Brian Reiter <brian.reiter@gmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "bluetooth.h"

#define ON 1
#define OFF 0

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


inline int BTPowerState()
{
	return IOBluetoothPreferenceGetControllerPowerState();
}

int BTSetPowerState(int powerState)
{
	IOBluetoothPreferenceSetControllerPowerState(powerState);
	
	usleep(2000000); // wait until BT has been set
	if (BTPowerState() != powerState) {
		printf("Error: unable to turn Bluetooth %s\n", powerState ? "on" : "off");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

void BTStatus()
{
	printf("Status: %s\n", BTPowerState() ? "on" : "off");
}

int main(int argc, const char * argv[])
{
	int result = EXIT_SUCCESS;

    if (!IOBluetoothPreferencesAvailable()) {
		printf("Error: Bluetooth not available");
		result = EXIT_FAILURE;
	} else if (argc == 2 && strcmp(argv[1], "status") == 0) {
		BTStatus();
	} else if (argc == 2 && strcmp(argv[1], "on") == 0) {
		result = BTSetPowerState(ON);
	} else if (argc == 2 && strcmp(argv[1], "off") == 0) {
		result = BTSetPowerState(OFF);
    } else if (argc == 2 && strcmp(argv[1], "restart") == 0) {
        IOBluetoothPreferenceSetControllerPowerState(OFF);
        usleep(2000000);
        result = BTSetPowerState(ON);
	} else {
		printf("Usage: %s [status|on|off|restart]\n", argv[0]);
		result = EXIT_FAILURE;
	}

    return result;
}
