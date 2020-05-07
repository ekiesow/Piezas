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
  ASSERT_TRUE(piezas.dropPiece(0) == Piece::X);
}

TEST(PiezasTest, drop_and_check_single_piece_first_col) {
  Piezas piezas;
  piezas.dropPiece(0);
  ASSERT_TRUE(piezas.pieceAt(0, 0) == Piece::X);
}

TEST(PiezasTest, reset_board) {
  Piezas piezas;
  piezas.dropPiece(0);
  piezas.pieceAt(0, 0);
  piezas.reset();
  ASSERT_TRUE(piezas.pieceAt(0, 0) == Piece::Blank);
}