/*by Yawo Alphonse Siatitse
University of Rochester '20
*/



#include <stdio.h> //Standard Library
#include <stdlib.h>
#include <math.h>
//board Size Constant
#define BOARD_SIZE 	8

//board Space Constants
#define EMPTY_SPACE 0
#define P1_SPACE 	1
#define P2_SPACE 	2

//Player Constants
#define PLAYER1 	1
#define PLAYER2 	2

// function prototypes:
void printboard(int board[][BOARD_SIZE]);
int validateInput();
int playMove(int x, int y, int PLAYER, int board[][BOARD_SIZE]);
int gameOverPlayMove(int x, int y, int PLAYER, int board[][BOARD_SIZE]);
int gameOver(int board[BOARD_SIZE][BOARD_SIZE]);
int score (int player, int board[][BOARD_SIZE]);

int main(void){
	setbuf(stdout, NULL);

	//char arrays to hold the names
	char Player1fname[20];
	char Player1Lname[20];
	char Player2fname[20];
	char Player2Lname[20];
	int board[BOARD_SIZE][BOARD_SIZE];  //Game board Variable
	float score1, score2;   //score variable.
	int playTurn = PLAYER1;  // variable keeping track of the player that has the turn
	int x, y, point=0;

	//filling the board
	for(int i=0; i<=BOARD_SIZE; i++){
		for(int j=0; j<BOARD_SIZE; j++){
			board[i][j]= EMPTY_SPACE;
		}
	}
	board[4][4]= board[3][3]= P1_SPACE; //initializing the board
	board[4][3]= board[3][4]= P2_SPACE;

	//getting users' inputs to initialize the variable declared
	printf( "Welcome to OtHello!\n\n");
	printf("Enter Player 1’s First Name: ");
	scanf("%s", Player1fname);
	while(getchar()!='\n'){}
	printf("Enter Player 1’s Last Name: ");
	scanf("%s", Player1Lname);
	while(getchar()!='\n'){}
	printf("Enter Player 2’s First Name: ");
	scanf("%s", Player2fname);
	while(getchar()!='\n'){}
	printf("Enter Player 2’s Last Name: ");
	scanf("%s", Player2Lname);
	while(getchar()!='\n'){}

	//printing the board
	printboard(board);

	int turn =1;

    do{
    	score1 = score(PLAYER1, board);
    	score2 = score(PLAYER2, board);

		// Printing Players' fullnames and scores
		printf("\n%s %s's Score (B): %.1f\n", Player1fname, Player1Lname, score1);
		printf("%s %s's Score (W): %.1f\n\n", Player2fname, Player2Lname, score2);

		// This part determine who's turns it is based on the sign on the variable "turn"
		if (turn > 0){
			//Player1 move tracker
			playTurn = PLAYER1;
			printf("%s %s, it is your turn.", Player1fname, Player1Lname);
		}
		else{
			//Player2 move tracker
			playTurn = PLAYER2;
			printf("%s %s, it is your turn.", Player2fname, Player2Lname);
		}

		turn = -1*turn;

    	//Getting Player Input

        printf("\n");
        printf("Enter X coordinate: ");
        x = validateInput();
        printf("Enter Y coordinate: ");
        y = validateInput();
        point = playMove(x, y, playTurn, board);	// Place Move on board
        printf("\nPoints Gained: %d\n\n", point);
        printboard(board); // function call
    }while(!gameOver(board)); //Loop while the game is not over

    //After game over this part will run
    printf("\nGame Over!\n\n");
    printf("Final Score:\n");

	score1 = score(PLAYER1, board);
	score2 = score(PLAYER2, board);
	printf("%s %s's Score(B): %.1f\n", Player1fname, Player1Lname, score1);
	printf("%s %s's Score (W): %.1f\n\n", Player2fname, Player2Lname, score2);
	printf("%s %s Wins!!!", score1 > score2? Player1fname:Player2fname, score1 > score2? Player1Lname:Player2Lname );

    return 0;
}

//printing board with current coordinates
void printboard(int board[BOARD_SIZE][BOARD_SIZE]){


	printf(" ");
	for(int i=1; i<=BOARD_SIZE; i++)
		printf(" %d",i);
	printf("\n");
	for(int i=1; i<=BOARD_SIZE; i++){
		printf("%d ",i);
			for (int j=0; j < BOARD_SIZE; j++){
				if(board[i-1][j]==1) printf("%c ",'B');
				else if ( board[i-1][j]==2) printf("%c ",'W');
				else printf("%c ",'.');
			}
			printf("\n");
	}
}

//this function modify the board based Players moves

int playMove(int x, int y, int PLAYER, int board[][BOARD_SIZE]){
	int point=0;//points gained for single move
	int i;

    if (board[y][x] == EMPTY_SPACE){
    	//Horiz <----
    	i=1;
    	while((board[y][x-i] != EMPTY_SPACE)&&(board[y][x-1] != PLAYER)&&(x-i >= 0)){
    		if (board[y][x-i] == PLAYER){
    			point+=i-1;
    			for(int j=i; j>=0; j--){
    				board[y][x-j]=PLAYER;
    			}
    			break;
    		}
    		else{i++;}
    	}
    	//Horiz ---->
    	i=1;
    	while((board[y][x+i] != EMPTY_SPACE)&&(board[y][x+1] != PLAYER)&&(x+i < 8)){
    		if (board[y][x+i] == PLAYER){
    			point+=i-1;
    			for(int j=i; j>=0; j--){
    				board[y][x+j]=PLAYER;
    			}
    			break;
    		}
    		else{i++;}
    	}
    	//Diagonal Left-Up
    	i=1;
    	while((board[y-i][x-i] != EMPTY_SPACE)&&(board[y-1][x-1] != PLAYER)&&(y-i >= 0 && x-i >= 0)){
    		if (board[y-i][x-i] == PLAYER){
    			point+=i-1;
    			for(int j=i; j>=0; j--){
    				board[y-j][x-j]=PLAYER;
    			}
    			break;
      		}
    		else{i++;}
    	}
    	// Diagonal Right-Up
    	i=1;
    	while((board[y-i][x+i] != EMPTY_SPACE)&&(board[y-1][x+1] != PLAYER)&&(y-i >= 0 && x+i < 8)){
    		if (board[y-i][x+i] == PLAYER){
    			point+=i-1;
    			for(int j=i; j>=0; j--){
    				board[y-j][x+j]=PLAYER;
    			}
    			break;
    		}
    		else{i++;}
    	}

    	//Diagonal Right-Down
    	i=1;
    	while((board[y+i][x+i] != EMPTY_SPACE)&&(board[y+1][x+1] != PLAYER)&&(y+i < 8 && x+i < 8)){
    		if (board[y+i][x+i] == PLAYER){
    			point+=i-1;
    			for(int j=i; j>=0; j--){
    				board[y+j][x+j]=PLAYER;
    			}
    			break;
    		}
    		else{i++;}
    	}
    	//Diagonal Left-Down
    	i=1;
    	while((board[y+i][x-i] != EMPTY_SPACE)&&(board[y+1][x-1] != PLAYER)&&(y+i < 8 && x-i >= 0)){
    		if (board[y+i][x-i] == PLAYER){
    			point+=i-1;
    			for(int j=i; j>=0; j--){
    				board[y+j][x-j]=PLAYER;
    			}
    			break;
      		}
    		else{i++;}
    	}
    	//Vertical Down
    	while((board[y+i][x] != EMPTY_SPACE)&&(board[y+1][x] != PLAYER)&&(y+i < 8)){
    		if (board[y+i][x] == PLAYER){
    			point+=i-1;
    			for(int j=i; j>=0; j--){
    				board[y+j][x]=PLAYER;
    			}
    			break;
    		}
    		else{i++;}
    	}
    	//Vertical Up
    	i=1;
    	while((board[y-i][x] != EMPTY_SPACE)&&(board[y-1][x] != PLAYER)&&(y-i >= 0)){
    		if (board[y-i][x] == PLAYER){
   				point+=i-1;
    			for(int j=i; j>=0; j--){
    				board[y-j][x]=PLAYER;
    			}
    			break;
      		}
    		else{i++;}
    	}
    }

    else return 0;

    return point==0 ? point : point+1;
}


//this function check whether there is a possible move that can gain point for any player
int gameOver(int board[BOARD_SIZE][BOARD_SIZE]){
	int i, j;
	for (i=0; i<BOARD_SIZE; i++){
		for (j=0; j<BOARD_SIZE; j++){
			if(board[i][j]== EMPTY_SPACE){
				if ((gameOverPlayMove(j, i, PLAYER1, board)>0) ||(gameOverPlayMove(j, i, PLAYER1, board)>0)){
					return 0;
				}

			}
		}
	}
    return 1;
}

//this function validate the coordinates entered by the users
int validateInput(){
	int input;
	int flag=0;
	while(!(flag=scanf("%d", &input)) || (input < 1)||(input> BOARD_SIZE)){
		while(getchar()!='\n'){}
		printf("Invalid Input. Enter again: ");
	}
	while(getchar()!='\n'){}
	return input-1;
}

//this function update the score board
int score (int PLAYER, int board[][BOARD_SIZE]) {
  int i, cnt;
  cnt=0;
  for (i=0; i<BOARD_SIZE; i++){
	  for (int j=0; j<BOARD_SIZE; j++ ){
		  if (board[i][j] == PLAYER) cnt++;
	  	  }
	  }
  return cnt;
}

// this functions help the gameOver() function to check for the outcome of a move on an empty space
int gameOverPlayMove(int x, int y, int PLAYER, int board[][BOARD_SIZE]){
	int point=0;
	int i;

    if (board[y][x] == EMPTY_SPACE){
    	//Horiz <----
    	i=1;
    	while((board[y][x-i] != EMPTY_SPACE)&&(board[y][x-1] != PLAYER)&&(x-i >= 0)){
    		if (board[y][x-i] == PLAYER){
    			point+=i-1;
    			break;
    		}
    		else{i++;}
    	}
    	//Horiz ---->
    	i=1;
    	while((board[y][x+i] != EMPTY_SPACE)&&(board[y][x+1] != PLAYER)&&(x+i < 8)){
    		if (board[y][x+i] == PLAYER){
    			point+=i-1;
    			break;
    		}
    		else{i++;}
    	}
    	//Diagonal Left-Up
    	i=1;
    	while((board[y-i][x-i] != EMPTY_SPACE)&&(board[y-1][x-1] != PLAYER)&&(y-i >= 0 && x-i >= 0)){
    		if (board[y-i][x-i] == PLAYER){
    			point+=i-1;
    			break;
      		}
    		else{i++;}
    	}
    	// Diagonal Right-Up
    	i=1;
    	while((board[y-i][x+i] != EMPTY_SPACE)&&(board[y-1][x+1] != PLAYER)&&(y-i >= 0 && x+i < 8)){
    		if (board[y-i][x+i] == PLAYER){
    			point+=i-1;
    			break;
    		}
    		else{i++;}
    	}

    	//Diagonal Right-Down
    	i=1;
    	while((board[y+i][x+i] != EMPTY_SPACE)&&(board[y+1][x+1] != PLAYER)&&(y+i < 8 && x+i < 8)){
    		if (board[y+i][x+i] == PLAYER){
    			point+=i-1;
    			break;
    		}
    		else{i++;}
    	}
    	//Diagonal Left-Down
    	i=1;
    	while((board[y+i][x-i] != EMPTY_SPACE)&&(board[y+1][x-1] != PLAYER)&&(y+i < 8 && x-i >= 0)){
    		if (board[y+i][x-i] == PLAYER){
    			point+=i-1;
    			break;
      		}
    		else{i++;}
    	}
    	//Vertical Down
    	while((board[y+i][x] != EMPTY_SPACE)&&(board[y+1][x] != PLAYER)&&(y+i < 8)){
    		if (board[y+i][x] == PLAYER){
    			point+=i-1;
    			break;
    		}
    		else{i++;}
    	}
    	//Vertical Up
    	i=1;
    	while((board[y-i][x] != EMPTY_SPACE)&&(board[y-1][x] != PLAYER)&&(y-i >= 0)){
    		if (board[y-i][x] == PLAYER){
   				point+=i-1;
    			break;
      		}
    		else{i++;}
    	}
    }

    else return 0;

    return point==0 ? point : point+1;
}


