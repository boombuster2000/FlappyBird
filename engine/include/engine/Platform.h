#pragma once

// Avoid Windows macro conflicts (raylib, spdlog)
#if defined(_WIN32)
    #define NOGDI
    #define NOUSER
#endif
