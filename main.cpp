// Programmer: Sophia Bhoria
// Date: 11/04/2024
// Purpose: Main entry point for the Bee Infestation program. Loads input, processes bee infestations, and outputs results.

#include "World.h"

int main() {
    World world;
    world.loadFromFile("input.txt");
    world.processAirdrops();
    world.saveToFile("output.txt");
    return 0;
}
