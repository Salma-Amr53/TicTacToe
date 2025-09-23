//Display
void display()
{
	for(int i=0;i<size+2;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(i%2==0)
			{
			char current = getCell(i,j);
			if(current=='X'||current=='O')
				cout<<' '<<getCell(i,j)<<' ';
			else
				cout<<' ';
			if(j<size-1)
				cout<<'|';
			}
			else
				cout<<"--- ";

		}
		cout<<endl;
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