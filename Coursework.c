#include<stdio.h>
#include<string.h>
#include<stdlib.h>  //importing libraries

#define ROWS 3
#define COLUMNS 3
#define LENGTH 5 //macros used

char c; // represents the nout or cross that will be placed into the cells


void createPlayBoard(char array[ROWS][COLUMNS]) //method creates the standard playboard
{
	printf("\n");
	printf("|	%c	|	%c	|	%c	| \n",array[0][0],array[0][1],array[0][2]);
	printf("-----------------------------------------------------------\n");
	printf("|	%c	|	%c	|	%c	| \n",array[1][0],array[1][1],array[1][2]);
	printf("-----------------------------------------------------------\n");
	printf("|	%c	|	%c	|	%c	| \n\n\n",array[2][0],array[2][1],array[2][2]);
	printf("-----------------------------------------------------------\n"); // making the board and allocating cells for each move.
}

int winnerCheck(char array[ROWS][COLUMNS], int* winner) //logic for checking if there is a winner or not
{
	if(((array[0][0] == array[0][1]) && (array[0][1] == array[0][2]) && array[0][0] != ' ') || ((array[1][0]) == array[1][1]) && (array[1][1] == array[1][2] && array[1][0] != ' ') 
	|| ((array[2][0] == array[2][1]) && (array[2][1] == array[2][2]) && array[2][0] != ' ') || ((array[0][0] == array[1][0]) && (array[1][0]== array[2][0]) && array[0][0] != ' ') 
	|| ((array[0][1] == array[1][1]) && (array[1][1] == array[2][1]) && array[0][1] != ' ') || ((array[0][2] == array[1][2]) && (array[1][2]== array[2][2]) && array[0][2] != ' ') 
	|| ((array[0][0] == array[1][1]) && (array[1][1] == array[2][2]) && array[0][0] != ' ') || ((array[0][2] == array[1][1]) && (array[1][1]== array[2][0])) && array[0][2] != ' ')
	{//checks if the cells are 'matching'
		*winner = 1;
		return 1; //returns 1 if a winner is found
	}
	else
	{
		return 0;
	}
}


void changePlayer(int* value) //changes which player is currently playing
{
	if(*value ==1) //pointer values to change the current player 
	{
		*value = 2;
	}
	else
	{
		*value = 1;
	}
}

int menu() //menu and choice 
{
	int choice;
	printf("\nNew Game = 1.\n");
	printf("\nReplays = 2.\n");
	printf("\nExit = 3.\n");
	printf("\nEnter your choice\n"); //menu
	do
	{
		scanf("%d", &choice); //collects the choice 
		getchar();
	}while(choice > 3 && printf("Please enter a valid choice: \n"));
	
	return choice;
}

void clrscr() //clears screen
{
    system("@cls||clear");
}

void undo(char array[ROWS][COLUMNS], int x, int* player, int* turns) //undo last move
{
	clrscr(); //clears screen 
	array[x/ROWS][x%ROWS] = ' '; //makes the cell you want to undo clea
	createPlayBoard(array); //updates board to reflect change
	changePlayer(player);
	*turns -= 1; //reverts turn number 
}

int addMove(char array[ROWS][COLUMNS], int value, int player)// logic for selecting a valid cell
{
	if(player == 1) // Player 1 is always the X
	{
		if(array[value/ROWS][value%ROWS] == ' ')
		{
			clrscr();
			array[value/ROWS][value%ROWS] = 'X';// adds X to the selected cell
			return 1;
		}
		else
		{
			printf("\nThis cell has been taken, please enter another number: \n");
			return 0; //if the cell is taken it will loop until a valid one is chosen
		}
		
	}
	else if(player == 2)// Player 2 is always the O
	{
		if(array[value/ROWS][value%ROWS] == ' ')
		{
			clrscr();
			array[value/ROWS][value%ROWS] = 'O';// adds O to the selected cell
			return 1;
		}
		else
		{
			printf("\nThis cell has been taken, please enter another number: \n");
			return 0; //if the cell is taken it will loop until a valid one is chosen
		}
	}
	return 1;
}

	
void Game(char array[ROWS][COLUMNS],int replayArray[10][10],int numberOfReplays) //gmae logic 
{
	int Movement[COLUMNS*ROWS+1]; // to store movement 
	int i = 0,redo = 0;
	for(i = 0;i<=COLUMNS*ROWS;i++)
	{
		Movement[i] = -1; 
	}
	int redoMovement[COLUMNS*ROWS];
	char string[LENGTH];
	int turnCounter = 0,player = 1,win = 0;
	do
	{
		if(turnCounter >= 5) //checking for wins is only possible after the 5th move
		{
			if(winnerCheck(array,&win) || (turnCounter == COLUMNS*ROWS)) // if win criteria is met 
			{
				changePlayer(&player);
				if(win)
				{
					printf("Player %d wins \n\n",player);
					Movement[COLUMNS*ROWS] = player;
				}
				else
				{
					printf("Game is draw \n"); //if no win combination is found its a draw
					Movement[COLUMNS*ROWS] = -1;
				}				
				printf("To return to main menu enter - m \n To undo last move - u \n\n");
				char c;
				scanf("%c", &c); //reads the character option u, r or m 
				getchar();
				if(c == 'm')
				{
					for(i = 0;i <= COLUMNS*ROWS;i++)
					{
						replayArray[numberOfReplays-1][i] = Movement[i]; // store the moves of the most recent game to the replay array 
					}
					break;
				}
				else if(c == 'u') //if its undo, undo the last move 
				{
					win = 0;
					changePlayer(&player);
					undo(array,Movement[turnCounter-1],&player,&turnCounter);
				}
				else
				{
					for(i = 0;i <= COLUMNS*ROWS;i++)
					{
						replayArray[numberOfReplays-1][i] = Movement[i];
					}
					break;
					printf("Returning to main menu\n\n");
					break; //defaults to return to the movement 
				}
			}
		}
		printf("Player %d your choice:  \n\n",player); //if there is no win check it just asks what play you want to make 
		fgets(string, LENGTH, stdin);
		string[LENGTH-1] = '\0'; //end of string is a null finisher/blank char
		if((string[0] == 'r'))//if its redo
		{
			if(Movement[turnCounter] != -1)//redo move 
			{
				redo = 1;
				addMove(array,Movement[turnCounter],player);
				changePlayer(&player);
				turnCounter++;
				createPlayBoard(array);

			}
			else
			{
				printf("There are no more moves\n"); //if you cant redo a move 
			}
			
		}
		else if(string[0] == 'u')
		{
			if(turnCounter != 0)
			{
				undo(array,Movement[turnCounter-1],&player,&turnCounter); //undo last move using the turn counter to find what move was made at that index 
			}
			else 
			{
				printf("Cant undo on first turn \n");
			}	

		}
		else if((string[2] == '\0') && ((string[0] >= '1') && (string[0] <= '9'))) // if string pos3 is a char teminator and between 1-9 chars in the array do...
		{
			int choiceNumber = string[0]-0x30; //without this, each cell comes up as being taken by default.
			if (addMove(array,choiceNumber-1,player))
			{
				if(redo)
				{
					clearRedo(Movement,turnCounter);
					redo = 0;
				}
				Movement[turnCounter] = choiceNumber-1;
				turnCounter++;
				createPlayBoard(array);
			    changePlayer(&player);
			}
		}
		else
		{
			printf("Enter valid choice \n");
		}
		
	} while (turnCounter <= COLUMNS*ROWS);
	
}	
	

void clearRedo(int array[COLUMNS*ROWS], int index)// redo method . Columns*rows  creates the array eg 0,1 , 1,1 , 2,1
{
	clrscr();
	int i;
	for(int i =index; i < COLUMNS*ROWS; i++)
	{
		array[i] = -1;
	}
}

void Replays(int array[][COLUMNS*ROWS+1],int replayNums)// ability to watch replays
{
	int x=0, y=0, player =1;
	printf("You have played %d games", replayNums); //shows the number of games played
	while(x < replayNums)
	{
		char replayGame[COLUMNS][ROWS] = {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}}; // clears the array at the start of each game 
		printf("Game %d \n",x+1);
		
		while((array[x][y] != -1) ||  y == ((COLUMNS*ROWS)-1)) //while not at the end of the array
		{
			printf("Player %d played %d\n", player, array[x][y]+1); // adds to the winning combination array to check for winners  
			addMove(replayGame, array[x][y], player); //adds the move 
			createPlayBoard(replayGame);
			changePlayer(&player); //changes the player 
			y++; //updates y 
		}
		y=0;
		x++;
		if(array[x][COLUMNS*ROWS] !=-1)
		{
			printf("Player %d won\n",array[x][COLUMNS*ROWS]); //if theres a match whichever player made the winning move is the winner 
		}
		else
		{
			printf("Draw!\n");
		}
	}
}



int main()
{
	int player = 0, turns = 0, gameStarted =0, replays = 0;
	int replayArrays[COLUMNS*ROWS][10];
	while(1)//while true 
	{
		if(gameStarted)
		{
			replays++;
			char currentGame[COLUMNS][ROWS] = {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}};
			Game(currentGame, replayArrays, replays);
			gameStarted=0;
		}
		else
		{
			int choice = menu();
			if(choice == 1)
			{
				gameStarted=1;
			}
			else if(choice == 2)
			{
				Replays(replayArrays, replays);
			}
			else
			{
				break;
			}
		}
	}
	return 0;
}




