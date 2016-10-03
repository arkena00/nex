#ifndef VERSION_H_NDB
#define VERSION_H_NDB

namespace ndb_version{
	
	//Date Version Types
	static const char DATE[] = "05";
	static const char MONTH[] = "09";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] =  "16.09";
	
	//Software Status
	static const char STATUS[] =  "Custom";
	static const char STATUS_SHORT[] =  "";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 1;
	static const long REVISION  = 8;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3;
	#define RC_FILEVERSION 1,0,1,8
	#define RC_FILEVERSION_STRING "1, 0, 1, 8\0"
	static const char FULLVERSION_STRING [] = "1.0.1.8";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 1;
	

}
#endif //VERSION_H_NDB
