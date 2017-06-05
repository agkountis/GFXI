#ifndef BLADE_TRACE_H_
#define BLADE_TRACE_H_

#ifdef _DEBUG

#include <iostream>

// Trace macros
#define BLADE_TRACE(trace) std::clog << "TRACE: " << trace << std::endl

// Error macros
#define BLADE_ERROR(error) std::cerr << "ERROR: " << error << std::endl

// Warning macros
#define BLADE_WARNING(warning) std::clog << "WARNING: " << warning << std::endl

#else
#define BLADE_TRACE(trace)
#define BLADE_ERROR(trace)
#define BLADE_WARNING(trace)
#endif


#endif //BLADE_TRACE_H_
