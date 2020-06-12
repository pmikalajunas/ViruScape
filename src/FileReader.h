#ifndef FILEREADER_H
#define FILEREADER_H

#include <unordered_map>

using namespace std;

#define SCORES_FILE "scores.txt"
#define PLAYER_FILE "player.txt"

class FileReader
{
    public:
        FileReader();
        virtual ~FileReader();
        void readScores();
        void writeScores();
        void readPlayer();
        void addScore(int score);

        unordered_map<string, int> getScores() { return scores; }
        string getPlayer() { return player; }

    protected:

    private:
        // Stores all the scores.
	    unordered_map<string, int> scores;
        // Current player's name.
        string player;  
};

#endif // FILEREADER_H
