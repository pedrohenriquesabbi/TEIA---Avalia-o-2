#ifndef PUZZLE_STATE_H
#define PUZZLE_STATE_H

#include <vector>

struct PuzzleState {
    int board[3][3]; 
    int emptyRow;
    int emptyCol;
    int cost;

    bool operator==(const PuzzleState& other) const;
};

#endif // PUZZLE_STATE_H