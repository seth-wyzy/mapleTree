#include <string>
#include <fstream>
#include "objects.h"

class Loader {
public:
    void loadFromFile (std::string filename, std::vector<cube*>& fullScene);
};