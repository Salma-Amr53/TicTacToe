#include <iostream>
#include <vector>
using namespace std;

enum Difficulty { Easy, Hard };

class Board {
private:
    vector<vector<char>> grid;
    int size;
public:
    Board(int s) : size(s), grid(s, vector<char>(s, ' ')) {}

    void display(){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                cout << " " << grid[i][j] << " ";
                if(j < size - 1){
                    cout << "|";
                }
            }
            cout << endl;
            if(i < size -1){
                for(int j = 0; j < size; j++)
                {
                    cout << "---";
                    if(j < size - 1)
                    {
                        cout << "+";
                    }
                }
                cout << endl;
            }
        }
    }

    bool isValidMove(int r, int c)
    {
        return r >= 0 && r < size && c >= 0 && c < size && grid[r][c] == ' ';
    }

    void makeMove(int r, int c, char sym)
    {
        grid[r][c] = sym;
    }

    void undoMove(int r, int c){
        grid[r][c] = ' ';
    }

    bool isFull() {
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(grid[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool checkWin(char sym){
        for(int i = 0; i < size; i++){
            bool rowWin = true;
            bool colWin = true;
            for(int j = 0; j < size; j++){
                if(grid[i][j] != sym){
                    rowWin = false;
                }
                if(grid[j][i] != sym){
                    colWin = false;
                }
            }
            if(rowWin || colWin){
                return true;
            }
        }

        bool diag1 = true;
        bool diag2 = true;
        for(int i = 0; i < size; i++){
            if(grid[i][i] != sym){
                diag1 = false;
            }
            if(grid[i][size - i - 1] != sym){
                diag2 = false;
            }
        }
        return diag1 || diag2;
    }

    void reset()
    {
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                grid[i][j] = ' ';
            }
        }
    }

    char getCell(int r, int c){
        return grid[r][c];
    }

    int getSize(){
        return size;
    }
};

class Player {
protected:
    string name;
    char symbol;
public:
    Player(const string& n, char s) : name(n), symbol(s) {}

    virtual void getMove(int &row, int &col, Board &board){
        while(true)
        {
            cout << name << " (" << symbol << "), enter row and column (1-based): ";
            cin >> row >> col;
            row--;
            col--;
            if(board.isValidMove(row, col)){
                break;
            }
            else{
                cout << "Invalid move. Try again.\n";
            }
        }
    }

    string getName(){
        return name;
    }

    char getSymbol(){
        return symbol;
    }
};

class AIPlayer : public Player {
private:
    Difficulty level;
    unsigned long seed;
public:
    AIPlayer(const string& n, char s, Difficulty d) : Player(n, s), level(d), seed(123456789) {}

    void setDifficulty(Difficulty d)
    {
        level = d;
    }

    int randomIndex(int max)
    {
        seed = (seed * 1103515245 + 12345) % 2147483648;
        return seed % max;
    }

    void getRandomMove(Board &board, int &row, int &col)
    {
        vector<pair<int,int>> emptyCells;
        for(int i = 0; i < board.getSize(); i++){
            for(int j = 0; j < board.getSize(); j++){
                if(board.getCell(i,j) == ' '){
                    emptyCells.push_back({i,j});
                }
            }
        }
        if(emptyCells.size() > 0){
            int idx = randomIndex(emptyCells.size());
            row = emptyCells[idx].first;
            col = emptyCells[idx].second;
        }
        else{
            row = -1;
            col = -1;
        }
    }

    void getBestMove(Board &board, int &row, int &col){
        char ai = symbol;
        char human = (symbol == 'X') ? 'O' : 'X';
        int bestScore = -10000;
        for(int i = 0; i < board.getSize(); i++){
            for(int j = 0; j < board.getSize(); j++){
                if(board.isValidMove(i,j)){
                    board.makeMove(i,j,ai);
                    int score = minimax(board, 0, false, ai, human);
                    board.undoMove(i,j);
                    if(score > bestScore){
                        bestScore = score;
                        row = i;
                        col = j;
                    }
                }
            }
        }
    }

    int evaluateBoard(Board &board, char ai, char human)
    {
        if(board.checkWin(ai)){
            return 10;
        }
        if(board.checkWin(human)){
            return -10;
        }
        return 0;
    }

    int minimax(Board &board, int depth, bool isMax, char ai, char human)
    {
        int score = evaluateBoard(board, ai, human);
        if(score == 10){
            return score - depth;
        }
        if(score == -10){
            return score + depth;
        }
        if(board.isFull()){
            return 0;
        }

        if(isMax){
            int best = -1000;
            for(int i = 0; i < board.getSize(); i++){
                for(int j = 0; j < board.getSize(); j++){
                    if(board.isValidMove(i,j)){
                        board.makeMove(i,j,ai);
                        int val = minimax(board, depth + 1, false, ai, human);
                        board.undoMove(i,j);
                        if(val > best){
                            best = val;
                        }
                    }
                }
            }
            return best;
        }
        else{
            int best = 1000;
            for(int i = 0; i < board.getSize(); i++){
                for(int j = 0; j < board.getSize(); j++){
                    if(board.isValidMove(i,j)){
                        board.makeMove(i,j,human);
                        int val = minimax(board, depth + 1, true, ai, human);
                        board.undoMove(i,j);
                        if(val < best){
                            best = val;
                        }
                    }
                }
            }
            return best;
        }
    }

    void getMove(int &row,int &col, Board &board) override
    {
        if(level == Easy){
            getRandomMove(board, row, col);
        }
        else{
            getBestMove(board, row, col);
        }
    }
};

class Game {
private:
    Board board;
    Player *player1;
    Player *player2;
    Player *current;
public:
    Game(int size) : board(size), player1(nullptr), player2(nullptr), current(nullptr) {}

    void switchPlayer()
    {
        current = (current == player1) ? player2 : player1;
    }

    bool checkGameEnd()
    {
        return board.checkWin(player1->getSymbol()) || board.checkWin(player2->getSymbol()) || board.isFull();
    }

    void displayResult()
    {
        if(board.checkWin(player1->getSymbol())){
            cout << player1->getName() << " wins!\n";
        }
        else if(board.checkWin(player2->getSymbol())){
            cout << player2->getName() << " wins!\n";
        }
        else{
            cout << "It's a draw!\n";
        }
    }

    void handleMove()
    {
        int r, c;
        current->getMove(r, c, board);
        board.makeMove(r, c, current->getSymbol());
    }

    void setupPVP(const string& n1, const string& n2)
    {
        player1 = new Player(n1,'X');
        player2 = new Player(n2,'O');
    }

    void setupPVC(const string& n, Difficulty diff)
    {
        player1 = new Player(n,'X');
        player2 = new AIPlayer("Computer",'O', diff);
    }

    void start()
    {
        board.reset();
        current = player1;

        while(!checkGameEnd()){
            board.display();
            handleMove();
            if(checkGameEnd()){
                break;
            }
            switchPlayer();
        }

        board.display();
        displayResult();
    }

    void reset(){
        board.reset();
    }
};

int main()
{
    int size;
    cout << "Enter board size: ";
    cin >> size;

    Game game(size);
    char playAgain = 'y';

    while(playAgain == 'y' || playAgain == 'Y'){
        int mode;
        cout << "Select mode:\n1. Player vs Player\n2. Player vs Computer\nChoice: ";
        cin >> mode;

        if(mode == 1){
            string n1, n2;
            cout << "Enter Player 1 name: ";
            cin >> n1;
            cout << "Enter Player 2 name: ";
            cin >> n2;
            game.setupPVP(n1, n2);
        }
        else{
            string n;
            int diff;
            cout << "Enter Your Name: ";
            cin >> n;
            cout << "Select Difficulty: 1=Easy, 2=Hard: ";
            cin >> diff;
            game.setupPVC(n, diff == 1 ? Easy : Hard);
        }

        game.start();

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        game.reset();
    }

    return 0;
}
