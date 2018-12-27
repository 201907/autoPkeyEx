#include <vector>
using namespace std;

#ifndef _KEY_CONFIG
#define _KEY_CONFIG 
struct KEY_CONFIG {
	long duration;
	long times;
	long delay;
	vector<int> keys;
};
#endif // !_KEY_CONFIG
