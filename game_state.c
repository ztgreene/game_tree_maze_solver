/*
*	Game State ADT Implementation
*	Author: <<Zac Greene (067946)>>
*	Version: May 2017
*
*	This file holds the game_state ADT.  It comprises
*	the coordinate of the current position (as "row" and
*	"column"), the size of the board (the number of rows
*	and columns), the value of the goal square (called
*	"goal"), and the maze itself (as a two-dimensional
*	array called "board").
*
*/


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_state.h"
#include "solution.h"


struct game_state_int {
	square_state **board;	// 2-dimensional array containing maze
	int row_size;			// number of rows
	int col_size;			// number of columns
	int goal;				// value of goal square
	int current_row;		// current row number
	int current_col;		// current column number
};


const int WALL = -1;	// value of wall


/*
*	read_value
*	utility function to read value from file
*	Pre-condition: file is open
*	Post-condition: an integer value is read from the file and
*					returned (with comment lines skipped if
*					encountered)
*	Informally: the next number is read from the file and
*				returned
*
*	Param fp (FILE *) the file pointer for the data file
*	return int the value read from the file
*/
int read_value(FILE *fp)
{
	const char COMMENT = '#';	// prefix of comments

	char line[81];	// line from file
	char msg[81];	// message for debugging

	trace("read_value: read_value begins");
	//get line from file, skipping lines which are comments
	do
	{
		trace("read_value: read a line from file");
		fscanf(fp, "%[^\n]\n", line);
		if (TRACING)
		{
			sprintf(msg, "read_value: line is: %s;", line);
			trace(msg);
		}
	} while (line[0] == COMMENT);

	if (TRACING)
	{
		sprintf(msg, "read_value: read_value ends with return value %d\n", atoi(line));
		trace(msg);
	}

	//convert line to int and return it
	return atoi(line);
}


/*
*	read_in_data
*	utility function to load maze from data file.
*	Pre-condition: game_state is defined
*	Post-condition: a game_state variable is populated with
*					the maze read from a file
*	Informally: creates a maze by loading it from a file
*/
void read_in_data(game_state g)
{
	const char *FILENAME = "maze.txt";	// file containing maze

	int num_rows;	// number of rows in maze
	int num_cols;	// number of columns in maze
	int goal;		// value of goal square from maze
	FILE *fp;		// file pointer for maze text file
	char msg[81];	// message for debugging

	trace("read_in_data: read_in_data begins");

	trace("read_in_data: opening file");
	fp = fopen(FILENAME, "r");
	if (fp == NULL)
	{
		trace("read_in_data: open failed; quitting");
		fprintf(stderr, "Cannot open file.\n");
		exit(1);
	}
	else
	{
		trace("read_in_data: file opened, getting settings");
		num_cols = read_value(fp);
		g->col_size = num_cols;	// number of columns in maze
		num_rows = read_value(fp);
		g->row_size = num_rows; // number of rows in maze
		goal = read_value(fp);
		g->goal = goal;	// value of goal square
		if (TRACING)
		{
			sprintf(msg, "read_in_data: %dx%d with goal of %d...\n", num_cols, num_rows, goal);
			trace(msg);
		}

		// create maze component
		trace("read_in_data: creating maze");
		g->board = (square_state **)malloc(num_rows*sizeof(square_state *));
		trace("read_in_data: creating rows");
		for (int r = 0; r < num_rows; r++)
		{
			g->board[r] = (square_state *)malloc(num_cols*sizeof(square_state));

			trace("read_in_data: filling row");
			for (int c = 0; c < num_cols; c++)
			{
				// create square
				init_square_state(&(g->board[r][c]), read_value(fp));
			}
		}
	}

	trace("read_in_data: closing file");
	fclose(fp);

	trace("read_in_data: read_in_data ends");
}


/*
*	init_game_state
*	initialiser function.
*	Pre-condition: none
*	Post-condition: a game_state variable is created and pointed
*					to by the first parameter.  Its contents are
*					read from a file
*	Informally: load the maze
*
*	Param r int starting row number
*	Param c int starting column number
*/
void init_game_state(game_state *gp, int r, int c)
{
	char msg[100];	// message for debugging

	trace("init_game_state: init_game_state starts");

	// create game_state
	*gp = (game_state)malloc(sizeof(struct game_state_int));

	trace("init_game_state: get contents from file");
	read_in_data(*gp);

	// set other fields
	(*gp)->current_row = r;
	(*gp)->current_col = c;
	set_visited((*gp)->board[r - 1][c - 1], true);
	if (TRACING)
	{
		sprintf(msg, "init_game_state: starting at (%d,%d)\n", r, c);
		trace(msg);
	}

	trace("init_game_state: init_game_state ends");
}


/*
* 	get_row_size
*	Get function for row_size field.
*	Pre-condition: none
*	Post-condition: the value of the game_state variable's
*					row_size field is returned
*	Informally: return the game_state variable's number of rows
*
*	return int how many rows the maze has
*/
int get_row_size(game_state s)
{
	trace("get_row_size: get_row_size starts and finishes");

	return s->row_size;
}


/*	get_column_size
*	Get function for column_size field.
*	Pre-condition: none
*	Post-condition: the value of the game_state variable's
*					column_size field is returned
*	Informally: return the game_state variable's number of columns
*
*	return int how many columns the maze has
*/
int get_column_size(game_state s)
{
	trace("get_column_size: get_column_size starts and finishes");

	return s->col_size;
}


/*
* 	get_current_row
*	Get function for current_row field.
*	Pre-condition: the game_state is defined
*	Post-condition: the value of the game_state variable's current_row
*					field is returned
*	Informally: return the game_state variable's current_row
*
*	return int the current occupied row number
*/
int get_current_row(game_state s)
{
	trace("get_current_row: get_current_row starts and finishes");

	return s->current_row;
}


/*
* 	get_current_column
*	Get function for current_column field.
*	Pre-condition: the game_state is defined
*	Post-condition: the value of the game_state variable's
*					current_column field is returned
*	Informally: return the game_state variable's current_column
*
*	return int the current occupied column number
*/
int get_current_column(game_state s)
{
	trace("get_current_column: get_current_column starts and finishes");

	return s->current_col;
}


/*
* 	set_row_size
*	Set function for row_size field.
*	Pre-condition: the given game_state is defined and the given row
*					is within the bounds of that game_state variable's
*					board
*	Post-condition: the value of the game_state variable's row_size
*					field is updated to the given int value
*	Informally: update the game_state variable's row
*
* Param r int value to be placed into the game_state's row field
*/
void set_row_size(game_state s, int r)
{
	trace("set_row_size: set_row_size starts");

	s->row_size = r;

	trace("set_row_size: set_row_size ends");
}


/*
* 	set_column_size
*	Set function for column_size field.
*	Pre-condition: the given game_state is defined and the given column
*					is within the bounds of that game_state variable's
*					board
*	Post-condition: the value of the game_state variable's column_size
*					field is updated to the given int value
*	Informally: update the game_state variable's column_size
*
*	Param c int value to be placed into the game_state's column_size field
*/
void set_column_size(game_state s, int c)
{
	trace("set_column_size: set_column_size starts");

	s->col_size = c;

	trace("set_column_size: set_column_size ends");
}


/*
* 	set_row_size
*	Set function for row_size field.
*	Pre-condition: the given game_state is defined and the given row
*					is within the bounds of that game_state variable's
*					board
*	Post-condition: the value of the game_state variable's row_size
*					field is updated to the given int value
*	Informally: update the game_state variable's row_size
*
* Param r int value to be placed into the game_state's row_size field
*/
void set_current_row(game_state s, int r)
{
	trace("set_current_row: set_current_row starts");

	s->current_row = r;

	trace("set_current_row: set_current_row ends");
}


/*
* 	set_column_size
*	Set function for column_size field.
*	Pre-condition: the given game_state is defined and the given column
*					is within the bounds of that game_state variable's
*					board
*	Post-condition: the value of the game_state variable's column_size
*					field is updated to the given int value
*	Informally: update the game_state variable's column_size
*
*	Param c int value to be placed into the game_state's column_size field
*/
void set_current_col(game_state s, int c)
{
	trace("set_current_col: set_current_col starts");

	s->current_col = c;

	trace("set_current_col: set_current_col ends");
}


/*
* 	valid
*	Check whether a square is on the board
*	Pre-condition: the given game_state is defined
*	Post-condition: true is returned if (r,c) is within the bounds
*					of the given game_state variable's board field,
*					and false is returned otherwise
*	Informally: Return whether or not a square is on the board
*
*	Param r int row value to check
*	Param c int column value to check
*
*	return whether or not coordinate is in the maze
*/
bool valid(game_state s, int r, int c)
{
	trace("valid: valid starts and finishes");

	if ((r <= 0) || (c <= 0) || (r > get_row_size(s)) || (c > get_column_size(s)))	// Checks to see if square is within bounds of board 
	{
		return false;
	}

	else
	{
		return true;
	}
}


/*
* 	taken
*	Check whether a square on the board has already been visited
*	Pre-condition: the given game_state is defined and (r,c) is
*					within the bounds of the given game_state
*					variable's board field
*	Post-condition: true is returned if (r,c) has been visited (i.e.
*					is non-zero, and false is returned otherwise
*	Informally: Return whether or not a square has been taken
*
*	Param r int row value to check
*	Param c int column value to check
*
*	return bool whether or not square is visited
*/
bool taken(game_state s, int r, int c)
{
	trace("taken: taken starts and finishes");

	square_state square;				// The square at (row, column)
	square = s->board[r - 1][c - 1];	// Adjust for array index
	return get_visited(square);			// Returns if square has been visited or not
}


/*
* 	wall
*	Check whether a square on the board is a wall
*	Pre-condition: the given game_state is defined and (r,c) is
*					within the bounds of the given game_state
*					variable's board field
*	Post-condition: true is returned if (r,c) is a wall, and
*	false is returned otherwise
*	Informally: Return whether or not a square is a wall
*
*	Param r int row value to check
*	Param c int column value to check
*
*	return bool whether the given square is a wall
*/
bool wall(game_state s, int r, int c)
{
	trace("wall: wall starts and finishes");

	square_state square;				// The square at (row, column)
	square = s->board[r - 1][c - 1];	// Adjust for array index
	if (get_value(square) == WALL)		// CHecks if square is wall or not
	{
		return true;
	}
	else
	{
		return false;
	}

}

/*
* 	move
*	Update current location in the maze
*	Pre-condition: the given game_state is defined
*	Post-condition: if (r,c) can be visited then it is and true
*					is returned; false is returned otherwise
*	Informally: Update current location and return whether it
*				has changed
*
*	Param r int row value to check
*	Param c int column value to check
*
*	return bool success
*/
bool move(game_state s, int r, int c)
{
	char msg[31];	// message for debugging

	trace("move: move begins");

	if (valid(s, r, c) && !wall(s, r, c) && !taken(s, r, c))	// If square at (r,c) is valid and we can move there,
	{															// move to that square, and update location
		set_current_row(s, r);
		set_current_col(s, c);
		set_visited(s->board[r - 1][c - 1], true);
		return true;
	}
	else
	{
		return false;
	}


}


/*
* 	clone
*	Create a new board based on an old one
*	Pre-condition: the given game_state is defined and (r,c) is
*					within the bounds of the given game_state
*					variable's board field
*	Post-condition: a copy of the given game_state variable is
*					returned
*	Informally: Copy an existing game_state
*
*	return the copy of the given game_state
*/
game_state clone(game_state s)
{
	game_state n;

	trace("clone: clone starts");

	// create a new the game state
	n = (game_state)malloc(sizeof(struct game_state_int));
	n->row_size = s->row_size;
	n->col_size = s->col_size;
	n->goal = s->goal;
	n->current_row = s->current_row;
	n->current_col = s->current_col;

	// duplicate the existing moves
	trace("clone: duplicating existing moves");
	n->board = (square_state **)malloc(n->row_size*sizeof(square_state *));
	for (int r = 0; r < n->row_size; r++)
	{
		n->board[r] = (square_state *)malloc(n->col_size*sizeof(square_state));

		for (int c = 0; c < n->col_size; c++)
		{
			n->board[r][c] = clone_square(s->board[r][c]);
		}
	}

	trace("clone: derive ends");

	return n;
}


/*
* 	solved
*	Check whether maze has been solved because goal has been found
*	Pre-condition:	the given game_state is defined
*	Post-condition: true is returned if the current location is that
*					of the goal, and false is returned otherwise
*	Informally: Return whether or not the maze is solved
*
*	return bool whether the maze has been solved
*/
bool solved(game_state s)
{
	trace("solved: solved starts and ends");

	int r, c, current_value, goal_value;
	square_state current_location;

	r = get_current_row(s);
	c = get_current_column(s);
	current_location = s->board[r - 1][c - 1];
	current_value = get_value(current_location);
	goal_value = s->goal;

	if (current_value == goal_value)
	{
		return true;
	}
	else
	{
		return false;
	}

}

/*
* 	show_game_state
*	Display a game state
*	Pre-condition: the given game_state is defined
*	Post-condition: the given game_state has been displayed on
*					the standard output stream
*	Informally: Print the maze
*/
void show_game_state(game_state s)
{
	bool here;		// whether current location is visited
	char msg[100];	// message for debugging

	if (TRACING)
	{
		trace("show_game_state: show_game_state starts");

		sprintf(msg, "show_game_state: row_size is %d", s->row_size);
		trace(msg);
		sprintf(msg, "show_game_state: column_size is %d", s->col_size);
		trace(msg);
		sprintf(msg, "show_game_state: goal is %d", s->goal);
		trace(msg);
	}

	// show every square in the maze
	for (int r = 0; r < s->row_size; r++)
	{
		for (int c = 0; c < s->col_size; c++)
		{
			// show square
			here = ((s->current_row - 1 == r) && (s->current_col - 1 == c));
			show_square_state(s->board[r][c], here, WALL, s->goal);
		}
		printf("\n");
	}

	trace("show_game_state: show_game_state ends");
}
