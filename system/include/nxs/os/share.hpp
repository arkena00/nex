#ifndef OS_SHARE_H_NXS
#define OS_SHARE_H_NXS

// no target specified
#if !defined NXS_UNIX && !defined NXS_WIN
    #error "you must define the target OS with NXS_WIN or NXS_UNIX"
#endif

// unix constant
#ifdef NXS_UNIX
    #define NXS_IMPORT
    #define NXS_EXPORT __attribute__ ((visibility ("default")))
#endif

// win constant
#ifdef NXS_WIN
    #define NXS_IMPORT __declspec(dllimport)
    #define NXS_EXPORT __declspec(dllexport)

    #pragma warning(disable: 4251)
#endif

// export function
#define NXS_SHARED NXS_EXPORT

#endif // OS_SHARE_H_NXS
