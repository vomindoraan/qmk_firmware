#pragma once

#define DO_PRAGMA(x) _Pragma (#x)

#define DEPRECATED(name, value) \
    DO_PRAGMA(GCC warning "The below identifier is deprecated and will be removed in future versions of QMK.") \
    DO_PRAGMA(GCC warning #name) \
    value

#define RENAMED(name, new_name) \
    DO_PRAGMA(GCC warning "The below identifier is deprecated and will be removed in future versions of QMK.") \
    DO_PRAGMA(GCC warning #name) \
    DO_PRAGMA(GCC warning "Please use the new name:") \
    DO_PRAGMA(GCC warning #new_name) \
    new_name

#define REPLACED(name, replacement, value) \
    DO_PRAGMA(GCC warning "The below identifier is deprecated and will be removed in future versions of QMK.") \
    DO_PRAGMA(GCC warning #name) \
    DO_PRAGMA(GCC warning "Please use the following replacement:") \
    DO_PRAGMA(GCC warning #replacement) \
    value
