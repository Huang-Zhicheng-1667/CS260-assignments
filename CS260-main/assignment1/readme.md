Bag of Marbles

Description:
This program models a bag of marbles, allowing users to make changes to the three colors marbles.

Variables:
Marble: Represents individual marble with its color, red, yellow, or blue.
Bag: Represents the numbers of the marbles.

Methods:
add_marble(marble): Adds a new marble to the bag.
remove_marble(): Removes a random marble from the bag.
get_marbles(): Return numbers of each color marble. And total numbers of marbles.
is_empty(): Checks if the bag is empty.
clear(): Removes all marbles from the bag.

Tests:
add_marble(marble):
    Start with an empty bag.
    get_marbles(): Red is 0, Yellow is 0, Blue is 0. Total is 0.
    Add a marble with color red.
    get_marbles(): Red is 1, Yellow is 0, Blue is 0. Total is 1.

remove_marble():
    Now we have Red is 1, Yellow is 0, Blue is 0. Total is 1.
    remove_marble();
    get_marbles(): Total number of the marbles adding together will be 0.
