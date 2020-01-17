/* Author: Hila Manalai 
*/

#include <iostream> // for i/o
#include <fstream> // for file handling
#include <vector>
#include <string>
#include "stdlib.h" // for the system command
#include "CTurtle.hpp"
namespace ct = cturtle;
using namespace std;

char PART_OF_PATH = 'O', TRIED = '.', OBSTACLE = '+', DEAD_END = '-', TREASURE='T', TREASURE_FOUND = 'X', TRIED_2='!', DEAD_END_2='~'; // symbols
class Maze {
private:
	int rows = 0;
	int cols = 0;
	vector <vector <char>> mazeVect; // Matrix of chars
	int startRow; // stores the most current row
	int startColumn; // stores the most current col

public: 
	

	Maze() {
		//readMaze("mazemap2.txt");
		cout << "Default constructor called.\n" << endl;
	}

	void readMaze(string fileName) {
		string line;
		ifstream readFile (fileName);
		int lineCount = 0;

		if (!readFile.is_open()) {// Checking for errors opening the file
			cout << ("Error opening file.");
			return;
		}
		while (getline(readFile, line)) {// Reading file until the end is reached or an error occurs
			vector <char> thisLine;
			for (unsigned int i = 0; i < line.length(); ++i) {
				thisLine.push_back(line[i]);
			}
			mazeVect.push_back(thisLine);
			lineCount++;
		}

		if (readFile.bad()) { // More error checking
			cout << ("Error reading file.");
			return;
		}

		readFile.close();
		rows = mazeVect.size();			// Updating class attributes "rows" and "cols"
		cols = mazeVect[0].size();
		cout << "There are " << rows << " rows, and " << cols << " columns.\n\n";
		return;
	}

	void printMaze() {
		for (unsigned int i = 0; i < mazeVect.size(); i++) {
			for (unsigned int j = 0; j < mazeVect[i].size(); j++) {
				cout << mazeVect[i][j];

			}
			cout << endl;
		}
		cout << endl;
		return;
	}

	vector <int> startPosition() { 
		/*Finds the Start point in the maze */
		vector <int> coord;
		for (unsigned int i = 0; i < mazeVect.size(); i++) {
			for (unsigned int j = 0; j < mazeVect[i].size(); j++) {
				if (mazeVect[i][j] == 'S') {
					startRow = i;
					startColumn = j;
					cout << startRow << startColumn;
				}
			}
		}
		return coord = { startRow, startColumn };
	}
	
	void updatePosition(int row, int col, char val = NULL) {
		/* updates the position based on what we are encountering. Ex. Obstacle, dead end etc. */
		if (val) {
			mazeVect[row][col] = val;
		}
	}
	
	int isExit(int row, int col) {
		/* Finds the exit*/
		return (row == 0 || row == rows - 1 || col == 0 || col == cols - 1);
	}


	bool searchTreasure(int startRow, int startColumn) {
		/* Goes through the whole maze and finds T's */
		Sleep(5);
		system("cls");
		printMaze();
		if (mazeVect[startRow][startColumn] == OBSTACLE) {
			return false;
		}
		if (mazeVect[startRow][startColumn] == TRIED || mazeVect[startRow][startColumn] == DEAD_END) {
			return false;
		}
		if (isExit(startRow, startColumn)) {
			//updatePosition(startRow, startColumn, PART_OF_PATH);
			return false;
		}
		if (mazeVect[startRow][startColumn] == TREASURE) {
			mazeVect[startRow][startColumn] = TREASURE_FOUND;
			return true;
		}
		updatePosition(startRow, startColumn, TRIED);
		bool found = searchTreasure(startRow - 1, startColumn) ||
					 searchTreasure(startRow + 1, startColumn) ||
					 searchTreasure(startRow, startColumn - 1) ||
					 searchTreasure(startRow, startColumn + 1);
		if (found) {
			updatePosition(startRow, startColumn, PART_OF_PATH);
		}
		else {
			updatePosition(startRow, startColumn, DEAD_END);
		}
		return false;

	}

	bool searchFrom(int startRow, int startColumn) {
		/* Goes through the maze to find the Exit. */
		Sleep(5);
		system("cls");
		printMaze();
		if (mazeVect[startRow][startColumn] == OBSTACLE) {
			return false;
		}
		if (mazeVect[startRow][startColumn] == TRIED_2 || mazeVect[startRow][startColumn] == DEAD_END_2) {
			return false;
		}
		if (isExit(startRow, startColumn)){
			updatePosition(startRow, startColumn, PART_OF_PATH);
			return true;
		}
		updatePosition(startRow, startColumn, TRIED_2);
		bool found = searchFrom(startRow - 1, startColumn) ||
					 searchFrom(startRow, startColumn - 1) ||
					 searchFrom(startRow + 1, startColumn) ||
					 searchFrom(startRow, startColumn + 1);
		if (found){
			updatePosition(startRow, startColumn, PART_OF_PATH);
		}
		else {
			updatePosition(startRow, startColumn, DEAD_END_2);
		}
		return found;

	}

};






int main() {
	Maze myMaze;
	string user_choice;
	
	cout << "Please choose a Maze Map. A) mazemap1.txt B) mazemap2.txt C) mazemap3.txt D) mazemap4.txt (RECOMMENDED) E) mazemap5.txt" << endl;
	cin >> user_choice;
	myMaze.readMaze(user_choice);
	myMaze.printMaze();
	vector <int> coord = myMaze.startPosition();

	myMaze.searchTreasure(coord[0], coord[1]); // first find the treasures
	myMaze.searchFrom(coord[0], coord[1]);  // then find the exit
	
	cout << "Press Enter to exit...";
	getchar();
	return 0;
};