#ifndef BLADE_TRACE_H_
#define BLADE_TRACE_H_


#ifdef _DEBUG

#include <iostream>

// Trace macros
#define BLADE_TRACE_CON(trace) std::clog << "TRACE: " << trace << std::endl

#define BLADE_TRACE_VSOUT(trace) \
{ std::wstringstream s;  s << "TRACE: " << (trace) << std::endl; \
OutputDebugString(s.str().c_str()); }

#define BLADE_TRACE(trace) BLADE_TRACE_CON(trace)

// Error macros
#define BLADE_ERROR_CON(error) std::cerr << "ERROR: " << error << std::endl

#define BLADE_ERROR_VSOUT(error) \
{std::wstringstream s; s << "ERROR: "<< error << std::endl; \
OutputDebugString(s.str().c_str());}

#define BLADE_ERROR(error) BLADE_ERROR_CON(error)

// Warning macros
#define BLADE_WARNING_CON(warning) std::clog << "WARNING: " << warning << std::endl
#define BLADE_WARNING(warning) BLADE_WARNING_CON(warning)

#else
#define BLADE_TRACE_CON(trace)
#define BLADE_TRACE_VSOUT(trace)
#define BLADE_TRACE(trace)
#define BLADE_ERROR(trace)
#define BLADE_WARNING(trace)
#endif


#endif //BLADE_TRACE_H_
