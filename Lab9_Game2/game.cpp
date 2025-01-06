// The main gameplay of the maze game
// Rowan Ess
// cs1b lab 9 part 2
// 5-4-24

//declare an object of class Maze
//declare a finish room with the cheese
//call build() method on the maze
//prompt the user if she wants to see the maze wall positions printed
//loop while the current mouse location is not the finish room and the user
//	wants to continue the game(the selected room is not the - 1 *)
//		inside the loop
//		get the current mouse room
//		print it
//		on the basis of the current room, get the next room from the user,
//		form a room pair, invoke move() to see if it this move is possible
//		analyze the return value from this move() to see if it was successful
//		if not: report a  wall

#include "maze.hpp"
#include <iostream>

using std::cout; using std::cin;

int main() {
	srand(time(nullptr));

	Maze maze;
	Room finish;
	finish.makeCheeseRoom();
	maze.build();
	maze.start();

	cout << "Would you like to see the maze? (y/n?)\n";
	char yn;
	cin >> yn;
	if (yn == 'y') {
		maze.print();
		cout << "\n";
	}

	bool endFlag = false;
	while (endFlag == false) {

		Room current = maze.getCurrentRoom();
		current.print();
		cout << "\n";
		Room nextRoom = current.nextMove();
		RoomPair move(current, nextRoom);
		maze.move(nextRoom);
		if (matchRoom(current, maze.getCurrentRoom()))
			cout << "You hit a wall!\n";

		Room quit;
		if (matchRoom(nextRoom, quit))
			endFlag = true;
		else if (matchRoom(maze.getCurrentRoom(), finish)) {
			cout << "YOU WIN!\n";
			endFlag = true;
		}
	}
	cout << "Thanks for playing!";
}