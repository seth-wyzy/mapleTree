#include "load.h"
#include <fstream>
#include <string>


void Loader::loadFromFile(std::string filename, std::vector<cube*>& fullScene) {
    std::ifstream inMap(filename);
    std::string line;
    int row = 0;
    int col = 0;
    if (inMap.is_open()) {
        while (std::getline(inMap, line)) {
            for (const auto& it: line) {
                if (it == '1') {
                    cube *tempCube = new cube(row, 0, col, 1, 1, 1, 0);
                    fullScene.push_back(tempCube);
                    col += 2;
                } else {
                    col += 2;
                }
            }
            row += 2;   
        }
    }
    

}