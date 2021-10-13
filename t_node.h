/*
 *	Tree Node
 *	
 *	Version: May 2017
 *
 *	This file holds the specification of the game tree nodes.
 *
 */

#ifndef TNODE_H
#define TNODE_H

struct t_node_int;
typedef struct t_node_int *t_node;

void init_t_node(t_node *tp,void *o);
void set_t_node_data(t_node t,void *o);
void *get_t_node_data(t_node t);
void set_t_node_left(t_node t, t_node n);
t_node get_t_node_left(t_node t);
void set_t_node_middle(t_node t, t_node n);
t_node get_t_node_middle(t_node t);
void set_t_node_right(t_node t, t_node n);
t_node get_t_node_right(t_node t);
void set_t_node_parent(t_node t, t_node n);
t_node get_t_node_parent(t_node t);

#endif