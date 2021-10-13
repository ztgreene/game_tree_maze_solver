/*
 *	Square State
 *	
 *	Version: May 2017
 *
 *	This file holds the specification of the state of a maze square.
 *
 */

#ifndef SQUARE_STATE_H
#define SQUARE_STATE_H

struct square_state_int;
typedef struct square_state_int *square_state;

void init_square_state(square_state *sp, int v);
void set_value(square_state s, int v);
void set_visited(square_state s, bool v);
int get_value(square_state s);
bool get_visited(square_state s);
square_state clone_square(square_state s);
void show_square_state(square_state s, bool here, const int WALL, const int GOAL);

#endif