#ifndef VERSION_H
#define VERSION_H

namespace CasaEngine
{
	static const int CA_PRODUCT_VERSION = 0;
	static const int CA_MAJOR_VERSION = 0;
	static const int CA_MINOR_VERSION = 1;

#define CA_NAME "CasaEngine v" CA_STRINGIZE(CA_PRODUCT_VERSION) "." CA_STRINGIZE(CA_MAJOR_VERSION) "." CA_STRINGIZE(CA_MINOR_VERSION)
}

#endif // VERSION_H
