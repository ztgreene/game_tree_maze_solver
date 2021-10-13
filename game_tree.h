/*
 *	Game Tree
 *
 *	Version: May 2017
 *
 *	This file holds the specification of the game tree.
 *
 */

#ifndef GAME_TREE_H
#define GAME_TREE_H

#include <stdbool.h>
#include "square_state.h"
#include "solution.h"
#include "stack.h"
#include "queue.h"

struct game_tree_int;
typedef struct game_tree_int *game_tree;

void init_game_tree(game_tree *gp, bool e, void *o);
bool is_empty_game_tree(game_tree g);
void set_data(game_tree g, void *o);
void *get_data(game_tree g);
void set_left(game_tree g, game_tree l);
game_tree get_left(game_tree g);
void set_middle(game_tree g, game_tree c);
game_tree get_middle(game_tree g);
void set_right(game_tree g, game_tree s);
game_tree get_right(game_tree g);
void set_parent(game_tree g, game_tree p);
game_tree get_parent(game_tree g);
void generate_levelBF(game_tree g, queue q);
game_tree build_gameBF(game_tree g, queue q);
void generate_levelDF(game_tree g, stack k);
game_tree build_gameDF(game_tree g, stack k);
char *to_string_game_tree(game_tree g);

#endif
