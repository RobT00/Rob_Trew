#pragma once

//
// helper.h
//
// Copyright (C) 2011 - 2018 jones@scss.tcd.ie
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software Foundation;
// either version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//

#ifdef _WIN32
#include <tchar.h>          //
#include <Windows.h>        //
#include <intrin.h>         // intrinsics
#endif

#if __linux__
#include <math.h>           // log10
#include <cpuid.h>          // cpuid
#include <string.h>         // strcpy
#include <pthread.h>        // pthread_create
#include <x86intrin.h>      // need to specify gcc flags -mrtm -mrdrnd
#include <limits.h>         // {joj 17/11/14}
#endif

#include <iomanip>          // {joj 27/5/14}
#include <locale>           // {joj 7/6/14}

//
// INT64 and UINT64
//
typedef long long INT64;
typedef unsigned long long UINT64;
#define INT64MIN LLONG_MIN
#define INT64MAX LLONG_MAX
#define UINT64MAX ULLONG_MAX

#define STRTOVINT(s, c, r) _strtoi64(s, c, r)
#define STRTOVUINT(s, c, r) _strtoui64(s, c, r)

#define AMALLOC(sz, align)  _aligned_malloc(((sz) + (align)-1) / (align) * (align), align)
#define AFREE(p)            _aligned_free(p)

#ifdef WIN32

#define CPUID(cd, v) __cpuid((int*) &cd, v);
#define CPUIDEX(cd, v0, v1) __cpuidex((int*) &cd, v0, v1)

#define THREADH HANDLE

#define WORKERF DWORD (WINAPI *worker) (void*)
#define WORKER DWORD WINAPI

#define ALIGN(n) __declspec(align(n))

#define TLSINDEX DWORD
#define TLSALLOC(key) key = TlsAlloc()
#define TLSSETVALUE(tlsIndex, v) TlsSetValue(tlsIndex, v)               // {joj 24/11/15}
#define TLSGETVALUE(tlsIndex) TlsGetValue(tlsIndex)                     // {joj 24/11/15}

#define thread_local __declspec(thread)

#elif __linux__

#define BYTE    unsigned char
#define UINT    unsigned int
#define INT64   long long
#define UINT64  unsigned long long
#define LONG64  signed long long
#define PVOID   void*
#define MAXINT  INT_MAX
#define MAXUINT UINT_MAX

#define MAXUINT64   ((UINT64)~((UINT64)0))
#define MAXINT64    ((INT64)(MAXUINT64 >> 1))
#define MININT64    ((INT64)~MAXINT64)

#define CPUID(cd, v) __cpuid(v, cd.eax, cd.ebx, cd.ecx, cd.edx);
#define CPUIDEX(cd, v0, v1) __cpuid_count(v0, v1, cd.eax, cd.ebx, cd.ecx, cd.edx)

#define THREADH pthread_t
#define GetCurrentProcessorNumber() sched_getcpu()

#define WORKER void*
#define WORKERF void* (*worker) (void*)

#define ALIGN(n) __attribute__ ((aligned (n)))
#define _aligned_malloc(sz, align)  aligned_alloc(align, ((sz)+(align)-1)/(align)*(align))
#define _aligned_free(p) free(p)
#define _alloca alloca

#define strcpy_s(dst, sz, src) strcpy(dst, src)
#define _strtoi64(str, end, base)  strtoll(str, end, base)
#define _strtoui64(str, end, base)  strtoull(str, end, base)

#define _InterlockedIncrement(addr)                                 __sync_fetch_and_add(addr, 1)
#define _InterlockedIncrement64(addr)                               __sync_fetch_and_add(addr, 1)
#define _InterlockedExchange(addr, v)                               __sync_lock_test_and_set(addr, v)
#define _InterlockedExchangePointer(addr, v)                        __sync_lock_test_and_set(addr, v)
#define _InterlockedExchangeAdd(addr, v)                            __sync_fetch_and_add(addr, v)
#define _InterlockedExchangeAdd64(addr, v)                          __sync_fetch_and_add(addr, v)
#define _InterlockedCompareExchange(addr, newv, oldv)               __sync_val_compare_and_swap(addr, oldv, newv)
#define _InterlockedCompareExchange64(addr, newv, oldv)             __sync_val_compare_and_swap(addr, oldv, newv)
#define _InterlockedCompareExchange64_HLERelease(addr, newv, oldv)  __sync_val_compare_and_swap(addr, oldv, newv, __ATOMIC_ACQUIRE | __ATOMIC_HLE_ACQUIRE)      // {joj 12/1/18}
#define _InterlockedCompareExchangePointer(addr, newv, oldv)        __sync_val_compare_and_swap(addr, oldv, newv)
#define _InterlockedExchange_HLEAcquire(addr, val)                  __atomic_exchange_n(addr, val, __ATOMIC_ACQUIRE | __ATOMIC_HLE_ACQUIRE)
#define _InterlockedExchangeAdd64_HLEAcquire(addr, val)             __atomic_exchange_n(addr, val, __ATOMIC_ACQUIRE | __ATOMIC_HLE_ACQUIRE)
#define _Store_HLERelease(addr, v)                                  __atomic_store_n(addr, v, __ATOMIC_RELEASE | __ATOMIC_HLE_RELEASE)
#define _Store64_HLERelease(addr, v)                                __atomic_store_n(addr, v, __ATOMIC_RELEASE | __ATOMIC_HLE_RELEASE)

#define _mm_pause() __builtin_ia32_pause()
#define _mm_mfence() __builtin_ia32_mfence()

#define TLSINDEX pthread_key_t
#define TLSALLOC(key) pthread_key_create(&key, NULL)
#define TLSSETVALUE(key, v) pthread_setspecific(key, v)
#define TLSGETVALUE(key) (size_t) pthread_getspecific(key)

#define thread_local __thread                                       // {joj 26/10/12}

#define Sleep(ms) usleep((ms)*1000)

#endif

extern UINT ncpu;                                                   // # logical CPUs {joj 25/7/14}

extern void getDateAndTime(char*, int, time_t = 0);                 // getDateAndTime {joj 18/7/14}
extern char* getHostName();                                         // get host name
extern char* getOSName();                                           // get OS name
extern int getNumberOfCPUs();                                       // get number of CPUs
extern UINT64 getPhysicalMemSz();                                   // get RAM sz in bytes
extern int is64bitExe();                                            // return 1 if 64 bit .exe
extern size_t getMemUse();                                          // get working set size {joj 10/5/14}
extern size_t getVMUse();                                           // get page file usage {joj 10/5/14}

extern UINT64 getWallClockMS();                                     // get wall clock in milliseconds from some epoch
extern void createThread(THREADH*, WORKERF, void*);                 //
extern void runThreadOnCPU(UINT);                                   // run thread on CPU {joj 25/7/14}
extern void waitForThreadsToFinish(UINT, THREADH*);                 // {joj 25/7/14}
extern void closeThread(THREADH);                                   //

extern UINT64 rand(UINT64&);                                        // {joj 11/5/14}
#define RDRANDSTEP(r)   _rdrand64_step(r)                           // {joj 28/11/15}

extern int cpu64bit();                                              // return 1 if CPU is 64 bit
extern int cpuFamily();                                             // CPU family
extern int cpuModel();                                              // CPU model
extern int cpuStepping();                                           // CPU stepping
extern char *cpuBrandString();                                      // CPU brand string

extern int rtmSupported();                                          // return 1 if RTM supported (restricted transactional memory)
extern int hleSupported();                                          // return 1 if HLE supported (hardware lock elision)

extern int getCacheInfo(int, int, int &, int &, int&);              // getCacheInfo
extern int getCacheLineSz();                                        // get cache line sz
extern UINT getL2CacheSz();                                         // get level 2 cache size (bytes)                                           
extern UINT getL3CacheSz();                                         // get level 3 cache size (bytes)
extern UINT getPageSz();                                            // get page size

extern void pauseIfKeyPressed();                                    // pause if key pressed
extern void pressKeyToContinue();                                   // press key to continue
extern void quit(int = 0);                                          // quit

//
// CommaLocale
//
// VS2015 BUG doesn't output comma thousands separator in RELEASE mode {joj 25/11/15}
//
class CommaLocale : public std::numpunct<char>
{
protected:
    virtual char do_thousands_sep() const { return ','; }
    virtual std::string do_grouping() const {return "\03"; }
};

extern void setCommaLocale();
extern void setLocale();

// eof
