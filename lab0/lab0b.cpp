#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

class CSV {
private:
    map<string, int> wordCount;
    int totalWords;
    string currentWord = "";
    int BUFFER = 5 * 1024 * 1024;

    bool Isword(unsigned char c) {
        if (c >= '0' && c <= '9') return true;
        if (c >= 'a' && c <= 'z') return true;
        if (c >= 'A' && c <= 'Z') return true;
        if (c >= 128) return true;
        if (c == '\'' || c == '.' || c == '-') return true;
        return false;
    }

    string PointDefis(const string& word) {
        if (word.empty()) return word;
        string result = word;
        while (!result.empty() && (result.back() == '.' || result.back() == '-')) {
            result.pop_back();
        }
        return result;
    }

    bool ComparePairs(const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    }

public:
    CSV() : totalWords(0) {}

    bool OpenFIle(const char* filename) {
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cout << "mistake open" << endl;
            return false;
        }

        char* inputBuffer = new char[BUFFER];
        inputFile.rdbuf()->pubsetbuf(inputBuffer, BUFFER);

        char c;
        while(inputFile.get(c)) {
            if (Isword((unsigned char)c)) {
                currentWord += tolower((unsigned char)c);
            }
            else if (!currentWord.empty()) {
                string cleanedWord = PointDefis(currentWord);
                if (!cleanedWord.empty()) {
                    wordCount[cleanedWord]++;
                    totalWords++;
                }
                currentWord = "";
            }
        }

        if (!currentWord.empty()) {
            string cleanedWord = PointDefis(currentWord);
            if (!cleanedWord.empty()) {
                wordCount[cleanedWord]++;
                totalWords++;
            }
        }

        inputFile.close();
        delete[] inputBuffer;
        return true;
    }

    bool CloseFile(const char* filename) {
        vector<pair<string, int>> wordList;
        for (auto& pair : wordCount) {
            wordList.push_back(make_pair(pair.first, pair.second));
        }

        sort(wordList.begin(), wordList.end(), ComparePairs);

        ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            cout << "mistake open ";
            return false;
        }

        char* outputBuffer = new char[BUFFER];
        outputFile.rdbuf()->pubsetbuf(outputBuffer, BUFFER);

        outputFile << "Word Count Frequency" << endl;

        for (auto& pair: wordList) {
            float percent = (pair.second * 100.0f) / totalWords;
            outputFile << pair.first << "," << pair.second << "," 
                      << fixed << setprecision(6) << percent << endl;
        }

        outputFile.close();
        delete[] outputBuffer;
        return true;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "wrong input" << endl;
        return 1;
    }

    CSV programm;
    if (!programm.OpenFIle(argv[1])) {
        return 1;
    }

    if (!programm.CloseFile("output.csv")) {
        return 1;
    }

    return 0;
}
