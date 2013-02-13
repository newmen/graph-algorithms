#ifndef PROCESS_MEM_USAGE_H
#define PROCESS_MEM_USAGE_H

//////////////////////////////////////////////////////////////////////////////
//
// process_mem_usage(double &, double &) - takes two doubles by reference,
// attempts to read the system-dependent data for a process' virtual memory
// size and resident set size, and return the results in KB.
//
// On failure, returns 0.0, 0.0

void process_mem_usage(double& vm_usage, double& resident_set);

#endif // PROCESS_MEM_USAGE_H
