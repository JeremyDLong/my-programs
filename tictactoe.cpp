
#include <stdio.h>
#include <iostream>
using namespace std;

char board[3][3];
char player;
int numTurns;

void setupGame(){
	player='X';
	numTurns=0;
	for (int row=0; row<3; row++){	
		for(int col=0;col<3; col++){
			board[row][col]=' ';
		}
	}
}

void drawScreen(){
	printf(" %c | %c | %c\n",
			board[0][0],
			board[0][1],
			board[0][2]
		);
	printf("-----------\n");

	printf(" %c | %c | %c\n",
			board[1][0],
			board[1][1],
			board[1][2]
		);
	printf("-----------\n");

	printf(" %c | %c | %c\n",
			board[2][0],
			board[2][1],
			board[2][2]
		);
}

bool updateState(){
	int r,c;
	bool inputIsInvalid=true;
	// Get players move and validate it.
	while (inputIsInvalid){
		printf("Player %c, Enter your coordinates:", player);
		cin >> r >> c;
		r--; c--;
		if(r<0 || r>=3) {printf("Invalid row.\n");}
		else if(c<0 || c>2)  {printf("Invalid column.\n");}
		else if(board[r][c] != ' '){printf("That square is already taken.\n");}
		else inputIsInvalid=false;
	}

	// Set the player's square.
	board[r][c]=player;

	// See if player has won.
	if(board[0][0]==player && board[0][1]==player && board[0][2]==player ){return true;}
	if(board[1][0]==player && board[1][1]==player && board[1][2]==player ){return true;}
	if(board[2][0]==player && board[2][1]==player && board[2][2]==player ){return true;}
	 
	if(board[0][0]==player && board[1][0]==player && board[2][0]==player ){return true;}
	if(board[0][1]==player && board[1][1]==player && board[2][1]==player ){return true;}
	if(board[0][2]==player && board[1][2]==player && board[2][2]==player ){return true;}

	if(board[0][0]==player && board[1][1]==player && board[2][2]==player ){return true;}
	if(board[2][0]==player && board[1][1]==player && board[0][2]==player ){return true;}

	numTurns++;

	if(numTurns==9){player=' '; return true;}

	// Switch player
	if(player=='X') player='O';
	else if(player=='O') player='X';
	return false;
}

void shutDown(){
	if(player==' '){printf("It was a tie.\n");}
	else {printf("Player %c won!\n",player);}
}

int main(int argc, char **argv){
	setupGame();
	drawScreen();
	bool done=false;
	while(! done){
		done=updateState();
		drawScreen();
	}
	shutDown();
	return 0;
}

