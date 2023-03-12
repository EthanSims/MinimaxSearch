/**
 * @file test.cpp
 * @author Ethan Sims (ea.sims@me.com)
 * @brief 
 */

#include "../includes/GameBoard.h"
#include <iostream>

using namespace std;

/**
 * @brief entry point for tests
 * 
 * @return int exit status
 */
int main() {
   // test setup 1
   GameBoard board("input3.txt", 1);

   // test scores
   // test red's score (vertical and diagonal up-right)
   cout << "Expected: 2, Actual: " << board.getScores()[0] << endl;

   // test green's score (horizontal 5 and diagonal down-right 5)
   cout << "Expected: 4, Actual: " << board.getScores()[1] << endl;

   board = GameBoard("edgecases.txt", 1);

   // test scores
   // test red's score (vertical and diagonal up-right)
   cout << "Expected: 13, Actual: " << board.getScores()[0] << endl;

   board = GameBoard("test2.txt", 1);

   return 0;
}