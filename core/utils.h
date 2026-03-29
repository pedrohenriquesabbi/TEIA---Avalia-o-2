#pragma once
#include "puzzle_state.h"
#include <vector>

PuzzleState getGoalState();
PuzzleState generateRandomInitial(int shuffles);
int calculateManhattan(const PuzzleState& state);
std::vector<PuzzleState> getNeighbors(const PuzzleState& state);