#ifndef BLADE_TRACE_H_
#define BLADE_TRACE_H_


#ifdef _DEBUG

/* MEMORY LEAKS DETECTION */
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

struct AtExit
{
	~AtExit()
	{
		_CrtDumpMemoryLeaks();
	}
} doAtExit;

/* ENDS - MEMORY LEAKS DETECTION */

#include <iostream>
#include <sstream>
#include <string>

#define BLADE_TRACE_CON(trace) std::clog << "TRACE: " << trace << std::endl;

#define BLADE_TRACE_VSOUT(trace) \
{ std::wstringstream s;  s << "TRACE: " << (trace) << std::endl; \
  OutputDebugString(s.str().c_str()); \
} 


#define BLADE_TRACE(trace)  {BLADE_TRACE_CON(trace); BLADE_TRACE_VSOUT(trace)}

#else
#define BLADE_TRACE_CON(trace)
#define BLADE_TRACE_VSOUT(trace)
#endif


#endif //BLADE_TRACE_H_

