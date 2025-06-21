# defer.h - A Minimal, Portable Defer Macro for C

This is a small experiment with a `defer(...) { ... }` macro for C, implemented using nested `for`-loops and comma expressions. It requires no compiler extensions and should work in standard C (C89+). 

## Example

```c
defer(
    fclose(f),
    free(buf),
    printf("cleanup done\n")
) {
    // use f and buf here
}
```

## Features

- ✅ Fully portable (no compiler extensions)
    
- ✅ Clean syntax
    
- ✅ Nestable
    
- ✅ Supports multiple cleanup actions

- ⚠️ Defer arguments must be expressions (not statement blocks)
    
- ⚠️ Cleanup runs when the block ends - don’t return early

- ⚠️ Minimally tested!
    

## How It Works

The macro is defined like this:

```c
#define defer(...) \
    for (int _defer_outer = 1; _defer_outer; (_defer_outer = 0, __VA_ARGS__)) \
        for (int _defer_inner = 1; _defer_inner; _defer_inner = 0)
```

It creates a nested block that ensures the cleanup expressions are executed after the main block completes, unless exited via early return.

## Why

This was written mostly for fun while exploring C's macro system.

Created by James Verran
MIT License
