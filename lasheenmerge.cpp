#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Difficulty {
    Easy,Hard      
};

int minimax(Board& board, int depth, bool isMaximizing, char ai, char human) 
{
    int score = evaluateBoard(board, ai, human);

    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (board.isFull()) return 0;

    int size = board.getSize();

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board.isValidMove(i, j)) {
                    board.makeMove(i, j, ai);
                    best = max(best, minimax(board, depth + 1, false, ai, human));
                    board.undoMove(i, j);
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board.isValidMove(i, j)) {
                    board.makeMove(i, j, human);
                    best = min(best, minimax(board, depth + 1, true, ai, human));
                    board.undoMove(i, j);
                }
            }
        }
        return best;
    }
}

void undoMove(int row, int col) {
    if (row >= 0 && row < size && col >= 0 && col < size) {
        grid[row][col] = ' ';
    }
}

class Board{
private:
    int size;
    vector<vector<char>> grid;
public:
    Board(){
    }
    Board(int s){
        
    }
    void dispaly()
    {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                char current = getCell(i, j);
                if (current == 'X' || current == 'O')
                    cout << " " << current << " ";
                else
                    cout << "   ";

                if (j < size - 1)
                    cout << "|";
            }
            cout << endl;

            if (i < size - 1) {
                for (int j = 0; j < size; j++) {
                    cout << "---";
                    if (j < size - 1)
                        cout << "+";
                }
                cout << endl;
            }
        }
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
    bool isFull()const
    {
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                char current = getCell(i,j);
                if(current=='X'||current=='O')
                    continue;
                else
                    return 0;
            }
        }   
        return 1;
    }
    char getCell(int row, int col)const{
        return grid[row][col];
    }
    void reset(){
    }
    int getSize()const{

    }
    friend void undoMove(int row, int col);
};


class Player{
private:
    string name;
    char symbol;
public:
    Player(const string& name, char symbol)
    {
        this.name=name;
        this.symbol=symbol;
    }
    virtual void getMove(int &row, int &col) = 0;
    string getName()const{

    }
    char getSymbol()const{

    }
    void setName(const string & name){
        this.name=name;
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

    friend int minimax(Board& board, int depth, bool isMaximizing, char ai, char human);
    
    void getBestMove(Board& board, int& row, int& col) const
    {
        char ai=this->getSymbol();
        char human;
        if(ai=='X')
            human='O';
        else
            human='X'; 
        int bestScore=-5000;
        int size=board.getSize();

        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                 if (board.isValidMove(i, j)) {
                    board.makeMove(i, j, ai);
                    int score = minimax(board, 0, false, ai, human);
                    board.undoMove(i, j);    //for integration it might not work so we need a function to empty the space after trying a move

                    if (score > bestScore) {
                        bestScore = score;
                        row = i;
                        col = j;
                    }
                }
            }   
        }
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
    void start()
    {
        board.reset();            
        showMenu();                 

        currentPlayer = player1;    

        while (!checkGameEnd()) {   
            board.display();
            std::cout << currentPlayer->getName() 
                      << " (" << currentPlayer->getSymbol() << ")'s turn.\n";

            int row, col;

            if (AIPlayer* ai = dynamic_cast<AIPlayer*>(currentPlayer)) {
                handleAIMove(ai);   
            } else {
                handleHumanMove(currentPlayer); 
            }

            switchPlayer();      
        }

        board.display();          
        displayResult();         
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
    void switchPlayer() 
    {
        if (currentPlayer == player1)
            currentPlayer = player2;
        else
            currentPlayer = player1;
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