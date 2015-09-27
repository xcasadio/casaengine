#ifndef COMPILATIONMACRO_H_
#define COMPILATIONMACRO_H_

#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1)
#define GCC411_OR_LATER
#endif

#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MAJOR__ >= 7 && __GNUC_MINOR__ >= 7)
#define GCC471_OR_LATER
#endif

// check if the function is overriding with exactly same signature
#ifndef OVERRIDE
#if defined(WIN32) || defined(XENON) || defined(DURANGO) || defined(GCC471_OR_LATER)
//#define OVERRIDE override
#define OVERRIDE
#else
#define OVERRIDE
#endif
#endif


#endif // COMPILATIONMACRO_H_