#include "rapidxml.hpp"
#include "keyMapper.h"
#include <vector>
#include <list>

using namespace rapidxml;
using namespace std;

class XMLParser {
	xml_document<> doc;
	KeyMapper map;

public:
	XMLParser();
	std::vector< pair<int, list<keyType> > > xmlKeyList();

};