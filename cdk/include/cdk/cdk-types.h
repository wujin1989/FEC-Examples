/** Copyright (c) 2021, Wu Jin <wujin.developer@gmail.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 */

#ifndef __CDK_TYPES_H__
#define __CDK_TYPES_H__

#include <stdbool.h>
#include <stdint.h>

 //======================================= unix ================================================================
#if defined(__linux__) || defined(__APPLE__)

#include <stdatomic.h>
#include <netinet/in.h>
#include <pthread.h>

#if defined(__linux__)
#include <sys/types.h>
#endif

#if defined(__APPLE__)
typedef uint64_t                         tid_t;
#endif
#if defined(__linux__)
typedef pid_t                            tid_t;
#endif
typedef pthread_t                        thrd_t;
typedef pthread_once_t                   once_flag;
typedef pthread_mutex_t                  mtx_t;
typedef pthread_cond_t                   cnd_t;
typedef atomic_llong                     atomic_t;
typedef int                              sock_t;
#endif


//======================================= windows ================================================================

#if defined(_WIN32)

#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <Windows.h>
#include <ws2ipdef.h>

typedef struct _atomic_flag {
	_Bool v; 
} _atomic_flag;

typedef DWORD                            tid_t;
typedef HANDLE                           thrd_t;
typedef DWORD                            pid_t;
typedef INIT_ONCE                        once_flag;
typedef CRITICAL_SECTION                 mtx_t;
typedef CONDITION_VARIABLE               cnd_t;

typedef _atomic_flag                     atomic_flag;
typedef LONG64                           atomic_t;

typedef SOCKET                           sock_t;
typedef int                              socklen_t;
typedef SSIZE_T                          ssize_t;
#endif

//======================================= common ================================================================
typedef struct _rwlock_t {
	atomic_t w;
	atomic_t r;
}rwlock_t;

#define MAX_ADDRSTRLEN INET6_ADDRSTRLEN
typedef struct _addrinfo_t {
	char        a[MAX_ADDRSTRLEN];
	uint16_t    p;
}addrinfo_t;

typedef void (*routine_t)(sock_t s);

typedef struct _list_t {
	struct _list_t* p;
	struct _list_t* n;
}list_t;
typedef list_t    list_node_t;

typedef list_t    fifo_t;
typedef fifo_t    fifo_node_t;

typedef list_t    filo_t;
typedef filo_t    filo_node_t;

typedef struct _thrdpool_job_t {
	void          (*fn)(void*);
	void*         p;
	fifo_node_t   q_n;      /* queue node */
}thrdpool_job_t;

typedef struct _thrdpool_t {
	thrd_t*       t;       /* threads */
	size_t        t_c;     /* thread count */
	fifo_t        q;
	mtx_t         t_m;     /* create thread mutex */
	mtx_t         j_m;     /* handle job mutex */
	cnd_t         j_c;
	bool          s;       /* status, idle or running */
}thrdpool_t;

typedef struct _net_msg_hdr_t {

	uint32_t      p_s;   /* payload size */
	uint32_t      p_t;   /* payload type */
}net_msg_hdr_t;

typedef struct _net_msg_t {

	net_msg_hdr_t      h;
	char               p[];
}net_msg_t;

#endif /* __CDK_TYPES_H__ */
