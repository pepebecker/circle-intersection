#ifndef __MACROS_H__
#define __MACROS_H__

#ifdef __wasm__
#define IMPORT_FUNC(name) __attribute__((import_module("env"), import_name(name)))
#else
#define IMPORT_FUNC(name)
#endif

#endif // __MACROS_H__

