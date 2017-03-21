#ifndef PREPROCESSOR_H_NXS
#define PREPROCESSOR_H_NXS

#if defined(__GNUG__)
    #define NXS_FUNC_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define NXS_FUNC_NAME __FUNCTION__
#endif

#define NXS_STRINGIFY(x) #x
#define NXS_TOSTRING(x) NXS_STRINGIFY(x)
#define NXS_LINE  __FILE__ ":" NXS_TOSTRING(__LINE__)

#endif // PREPROCESSOR_H_NXS
