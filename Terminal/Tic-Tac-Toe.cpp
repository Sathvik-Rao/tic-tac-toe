#include<iostream>
#include <limits>
#include<fstream>

using namespace std;

/*
Author     : Sathvik Rao
Start date : 23-06-2020
End date   : 25-06-2020
*/

string playerName;	//player name
char playerCharacter, computerCharacter;  // O or X

constexpr short O = 0, X = 10;

short playerNumber;	//player move number

short level ;	//easy,moderate,hard -1,0,1,2

constexpr short winnerLoactions[8][3] {		//win locations
0,1,2 ,
3,4,5 ,
6,7,8 ,
0,3,6 ,
1,4,7 ,
2,5,8 ,
0,4,8 ,
2,4,6
};

static bool flag = false;	//false -> player turn (or) true -> computer turn [for tree]
static bool flag1 = true;	//false -> player turn (or) true -> computer turn [for game]

fstream file;
string fileName;
string *fileData;
long fileDataSize;

//Tree node data type
struct tree 
{
	tree *p[8] {nullptr};
	short a[9];
	short points = 0;
};

//generate tree
class TreeOperations
{
	tree *root = new tree; //create root node
	public:
	TreeOperations()
	{
		//root node array
		for(short i = 0; i < 9; i++)
		{
			if(i+1 == playerNumber)
			{
				if(playerCharacter == 'O')
				  root -> a[i] = O;
				else
				  root -> a[i] = X;
			}
			else
			  root -> a[i] = i + 1;
		}
		
		//create tree
		for(short i = 1; i < 9; i++)	//8 nodes to root node
		{
			createFullTree(root); 
		}
		
		fileDataSize = 0;
		if(level == 2)	//Open file
		{
			fileName = to_string(playerNumber) + ".txt";
			file.open(fileName, ios::in );
			if(file)
			{
				string waste;
				while(!file.eof()) 	//find no of lines in file
				{
				    getline(file, waste);
				    fileDataSize++;
				}
				fileData = new string[fileDataSize];
				long dummy = 0;
				file.clear();  //clear pointer flags
            			file.seekg (0, ios::beg);  //rewind to starting position
				while(!file.eof()) 	//dublicate each line as array
				{
				    getline(file, fileData[dummy++]);
				}
				fileDataSize--;	//get exact size
			}
			file.close();
		}
		
		display(root, 0);
		
		//game
		tree *workingNode = root;	//reference node
		
		flag1 = true;
		string past {};
		
		while(1) 
		{
			if(flag1) //computer turn
			{
				cout << "Computer Turn:" << endl;
				short c = 0, loc = 0;
				
				short arr[9];
				for(short i = 0; i < 9; i++)
				{
					arr[i] = workingNode -> a[i];
				}
				
				if(level == 2 || level == 1)	//ML, hard level
				{
					//win if two computer characters are near
					for(short k = 0; k < 8; k++)	//winnerLoactions[8][3]
					{
						c = 0;
						for(short j = 0; j < 3; j++)	//winnerLoactions[8][3]
						{
							short t = workingNode -> a[ winnerLoactions[k][j] ]; 	
							if(playerCharacter == 'O')
							{
								if(t == 0)
								  --c;
							}
							else
							{
								if(t == 10)
								  --c;
							}
							
							if(computerCharacter == 'O')
							{
								if(t == 0)
								  ++c;
							}
							else
							{
								if(t == 10)
								  ++c;
							}
							
							if(t > 0 && t < 10)
							  loc = t;

						}
						if(c == 2)
						  break;
					}
					if(c == 2)
					{
						if(computerCharacter == 'O')
						  arr[loc-1] = O;
						else
						  arr[loc-1] = X;
						
						for(short i = 0; i < 9; i++)
						{
							workingNode -> a[i] = arr[i];
						}
						display(workingNode, 1);
						cout << "Computer Won!" << endl;
						break; 
					}
				}
				if(level == 2 || level == 1 || level == 0)	//ML / hard level / moderate
				{
					//defend if player two characters are near to winning	
					for(short k = 0; k < 8; k++)	//winnerLoactions[8][3]
					{
						c = 0;
						for(short j = 0; j < 3; j++)	//winnerLoactions[8][3]
						{
							short t = workingNode -> a[ winnerLoactions[k][j] ]; 	
							if(playerCharacter == 'O')
							{
								if(t == 0)
								  ++c;
							}
							else
							{
								if(t == 10)
								  ++c;
							}
							
							if(computerCharacter == 'O')
							{
								if(t == 0)
								  --c;
							}
							else
							{
								if(t == 10)
								  --c;
							}
							
							if(t > 0 && t < 10)
							  loc = t;

						}
						if(c == 2)
						  break;
					}
				}
				if(c == 2)
				{
					if(computerCharacter == 'O')
					  arr[loc-1] = O;
					else
					  arr[loc-1] = X;
					  
					short count;
					for(short i = 0; i < 8; i++)
					{
						if(workingNode->p[i] != nullptr)
						{
							count = 0;
							for(short j = 0; j < 9; j++)
							{
								if( (workingNode->p[i])->a[j] == arr[j] )
								{
									count++;
								}
							}
							if(count == 9)
							{
								workingNode = workingNode -> p[i];
								past += to_string(i);
								break;
							}
						}
					}
				}
				else
				{	
					//BASED ON "COST OF NODE"
					short cost = 0, number = 0, negativeCost = -9999, negativeNumber = 0 ;
					short i;
					bool countFlag = false;
					for( i = 0; i < 8; i++)
					{
						if(workingNode->p[i] != nullptr)
						{
							//MACHINE LEARNING FROM PAST EXPERIENCE
							if(level == 2)
							{
								if(past.length() == 0)  //second level(after root)
								{
									for(long j = 0; j < fileDataSize; j++)
									{
										if( fileData[j].substr(0,1) == to_string(i) )
										  (workingNode -> p[i]) -> points -= 99; 
									}
								}
								else	//third - else level
								{
									for(long j = 0; j < fileDataSize; j++)
									{
										if( fileData[j].substr(0,past.length()+1) == (past + to_string(i)) )
										  (workingNode -> p[i]) -> points -= 99; 
									}
								}
							}
							
							if(cost <= ((workingNode->p[i])->points))
							{
								cost = (workingNode->p[i])->points;
								number = i;
								countFlag = true;
							}
							if( ((workingNode->p[i])->points) < 0 && ((workingNode->p[i])->points) > negativeCost )
							{
								negativeCost = (workingNode->p[i])->points;
								negativeNumber = i;
							}
						}
						else
						 break;
					}
					if(!countFlag)  //if all points are negative
					  number = negativeNumber;
					  
					workingNode = workingNode -> p[number];
					past += to_string(number); 
				}
				
				display(workingNode, 1);
				
				//check win or lose	
				for(short k = 0; k < 8; k++)	//winnerLoactions[8][3]
				{
					c = 0;
					for(short j = 0; j < 3; j++)	//winnerLoactions[8][3]
					{
						short t = workingNode -> a[ winnerLoactions[k][j] ]; 	
						if(computerCharacter == 'O')
						{
							if(t == 0)
							  ++c;
						}
						else
						{
							if(t == 10)
							  ++c;
						}
					}
					if(c == 3)
					{
						cout << "Computer Won!" << endl;
						break;
					}
				}
				if(c == 3)
				  break;
				
				if(workingNode->p[0] == nullptr)
				{
					cout << "Game Draw!" << endl;
					break;
				}
				
				flag1 = !flag1;
			}
			else //player turn
			{
				cout << "Your Turn: ";
				cin >> playerNumber;
				
				short arr[9];
				for(short i = 0; i < 9; i++)
				{
					arr[i] = workingNode -> a[i];
				}
				
				while(1)	
				{
					if(playerNumber < 1 && playerNumber > 9)
					{
						cout << "Invalid Number\nTry Again: ";
						if (cin.fail()) //clear cin is string is give as input
						{
			    				cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
						cin >> playerNumber;
					}
					else
					{
						if( arr[playerNumber-1] != O && arr[playerNumber-1] != X )
						  break;
						else
						{
							cout << "Invalid Number\nTry Again: ";
							if (cin.fail()) //clear cin is string is give as input
							{
				    				cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							cin >> playerNumber;
						}  
					}
				}
				
				if(playerCharacter == 'O')
				  arr[playerNumber-1] = O;
				else 
				  arr[playerNumber-1] = X;
				
				short i, count = 0;
				for( i = 0; i < 8; i++)
				{
					if(workingNode->p[i] != nullptr)
					{
						count = 0;
						for(short j = 0; j < 9; j++)
						{
							if( (workingNode->p[i])->a[j] == arr[j] )
							{
								count++;
							}
						}
						if(count == 9)
						{
							workingNode = workingNode -> p[i];
							past += to_string(i);
							break;
						}
					}
				}
				
				display(workingNode, 0);
				
				//check win or lose
				short c;	
				for(short k = 0; k < 8; k++)	//winnerLoactions[8][3]
				{
					c = 0;
					for(short j = 0; j < 3; j++)	//winnerLoactions[8][3]
					{
						short t = workingNode -> a[ winnerLoactions[k][j] ]; 	
						if(playerCharacter == 'O')
						{
							if(t == 0)
							  ++c;
						}
						else
						{
							if(t == 10)
							  ++c;
						}
					}
					if(c == 3)
					{
						if(level == 2)	//save pointer path's to file.
						{
							file.open(fileName, ios::out | ios::app ); //if file is past append or create.
							if(file) 
							  file << past << "\n";
							file.close();
						}
						cout << playerName << " Won!" << endl;
						break;
					}
				}
				if(c == 3)
				  break;
				
				if(workingNode->p[0] == nullptr)
				{
					cout << "Game Draw!" << endl;
					break;
				}
				
				flag1 = !flag1;
			}
		}
	}	
	
	tree *ref;	//back track reference
	void createFullTree(tree *t)
	{
		tree *temp = new tree;
		short noRepeat;
		for(short i = 0; i < 8; i++)	//check available pointers in previous node
		{
			if(t->p[i] == nullptr)
			{
				t -> p[i] = temp;
				noRepeat = i;
				break;
			}
		}
		flag = !flag;
		for(short i = 0; i < 9; i++)	//dublicate previous array
		{
			temp -> a[i] = t -> a[i];
		}
		for(short i = 0; i < 9; i++)	//replace number with X or O
		{
			if(temp -> a[i] != O && temp -> a[i] != X && noRepeat-- == 0)
			{
				if(flag)	//true -> computer
				{
					if(computerCharacter == 'O')
					  temp -> a[i] = O;
					else
					  temp -> a[i] = X;
				}
				else		//false -> player
				{	
				  	if(playerCharacter == 'O')
					  temp -> a[i] = O;
					else
					  temp -> a[i] = X;
				}
				break;
			}
		}
		//check win or lose
		for(short i = 0; i < 8; i++)	//winnerLoactions[8][3]
		{
			short c = 0;	//count matching (+3 win, -3 lose)
			for(short j = 0; j < 3; j++)	//winnerLoactions[8][3]
			{
				short t = temp -> a[ winnerLoactions[i][j] ]; 	
				if(computerCharacter == 'O')
				{
					if(t == 0)
					  ++c;
				}
				else if(computerCharacter == 'X')
				{
					if(t == 10)
					  ++c;
				}
				if(playerCharacter == 'O')
				{
					if(t == 0)
					  --c;
				}
				else if(playerCharacter == 'X')
				{
					if(t == 10)
					  --c;
				}
			}
			if(c == 3)	//computer win
			{
				ref = temp;
				temp -> points += 1;
				flag = !flag;
				return;
			}
			if(c == -3)	//computer lose
			{
				ref = temp;
				temp -> points -= 1; 
				flag = !flag;
				return;
			}
		}
		//check if end of line for leaf nodes
		short s = 0;
		for(short i = 0; i < 9; i++)
		{
			if(temp -> a[i] != O && temp -> a[i] != X)
			  s++;
		}
		if(s == 0)	//if last node
		{
			ref = temp;
			flag = !flag;
			return;
		}

		for(short i = 0; i < 9; i++)
		{
			if(temp -> a[i] != O && temp -> a[i] != X)
			{
				createFullTree(temp);
				temp -> points += ref -> points;
			}
		}
		flag = !flag;
	}
	
	//DISPLAY NODE
	void display(tree *t , short space)
	{
		char s[9];
		for(short i=0;i<9;i++)
		{
			if(t-> a[i] == 10)
			  s[i] = 'X';
			else if(t-> a[i] == 0)
			  s[i] = 'O';
			else
			  s[i] = (t-> a[i]) + 48;	//ascii of 1 is 49
		}
		if(space)
		cout << "\n " << s[0] <<" | "<< s[1] <<" | "<< s[2]<<"\n ---------\n "<<s[3]<<" | "<< s[4] <<" | "<<s[5]<<"\n ---------\n "<<s[6]<<" | "<<s[7]<<" | "<<s[8]<<"\n\n";
		else
		cout << "\n" << s[0] <<" | "<< s[1] <<" | "<< s[2]<<"\n---------\n"<<s[3]<<" | "<< s[4] <<" | "<<s[5]<<"\n---------\n"<<s[6]<<" | "<<s[7]<<" | "<<s[8]<<"\n\n";
	}

	//DEALLOCATE TREE
	void deleteFullTree(tree *t)
	{
    		for(short i = 0; i < 8; i++)
    		{
     		 	if(t->p[i] != nullptr)
        			{
            				deleteFullTree(t->p[i]);
			               delete(t->p[i]);
        			}
    		}
	}
	~TreeOperations ()
	{
		deleteFullTree(root);
		delete(root);
	}
};


int main(void)
{
	//PLAYER NAME
	cout << "Enter your name : ";	
	cin >> playerName;
	cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << "\nWelcome to Tic-Tac-Toe " << playerName << "!" << endl;	
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		
	//PLAYABLE CHARACTER
	cout << "\nSelect a playable character, O or X : ";		
	cin >> playerCharacter; 
	while(1)
	{
		if (playerCharacter == 'x' || playerCharacter == 'X')
		{
			playerCharacter = 'X';
			computerCharacter = 'O';
			break;
		}
		else if (playerCharacter == 'o' || playerCharacter == 'O' || playerCharacter == '0')
		{
			playerCharacter = 'O';
			computerCharacter = 'X';
			break;
		}
		else
		{
			cout << "Invalid character\nEnter O or X : " ;
			if (cin.fail()) //clear cin is string is give as input
			{
	    			cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cin >> playerCharacter;
		}
	}
	
	//LEVEL (easy/moderate/hard/ML)
	cout << "\nGame Play -\n1->Easy\n2->Moderate\n3->Hard\n4->Machine Learning\nOption : ";
	cin >> level;
	while(1)
	{
		if(level == 1)
		{
			level = -1;
			break;
		}
		else if(level == 2)
		{
			level = 0;
		  	break;	
		}  
		else if(level == 3)
		{
			level = 1;
			break;
		}
		else if(level == 4)
		{
			level = 2;
			break;
		}  
		else
		{
			cout<<"Enter valid option [1-4] : ";
			if (cin.fail()) //clear cin is string is give as input
			{
	    			cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cin >> level;
		}
	}
	
	//ask to repeat game and launch
	char ch;
	do
	{
		//DESCRIPTION OR HELP
		cout<<"\n+-------------------------------------+";
		cout <<"\nEnter preferred number as your choice.\n" <<"\n" <<"1 | 2 | 3\n---------\n4 | 5 | 6\n---------\n7 | 8 | 9\n";
		cout<<"+-------------------------------------+"<<endl;
	
		//First move by player
		cout << "\nYour Turn: ";
		cin >> playerNumber;

		while(1)
		{
			if(playerNumber > 0 && playerNumber < 10)
		  	{	
		  		new TreeOperations();
		  		break;
		  	}
			else
			{
				cout << "Invalid Number\nTry Again: ";
				if (cin.fail()) //clear cin is string is give as input
				{
	    				cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cin >> playerNumber;
			}
		}

		cout << "\nPlay again (y/n): ";
		cin >> ch;
	} while(ch == 'y' || ch == 'Y');
	
	cout << "\nSee you soon!" << endl;
	
	return 0;
}
