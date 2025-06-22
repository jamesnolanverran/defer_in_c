# defer.h - A Minimal, Portable Defer Macro for C

This is a small experiment with a `defer(...) { ... }` macro for C, implemented using nested `for`-loops and comma expressions. It requires no compiler extensions and should work in standard C (C89+). 

## Example

```c
FILE *f = fopen("file.txt", "r");
defer(
    fclose(f),
    printf("cleanup done\n")
) {
    // use f here
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

## On Scope, Cleanup, and Tradeoffs
The use case for defer is typically to run cleanup code when you're done with a resource - closing a file, freeing memory, releasing a lock, etc.

In Go, deferred code runs automatically at the end of the function, no matter where you return.

This macro takes a different approach: it ties cleanup to a block scope, not the entire function. You get cleanup when the block ends - whether that's mid-function, at the bottom, or anywhere you're done using a resource.

You can still exit the block early using break. You just can't use return inside the block, or the cleanup code will be skipped.

```c
defer(free(x)) {
    if (some_condition) break; // early exit, cleanup still runs
    // use x here
} // cleanup happens here
return result; // after cleanup
```

## Why

This was written mostly for fun while exploring C's macro system.

--

Created by James Verran

MIT License
