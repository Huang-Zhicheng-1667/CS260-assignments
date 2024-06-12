#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define YELLOW 1
#define BLUE 2

// Represent a marble
typedef struct {
    int color;
} Marble;

// Marble bag
typedef struct {
    int red_count;
    int yellow_count;
    int blue_count;
    int total_count;
} BagOfMarbles;

// Add a marble into bag
void add_marble(BagOfMarbles *bag, Marble marble) {
    switch (marble.color) {
        case RED:
            bag->red_count++;
            break;
        case YELLOW:
            bag->yellow_count++;
            break;
        case BLUE:
            bag->blue_count++;
            break;
    }
    bag->total_count++;
}

// Remove a random marble
void remove_marble(BagOfMarbles *bag) {
    if (bag->total_count == 0)
        return;

    int rand_color = rand() % 3;

    switch (rand_color) {
        case RED:
            if (bag->red_count > 0)
                bag->red_count--;
            break;
        case YELLOW:
            if (bag->yellow_count > 0)
                bag->yellow_count--;
            break;
        case BLUE:
            if (bag->blue_count > 0)
                bag->blue_count--;
            break;
    }
    bag->total_count--;
}

// Return numbers for each color and total.
void get_marbles(BagOfMarbles bag) {
    printf("Red is %d, Yellow is %d, Blue is %d. Total is %d.\n", bag.red_count, bag.yellow_count, bag.blue_count, bag.total_count);
}

// Check if bag emtpy
int is_empty(BagOfMarbles bag) {
    return bag.total_count == 0;
}

// Clear bag
void clear(BagOfMarbles *bag) {
    bag->red_count = 0;
    bag->yellow_count = 0;
    bag->blue_count = 0;
    bag->total_count = 0;
}

// Define for test.
#define MAX_INITIAL_COUNT 10

int main() {
    srand(time(NULL));

    // Empty bag
    BagOfMarbles bag = {0, 0, 0, 0};

    // Test add marble
    printf("Test add_marble(marble):\n");
    printf("Start with an empty bag.\n");
    get_marbles(bag);
    Marble red_marble = {RED};
    add_marble(&bag, red_marble);
    printf("Add a marble with color red.\n");
    get_marbles(bag);

    // Test remove marble
    printf("\nTest remove_marble():\n");
    get_marbles(bag);
    remove_marble(&bag);
    printf("After removing a marble:\n");
    get_marbles(bag);

    return 0;
}
