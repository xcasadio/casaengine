
#ifndef XMLHELPER_H_
#define XMLHELPER_H_

#include <vector>
#include <string>

#include "CA_Export.h"
#include "tinyxml2.h"


using namespace std;

namespace CasaEngine
{

/**
 * 
 */
class CA_EXPORT XMLHelper
{
public:

	/**
	 * split: receives a char delimiter; returns a vector of strings
	 * By default ignores repeated delimiters, unless argument rep == 1.
	 */ 
	static vector<string> Split(string src_, char delim, int rep = 0) ;

	/**
	 *
	 */
	static const tinyxml2::XMLElement *GetNodeXmlPath(const tinyxml2::XMLElement *element_, const char *path_);

	/**
	 *
	 */
	static const tinyxml2::XMLElement *GetChildNodeByName(const tinyxml2::XMLElement *element_, const char *name_);
};

}


#endif // XMLHELPER_H_
