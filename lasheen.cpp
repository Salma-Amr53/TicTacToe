#include <vector>
#include <iostream>
using namespace std;

vector<vector<char>> k ={{'X','O','O'},{'X','X','O'},{'O','O','X'}};
char getCell(int i,int j)
{
	return k[i][j];
}

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

/////////////////////////////////

//Start

/////////////////////////////////

//switchPlayer

/////////////////////////////////