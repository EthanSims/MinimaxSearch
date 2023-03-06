/**
 * @file GameBoard.cpp
 * @author Ethan Sims (ea.sims@me.com)
 * @brief contains information about the game
 */
#include "../includes/GameBoard.h"

#include <iostream>
#include <algorithm>

using namespace std;

/**
 * @brief Construct a new Game Board object
 * 
 * @param input filestream to read initial state from
 */
GameBoard::GameBoard(ifstream &input) {
   int currSlot;
   char currInput;
   this->numPieces = 0;

   // create empty vectors
   for (int column = 0 ; column < NUM_COLS ; column++) {
      this->columns[column] = new vector<Pieces>(NUM_ROWS, Pieces::NONE);
   }

   // get main board input
   for (int row = 0 ; row < NUM_ROWS ; row++) {
      for (int column = 0 ; column < NUM_COLS ; column++) {
         // check if current slot is empty, red, or green
         input.get(currInput);
         if (currInput == '\n') input.get(currInput);
         currSlot = currInput - '0';
         if (currSlot == 0) { // empty
            continue;
         } else if (currSlot == 1){ // red
            this->columns[column]->at(NUM_ROWS - 1 - row) = Pieces::RED;
            this->numPieces++;
         } else { // green
            this->columns[column]->at(NUM_ROWS - 1 - row) = Pieces::GREEN;
            this->numPieces++;
         }
      }
   }

   input >> currSlot;
   this->redNext = (currSlot == '1'); // if last char is 1, red is next

   // init scores to 0
   this->scores[0] = 0; // red score
   this->scores[1] = 0; // green score

   calcScores();
}

/**
 * @brief checks which moves are still possible
 * 
 * @return a vector of possible moves
 */
vector<int> GameBoard::getAvailMoves() {
   vector<int> moves;
   for (int column = 0 ; column < NUM_COLS ; column++) {
      if (this->columns[column]->size() < NUM_ROWS) {
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
void GameBoard::calcScores() {
   Pieces currPiece;
   int numInRow;
   bool last;

   // get horizontal scores
   for (int row = 0 ; row < NUM_ROWS ; row++) {
      last = false;
      currPiece = Pieces::NONE;
      for (int col = 0 ; col < NUM_COLS ; col++) {
         if (col == NUM_COLS - 1) last = true;
         calcScoresHelper(row, col, numInRow, currPiece, last);
         if (col >= NUM_COLS - 4 && numInRow == 1) { // no need to keep searching this row, cant get more points
            break;
         }
      }
   }

   // get vertical scores
   for (int col = 0 ; col < NUM_COLS ; col++) {
      last = false;
      currPiece = Pieces::NONE;
      for (int row = 0 ; row < NUM_ROWS ; row++) {
         if (row == NUM_ROWS- 1) last = true;
         calcScoresHelper(row, col, numInRow, currPiece, last);
         if (row >= NUM_ROWS - 4 && numInRow == 1) { // no need to keep searching this row, cant get more points
            break;
         }
      }
   }

   // get diagonal scores (up-right)
   for (int i = NUM_ROWS - 4 ; i >= -NUM_ROWS + 4 ; i--) {
      last = false;
      currPiece = Pieces::NONE;
      for (int col = 0 ; col < NUM_COLS; col++) {
         int row = col + i;
         if (row == NUM_ROWS - 1 || col == NUM_COLS - 1) last = true;
         if (row < 0) continue;

         calcScoresHelper(row, col, numInRow, currPiece, last);
         if ((row > NUM_ROWS - 4 || col > NUM_COLS - 4) && numInRow == 1) { // no need to keep searching this row, cant get more points
            break;
         }
      }
   }

   // get diagonal scores (down-right)
   for (int i = NUM_ROWS + 4 ; i >= 4 ; i--) {
      last = false;
      currPiece = Pieces::NONE;
      for (int col = 0 ; col < NUM_COLS ; col++) {
         int row = i - col;
         if (row == 0 || col == NUM_COLS - 1) last = true;
         if (row >= NUM_ROWS) continue;

         calcScoresHelper(row, col, numInRow, currPiece, last);
         if ((row < 3 || col > NUM_COLS - 4) && numInRow == 1) { // no need to keep searching this row, cant get more points
            break;
         }
      }
   }
}

/**
 * @brief helper for get scores function. Handles scoring for one piece given some contextual information
 * 
 * @param row current row location
 * @param column current column location
 * @param numInRow current number counted in a row
 * @param prevPiece previous piece
 * @param last boolean value dictating if it is the last cell in its row/column/diagonal
 */
void GameBoard::calcScoresHelper(int row, int column, int& numInRow, Pieces& prevPiece, bool last) {
   Pieces currPiece = this->columns[column]->at(row);
   if (currPiece != Pieces::NONE && currPiece == prevPiece) { // there are at least 2 pieces in a row
      numInRow++;
         // cout << column << ',' << row << ": " << numInRow << endl;

   } 
   
   if (currPiece != prevPiece || last) { // end of row or end of streak
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
         if (this->columns[column]->size() < NUM_ROWS - row) { // this spot is empty
            cout << "O ";
         }
         // not empty, print color
         Pieces piece = this->columns[column]->at(NUM_ROWS - 1 - row);
         cout << piece << " ";
      }
      cout << '\n';
   }
}

/**
 * @brief getter for scores
 * 
 * @return a 2-D array in which the 0th index is red's score and the 1st index is green's score
 */
int* GameBoard::getScores() {
   return this->scores;
}

/**
 * @brief gets user input and performs their move
 */
void GameBoard::getUserMove() {
   Pieces userPiece = Pieces::GREEN;
   if (redNext) userPiece = Pieces::RED;

   vector<int> moves = this->getAvailMoves();

   // print prompt
   cout << "The available moves are columns: ";
   for (int move : moves) {
      cout << move << " ";
   }
   cout << endl;

   cout << "Please choose a move: ";

   // handle user input
   int userMove;
   while (true) {
      cin >> userMove;
      if (find(moves.begin(), moves.end(), userMove) == moves.end()) { // not an option
         cout << "Not an option. Please enter a valid move: ";
      } else {
         break;
      }
   }

   this->insertPiece(userPiece, userMove);
}

/**
 * @brief inserts piece into given column
 * 
 * @param piece piece to insert
 * @param col column to insert to
 */
void GameBoard::insertPiece(Pieces piece, int col) {
   for (int row = 0 ; row < NUM_ROWS ; row++) {
      if (this->columns[col]->at(row) == Pieces::NONE) {
         this->columns[col]->at(row) = piece;
      }
   }
   redNext = !redNext;
}
