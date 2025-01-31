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

#ifndef __CDK_LIST_H__
#define __CDK_LIST_H__

#include "cdk-types.h"
#include <stddef.h>

/**
 *  get current node data.
 *
 *  @param x [in] current node.
 *  @param t [in] type of the structure where the current node is located.
 *  @param m [in] name of the member in the structure where the list node is located.
 *  @return type pointer of the structure where the current node is located.
 */
#define cdk_list_data(x, t, m)                              \
    ((t *) ((char *) (x) - offsetof(t, m)))

/**
 *  create a null list that contains sentinel node.
 *
 *  @param l [in] current list.
 *  @return N/A.
 */
extern void cdk_list_create(list_t* l);
/**
 *  initialize a list node.
 *
 *  @param x [in].
 *  @return N/A.
 */
extern void cdk_list_init_node(list_node_t* x);
/**
 *  insert a node at the head of the list.
 *
 *  @param l [in] current list.
 *  @param x [in] new node.
 *  @return N/A.
 */
extern void cdk_list_insert_head(list_t* l, list_node_t* x);
/**
 *  insert a node at the tail of the list.
 *
 *  @param l [in] current list.
 *  @param x [in] new node.
 *  @return N/A.
 */
extern void cdk_list_insert_tail(list_t* l, list_node_t* x);
/**
 *  check if the list is empty.
 *
 *  @param l [in] current list.
 *  @return if list is empty return true, otherwis return false.
 */
extern bool cdk_list_empty(list_t* l);
/**
 *  get head node by sentinel node in the list.
 *
 *  @param l [in] current list.
 *  @return head node in the list.
 */
extern list_t* cdk_list_head(list_t* l);
/**
 *  get tail node by sentinel node in the list.
 *
 *  @param l [in] current list.
 *  @return tail node in the list.
 */
extern list_t* cdk_list_tail(list_t* l);
/**
 *  get current node's next node.
 *
 *  @param x [in] current node.
 *  @return current node's next node in the list.
 */
extern list_t* cdk_list_next(list_node_t* x);
/**
 *  get current node's prev node.
 *
 *  @param x [in] current node.
 *  @return current node's prev node in the list.
 */
extern list_t* cdk_list_prev(list_node_t* x);
/**
 *  remove current node.
 *
 *  @param x [in] current node.
 *  @return N/A.
 */
extern void cdk_list_remove(list_node_t* x);
/**
 *  get sentinel node.
 *
 *  @param l [in] current list.
 *  @return sentinel node.
 */
extern list_t* cdk_list_sentinel(list_t* l);

#endif /* __CDK_LIST_H__ */
