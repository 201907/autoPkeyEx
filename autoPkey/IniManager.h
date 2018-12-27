#include <string>
#include <vector>
#include "common.h"
using namespace std;

class IniManager {
public:
	IniManager(string path);
	~IniManager();
	string *readIni();
	vector<KEY_CONFIG>* getKeyConfigs();
	vector<KEY_CONFIG> *getKeyConfigAt(int index);
private:
	string iniPath;
	string * content;
	vector<KEY_CONFIG>* keyConfigs;
};