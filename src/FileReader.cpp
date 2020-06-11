#include <fstream>
#include "FileReader.h"

using namespace std;

FileReader::FileReader()
{
    //ctor
}

FileReader::~FileReader()
{
    //dtor
}


void FileReader::readScores(string fileName) {

    ifstream infile(fileName);
    if (!infile.good()) {
        printf("Failed to read scores!\n");
        return;
    }
    string name;
    int score;
    while (infile >> name >> score)
    {
        scores[name] = score;
    }

}
