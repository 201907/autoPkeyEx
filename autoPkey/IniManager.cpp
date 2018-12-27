#include "IniManager.h"
#include <windows.h>
#include <vector>
#include "KcmnConst.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "common.h"

IniManager::IniManager(string path) {
	string exepath = string(_pgmptr);
	this->iniPath = exepath.substr(0, exepath.rfind("\\")) + path;
	keyConfigs = new vector<KEY_CONFIG>();
	int i = 1;

	//内容を取得する
	do {
		DWORD num = 0;
		char keys[16];
		stringstream ss;
		ss << SECTION << i;
		num = GetPrivateProfileString(ss.str().data(), KEY, "", keys, sizeof(keys), this->iniPath.data());
		if( num == 0 )break;
		KEY_CONFIG config;

		//キーを取得する
		string keyStr = string(keys);
		vector<int> keyVector = vector<int>();
		if( keyStr.find('|', 0) != string::npos ) {
			char *p = strtok(const_cast<char *>(keyStr.data()), "|");
			while( p ) {
				keyVector.insert(keyVector.end(), atoi(p));
				p = strtok(NULL, "|");
			}
		} else {
			keyVector.insert(keyVector.end(), atoi(keyStr.data()));
		}
		config.keys = keyVector;

		//　続く時間を取得する
		int duration = GetPrivateProfileInt(ss.str().data(), DURATION, 0, this->iniPath.data());
		config.duration = duration;

		// 回数を取得する
		int times = GetPrivateProfileInt(ss.str().data(), TIMES, 0, this->iniPath.data());
		config.times = times;

		// キー押下完了後続き時間を取得する
		int delay = GetPrivateProfileInt(ss.str().data(), DELAY, 0, this->iniPath.data());
		config.delay = delay;

		keyConfigs->insert(keyConfigs->end(), config);
		i++;
	} while( true );
}

IniManager::~IniManager() {
	if( keyConfigs ) {
		delete keyConfigs;
	}
	if( content ) {
		delete content;
	}
}

string *IniManager::readIni() {
	return NULL;
}

vector<KEY_CONFIG>* IniManager::getKeyConfigs() {
	return this->keyConfigs;
}

vector<KEY_CONFIG>* IniManager::getKeyConfigAt(int index) {
	return NULL;
}