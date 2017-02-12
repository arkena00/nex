#ifndef SHARE_H_NDB
#define SHARE_H_NDB

// no target specified
#if !defined NDB_UNIX && !defined NDB_WIN
    #error "you must define the target OS with NDB_WIN or NDB_UNIX"
#endif

// unix constant
#ifdef NDB_UNIX
    #define NDB_IMPORT
    #define NDB_EXPORT __attribute__ ((visibility ("default")))
#endif

// win constant
#ifdef NDB_WIN
    #define NDB_IMPORT __declspec(dllimport)
    #define NDB_EXPORT __declspec(dllexport)
#endif

// export function
#define NDB_SHARED NDB_EXPORT

#endif // SHARE_H_NDB
