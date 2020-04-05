#pragma once

// Deprecation flags for variables, functions and structs
#define DEPRECATED            __attribute__((deprecated))
#define RENAMED(new_name)     __attribute__((deprecated("please use the new name ‘" #new_name "’ instead")))
#define REPLACED(replacement) __attribute__((deprecated("please use ‘" #replacement "’ instead")))

#define DO_PRAGMA(x)    _Pragma (#x)
#define DO_WARNING(msg) DO_PRAGMA(GCC warning #msg)

// Deprecation wrappers for macros and other identifiers
#define DEPRECATED_M(name, value) \
    DO_WARNING(‘name’ is deprecated and may be removed in future versions of QMK) \
    value
#define RENAMED_M(old_name, new_name) \
    DO_WARNING(‘old_name’ is deprecated: please use the new name ‘new_name’ instead) \
    new_name
#define REPLACED_M(name, replacement, value) \
    DO_WARNING(‘name’ is deprecated: please use ‘replacement’ instead) \
    value
