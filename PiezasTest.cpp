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

TEST(PiezasTest, drop_single_piece_first_col) {
  Piezas piezas;
  ASSERT_EQ(Piece::X, piezas.dropPiece(0));
}

TEST(PiezasTest, drop_and_check_single_piece_first_col) {
  Piezas piezas;
  piezas.dropPiece(0);
  ASSERT_EQ(Piece::X, piezas.pieceAt(0, 0));
}

TEST(PiezasTest, reset_board) {
  Piezas piezas;
  piezas.dropPiece(0);
  piezas.reset();
  ASSERT_EQ(Piece::Blank, piezas.pieceAt(0, 0));
}

TEST(PiezasTest, drop_piece_out_of_bounds) {
  Piezas piezas;
  ASSERT_EQ(Piece::Invalid, piezas.dropPiece(4));
}

TEST(PiezasTest, drop_piece_out_of_bounds_negative) {
  Piezas piezas;
  ASSERT_EQ(Piece::Invalid, piezas.dropPiece(-1));
}

TEST(PiezasTest, drop_and_check_stacked_pieces_first_col) {
  Piezas piezas;
  piezas.dropPiece(0);  // X
  piezas.dropPiece(0);  // O
  ASSERT_EQ(Piece::O, piezas.pieceAt(1, 0));
}

TEST(PiezasTest, fill_first_col_check_top_piece) {
  Piezas piezas;
  piezas.dropPiece(0);  // X
  piezas.dropPiece(0);  // O
  piezas.dropPiece(0);  // X
  ASSERT_EQ(Piece::X, piezas.pieceAt(2, 0));
}