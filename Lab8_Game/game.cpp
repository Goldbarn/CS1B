// Maze game main gameplay loop
// Rowan Ess
// CS1B lab 8
// 21/3/24

#include <iostream>
#include <cstdlib>
#include "maze.hpp"

using std::cin; using std::cout;

//populate the maze by invoking build() on it 
//declare the room to keep the current mouse location, place the mouse
//in the top - left corner
//prompt the user if she wants to see the maze wall positions printed
//loop while the current mouse location is not the finish room and the user
//wants to continue the game(the selected room is not the - 1 *)
//inside the loop
//print the current(mouse) room
//on the basis of the current room, invoke nextMove() get the
//next room from the user,
//form a roomPair out of current room and next room to indicate the next move
//invoke checkMaze() to see if this move is possible
//if yes
//move the mouse by updating the current room
//if not
//report a wall
//report ending of the game

int main() {

	RoomPair maze[mazeSize];
	build(maze);
	Room current = { 1, 'a' };

	cout << "Would you like to see the maze walls? (y/n)\n";
	char confirm;
	cin >> confirm;
	if (confirm == 'y')
		printMaze(maze);

	Room finish = { (mazeSize), ('a' + mazeSize - 1)};
	while (!matchRoom(finish, current) && current.x != -1) {

		cout << "Current room: ";
		printRoom(current);
		cout << "\n";

		RoomPair move;
		Room next = nextMove(current);
		move.one = current;
		move.two = next;

		if (!checkMaze(maze, move))
			current = next;
		else
			cout << "You hit a wall!\n";

		if (matchRoom(current, finish)) 
			cout << "YOU WIN!!!!!!!\n";
	}
	cout << "Game End";
}