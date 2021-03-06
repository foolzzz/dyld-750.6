
// BUILD:  $CC foo.c -dynamiclib -install_name $RUN_DIR/libtlv.dylib -o $BUILD_DIR/libtlv.dylib
// BUILD:  $CC main.c  -DRUN_DIR="$RUN_DIR"  -o $BUILD_DIR/thread-local-cleanup.exe

// RUN:  ./thread-local-cleanup.exe

#include <stdio.h>
#include <dlfcn.h>

#include "test_support.h"

int main(int argc, const char* argv[], const char* envp[], const char* apple[]) {
    for (int i=0; i < 1000; ++i) {
        void* handle = dlopen(RUN_DIR "/libtlv.dylib", RTLD_FIRST);
        if ( handle == NULL ) {
            FAIL("dlopen error: iteration %d %s", i, dlerror());
        }

        int result = dlclose(handle);
        if ( result != 0 ) {
            FAIL("dlclose error: iteration %d %s", i, dlerror());
        }
    }

    PASS("Success");
}

