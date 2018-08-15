#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the maximum of the border
#define MAX_WIDTH 4
#define MAX_HEIGHT 2

// to record where the player at now
typedef struct Location {
    int x;
    int y;
} Location;

// function prototypes
void move(Location *, Location *);
void kick(Location *, Location *, int);
int checkKickable(Location, Location);
int checkScored(Location, Location, int);

// the entry point of the program
int main() {
	srand(time(NULL));	// reset the seed of rand function

	// init the player's location
	Location player1,player2;
	Location* attacker,* defender;
	Location ball = {2,1};	// init the ball's location
	char action = 'm';	// to decide what kind of action you take, move by default
	int ggFlag = 1;		// to check end of game state
	int turns = 0;		// stores which turns now on
	int theCoin = rand() % 2;	// to decide which player play first
	int playerNumber = theCoin % 2 + 1;	// to store which player plays now

	if (playerNumber == 1) {
		player1.x = 2;
		player1.y = 1;
		player2.x = 4;
		player2.y = 1;
	} else {
		player1.x = 0;
		player1.y = 1;
		player2.x = 2;
		player2.y = 1;
	}

	while(ggFlag) {
		if (theCoin % 2 == 0) {
			attacker = &player1;
			defender = &player2;
		} else {
			attacker = &player2;
			defender = &player1;
		}

		playerNumber = theCoin % 2 + 1;

		printf("\n*--------- TRUN %d (PLAYER%d)---------*\n", turns, playerNumber);
		printf("PLAYER1: (%d, %d)  PLAYER2: (%d, %d)  BALL: (%d, %d)\n", player1.x, player1.y,
		 player2.x, player2.y, ball.x, ball.y);

		do {
		printf("kick(k) or move(m)?\n");
		scanf(" %c", &action);
		} while (action != 'k' && action != 'm');

		while (action == 'k') {
			if (checkKickable(*attacker, ball)) break;

			printf("press 'm' to move\n");
			scanf(" %c", &action);
		}

		switch(action)
		{
			case 'm':
				move(attacker, &ball);
				break;
			case 'k':
				kick(attacker, &ball, playerNumber);
				ggFlag = checkScored(*defender, ball, playerNumber);
				break;
			default:
				move(attacker, &ball);
		}
		turns++;
		theCoin++;
		printf("*-----------------------------------*\n");
	}

	return 0;
}

// move the player and ball if its with you
void move(Location* player, Location* ball) {
	int newX, newY, disX, disY;		// for storing the new position, and the distance it moves
	disX = 0;
	disY = 0;
	printf("Enter the position you would like to move,format x,y:\n");

	while (scanf(" %d,%d", &newX, &newY) != 2) {
		printf("please enter the right format\n");
	}
	disX = abs(newX - (*player).x);
	disY = abs(newY - (*player).y);

	// check the point you move next you
	while (disX > 1 || disY > 1) {
		printf("you can only move to adjacent point,please enter again:\n");
		while (scanf(" %d,%d", &newX, &newY) != 2) {
			printf("please enter the right format\n");
		}
		printf("%d,%d\n", newX, newY);
		disX = abs(newX - (*player).x);
		disY = abs(newY - (*player).y);
	}

	// check whether you with ball or not
	if ((*player).x == (*ball).x && (*player).y == (*ball).y) {
		// move the ball with you
		(*ball).x = newX;
		(*ball).y = newY;
	}

	// move the player
	(*player).x = newX;
	(*player).y = newY;
	printf("you've moved to (%d,%d)\n", newX, newY);
}

// kick the ball to the ramdon position
void kick(Location* player, Location* ball, int playerNumber) {
	int randomX, randomY = 0;	// to store the new ball location
	int border = MAX_WIDTH;
	if (playerNumber == 2) border = 0;

	if ((*player).x == border) {
		printf("you are at the border\n");
		return;	// you are at the border,nothing to kick
	}

	int min = (*player).x;		// use player's x position as the minimum random value
	if (playerNumber == 1) randomX = (rand() % (MAX_WIDTH - min)) + min + 1;	// for store the random kick value of X
	else randomX = rand() % min;

	randomY = rand() % (MAX_HEIGHT + 1);	// for store the random kick value of Y
	(*ball).x = randomX;
	(*ball).y = randomY;

	printf("you've kicked the ball to (%d,%d)\n", randomX, randomY);
}

// check the ball's current position
// if match the Goal position then return 0 to end the game
// return 1 if missed or got blocked
int checkScored(Location defender, Location ball, int playerNumber) {
	if (defender.x == ball.x && defender.y == ball.y) {
		printf("defender blocked the ball\n");
		return 1;
	}

	int goalX, goalY;	// define the position of goal
	if (playerNumber == 1) {
		goalX = 4;
		goalY = 1;
	} else {
		goalX = 0;
		goalY = 1;
	}

	if (ball.x == goalX && ball.y == goalY) {
		printf("!------------player%d won the game------------!\n", playerNumber);
		return 0;
	}

	return 1;
}

// check whether you have ball or not
// return 1 if kickable, 0 for failed
int checkKickable(Location player, Location ball) {
	if (player.x != ball.x || player.y != ball.y) {
		printf("you've kicked the air\n");
		return 0;
	}

	return 1;
}