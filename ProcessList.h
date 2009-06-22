/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_ProcessList
#define HEADER_ProcessList
/*
htop - ProcessList.h
(C) 2004,2005 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

/* Darwin reference:
 *
 * http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/
 *
 */

#ifndef CONFIG_H
#define CONFIG_H
#include "config.h"
#endif

#include "Process.h"
#include "Vector.h"
#include "UsersTable.h"
#include "Hashtable.h"
#include "String.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/utsname.h>
#include <stdarg.h>

#include <mach/host_info.h>
#include <mach/mach_host.h>
#include <mach/mach_interface.h>
#include <mach/machine.h>
#include <mach/processor_info.h>

#include "debug.h"
#include <assert.h>

#ifndef PROCDIR
#define PROCDIR "../proc"
#endif

#ifndef PROCSTATFILE
#define PROCSTATFILE PROCDIR "/stat"
#endif

#ifndef PROCMEMINFOFILE
#define PROCMEMINFOFILE PROCDIR "/meminfo"
#endif

#ifndef MAX_NAME
#define MAX_NAME 128
#endif

#ifndef MAX_READ
#define MAX_READ 2048
#endif

#ifndef PER_PROCESSOR_FIELDS
#define PER_PROCESSOR_FIELDS 22
#endif



#ifdef DEBUG_PROC
typedef int(*vxscanf)(void*, const char*, va_list);
#endif

typedef struct ProcessList_ {
   Vector* processes;
   Vector* processes2;
   Hashtable* processTable;
   Process* prototype;
   UsersTable* usersTable;

   int processorCount;
   int totalTasks;
   int runningTasks;
   vm_size_t pageSize;

   // Must match number of PER_PROCESSOR_FIELDS constant
   unsigned long long int* totalTime;
   unsigned long long int* userTime;
   unsigned long long int* systemTime;
   unsigned long long int* systemAllTime;
   unsigned long long int* idleAllTime;
   unsigned long long int* idleTime;
   unsigned long long int* niceTime;
   unsigned long long int* ioWaitTime;
   unsigned long long int* irqTime;
   unsigned long long int* softIrqTime;
   unsigned long long int* stealTime;
   unsigned long long int* totalPeriod;
   unsigned long long int* userPeriod;
   unsigned long long int* systemPeriod;
   unsigned long long int* systemAllPeriod;
   unsigned long long int* idleAllPeriod;
   unsigned long long int* idlePeriod;
   unsigned long long int* nicePeriod;
   unsigned long long int* ioWaitPeriod;
   unsigned long long int* irqPeriod;
   unsigned long long int* softIrqPeriod;
   unsigned long long int* stealPeriod;

   unsigned long long int totalMem;
   unsigned long long int usedMem;
   unsigned long long int freeMem;
   unsigned long long int sharedMem;
   unsigned long long int buffersMem;
   unsigned long long int cachedMem;
   unsigned long long int totalSwap;
   unsigned long long int usedSwap;
   unsigned long long int freeSwap;

   ProcessField* fields;
   ProcessField sortKey;
   int direction;
   bool hideThreads;
   bool shadowOtherUsers;
   bool hideKernelThreads;
   bool hideUserlandThreads;
   bool treeView;
   bool highlightBaseName;
   bool highlightMegabytes;
   bool highlightThreads;
   bool detailedCPUTime;
   #ifdef DEBUG_PROC
   FILE* traceFile;
   #endif

} ProcessList;

#ifdef DEBUG_PROC

#define ProcessList_read(this, buffer, format, ...) ProcessList_xread(this, (vxscanf) vsscanf, buffer, format, ## __VA_ARGS__ )
#define ProcessList_fread(this, file, format, ...)  ProcessList_xread(this, (vxscanf) vfscanf, file, format, ## __VA_ARGS__ )

#else

#ifndef ProcessList_read
#define ProcessList_fopen(this, path, mode) fopen(path, mode)
#define ProcessList_read(this, buffer, format, ...) sscanf(buffer, format, ## __VA_ARGS__ )
#define ProcessList_fread(this, file, format, ...) fscanf(file, format, ## __VA_ARGS__ )
#endif

#endif

ProcessList* ProcessList_new(UsersTable* usersTable);

void ProcessList_delete(ProcessList* this);

void ProcessList_invertSortOrder(ProcessList* this);

RichString ProcessList_printHeader(ProcessList* this);

Process* ProcessList_get(ProcessList* this, int index);

int ProcessList_size(ProcessList* this);

void ProcessList_sort(ProcessList* this);

#ifdef HAVE_TASKSTATS

#endif

void ProcessList_scan(ProcessList* this);

ProcessField ProcessList_keyAt(ProcessList* this, int at);

#endif
