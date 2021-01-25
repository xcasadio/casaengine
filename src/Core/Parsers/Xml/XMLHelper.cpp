#include <vector>
#include <string>

#include "Base.h"
#include "XMLHelper.h"
#include "tinyxml2.h"

using namespace std;

namespace CasaEngine
{
	/**
	 * split: receives a char delimiter; returns a vector of strings
	 * By default ignores repeated delimiters, unless argument rep == 1.
	 */
	vector<string> XMLHelper::Split(string src_, char delim, int rep)
	{
		vector<string> flds;

		string buf = "";
		unsigned int i = 0;

		while (i < src_.length())
		{
			if (src_[i] != delim)
			{
				buf += src_[i];
			}
			else if (rep == 1)
			{
				flds.push_back(buf);
				buf = "";
			}
			else if (buf.length() > 0)
			{
				flds.push_back(buf);
				buf = "";
			}
			i++;
		}
		if (!buf.empty())
			flds.push_back(buf);

		return flds;
	}

	/**
	 *
	 */
	const tinyxml2::XMLElement* XMLHelper::GetNodeXmlPath(const tinyxml2::XMLElement* element_, const char* path_)
	{
		vector<string> els = Split(path_, '\\');
		const tinyxml2::XMLElement* pElt = element_;

		for (unsigned int i = 0; i < els.size(); i++)
		{
			pElt = GetChildNodeByName(pElt, els[i].c_str());

			if (pElt == nullptr) break;
		}

		return nullptr;
	}

	/**
	 *
	 */
	const tinyxml2::XMLElement* XMLHelper::GetChildNodeByName(const tinyxml2::XMLElement* element_, const char* name_)
	{
		if (element_ == nullptr) return nullptr;
		return element_->FirstChildElement(name_);
	}
}