/**
 * @file GameBoard.cpp
 * @author Ethan Sims (ea.sims@me.com)
 * @brief contains information about the game
 * @date 2023-02-22
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
   for (int row = 0 ; row < 6 ; row++) {
      for (int column = 0 ; column < 7 ; column++) {
         // check if current slot is empty, red, or green
         input >> currSlot;
         if (currSlot == 0) { // empty
            continue;
         } else if (currSlot == 1){ // red
            this->columns[column].at(5 - row) = Pieces::RED;
            this->numPieces++;
         } else { // green
            this->columns[column].at(5 - row) = Pieces::GREEN;
            this->numPieces++;
         }
      }
   }

   input >> currSlot;
   this->redNext = (currSlot == '1');

   getScores();
}

/**
 * @brief checks which moves are still possible
 * 
 * @return a vector of possible moves
 */
vector<int> GameBoard::getAvailMoves() {
   vector<int> moves;
   for (int column = 0 ; column < 7 ; column++) {
      if (this->columns[column].size() < 6) {
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
   // TODO: implement 
}

/**
 * @brief prints the current board state
 */
void GameBoard::printBoard() {
   for (int row = 0 ; row < 6 ; row++) {
      for (int column = 0 ; column < 7 ; column++) {
         if (this->columns[column].size() < 6 - row) { // this spot is empty
            cout << "O ";
         }
         // not empty, print color
         Pieces color = this->columns[column].at(5 - row);
         cout << color << " ";
      }
      cout << '\n';
   }
}