#include <iostream>
#include <vector>
#include <string>
/*
UserId=Moinul
Password=Moinul909
*/

using namespace std;

// Constants for login credentials
const string USER_ID = "Moinul";
const string PASSWORD = "Moinul909";

// Login System Class
class LoginSystem {
public:
    // Function to validate user credentials
    bool validateLogin(string userId, string password) {
        return (userId == USER_ID && password == PASSWORD);
    }
};

// Sudoku Board Class
class SudokuBoard {
public:
    // Function to print the Sudoku board
    void printBoard(vector<vector<int>>& board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                cout << board[row][col] << " ";
            }
            cout << endl;
        }
    }
};

// Sudoku Solver Class using Backtracking
class SudokuSolver {
public:
    // Function to check if placing a number is safe
    bool isSafe(vector<vector<int>>& board, int row, int col, int num) {
        // Check the row and column
        for (int x = 0; x < 9; x++) {
            if (board[row][x] == num || board[x][col] == num) {
                return false;
            }
        }

        // Check the 3x3 grid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }
        return true;
    }

    // Function to solve the Sudoku using backtracking
    bool solveSudoku(vector<vector<int>>& board, int row, int col) {
        if (row == 9 - 1 && col == 9) return true;  // Reached end of board
        if (col == 9) {  // Move to the next row
            row++;
            col = 0;
        }
        if (board[row][col] != 0) return solveSudoku(board, row, col + 1);

        for (int num = 1; num <= 9; num++) {
            if (isSafe(board, row, col, num)) {
                board[row][col] = num;  // Make tentative assignment

                if (solveSudoku(board, row, col + 1)) return true;

                board[row][col] = 0;  // Undo assignment if not solved
            }
        }
        return false;
    }
};

// Main Function
int main() {
    LoginSystem login;
    string userId, password;

    cout << "Enter User ID: ";
    cin >> userId;
    cout << "Enter Password: ";
    cin >> password;

    // Validate Login
    if (!login.validateLogin(userId, password)) {
        cout << "Invalid credentials! Access Denied." << endl;
        return 0;
    }

    cout << "Access Granted! Welcome, " << userId << "!" << endl;

    // Example Sudoku board (0 represents empty cells)
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    SudokuSolver solver;
    SudokuBoard display;

    cout << "Original Sudoku Board:" << endl;
    display.printBoard(board);

    if (solver.solveSudoku(board, 0, 0)) {
        cout << "Solved Sudoku Board:" << endl;
        display.printBoard(board);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}

