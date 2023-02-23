#ifndef _LUNA_PROFILER_H_
#define _LUNA_PROFILER_H_

#include <vector>

#include <iostream>

#include <chrono>
#include <fstream>
#include <string>

#include "utils/types.h"

namespace luna {
    struct Profile {
        private:
            std::chrono::steady_clock::time_point record_start_timestamp;
        public:
            u64 _execution_times;
            f64 _exception_time;
            std::string label;

            Profile(std::string text);
            void Record();
            void Stop();
    };

    class Profiler {
        static std::vector<Profile*> profiles;

        public:
            static void BindProfile(Profile *profile);
            static void SumUp();
    };
}

#endif
