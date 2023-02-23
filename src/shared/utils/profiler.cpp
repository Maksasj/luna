#include "utils/profiler.h"

std::vector<luna::Profile*> luna::Profiler::profiles;

luna::Profile::Profile(std::string text) {
    label = text;

    Profiler::BindProfile(this);
}

void luna::Profile::Record() {
    ++_execution_times;
    record_start_timestamp = std::chrono::high_resolution_clock::now();  
}

void luna::Profile::Stop() {
    auto record_stop_timestamp = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(record_stop_timestamp - record_start_timestamp).count(); 
    _exception_time += duration;
}

void luna::Profiler::BindProfile(Profile *profile) {
    profiles.push_back(profile);
}

void luna::Profiler::SumUp() {
    for(auto profile : profiles) {
        std::cout << "Label: '"<< profile->label << "', times executed: " << profile->_execution_times << ", total execution time: " << profile->_exception_time << "ns\n";
    }
}
