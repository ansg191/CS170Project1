//
// Created by Anshul Gupta on 5/4/24.
//

#ifndef CS170PROJECT1_PUZZLE_H
#define CS170PROJECT1_PUZZLE_H

#include <cstdint>
#include <iostream>
#include <vector>

/**
 * @class Puzzle
 * @brief Represents a 8-puzzle board of width N.
 *
 * @tparam N The size of the puzzle board. ex. 8-puzzle has N = 3. 15-puzzle has N = 4.
 */
template<size_t N = 3>
class Puzzle {
public:
	/**
	 * @brief Constructs a puzzle board from a 2D array.
	 *
	 * Will throw an exception if the board is invalid.
	 */
	explicit Puzzle(const uint8_t board[N][N]);

	/// Enumerates all possible board states via moves from the current board state
	[[nodiscard]] std::vector<Puzzle<N>> availableMoves() const;

	/// Counts the number of misplaced tiles in the current board state compared to the goal state.
	size_t countMisplacedTiles(const Puzzle<N> &goal) const;

	/// Calculates the Euclidean distance of the current board state compared to the goal state.
	double calcEuclidDist(const Puzzle<N> &goal) const;

	bool operator==(const Puzzle<N> &other) const;

	friend std::ostream &operator<<(std::ostream &os, const Puzzle<N> &puzzle)
	{
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < N; j++) {
				uint8_t value = puzzle.board[i][j];
				if (value == 0)
					os << "* ";
				else
					os << static_cast<int>(value) << ' ';
			}
			os << '\n';
		}
		return os;
	}

private:
	/// Maximum value of a tile on the board.
	constexpr static uint8_t MAX_VALUE = N * N - 1;

	/// The board state.
	uint8_t board[N][N];

	/// Returns the location of the empty space on the board.
	[[nodiscard]] std::tuple<size_t, size_t> emptySpace() const;
};

template<size_t N>
Puzzle<N>::Puzzle(const uint8_t board[N][N])
{
	bool seen[N * N] = {false};
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			uint8_t value = board[i][j];

			if (value > MAX_VALUE)
				throw std::invalid_argument("Invalid board state");
			if (seen[value])
				throw std::invalid_argument("Duplicate value in board state");

			this->board[i][j] = value;
			seen[value] = true;
		}
	}
}

template<size_t N>
std::tuple<size_t, size_t> Puzzle<N>::emptySpace() const
{
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			if (board[i][j] == 0)
				return {i, j};
		}
	}

	throw std::invalid_argument("No empty space on board");
}


template<size_t N>
std::vector<Puzzle<N>> Puzzle<N>::availableMoves() const
{
	// Find location of 0 (empty space) on board
	size_t i, j;
	std::tie(i, j) = emptySpace();

	// All possible swappable locations
	std::tuple<size_t, size_t> swaps[4];
	size_t numSwaps = 0;

	if (i > 0) swaps[numSwaps++] = {i - 1, j};
	if (i < N - 1) swaps[numSwaps++] = {i + 1, j};
	if (j > 0) swaps[numSwaps++] = {i, j - 1};
	if (j < N - 1) swaps[numSwaps++] = {i, j + 1};

	// Convert swappable locations to board states
	std::vector<Puzzle<N>> moves;
	for (size_t k = 0; k < numSwaps; k++) {
		size_t x, y;
		std::tie(x, y) = swaps[k];

		Puzzle<N> move = *this;
		std::swap(move.board[i][j], move.board[x][y]);
		moves.push_back(move);
	}

	return moves;
}

template<size_t N>
size_t Puzzle<N>::countMisplacedTiles(const Puzzle<N> &goal) const
{
	size_t misplaced = 0;
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			uint8_t value = this->board[i][j];
			// Skip the empty space
			if (value == 0)
				continue;
			if (value != goal.board[i][j])
				misplaced++;
		}
	}
	return misplaced;
}

template<size_t N>
double Puzzle<N>::calcEuclidDist(const Puzzle<N> &goal) const
{
	// Mappings of tile values to their positions
	std::pair<size_t, size_t> thisPos[N * N];
	std::pair<size_t, size_t> goalPos[N * N];

	// Fill in the mappings & skip the empty spaces
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			if (this->board[i][j])
				thisPos[this->board[i][j]] = {i, j};
			if (goal.board[i][j])
				goalPos[goal.board[i][j]] = {i, j};
		}
	}

	// Calculate the Euclidean distance
	double totalDistance = 0.0;
	for (size_t i = 1; i < N * N; i++) {
		double x1 = thisPos[i].first;
		double y1 = thisPos[i].second;
		double x2 = goalPos[i].first;
		double y2 = goalPos[i].second;
		totalDistance += std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}

	return totalDistance;
}


template<size_t N>
bool Puzzle<N>::operator==(const Puzzle<N> &other) const
{
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			if (board[i][j] != other.board[i][j])
				return false;
		}
	}
	return true;
}


#endif//CS170PROJECT1_PUZZLE_H
