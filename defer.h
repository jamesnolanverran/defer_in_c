// defer.h - Minimal portable defer macro for C
// Author: James Verran
// License: MIT
// https://github.com/jamesnolanverran/defer_in_c

#ifndef DEFER_H
#define DEFER_H

#define defer(...) \
    for (int _defer_outer = 1; _defer_outer; (_defer_outer = 0, __VA_ARGS__)) \
        for (int _defer_inner = 1; _defer_inner; _defer_inner = 0)

#endif // DEFER_H
