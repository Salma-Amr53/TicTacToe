#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Difficulty {
    Easy,Hard      
};

class Board{
private:
    int size;
    vector<vector<char>> grid;
public:
    Board(){
    }
    Board(int s){
        
    }
    void dispaly(){

    }
    bool makeMove(int row, int col, char symbol){
        if(isValidMove(row,col)){
            grid[row][col] = symbol;
            return true;
        }
        return false;
    }
    bool isValidMove(int row, int col)const{
        

    }
    bool checkWin(char symbol) const{

    }
    bool isFull()const{

    }
    char getCell(int row, int col)const{
        return grid[row][col];
    }
    void reset(){
    }
    int getSize()const{

    }
};


class Player{
private:
    string name;
    char symbol;
public:
    Player(const string& name, char symbol){

    }
    virtual void getMove(int &row, int &col) = 0;
    string getName()const{

    }
    char getSymbol()const{

    }
    void setName(const string & name){

    }
};


class AIPlayer : public Player {
    private:
    Difficulty difficultyLevel;
    public:
    AIPlayer(const string& name, char symbol, Difficulty difficulty)
    : Player(name, symbol) {
        difficultyLevel = difficulty;
    }
    void getMove(int& row, int& col) override{

    }
    void setDifficulty(Difficulty newDifficulty){

    }
    void getRandomMove(const Board& board, int& row, int& col) const{
        vector<pair<int, int>> emptyCells;
        for (int r = 0; r < board.getSize(); r++)
            for (int c = 0; c < board.getSize(); c++)
                if(board.getCell(r,c) == ' ')       //empty cell
                    emptyCells.push_back({r,c});
        if(emptyCells.size() != 0){     //has empty cells
            int index = rand() % emptyCells.size();
            row = emptyCells[index].first;
            col = emptyCells[index].second;
        }
        else{       //set row and col = -1
            row = -1;
            col = -1;
        }

    }
    void getBestMove(Board& board, int& row, int& col) const{

    }
    int evaluateBoard(const Board& board) const{

    } 
};


class Game{
    private:
    Board board;                       // The game board
    Player* player1;                   // First player
    Player* player2;                   // Second player
    Player* currentPlayer;

    public:
    Game(){

    }
    void start(){

    }
    void showMenu(){
        int gameMode;
        while(true){
            cout << "Game mode\n1. Player vs Player (PvP)\n2. Player vs Computer (PvC)" << endl;
            cin >> gameMode;
            if(gameMode == 1){
                setupPvP();
                break;
            }
            else if(gameMode == 2){
                while(true){
                    cout << "Select the difficulty\n1. Easy\n2. Hard." << endl;
                    int d; 
                    cin >> d;
                    if(d == 1){
                        setupPvC(Easy);
                        break;
                    }
                    else if(d == 2){
                        setupPvC(Hard);
                        break;
                    }
                    else
                        cout << "Not Valid." << endl; 
                }
                break;
            }
            else
                cout << "Not Valid." << endl;
        }
    }
    void setupPvP(){

    }
    void setupPvC(Difficulty level){

    }
    void switchPlayer(){

    }
    void handleHumanMove(){
        int r, c;
        while(true){
            cout << "Enter the Row: " << endl;
            cin >> r;
            cout << "Enter the Column: " << endl;
            cin >> c;
            if(board.makeMove(r,c,currentPlayer->getSymbol())){
                cout << "Done." << endl;
                board.dispaly();
                break;
            }
            else
                cout << "invalid input." << endl;
        }
    }
    void handleAIMove(AIPlayer aiPlayer){


    }
    bool checkGameEnd(){

    }
    void displayResult(){
        if(board.checkWin(currentPlayer->getSymbol()))
            cout << currentPlayer->getName() << " Wins." << endl;
        else if(board.isFull())
            cout << "Draw!" << endl;
    }
    void reset(){

    }
    
};

int main(){
    return 0;
}