#include<bits/stdc++.h>
using namespace std;

// Dice Class
class Dice {
public:
    int roll() {
        return (rand() % 6) + 1;  // Random number between 1 and 6
    }
};

// Player Class
class Player {
public:
    string name;
    int position;

    Player(string name) {
        this->name = name;
        this->position = 1;  // Start from position 1
    }

    void move(int steps) {
        position += steps;
    }
};

// Board Class
class Board {
public:
    unordered_map<int, int> snakes;
    unordered_map<int, int> ladders;

    Board(unordered_map<int,int> snakes,unordered_map<int,int> ladders) {
        this->snakes = snakes;
        this->ladders = ladders;
    }

    int getNewPosition(int position) {
        if (snakes.find(position) != snakes.end()) {
            cout << "Oops! Bitten by a snake at " << position << endl;
            return snakes[position];
        }
        if (ladders.find(position) != ladders.end()) {
            cout << "Yay! Climbing a ladder at " << position << endl;
            return ladders[position];
        }
        return position;
    }
};

// Game Class
class Game {
private:
    
    queue<Player> players;
    Board board;
    Dice dice;
    int totalPlayers;
    bool isGameOver;

public:
    Game(vector<string> playerNames,unordered_map<int,int> &ladders,unordered_map<int,int> &snakes):board(snakes,ladders) {
        totalPlayers = playerNames.size();
        isGameOver = false;

        for (auto &name : playerNames) {
            players.push(Player(name));
        }
        srand(time(0));  // Seed for random number generation
    }

    void playTurn() {
        if (isGameOver) return;

        Player &player = players.front();
        players.pop();
        players.push(player);
        int diceRoll = dice.roll();
        cout << player.name << " rolled a " << diceRoll << endl;

        int newPosition = player.position + diceRoll;
        if (newPosition > 100) {
            cout << player.name << " needs an exact roll to win!" << endl;
            return;
        }

        player.position = board.getNewPosition(newPosition);
        cout << player.name << " moved to " << player.position << endl;

        if (player.position == 100) {
            cout << "🎉 " << player.name << " wins the game! 🎉" << endl;
            isGameOver = true;
        }
    }

    void start() {
        while (!isGameOver) {
            playTurn();
        }
    }
};

// Main Function
int main() {
    vector<string> playerNames;
    unordered_map<int,int> snakes,ladders;

    int total_palyers;
    cout<<"Enter total number of players: "<<"\n";
    cin>>total_palyers;

    cout<<"enter all players name "<<"\n";

    for(int i=0;i<total_palyers;i++){
        string playername;
        cin>>playername;
        playerNames.push_back(playername);
    }

    int total_ladders;
    cout<<"Enter number of total ladders :"<<"\n";
    cin>>total_ladders;

    cout<<"Enter coordinates of ladders, make sure first number must be ladder's bottom coordinate then ladder's top:"<<"\n";

    for(int i=0;i<total_ladders;i++){
        int ladder_start,ladder_end;
        cin>>ladder_start>>ladder_end;
        ladders[ladder_start] = ladder_end;
    }

    int total_snakes;
    cout<<"Enter total number of snakes :"<<"\n";
    cin>>total_snakes;

    cout<<"Enter coordinates of snakes, first enter coordinate of head of snake then coordinate of snake tail :"<<"\n";


    for(int i=0;i<total_snakes;i++){
        int snake_head,snake_tail;
        cin>>snake_head>>snake_tail;
        snakes[snake_head] = snake_tail;
    }

    Game game(playerNames,ladders,snakes);
    game.start();
    return 0;
}
