// Programmer: Sophia Bhoria
// Date: 11/04/2024
// Purpose: Implements the World class methods for managing infestations.

#include "World.h"
#include <fstream>
#include <iostream>

World::World() : worldMap(10, std::vector<char>(10, '_')) {}

/*
loadFromFile - Reads the initial world state and airdrop coordinates from input file.
*/
void World::loadFromFile(const std::string &filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error opening input file!" << std::endl;
        return;
    }

    // Read the 10x10 world map
    for (int i = 0; i < 10; ++i) {
        std::string line;
        std::getline(inputFile, line);
        for (int j = 0; j < 10; ++j) {
            worldMap[i][j] = line[j];
        }
    }

    // Read airdrop coordinates
    int x, y;
    while (inputFile >> x >> y) {
        airdrops.emplace_back(x, y);
    }

    inputFile.close();
}

/*
processAirdrops - Iterates through each airdrop and applies infestations.
*/
void World::processAirdrops() {
    for (const auto &coord : airdrops) {
        applyAirdrop(coord.first, coord.second);
    }
}

/*
saveToFile - Saves the final world map state to an output file.
*/
void World::saveToFile(const std::string &filename) {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cerr << "Error creating output file!" << std::endl;
        return;
    }

    for (const auto &row : worldMap) {
        for (char cell : row) {
            outputFile << cell;
        }
        outputFile << '\n';
    }

    outputFile.close();
}

/*
applyAirdrop - Places bees at the specified location and handles outbreaks.
*/
void World::applyAirdrop(int x, int y) {
    if (!isWithinBounds(x, y)) return;

    char &current = worldMap[x][y];
    if (current == '_') {
        current = 'B';  // Empty country becomes infested with bees
    } else {
        handleOutbreak(x, y);  // Outbreak if location already infested
    }
}

/*
handleOutbreak - Causes an outbreak around a specified location, with mutations.
*/
void World::handleOutbreak(int x, int y) {
    char currentType = worldMap[x][y];
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx, ny = y + dy;
            if (isWithinBounds(nx, ny) && !(dx == 0 && dy == 0)) {
                // Only mutate if the cell is within bounds and is not the center cell
                mutate(nx, ny, currentType);
            }
        }
    }
}

/*
mutate - Manages mutation logic for infestations based on current type.
*/
void World::mutate(int x, int y, char type) {
    char &target = worldMap[x][y];

    // Infest empty country with bees
    if (target == '_' && type == 'B') {
        target = 'B';
    } 
    // Bees mutate to wasps if bees already present
    else if (target == 'B' && type == 'B') {
        target = 'W';
    }
    // Wasps mutate to tarantula hawk wasps if wasps already present
    else if (target == 'W' && type == 'W') {
        target = 'T';
    }
    // Bees do not infest countries with wasps or tarantula hawk wasps
    // Wasps do not infest countries with tarantula hawk wasps
}

/*
isWithinBounds - Checks if given coordinates are within the 10x10 map bounds.
*/
bool World::isWithinBounds(int x, int y) {
    return x >= 0 && x < 10 && y >= 0 && y < 10;
}
