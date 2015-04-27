//
//  Bluetooth.h
//  blueutil
//
//  Created by Brian Reiter on 4/27/15.
//
//

#ifndef blueutil_bluetooth_h
#define blueutil_bluetooth_h

//Export private Bluetooth API functions in OS X

int IOBluetoothPreferenceGetControllerPowerState();
int IOBluetoothPreferencesAvailable();
void IOBluetoothPreferenceSetControllerPowerState(int);

#endif
