#include <fstream>
#include <vector>
#include "Iris.h"

using namespace std;
class Reader {
private:
    ifstream file;

    void close();

    Iris* parseLine(const string& line);
public:
    explicit Reader(const string& filePath);

    vector<Iris*>* buildDataset();
};
