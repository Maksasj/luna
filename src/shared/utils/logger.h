#ifndef _LUNA_LOGGER_H_
#define _LUNA_LOGGER_H_

#define _ENABLE_LUNA_LOGGER_

#include <iostream>
#include <fstream>
#include <chrono>

namespace luna {
    struct Logger {
        #ifdef _ENABLE_LUNA_LOGGER_
            static void Log(std::string message) {
                static std::ofstream out_file("luna.log", 'w');

                out_file << message << std::flush;
            }
        #endif
    };
}

#ifdef _ENABLE_LUNA_LOGGER_
    #define LUNA_LOG(message) Logger::Log(message)
#else 
    #define LUNA_LOG(message)
#endif

#endif