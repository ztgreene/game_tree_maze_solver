/*
 *	Harness File
 *	
 *	This file drives the solution.  
 *
 */


#include <stdio.h>
#include <stdbool.h>
#include "solution.h"
#include "game_tree.h"
#include "game_state.h"
#include "queue.h"
#include "stack.h"


/*
 *	trace
 *	Provide trace output.

 *	Pre-condition: none
 *	Post-condition: if trace output is desired then the given String
 *					parameter is shown on the console
 *	Informally: show the given message for tracing purposes
 *
 *	param s the String to be displayed as the trace message
 */
void trace(char *s)
{
	if (TRACING)
	{
		printf("%s\n",s);
	}
}


/*
 *	intro
 *	Provide introductory output.
 *	Pre-condition: none
 *	Post-condition: an introduction to the progrm has been displayed
 *	Informally: give the user some information about the program
 */
void intro()
{
	trace("intro: intro begins");

	printf("It's Amazing\n");
	printf("============\n");
	printf("Welcome to the Maze Solver.  This program solves mazes.  Twice.\n");
	printf("But this time it's %s-first.\n", DEPTH_FIRST ? "depth" : "breadth");
	printf("\n");

	trace("intro: intro ends");
}


/*
 *	main
 *	Program entry point.
 *	Pre-condition: none
 *	Post-condition: the solution to the Maze will be found and displayed
 *	Informally: solve the Maze
 */
int main(int argc, char *argv[])
{
	game_tree g,a;	// whole game tree and solution game tree
	game_state s;	// initial game state
	queue q;		// intermediate traversal use (BFS)
	stack k;		// intermediate traversal use (DFS)
	stack r;		// re-tracing solution path
	int m;			// move number

	trace("main: main begins");

	// give introduction and set up initial maze starting at row 2 column 1
	trace("main: setting up");
	intro();
	init_game_state(&s, 2, 1);

	// initialise solution data structures
	trace("main: initialising data structures");
	init_stack(&r);
	init_stack(&k);
	init_queue(&q);

	// show initial board
	trace("main: displaying starting point");
	printf("\nStarting board:\n");
	show_game_state(s);
	printf("\n");
	
	// solve
	init_game_tree(&g, false, s);
	if (DEPTH_FIRST)
	{
		trace("main: solving depth-first");
		a = build_gameDF(g, k);	// depth-first solution
	}
	else
	{
		trace("main: solving breadth-first");
		a = build_gameBF(g, q);	// breadth-first solution
	}

	// show results
	if (is_empty_game_tree(a))
	{
		trace("main: unsolvable");
		printf("No solution!\n");
	}
	else
	{
		// re-trace solution from leaf to root
		trace("main: building solution path");
		do
		{
			push(r, a);
			a = get_parent(a);
		} while (!is_empty_game_tree(a));

		// display move list
		trace("main: showing solution path");
		m = 1;
		while (!is_empty_stack(r))
		{
			a = (game_tree)top(r);	// next state
			s = (game_state)get_data(a);
			printf("Move %d: (%d,%d)\n", m, get_current_row(s), get_current_column(s));
			pop(r);	// remove next state
			m++;	// increment count of moves
		}

		// display final path
		trace("main: displaying solved maze");
		printf("\nFinal board:\n");
		show_game_state(s);
	}

	trace("main: main ends");
}
