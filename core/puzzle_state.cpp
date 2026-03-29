#include "puzzle_state.h"

bool PuzzleState::operator==(const PuzzleState& other) const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != other.board[i][j]) return false;
        }
    }
    return true;
}