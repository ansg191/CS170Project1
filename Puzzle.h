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
	explicit Puzzle(const uint8_t board[N][N]);

	/**
	 * @brief Enumerates all possible board states via moves from the current board state.
	 *
	 * @return Vector of all possible board states.
	 */
	[[nodiscard]] std::vector<Puzzle<N>> availableMoves() const;

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


#endif//CS170PROJECT1_PUZZLE_H
