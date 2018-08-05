#include <stdio.h>

// Define the maximum of the border
#define MAX_WIDTH 4
#define MAX_HEIGHT 2

// to record where the player at now
typedef struct Location {
    int x;
    int y;
} Location;

// function prototypes
void move(Location *);


int main() {
	Location player1 = {0,0};	// init the player's location
	char action = 'm';	// to decide what kind of action you take, move by default
	while(1) {
		printf("PLAYER1: (%d, %d)\n", player1.x, player1.y);
		printf("kick(k) or move(m)?\n");
		scanf(" %c", &action);

		switch(action)
		{
			case 'm':
				move(&player1);
				break;
			case 'k':
				break;
			default:
				move(&player1);
		}
	}

	return 0;
}

void move(Location* player) {
	(*player).y += 4;
}