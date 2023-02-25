#include "utils/profiler.h"

std::vector<luna::Profile*> luna::Profiler::stack;
std::vector<luna::Profile*> luna::Profiler::entryPoints;

luna::Profile::Profile(std::string label) {
    _label = label;

    Profiler::BindTopProfile(this);
}

luna::ProfilerCloser::ProfilerCloser() {
    Profiler::UnBindTopProfile();
}

u32 luna::Profile::CountChildProfiles() {
    return childs.size();
}

std::pair<std::vector<luna::Profile*>::iterator, std::vector<luna::Profile*>::iterator> luna::Profile::GetChilds() {
    return std::make_pair(childs.begin(), childs.end());
}

void luna::Profile::Record() {
    ++_execution_times;
    record_start_timestamp = std::chrono::high_resolution_clock::now();  
}

void luna::Profile::PushChildProfile(Profile *profile) {
    childs.push_back(profile);
}

void luna::Profile::Stop() {
    auto record_stop_timestamp = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(record_stop_timestamp - record_start_timestamp).count(); 
    _exception_time += duration;
}

void luna::Profiler::BindTopProfile(Profile *profile) {
    if(stack.size() == 0) {
        entryPoints.push_back(profile);
    } else {
        stack[stack.size() - 1]->PushChildProfile(profile);
    }

    stack.push_back(profile);
}

void luna::Profiler::UnBindTopProfile() {
    stack.pop_back();
}

void luna::traceProfiles(std::stringstream *ss, luna::Profile *profile, luna::Profile *parent, u32 depth) {
    auto childs = profile->GetChilds();

    for(auto i = childs.first; i < childs.second; ++i) {
        for(auto k = 0; k < depth; ++k)
            (*ss) << "    ";
        
        (*ss) << "Profile: '"<<(*i)->_label << "' executed " << (*i)->_execution_times << " times, total execution time: " << (*i)->_exception_time / 1000000.0 << "ms, " << 100.0*((*i)->_exception_time / profile->_exception_time) << "% | " << 100.0*((*i)->_exception_time / parent->_exception_time) << "% \n"; 

        luna::traceProfiles(ss, (*i), profile, depth + 1);
    }
}

void luna::Profiler::SumUp() {
    for(auto profile : entryPoints) {
        std::stringstream ss;

        ss  << "Profile: '"<<profile->_label 
            << "' executed " << profile->_execution_times << " times, total execution time: " 
            << profile->_exception_time / 1000000.0 << "ms, " 
            << "100% \n"; 

        traceProfiles(&ss, profile, profile, 1);

        std::cout << ss.str();
    }
}
