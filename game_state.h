/*
 *	Game State
 *
 *	Version: May 2017
 *
 *	This file holds the specification of the state of the maze.
 *
 *	This file is complete.
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>
#include "square_state.h"

struct game_state_int;
typedef struct game_state_int *game_state;

void init_game_state(game_state *sp, int r, int c);
void set_row_size(game_state s, int r);
void set_column_size(game_state s, int c);
void set_current_row(game_state s, int r);
void set_current_column(game_state s, int c);
int get_row_size(game_state s);
int get_column_size(game_state s);
int get_current_row(game_state s);
int get_current_column(game_state s);
bool valid(game_state s, int r, int c);
bool taken(game_state s, int r, int c);
bool wall(game_state s, int r, int c);
game_state clone(game_state s);
bool move(game_state s, int r, int c);
bool solved(game_state s);
void show_game_state(game_state s);

#endif