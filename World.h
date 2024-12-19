// Programmer: Sophia Bhoria
// Date: 11/04/2024
// Purpose: Declares the World class for managing bee infestations.

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>

class World {
public:
    World();
    void loadFromFile(const std::string &filename);
    void processAirdrops();
    void saveToFile(const std::string &filename);

private:
    std::vector<std::vector<char>> worldMap;
    std::vector<std::pair<int, int>> airdrops;

    void applyAirdrop(int x, int y);
    void handleOutbreak(int x, int y);
    void mutate(int x, int y, char type);
    bool isWithinBounds(int x, int y);
};

#endif
