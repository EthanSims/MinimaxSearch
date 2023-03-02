/**
 * @file GameBoard.cpp
 * @author Ethan Sims (ea.sims@me.com)
 * @brief contains information about the game
 */
#include "../includes/GameBoard.h"

#include <iostream>

using namespace std;

/**
 * @brief Construct a new Game Board object
 * 
 * @param input filestream to read initial state from
 */
GameBoard::GameBoard(ifstream &input) {
   int currSlot;
   this->numPieces = 0;
   
   // get main board input
   for (int row = 0 ; row < NUM_ROWS ; row++) {
      for (int column = 0 ; column < NUM_COLS ; column++) {
         // check if current slot is empty, red, or green
         input >> currSlot;
         if (currSlot == 0) { // empty
            continue;
         } else if (currSlot == 1){ // red
            this->columns[column].at(NUM_ROWS - 1 - row) = Pieces::RED;
            this->numPieces++;
         } else { // green
            this->columns[column].at(NUM_ROWS - 1 - row) = Pieces::GREEN;
            this->numPieces++;
         }
      }
   }

   input >> currSlot;
   this->redNext = (currSlot == '1'); // if last char is 1, red is next

   // init scores to 0
   this->scores[0] = 0;
   this->scores[1] = 0;

   getScores();
}

/**
 * @brief checks which moves are still possible
 * 
 * @return a vector of possible moves
 */
vector<int> GameBoard::getAvailMoves() {
   vector<int> moves;
   for (int column = 0 ; column < NUM_COLS ; column++) {
      if (this->columns[column].size() < NUM_ROWS) {
         moves.push_back(column);
      }
   }

   return moves;
}

/**
 * @brief getter for numPieces
 * 
 * @return the number of pieces on the board
 */
int GameBoard::getNumPieces() {
   return this->numPieces;
}

/**
 * @brief gets the scores for red and green (scores[0] is red, scores[1] is green)
 */
void GameBoard::getScores() {
   Pieces currPiece = Pieces::NONE;
   int numInRow;

   // get horizontal scores
   for (int row = 0 ; row < NUM_ROWS ; row++) {
      for (int col = 0 ; col < NUM_COLS ; col++) {
         numInRow = getScoresHelper(row, col, numInRow, currPiece);
         if (col >= NUM_COLS - 4 && numInRow == 1) { // no need to keep searching this row, cant get more points
            break;
         }
      }
   }

   // get vertical scores
   for (int col = 0 ; col < NUM_COLS ; col++) {
      for (int row = 0 ; row < NUM_ROWS ; row++) {
         numInRow = getScoresHelper(row, col, numInRow, currPiece);
         if (row >= NUM_ROWS - 4 && numInRow == 1) { // no need to keep searching this row, cant get more points
            break;
         }
      }
   }

   // get diagonal scores (up-right)
   for (int i = NUM_ROWS - 4 ; i >= -NUM_ROWS + 4 ; i--) {
      for (int col = 0 ; col < NUM_COLS; col++) {
         int row = col + i;
         if (row < 0) continue;

         numInRow = getScoresHelper(row, col, numInRow, currPiece);
         if ((row >= NUM_ROWS - 4 || col >= NUM_COLS - 4) && numInRow == 1) { // no need to keep searching this row, cant get more points
            break;
         }
      }
   }

   // get diagonal scores (down-right)
   for (int i = NUM_ROWS - 4 ; i >= -NUM_ROWS + 4 ; i--) {
      for (int col = 0 ; col < NUM_COLS ; col++) {
         int row = i - col;
         if (row < 0) continue;

         numInRow = getScoresHelper(row, col, numInRow, currPiece);
         if ((row >= NUM_ROWS - 4 || col >= NUM_COLS - 4) && numInRow == 1) { // no need to keep searching this row, cant get more points
            break;
         }
      }
   }
}

/**
 * @brief helper for get scores function
 * 
 * @param row current row location
 * @param column current column location
 * @param numInRow current number counted in a row
 * @param prevPiece previous piece
 * @return int value of numInRow after function completes
 */
int GameBoard::getScoresHelper(int row, int column, int numInRow, Pieces& prevPiece) {
   Pieces currPiece = this->columns[row].at(column);
   if (currPiece != Pieces::NONE && currPiece == prevPiece) { // there are at least 2 pieces in a row
      numInRow++;
   } 
   
   if (currPiece != prevPiece || column == NUM_COLS - 1) { // end of row or end of streak
      if (numInRow >= 4) { // award point(s) (1 for 4 in a row, 2 for 5, 3 for 6, etc)
         if (prevPiece == Pieces::RED) {
            this->scores[0] += numInRow - 3;
         } else if (prevPiece == Pieces::GREEN) {
            this->scores[1] += numInRow - 3;
         }
      }

      numInRow = 1;
   }

   prevPiece = currPiece;
} 

/**
 * @brief prints the current board state
 */
void GameBoard::printBoard() {
   for (int row = 0 ; row < NUM_ROWS ; row++) {
      for (int column = 0 ; column < NUM_COLS ; column++) {
         // if (this->columns[column].size() < NUM_ROWS - row) { // this spot is empty
         //    cout << "O ";
         // }
         // // not empty, print color
         Pieces piece = this->columns[column].at(NUM_ROWS - 1 - row);
         cout << piece << " ";
      }
      cout << '\n';
   }
}