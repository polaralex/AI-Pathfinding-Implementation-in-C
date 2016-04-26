#include <stdio.h>
#include <stdlib.h>

typedef struct coordinates {
	int x;
	int y;
} position_xy;

typedef struct positionList {
	position_xy * position;
	struct positionList * previous;
	struct positionList * next;
} list;

// Constants for 'positionsAreValid':
int CENTER = 0;
int UP = 1;
int DOWN = 2;
int LEFT = 3;
int RIGHT = 4;

void checkNeighbors(list * current, int **map_visited);
void addToQueue(position_xy * input);
position_xy * new_position(int x, int y);
void printCurrentMap(int **map, int x, int y);
int positionsAreValid(list * current, int direction);
void printFrontierQueue(list * node);

list * queue_head;

// Map initialization:
int mapHeight = 5;
int mapWidth = 5;

int main() {

	// Current-run values:
	int userInputXstart = 3;
	int userInputYstart = 3;
	int xstart = userInputXstart-1;
	int ystart = userInputYstart-1;

	int i;
	int y;

	// 'Map-visited' memory allocation:
	int **map_visited;
	map_visited = (int **) malloc(mapHeight*sizeof(int *));

	for(i=0; i<mapWidth; i++){
		map_visited[i] = (int *) malloc(mapWidth*sizeof(int));
	}

	// Initialize "visited" array:
	for (i=0; i<mapHeight; i++) {
		for (y=0; y<mapWidth; y++) {
			map_visited[i][y]=0;
		}
	}

	// Beginning of the sequence:
	position_xy * start = new_position(xstart, ystart);
	map_visited[xstart][ystart] = 1;
	addToQueue(start);

	// The main loop of the Algorithm:
	while (queue_head != NULL){

		list * current = queue_head;

		if (queue_head->next != NULL) {
			queue_head = queue_head->next;
			queue_head->previous = NULL;
		} else {
			queue_head = NULL;
		}

		// Implementation of Neighbor Checking:
		checkNeighbors(current, map_visited);

		// Printing of the current state of the search:
		printCurrentMap(map_visited, mapWidth, mapHeight);
		if(queue_head != NULL){
			printFrontierQueue(queue_head);
		} else {
			printf("-> The Queue is EMPTY.\n\n");
		}
	}
}

void checkNeighbors(list * current, int **map_visited){

		if (positionsAreValid(current, RIGHT) == 1 && (map_visited[current->position->x][(current->position->y)+1] == 0)) {

			position_xy * nextPosition = new_position(current->position->x, (current->position->y)+1);
			addToQueue(nextPosition);
			map_visited[current->position->x][(current->position->y)+1] = 1;
		}

		if (positionsAreValid(current, LEFT) == 1 && (map_visited[current->position->x][(current->position->y)-1] == 0)) {

			position_xy * nextPosition = new_position(current->position->x, (current->position->y)-1);
			addToQueue(nextPosition);
			map_visited[current->position->x][(current->position->y)-1] = 1;
		}

		if (positionsAreValid(current, UP) == 1 && (map_visited[(current->position->x)-1][current->position->y] == 0)) {

			position_xy * nextPosition = new_position((current->position->x)-1, current->position->y);
			addToQueue(nextPosition);
			map_visited[(current->position->x)-1][current->position->y] = 1;
		}

		if (positionsAreValid(current, DOWN) == 1 && (map_visited[(current->position->x)+1][current->position->y] == 0)) {

			position_xy * nextPosition = new_position((current->position->x)+1, current->position->y);
			addToQueue(nextPosition);
			map_visited[(current->position->x)+1][current->position->y] = 1;
		}
}

int positionsAreValid(list * current, int direction) {

	int x, y;
	x = current->position->x;
	y = current->position->y;

	if (direction == CENTER) {

		if (x < mapHeight && y < mapWidth && (x>=0) && (y>=0)) {
			return(1);
		} else {
			return(0);
		}

	} else if (direction == UP) {

		if ( x-1 < mapHeight && y < mapWidth && (x-1>=0) && (y>=0)) {
			return(1);
		} else {
			return(0);
		}

	} else if (direction == DOWN) {

		if ( x+1 < mapHeight && y < mapWidth && (x+1>=0) && (y>=0)) {
			return(1);
		} else {
			return(0);
		}

	} else if (direction == LEFT) {

		if( x < mapHeight && y-1 < mapWidth && (x>=0) && (y-1>=0)) {
			return(1);
		} else {
			return(0);
		}

	} else if (direction == RIGHT) {

		if( x < mapHeight && y+1 < mapWidth && (x>=0) && (y+1>=0) ) {
			return(1);
		} else {
			return(0);
		}

	} else {
		return(0);
	}
}

void addToQueue(position_xy * input) {
	
	if (queue_head == NULL) {

		queue_head = malloc(sizeof(list));
		queue_head->previous = NULL;
		queue_head->next = NULL;
		queue_head->position = input;

	} else {

		list * temp_node;
		temp_node = queue_head;

		while(temp_node->next != NULL) {
			temp_node = temp_node->next;
		}

		list * new_node = malloc(sizeof(list));

		temp_node->next = new_node;

		new_node->previous = temp_node;
		new_node->position = input;
		new_node->next = NULL;
	}
}

position_xy * new_position(int x, int y){

	position_xy * new_position = malloc(sizeof(position_xy));
	new_position->x = x;
	new_position->y = y;
	return (new_position);
}

void printCurrentMap(int ** map, int width, int height) {

	int i, z;

	for(i=0; i<height; i++) {
		for(z=0; z<width; z++) {

			if (map[i][z] == 0){
				printf("[ ]");
			} else {
				printf("[X]");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void printFrontierQueue(list * node) {

	list * temp = node;

	printf("Queue: ");
	while (temp->next != NULL) {
		printf("(%d,%d)->", temp->position->x, temp->position->y);
		temp = temp->next;
	}
	printf("NULL");

	printf("\n-----------------\n\n");
}

