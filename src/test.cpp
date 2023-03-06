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
   ifstream inputFile("input3.txt");
   GameBoard board(inputFile);
   inputFile.close();

   // test scores
   // test red's score (vertical and diagonal up-right)
   cout << "Expected: 2, Actual: " << board.getScores()[0] << endl;

   // test green's score (horizontal 5 and diagonal down-right 5)
   cout << "Expected: 4, Actual: " << board.getScores()[1] << endl;

   inputFile.open("edgecases.txt");
   GameBoard board2(inputFile);
   inputFile.close();

   // test scores
   // test red's score (vertical and diagonal up-right)
   cout << "Expected: 13, Actual: " << board2.getScores()[0] << endl;

   return 0;
}