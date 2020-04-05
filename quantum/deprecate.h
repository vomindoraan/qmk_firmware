#pragma once

#define DO_PRAGMA(x)    _Pragma (#x)
#define DO_WARNING(msg) DO_PRAGMA(GCC warning #msg)

#define DEPRECATED(name, value) \
    DO_WARNING(‘name’ is deprecated and will be removed in future versions of QMK) \
    value

#define RENAMED(name, new_name) \
    DO_WARNING(‘name’ is deprecated: please use ‘new_name’ instead) \
    new_name

#define REPLACED(name, replacement, value) \
    DO_WARNING(‘name’ is deprecated: please use ‘replacement’ instead) \
    value
