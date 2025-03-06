#include<bits/stdc++.h>
using namespace std;

class Board {
    private:
        char grid[3][3];  // 3x3 grid to hold 'X', 'O', or ' ' (empty space)
    
    public:
        Board() {
            // Initialize the board with empty spaces
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    grid[i][j] = ' ';
                }
            }
        }
    
        // Function to print the board
        void printBoard() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cout << grid[i][j];
                    if (j < 2) cout << "|";
                }
                cout << endl;
                if (i < 2) cout << "-----\n";
            }
        }
    
        // Function to check if a cell is empty
        bool isCellEmpty(int row, int col) {
            return grid[row][col] == ' ';
        }
    
        // Function to place a mark at a specific cell
        bool placeMark(int row, int col, char mark) {
            if (isCellEmpty(row, col)) {
                grid[row][col] = mark;
                return true;
            }
            return false;
        }
    
        // Function to check for a winner (horizontal, vertical, diagonal)
        bool checkWin(char mark) {
            // Check rows and columns
            for (int i = 0; i < 3; i++) {
                if ((grid[i][0] == mark && grid[i][1] == mark && grid[i][2] == mark) ||
                    (grid[0][i] == mark && grid[1][i] == mark && grid[2][i] == mark)) {
                    return true;
                }
            }
            // Check diagonals
            if ((grid[0][0] == mark && grid[1][1] == mark && grid[2][2] == mark) ||
                (grid[0][2] == mark && grid[1][1] == mark && grid[2][0] == mark)) {
                return true;
            }
            return false;
        }
    
        // Function to check if the board is full (draw condition)
        bool isFull() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (grid[i][j] == ' ') return false;
                }
            }
            return true;
        }
    };


class Player {
    private:
        char mark;
        string name;
    
    public:
        Player(string playerName, char playerMark) {
            name = playerName;
            mark = playerMark;
        }
    
        // Function to get the mark of the player
        char getMark() {
            return mark;
        }
    
        // Function to get the name of the player
        string getName() {
            return name;
        }
    };
        
class Game {
    private:
        Board board;
        Player player1, player2;
        Player* currentPlayer;
    
    public:
        Game(string name1,string name2) 
            : player1(name1, 'X'), player2(name2, 'O') {// imp line --------+++++------
            currentPlayer = &player1;
        }
    
        // Function to switch players
        void switchPlayer() {
            currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
        }
    
        // Function to play the game
        void play() {
            int row, col;
            bool validMove;
            while (true) {
                board.printBoard();
                cout << currentPlayer->getName() << "'s turn (" << currentPlayer->getMark() << "): \n";
                
                // Get valid input from the player
                do {
                    cout << "Enter row (0-2) and column (0-2): ";
                    cin >> row >> col;
                    validMove = board.placeMark(row, col, currentPlayer->getMark());
                    if (!validMove) cout << "Invalid move, try again.\n";
                } while (!validMove);
    
                // Check for a winner or draw
                if (board.checkWin(currentPlayer->getMark())) {
                    board.printBoard();
                    cout << currentPlayer->getName() << " wins!\n";
                    break;
                } else if (board.isFull()) {
                    board.printBoard();
                    cout << "It's a draw!\n";
                    break;
                }
    
                // Switch to the other player
                switchPlayer();
            }
        }
    };

int main() {
    string name1, name2;
    
    cout << "Enter name for Player 1 (X): ";
    cin >> name1;
    
    cout << "Enter name for Player 2 (O): ";
    cin >> name2;

    Game game(name1, name2);
    game.play();
    
    return 0;
}
    


        