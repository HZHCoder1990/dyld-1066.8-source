
// BUILD:  $CC foo.c -dynamiclib  -install_name $RUN_DIR/libfoo.dylib -o $BUILD_DIR/libfoo.dylib
// BUILD:  $CC main.c $BUILD_DIR/libfoo.dylib -o $BUILD_DIR/bind-absolute.exe

// RUN:  ./bind-absolute.exe

// Verify that large absolute values are encoded correctly

#include <stdio.h>

#include "test_support.h"

extern const struct { char c; } abs_value;
extern const struct { char c; } unserializable_abs_value;

// Choose a large enough negative offset to be before the shared cache or the image
const void* bind = &abs_value;
const void* bind2 = &unserializable_abs_value;

int main(int argc, const char* argv[], const char* envp[], const char* apple[]) {
    if ( (uintptr_t)bind != (uintptr_t)0xF000000000000000ULL ) {
        FAIL("bind-absolute: %p != %p", bind, (void*)0xF000000000000000ULL);
    }
    if ( (uintptr_t)bind2 != (uintptr_t)0x80000004FFFFFFFFULL ) {
        FAIL("bind-absolute: %p != %p", bind2, (void*)0x80000004FFFFFFFFULL);
    }

    PASS("bind-absolute");
}

