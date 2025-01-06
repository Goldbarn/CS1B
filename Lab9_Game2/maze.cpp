// Function definitions for maze game
// Rowan Ess
// Lab 9 part 1
// 22-3-24

#include "maze.hpp"
#include <iostream>

using std::cout; using std::cin;

// selects a random room within the maze
void Room::pick() {
    x_ = rand() % mazeSize_ + 1;
    y_ = 'a' + (rand() % mazeSize_);
}

void Room::print() const { cout << y_ << x_;}

// selects a random adjacent room
// uses goodDirection() and createAdjacent()
const Room Room::pickAdjacent() {
    while (true) {
        int randy = rand() % 4;
        switch (randy) {
        case 0:
            if (goodDirection('u'))
                return createAdjacent('u');
            break;
        case 1:
            if (goodDirection('r'))
                return createAdjacent('r');
            break;
        case 2:
            if (goodDirection('d'))
                return createAdjacent('d');
            break;
        case 3:
            if (goodDirection('l'))
                return createAdjacent('l');
            break;
        }
    }
}

// asks the user for the room to move adjacent to this room
// returns {-1,*} if the user wants to quit
// uses goodDirection() and createAdjacent()
const Room Room::nextMove() const {
    cout << "Which direction? (u/d/l/r/q)\n";
    char move;
    cin >> move;
    Room out;
    if (move == 'q')
        return out;
    if (goodDirection(move))
        return createAdjacent(move);
    out.x_ = x_;
    out.y_ = y_;
    return out;
}

// predicate returns true if the coordinates of the two rooms match
bool matchRoom(const Room& rm1, const Room& rm2) {
    if (rm1.x_ == rm2.x_ && rm1.y_ == rm2.y_)
        return true;
    return false;
}

// checks if this direction keeps the mouse inside the maze
bool Room::goodDirection(const char dr) const {
    if (dr == 'u' && y_ == 'a')
        return false;
    else if (dr == 'd' && y_ == 'a' + mazeSize_ - 1)
        return false;
    else if (dr == 'l' && x_ == 1)
        return false;
    else if (dr == 'r' && x_ == mazeSize_)
        return false;
    else
        return true;
}

// returns the room adjacent to this room in the specified direction
// assumes the direction is inside the maze
const Room Room::createAdjacent(const char dr) const {
    Room nxt;
    nxt.y_ = y_;
    nxt.x_ = x_;
    switch (dr) {
    case 'u':
        --nxt.y_;
        break;
    case 'd':
        ++nxt.y_;
        break;
    case 'l':
        --nxt.x_;
        break;
    case 'r':
        ++nxt.x_;
        break;
    }
    return nxt;
}

//selects a random wall, uses Room::pickAdjacent()
void RoomPair::pick() {
    Room rm;
    rm.pick();
    RoomPair rp;
    one_ = rm;
    two_ = rm.pickAdjacent();
}

// prints the locations of the two rooms in format a1|b1
// uses Room::print()
void RoomPair::print() const {
    one_.print();
    cout << '|';
    two_.print();
}

bool matchPair(const RoomPair& rp1, const RoomPair& rp2) {
    if ((matchRoom(rp1.one_, rp2.one_) && matchRoom(rp1.two_, rp2.two_)) || (matchRoom(rp1.one_, rp2.two_) && matchRoom(rp1.two_, rp2.one_)))
        return true;
    return false;
}


// prints the locations of all the internal walls of the maze
// and current mouse location
void Maze::print() const {
    for (int i = 0; i < numWalls_; ++i) {
        walls_[i].print();
        cout << ' ';
    }
}

// places internal walls in random locations of the maze
// all walls are different
void Maze::build() {
    for (int i = 0; i < numWalls_; ++i) {
        bool x = false;
        do {
            Room rm;
            rm.pick();
            RoomPair rp(rm, rm.pickAdjacent());
            if (checkMaze(rp))
                continue;
            walls_[i] = rp;
            x = true;
        } while (x == false);
    }
}

// takes the room to move the mouse to
// moves the mouse there and returns true if no walls (move is possible)
// does not move the mouse and returns false if wall
bool Maze::move(const Room& rm) {
    RoomPair rp(currentRoom_, rm);
    if (checkMaze(rp))
        return false;
    currentRoom_ = rm;
    return true;
}

// returns true if RoomPair matches one of the walls in the maze
bool Maze::checkMaze(const RoomPair& rp) const {
    for (int i = 0; i < numWalls_; ++i) {
        if (matchPair(walls_[i], rp))
            return true;
    }
    return false;
}
