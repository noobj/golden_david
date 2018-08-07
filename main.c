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
void kick(Location *, Location *);

int main() {
	Location player1 = {0,0};	// init the player's location
	Location ball = {0,0};	// init the ball's location
	char action = 'm';	// to decide what kind of action you take, move by default

	srand(time(NULL));	// reset the seed of rand function

	while(1) {
		printf("PLAYER1: (%d, %d)   BALL: (%d, %d)\n", player1.x, player1.y, ball.x, ball.y);
		printf("kick(k) or move(m)?\n");
		scanf(" %c", &action);

		switch(action)
		{
			case 'm':
				move(&player1, &ball);
				break;
			case 'k':
				kick(&player1, &ball);
				break;
			default:
				move(&player1, &ball);
		}
	}

	return 0;
}

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
	if ((*player).x == (*ball).x || (*player).y == (*ball).y) {
		(*ball).x = newX;
		(*ball).y = newY;
	}

	(*player).x = newX;
	(*player).y = newY;
	printf("you've moved to (%d,%d)\n", newX, newY);
}

void kick(Location* player, Location* ball) {
	// check whether you have ball or not
	if ((*player).x != (*ball).x || (*player).y != (*ball).y) {
		printf("you dont have the ball\n");
		return;
	}

	if ((*player).x == MAX_WIDTH) return;	// you are at the border,nothing to kick

	int min = (*player).x;		// use player's x position as the minimum random value
	int randomX = (rand() % (MAX_WIDTH - min)) + min + 1;	// for store the random kick value of X
	int randomY = rand() % (MAX_HEIGHT - 0 + 1);	// for store the random kick value of Y
	(*ball).x = randomX;
	(*ball).y = randomY;

	printf("you've kicked the ball to (%d,%d)\n", randomX, randomY);
}