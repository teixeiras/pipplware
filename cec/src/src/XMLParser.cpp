#include "XMLParser.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

using namespace std;
using namespace rapidxml;

XMLParser::XMLParser()
{
	map = KeyMapper();

	std::ifstream t("keys.xml");
	std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

	vector<char> xml_copy(str.begin(), str.end());
    xml_copy.push_back('\0');	
    doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);
    
}

std::vector< pair<int, list<keyType> > > XMLParser::xmlKeyList() {

	xml_node<>* cur_node = doc.first_node("rootnode");
	
	string rootnode_type = cur_node->first_attribute("type")->value();
	
	xml_node<>* cec_user_control_code = cur_node->first_node("CEC_USER_CONTROL_CODE");
	
	std::vector< pair<int, list<keyType> > > keyMap = std::vector< pair<int, list<keyType> > >(); 

	while(cec_user_control_code) {

		string code = cec_user_control_code->first_attribute("value")->value();

		xml_node<>* xmlkey = cur_node->first_node("KEY");
		
		list<keyType> keys = list<keyType>();

		while (xmlkey) {
		
			string key = xmlkey->first_attribute("value")->value();

			keys.insert(keys.end(), map.udev_key(key));

			xmlkey = xmlkey->next_sibling();
		}

	    keyMap.push_back(std::make_pair(map.cec_key(code),keys)); 
	    
	    cec_user_control_code = cec_user_control_code->next_sibling();
	}
	
	return keyMap;
}
