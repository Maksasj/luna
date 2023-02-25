#ifndef _LUNA_PROFILER_H_
#define _LUNA_PROFILER_H_

#include <vector>

#include <cassert>

#include <sstream>
#include <iostream>

#include <chrono>
#include <fstream>
#include <string>

#include "utils/types.h"

namespace luna {
    struct Profile {
        private:
            std::chrono::steady_clock::time_point record_start_timestamp;
            std::vector<Profile*> childs;

        public:
            u64 _execution_times;
            f64 _exception_time;
            std::string _label;

            Profile(std::string label);

            void Record();
            void PushChildProfile(Profile *profile);
            u32 CountChildProfiles();
            std::pair<std::vector<luna::Profile*>::iterator, std::vector<luna::Profile*>::iterator> GetChilds();
            void Stop();
    };

    struct ProfilerCloser {
        ProfilerCloser();
    };
    
    class Profiler {
        static std::vector<Profile*> stack;
        static std::vector<Profile*> entryPoints;
        
        public:
            static void BindTopProfile(Profile *profile);
            static void UnBindTopProfile();
            static void SumUp();
    };

    void traceProfiles(std::stringstream *ss, luna::Profile *profile, luna::Profile *parent, u32 depth);
}


#define PROFILE_RECORD(LABEL) static luna::Profile LABEL(#LABEL); LABEL.Record();
#define PROFILE_STOP(LABEL) static luna::ProfilerCloser LABEL ## _CLOSER; LABEL.Stop();

#endif
