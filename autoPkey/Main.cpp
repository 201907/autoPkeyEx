#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") 

#include <string>
#include <windows.h>
#include <Windows.h>
#include "common.h"
#include "IniManager.h"
#include "KcmnConst.h"
#include <algorithm>

int main() {

	IniManager iniManager = IniManager(PATH);
	vector<KEY_CONFIG>* keyConfigs = iniManager.getKeyConfigs();
	for_each(keyConfigs->cbegin(), keyConfigs->cend(), [](const KEY_CONFIG &config)->void {
		for( int i = 0; i < config.times; i++ ) {
			for_each(config.keys.cbegin(), config.keys.cend(), [](const int &key)->void {
				keybd_event(key, static_cast<BYTE>(0), 0, 0);
			});

			Sleep(config.duration);

			for_each(config.keys.cbegin(), config.keys.cend(), [](const int &key)->void {
				keybd_event(key, static_cast<BYTE>(0), KEYEVENTF_KEYUP, 0);
			});
		}
		Sleep(config.delay);
	});
	return 0;
}