/*
 *	Node
 *
 *	Version: May 2017
 *
 *	This file holds the specification of the linked-list Node.
 *
 */

#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

struct node_int;
typedef struct node_int *node;

void init_node(node *np, void *o);
void set_data_node(node n, void *o);
void set_next_node(node v, node n);
void *get_data_node(node n);
node get_next_node(node n);

#endif