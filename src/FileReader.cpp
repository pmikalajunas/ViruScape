#include <fstream>
#include "FileReader.h"

using namespace std;

FileReader::FileReader()
{
    readScores();
    readPlayer();
}

FileReader::~FileReader()
{
}

/*
    Reads scores from a file.
    Stores them in unordered map.
*/
void FileReader::readScores() {

    ifstream infile(SCORES_FILE);
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

/*
    Reads and stores player's name.
*/
void FileReader::readPlayer() {
    ifstream infile(PLAYER_FILE);
    if (!infile.good()) {
        printf("Failed to read player!\n");
        return;
    }
    infile >> player;
}

/*
    Writes all the scores from the map to the file.
*/
void FileReader::writeScores() {

    ofstream file;
    file.open(SCORES_FILE);
    for (auto& x : scores){
        char buf[64];
        sprintf( buf, "%s %d\n", x.first.c_str(), x.second);
        file << buf;
	}

}


/*
    Adds the score if player does not exist.
    Updates the score if player performed better.
*/
void FileReader::addScore(int score) {
    // Add score if player does not exist.
    if (scores.find(player) == scores.end())
        scores[player] = score;

    // Update score if player scored higher than before.
    if ( scores.at(player) < score )
        scores[player] = score;
}

