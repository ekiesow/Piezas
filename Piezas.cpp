#include "Piezas.h"

#include <iostream>
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
 **/

/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
 **/
Piezas::Piezas() {
  // resize the board
  board.resize(3, std::vector<Piece>(4, Blank));
  turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
 **/
void Piezas::reset() {
  // reset non-empty board
  board = std::vector<std::vector<Piece> >(3, std::vector<Piece>(4, Blank));
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
 **/
Piece Piezas::dropPiece(int column) {
  
  // save the current turn
  Piece temp = turn;
  // change turn to the other player
  turn == X ? turn = O : turn = X;

  // check that colum:n is a valid spot on the board
  // if invalid, player loses their turn
  if (column < 0 || column > 3) {
    return Invalid;
  }

  // try and place piece of current turrn if the column is not full
  // return the piece placed
  size_t counter = board.size() - 1;
  while (counter >= 0) {
    if (board[counter][column] == Blank) {
      board[counter][column] = temp;
      return temp;
    }
    counter--;
  }

  // return Blank, column is full. player loses their turn
  return Blank;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
 **/
Piece Piezas::pieceAt(int row, int column) {
  // check that the coordinates are not out of bounds
  if (row < 0 || row > 2) return Invalid;
  if (column < 0 || column > 3) return Invalid;

  // transpose top and bottom rows
  if(row == 0) row = 2;
  else if(row == 2) row = 0;

  // return the piece on the board at specified row and column
  // will return Blank if X or O has not placed a piece
  return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
 **/
Piece Piezas::gameState() {
  bool blank = false;
  int x_counter = 0, x_temp = 0;
  int o_counter = 0, o_temp = 0;

  // scan the board across the columns
  for (size_t i = 0; i < board.size(); i++) {
    x_temp = 0;
    o_temp = 0;
    for (size_t j = 0; j < board[i].size(); j++) {
      if (board[i][j] == X) {
        // increment X and reset O
        x_temp++;
        o_temp = 0;
      } else if (board[i][j] == O) {
        // increment O and reset X
        o_temp++;
        x_temp = 0;
      } else if (board[i][j] == Blank)
        // return Invalid if there is a blank space in the board
        // the game is not over. 
        return Invalid;

      // keep track of the most in a row
      if (x_temp > x_counter) x_counter = x_temp;
      if (o_temp > o_counter) o_counter = o_temp;
    }
  }

  // scan the board across the rows
  for (size_t i = 0; i < board.size(); i++) {
    x_temp = 0;
    o_temp = 0;
    for (size_t j = 0; j < board[i].size(); j++) {
      if (board[j][i] == X) {
        // increment X and reset O
        x_temp++;
        o_temp = 0;
      } else if (board[j][i] == O) {
        // increment O and reset X
        o_temp++;
        x_temp = 0;
      }

      // keep track of the most in a column
      if (x_temp > x_counter) x_counter = x_temp;
      if (o_temp > o_counter) o_counter = o_temp;
    }
  }
 
  // return Blank if there is a tie
  if(x_counter == o_counter) return Blank;
  // return the Piece of the winner
  if(x_counter > o_counter)
    return X;
  return O;
}