/**
 * Unit Tests for Piezas
 **/

#include <gtest/gtest.h>

#include "Piezas.h"

class PiezasTest : public ::testing::Test {
 protected:
  PiezasTest() {}             // constructor runs before each test
  virtual ~PiezasTest() {}    // destructor cleans up after tests
  virtual void SetUp() {}     // sets up before each test (after constructor)
  virtual void TearDown() {}  // clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck) { ASSERT_TRUE(true); }

/*** Test board reset ***/

TEST(PiezasTest, reset_board) {
  Piezas piezas;
  piezas.dropPiece(0);  // X
  ASSERT_EQ(Piece::X, piezas.pieceAt(0, 0));
  piezas.reset();
  ASSERT_EQ(Piece::Blank, piezas.pieceAt(0, 0));
}

/*** Test Out of Bounds errors ***/

TEST(PiezasTest, drop_piece_out_of_bounds) {
  Piezas piezas;
  ASSERT_EQ(Piece::Invalid, piezas.dropPiece(4));
}

TEST(PiezasTest, drop_piece_out_of_bounds_negative) {
  Piezas piezas;
  ASSERT_EQ(Piece::Invalid, piezas.dropPiece(-1));
}

TEST(PiezasTest, piece_at_out_of_bounds_row_negative) {
  Piezas piezas;
  ASSERT_EQ(Piece::Invalid, piezas.pieceAt(-1, 0));
}

TEST(PiezasTest, piece_at_out_of_bounds_row) {
  Piezas piezas;
  ASSERT_EQ(Piece::Invalid, piezas.pieceAt(3, 0));
}

TEST(PiezasTest, piece_at_out_of_bounds_col_negative) {
  Piezas piezas;
  ASSERT_EQ(Piece::Invalid, piezas.pieceAt(0, -1));
}

TEST(PiezasTest, piece_at_out_of_bounds_col) {
  Piezas piezas;
  ASSERT_EQ(Piece::Invalid, piezas.pieceAt(0, 4));
}

/*** Test dropPiece and pieceAt ***/

TEST(PiezasTest, drop_single_piece_first_col) {
  Piezas piezas;
  ASSERT_EQ(Piece::X, piezas.dropPiece(0));
}

TEST(PiezasTest, drop_and_check_single_piece_first_col) {
  Piezas piezas;
  piezas.dropPiece(0);  // X
  ASSERT_EQ(Piece::X, piezas.pieceAt(0, 0));
}

TEST(PiezasTest, drop_and_check_stacked_pieces_first_col) {
  Piezas piezas;
  piezas.dropPiece(0);  // X
  piezas.dropPiece(0);  // O
  // Test that the turns changed
  ASSERT_EQ(Piece::O, piezas.pieceAt(1, 0));
}

TEST(PiezasTest, fill_first_col_check_top_piece) {
  Piezas piezas;
  piezas.dropPiece(0);  // X
  piezas.dropPiece(0);  // O
  piezas.dropPiece(0);  // X
  ASSERT_EQ(Piece::X, piezas.pieceAt(2, 0));
}

TEST(PiezasTest, overflow_col) {
  Piezas piezas;
  piezas.dropPiece(0);                           // X
  piezas.dropPiece(0);                           // O
  piezas.dropPiece(0);                           // X
  ASSERT_EQ(Piece::Blank, piezas.dropPiece(0));  // O
}

/*** Test gameSate ***/

TEST(PiezasTest, test_game_state_game_not_finished) {
  Piezas piezas;
  piezas.dropPiece(0);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(0);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(0);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(2);  // X
  piezas.dropPiece(3);  // O
  piezas.dropPiece(2);  // X
  piezas.dropPiece(3);  // O
  piezas.dropPiece(2);  // X
  // game board is not full. gameState should return Invalid
  ASSERT_EQ(Piece::Invalid, piezas.gameState());
}

TEST(PiezasTest, test_game_state_tie_column_wise) {
  Piezas piezas;
  piezas.dropPiece(0);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(0);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(0);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(2);  // X
  piezas.dropPiece(3);  // O
  piezas.dropPiece(2);  // X
  piezas.dropPiece(3);  // O
  piezas.dropPiece(2);  // X
  piezas.dropPiece(3);  // O
  // game board full. Tie should return Blank
  ASSERT_EQ(Piece::Blank, piezas.gameState());
}

TEST(PiezasTest, test_game_state_tie_row_wise) {
  Piezas piezas;
  piezas.dropPiece(0);  // X
  piezas.dropPiece(0);  // O
  piezas.dropPiece(1);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(2);  // X
  piezas.dropPiece(2);  // O
  piezas.dropPiece(3);  // X
  piezas.dropPiece(3);  // O
  piezas.dropPiece(0);  // X
  piezas.dropPiece(2);  // O
  piezas.dropPiece(1);  // X
  piezas.dropPiece(3);  // O
  // game board full. Tie should return Blank
  ASSERT_EQ(Piece::Blank, piezas.gameState());
}

TEST(PiezasTest, test_game_state_X_wins_by_one) {
  Piezas piezas;
  piezas.dropPiece(0);  // X
  piezas.dropPiece(0);  // O
  piezas.dropPiece(1);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(2);  // X
  piezas.dropPiece(2);  // O
  piezas.dropPiece(3);  // X
  piezas.dropPiece(0);  // O
  piezas.dropPiece(3);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(3);  // X
  piezas.dropPiece(2);  // O
  // game board full. X with four and O with three should return X
  ASSERT_EQ(Piece::X, piezas.gameState());
}

TEST(PiezasTest, test_game_state_O_wins_by_one) {
  Piezas piezas;
  piezas.dropPiece(0);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(0);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(2);  // X
  piezas.dropPiece(1);  // O
  piezas.dropPiece(3);  // X
  piezas.dropPiece(2);  // O
  piezas.dropPiece(2);  // X
  piezas.dropPiece(0);  // O
  piezas.dropPiece(3);  // X
  piezas.dropPiece(3);  // O
  // game board full. O with three and X with two should return O
  ASSERT_EQ(Piece::O, piezas.gameState());
}