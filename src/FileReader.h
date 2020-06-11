#ifndef FILEREADER_H
#define FILEREADER_H

#include <unordered_map>

using namespace std;

#define FILE_NAME "scores.txt"

class FileReader
{
    public:
        FileReader();
        virtual ~FileReader();
        void readScores(string fileName);

        unordered_map<string, int> getScores() { return scores; }

    protected:

    private:
        // Stores all the scores.
	    unordered_map<string, int> scores;
};

#endif // FILEREADER_H
