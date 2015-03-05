#include <iostream>
#include <vector>

using namespace std;
typedef short unsigned int keyType;

class KeyMapper {
	vector< pair<string,keyType> > cecMapKey();
	vector< pair<string,keyType> > udevMapKey();
public:
	KeyMapper();
	keyType cec_key(string key);
	keyType udev_key(string key);
};