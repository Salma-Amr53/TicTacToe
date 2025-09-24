//Display
void display()
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

/////////////////////////////////

//Player Constructor
Player(const string& name, char symbol)
{
	this.name=name;
	this.symbol=symbol;
}

/////////////////////////////////

//full
bool isFull() const
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

/////////////////////////////////

//setName
void setName(const string& name)
{
	this.name=name;
}

/////////////////////////////////

//getBestMove
void getBestMove(Board& board,int& row,int& col)
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
                board.makeMove(i, j, ' ');    //for integration it might not work so we need a function to empty the space after trying a move

                if (score > bestScore) {
                    bestScore = score;
                    row = i;
                    col = j;
				}
			}
		}	
	}
}

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

/////////////////////////////////

//Start
void start() {
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


/////////////////////////////////

//switchPlayer
void switchPlayer() {
    if (currentPlayer == player1)
        currentPlayer = player2;
    else
        currentPlayer = player1;
}


/////////////////////////////////