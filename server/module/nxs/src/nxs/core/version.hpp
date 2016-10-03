#ifndef CORE_VERSION_H_NXS
#define CORE_VERSION_H_NXS

namespace nxs_autoversion{
	
	//Date Version Types
	static const char DATE[] = "03";
	static const char MONTH[] = "10";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] =  "16.10";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 5;
	static const long BUILD  = 226;
	static const long REVISION  = 74;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 4734;
	#define RC_FILEVERSION 2,5,226,74
	#define RC_FILEVERSION_STRING "2, 5, 226, 74\0"
	static const char FULLVERSION_STRING [] = "2.5.226.74";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 2;
	

}
#endif //CORE_VERSION_H_NXS
