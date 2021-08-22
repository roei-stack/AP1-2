#include <fstream>
#include <vector>
#include "Iris.h"

using namespace std;
class Reader {
private:
    ifstream file;

    Iris* parseLine(const string& line);
    void close();

public:
    explicit Reader(const string& filePath);

    vector<Iris*>* buildDataset();
};
