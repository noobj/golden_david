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
	Location player1 = {0,0};
	move(&player1);

	printf("FUCK YOU OUT (%d, %d)\n", player1.x, player1.y);
	return 0;
}

void move(Location* player) {
	(*player).y += 4;
}