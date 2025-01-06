// Functions for the maze game
// Rowan Ess
// CS1B lab 8
// 21/3/24

#include <iostream>
#include "maze.hpp"

using std::cout; using std::cin;

//
// initialization functions
//

// initializes the array of walls by placing every RoomPair to connect
// two non-existant rooms where x-coordinate is -1 and y-coordinate is '*' (a star)
// to signify that the walls are not built yet
void clearWalls(RoomPair rp[]) {
    for (int i = 0; i < numWalls; ++i) {
        rp[i].one.x = -1;
        rp[i].two.x = -1;
        rp[i].one.y = '*';
        rp[i].two.y = '*';
    }
}


// checks if direction dr ('u', 'd', 'l', or 'r')
// applied to Room rm keeps the mouse inside the maze
bool goodDirection(const Room& rm, const char dr) {
    if (dr == 'u' && rm.y == 'a')
        return false;
    else if (dr == 'd' && rm.y == 'a' + mazeSize - 1)
        return false;
    else if (dr == 'l' && rm.x == 1)
        return false;
    else if (dr == 'r' && rm.x == mazeSize)
        return false;
    else
        return true;
}

// returns the room adjacent to room rm
// in the specified direction dr
// assumes the direction is inside the maze
Room createAdjacent(const Room& rm, const char dr) {
    Room nxt = rm;
    switch (dr) {
    case 'u':
        --nxt.y;
        break;
    case 'd':
        ++nxt.y;
        break;
    case 'l':
        --nxt.x;
        break;
    case 'r':
        ++nxt.x;
        break;
    } 
    return nxt; 
}


// selects a random room adjacent to Room rm
// uses goodDirection() and createAdjacent()
const Room pickAdjacent(const Room& rm) {
    while (true) {
        int randy = rand() % 4;
        switch (randy) {
        case 0:
            if (goodDirection(rm, 'u'))
                return createAdjacent(rm, 'u');
            break;
        case 1:
            if (goodDirection(rm, 'r'))
                return createAdjacent(rm, 'r');
            break;
        case 2:
            if (goodDirection(rm, 'd'))
                return createAdjacent(rm, 'd');
            break;
        case 3:
            if (goodDirection(rm, 'l'))
                return createAdjacent(rm, 'l');
            break;
        }
    }
}


// selects a random wall, uses pickAdjacent()
const RoomPair pickPair() {
    Room rm;
    rm.x = rand() % mazeSize + 1;
    rm.y = 'a' + (rand() % mazeSize);
    RoomPair rp;
    rp.one = rm;
    rp.two = pickAdjacent(rm);
    return rp;
}


// predicate returns true if the coordinates of the two rooms match
bool matchRoom(const Room& rm1, const Room& rm2) {
    if (rm1.x == rm2.x && rm1.y == rm2.y)
        return true;
    return false;
}

// returns true if two pairs of adjacent rooms are the same,
// returns false otherwise, uses matchRoom()
// note that r1|r2 matches r2|r1
bool matchPair(const RoomPair& rp1, const RoomPair& rp2) {
    if ((matchRoom(rp1.one, rp2.one) && matchRoom(rp1.two, rp2.two)) || (matchRoom(rp1.one, rp2.two) && matchRoom(rp1.two, rp2.one)))
        return true;
    return false;
}

// returns true if rp matches one of the wall in the array
// false otherwise
// uses matchPair()
bool checkMaze(const RoomPair rpa[], const RoomPair& rp) {
    for (int i = 0; i < numWalls; ++i) {
        if (matchPair(rpa[i], rp))
            return true;
    }
    return false;
}


// places internal walls in random locations of the maze
void build(RoomPair rpa[]) {
    for (int i = 0; i < numWalls; ++i) {
        Room rm; 
        rm.x = rand() % mazeSize + 1; 
        rm.y = 'a' + (rand() % mazeSize); 
        RoomPair rp; 
        rp.one = rm; 
        rp.two = pickAdjacent(rm);
        rpa[i] = rp;
    }
    
}

//
// display functions
//
void printRoom(const Room& rm) {
    cout << rm.y << rm.x;
}// prints the location of the room

void printPair(const RoomPair& rp) {
    cout << rp.one.y << rp.one.x << "|" << rp.two.y << rp.two.x;
} // prints the locations of the adjacent rooms

void printMaze(const RoomPair rpa[]) {
    for (int i = 0; i < numWalls; ++i) {
        printPair(rpa[i]);
        cout << ' ';
    }
} // prints the locations of all the internal walls of the maze
                                  // uses printPair

//
// game functions
//

// asks the user for the direction and generates the next room
// to move to
// uses goodDirection() to valid (does not go outside external walls) and
//      createAdjacent() to generate the room for the next move
// returns {-1,*} if the user wants to quit
const Room nextMove(const Room& crm) {
    cout << "Which direction? (u/d/l/r/q)\n";
    char move;
    cin >> move;
    Room quit = { -1, '*'};
    if (move == 'q')
        return quit;
    if (goodDirection(crm, move))
        return createAdjacent(crm, move);
    return crm;
}

// note that checkMaze() is also used in the game
