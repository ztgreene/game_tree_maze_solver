/*
*	Tree Node ADT
*	Author: <<Zac Greene (067946)>>
*	Version: May 2017
*
*	This file holds the Tree Node ADT which represents
*	the nodes in a doubly-linked general tree.  Tree
*	nodes consist of a "data" field, a left branch
*	("left"), a middle branch ("middle"),a right
*	branch ("right"), and a link to the parent node
*	("parent").
*
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "solution.h"
#include "t_node.h"


struct t_node_int
{
	void *data;		// the value stored in the node
	t_node parent;	// the parent node of the current node
	t_node left;	// the eldest child node of the current node
	t_node middle;	// the next eldest node of the current node
	t_node right;	// the next eldest node of the current node
};


/*
*	init_t_node
*	Initialiser function
*	Pre-condition: none
*	Post-condition: the t_node variable holds the parameter value
*					(o) within its "data" field, and its "left",
*					"middle", "right", and "parent" fields are
*					NULL
*	Informally: intialises the fields of the newly created t_node
*				variable to hold the given parameter and to
*				terminate the "left", "middle", "right", and
*				"parent" fields
*
*	Param o the value to store in the data field of the node
*/
void init_t_node(t_node *tp, void *o)
{
	trace("t_node: Initialiser starts");

	*tp = (t_node)malloc(sizeof(struct t_node_int));
	(*tp)->data = o;
	(*tp)->parent = NULL;
	(*tp)->left = NULL;
	(*tp)->middle = NULL;
	(*tp)->right = NULL;

	trace("t_node: Initialiser ends");
}


/*
*	set_t_node_data
*	Set function for "data" field.
*	Pre-condition: none
*	Post-condition: the t_node varable's data field is altered to
*					hold the given (o) value
*	Informally: assign the value of the parameter to the t_node
*				variable's "data" field
*
*	param o the variable to store in the data field of the node
*/
void set_t_node_data(t_node t, void *o)
{
	trace("set_t_node_data: set_t_node_data starts");

	t->data = o;

	trace("set_t_node_data: set_t_node_data ends");
}


/*
*	set_t_node_left
*	Set function for "left" field.
*	Pre-condition: none
*	Post-condition: the t_node variable's left field is altered to
*					hold the given (l) value
*	Informally: assign the value of the parameter to the t_node
*				variable's "left" field
*
*	param l the left branch for the node
*/
void set_t_node_left(t_node t, t_node n)
{
	trace("set_t_node_left: set_t_node_left starts");

	t->left = n;

	trace("set_t_node_left: set_t_node_left ends");
}


/*
*	set_t_node_middle
*	Set function for "middle" field.
*	Pre-condition: none
*	Post-condition: the t_node variable's middle field is altered
*					to hold the given (n) value
*	Informally: assign the value of the parameter to the t_node
*				variable's "middle" field
*
*	Param n the node to set as the middle branch of the current node
*/
void set_t_node_middle(t_node t, t_node n)
{
	trace("set_t_node_middle: set_t_node_middle starts");

	t->middle = n;

	trace("set_t_node_middle: set_t_node_middle ends");
}


/*
*	set_t_node_right
*	Set function for "right" field.
*	Pre-condition: none
*	Post-condition: the t_node variable's right field is altered
*					to hold the given (n) value
*	Informally: assign the value of the parameter to the t_node
*				variable's "right" field
*
*	param n the node to set as the right of the current node
*/
void set_t_node_right(t_node t, t_node n)
{
	trace("set_t_node_right: set_t_node_right starts");

	t->right = n;

	trace("set_t_node_right: set_t_node_right ends");
}


/*
*	set_t_node_parent
*	Set function for "parent" field.
*	Pre-condition: none
*	Post-condition: the t_node variable's parent field is altered
*					to hold the given (n) value
*	Informally: assign the value of the parameter to the t_node
*				variable's "parent" field
*
*	Param n the node to set as the parent of the current node
*/
void set_t_node_parent(t_node t, t_node n)
{
	trace("set_t_node_parent: set_t_node_parent starts");

	t->parent = n;

	trace("set_t_node_parent: set_t_node_parent ends");
}


/*
*	get_t_node_data
*	Get function for "data" field.
*	Pre-condition: none
*	Post-condition: the t_node variable's data field is returned
*	Informally: examine the t_node variable's "data" field
*				returning its value
*
*	return variable the item in the node
*/
void *get_t_node_data(t_node t)
{
	trace("get_t_node_data: get_t_node_data starts and ends");

	return t->data;
}


/*
*	get_t_node_left
*	Get function for "left" field.
*	Pre-condition: none
*	Post-condition: the t_node variable's left field is
*				returned
*	Informally: examine the t_node variable's "left" field
*				variable returning its value
*
*	return t_node the left branch of the current node
*/
t_node get_t_node_left(t_node t)
{
	trace("get_t_node_left: get_t_node_left starts and ends");

	return t->left;
}


/*
*	get_t_node_child
*	Get function for "child" field.
*	Pre-condition: none
*	Post-condition: the t_node variable's child field is
*					returned
*	Informally: examine the t_node variable's "child"
*				field returning its value
*
*	return t_node the child of the current node
*/
t_node get_t_node_middle(t_node t)
{
	trace("get_t_node_middle: get_t_node_middle starts and ends");

	return t->middle;
}


/*
*	get_t_node_right
*	Get function for "right" field.
*	Pre-condition: none
*	Post-condition: the t_node variable's right field is
*					returned
*	Informally: examine the t_node variable's "right"
*				field returning its value
*
*	return t_node the right of the current node
*/
t_node get_t_node_right(t_node t)
{
	trace("get_t_node_right: get_t_node_right starts and ends");

	return t->right;
}


/*
*	get_t_node_parent
*	Get function for "parent" field.
*	Pre-condition: none
*	Post-condition: the t_node variable's parent field is
*					returned
*	Informally: examine the t_node variable's "parent"
*				field returning its value
*
*	return t_node the parent of the current node
*/
t_node get_t_node_parent(t_node t)
{
	trace("get_t_node_parent: get_t_node_parent starts and ends");

	return t->parent;
}
