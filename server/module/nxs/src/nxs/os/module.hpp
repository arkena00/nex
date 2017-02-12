#ifndef OS_MODULE_H_NXS
#define OS_MODULE_H_NXS

#include <nxs/share.hpp>

#ifdef NXS_UNIX
    #include <dlfcn.h>

    #define NXS_OS_MODULE_FUNCTION dlsym
    #define NXS_OS_MODULE_LOAD(path) dlopen(path, RTLD_LAZY)
    #define NXS_OS_MODULE_UNLOAD dlclose
    namespace nxs { typedef void* NXS_OS_MODULE_HANDLE; }
    #define NXS_OS_SHARELIBEXT "so"
#endif

#ifdef NXS_WIN
    #include <windows.h>

    #define NXS_OS_MODULE_FUNCTION GetProcAddress
    #define NXS_OS_MODULE_LOAD(path) LoadLibrary(path)
    #define NXS_OS_MODULE_UNLOAD FreeLibrary
    namespace nxs { typedef HINSTANCE NXS_OS_MODULE_HANDLE; }
    #define NXS_OS_SHARELIBEXT "dll"
#endif

#endif // OS_MODULE_H_NXS
