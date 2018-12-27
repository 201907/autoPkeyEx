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

	//���ݤ�ȡ�ä���
	do {
		DWORD num = 0;
		char keys[16];
		stringstream ss;
		ss << SECTION << i;
		num = GetPrivateProfileString(ss.str().data(), KEY, "", keys, sizeof(keys), this->iniPath.data());
		if( num == 0 )break;
		KEY_CONFIG config;

		//���`��ȡ�ä���
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

		//���A���r�g��ȡ�ä���
		int duration = GetPrivateProfileInt(ss.str().data(), DURATION, 0, this->iniPath.data());
		config.duration = duration;

		// ������ȡ�ä���
		int times = GetPrivateProfileInt(ss.str().data(), TIMES, 0, this->iniPath.data());
		config.times = times;

		// ���`Ѻ��������A���r�g��ȡ�ä���
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