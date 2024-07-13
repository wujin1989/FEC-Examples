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

#ifndef __CDK_NET_H__
#define __CDK_NET_H__

#include "cdk-types.h"
/* common */
extern void       cdk_net_rbuf(sock_t s, int v);
extern void       cdk_net_sbuf(sock_t s, int v);
extern void       cdk_net_rtimeo(sock_t s, int t);
extern void       cdk_net_stimeo(sock_t s, int t);

/* tcp */
extern void       cdk_tcp_obtain_addr(sock_t s, addrinfo_t* ai, bool p);
extern sock_t     cdk_tcp_listen(const char* restrict h, const char* restrict p);
extern void       cdk_tcp_netpoller(sock_t s, routine_t r, bool tp);
extern void       cdk_tcp_nodelay(sock_t s, int on);
extern void       cdk_tcp_keepalive(sock_t s);
extern void       cdk_tcp_maxseg(sock_t s);
extern void       cdk_tcp_close(sock_t s);
extern sock_t     cdk_tcp_dial(const char* restrict h, const char* restrict p);
extern net_msg_t* cdk_tcp_marshaller(char* restrict b, int tp, int sz);
extern void       cdk_tcp_demarshaller(net_msg_t* m, char* restrict b);
extern int        cdk_tcp_send(sock_t s, net_msg_t* restrict m);
extern net_msg_t* cdk_tcp_recv(sock_t s);

/* udp */
extern sock_t     cdk_udp_listen(const char* restrict h, const char* restrict p);
extern void       cdk_udp_close(sock_t s);
extern sock_t     cdk_udp_dial(const char* restrict h, const char* restrict p);
extern int        cdk_udp_send(sock_t s, char* restrict b, int sz, struct sockaddr_storage* restrict ss, socklen_t l);
extern int        cdk_udp_recv(sock_t s, char* restrict b, int sz, struct sockaddr_storage* restrict ss, socklen_t* restrict lp);

#endif /* __CDK_NET_H__ */
