#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

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

int main(int argc, char* argv[]){
    if (argc != 2){
        cout << "wrong input" << endl;
        return 1;
    }
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()){
        cout << "mistake open File" << endl;
        return 1;
    }
    const int BUFFER_SIZE = 5 * 1024 * 1024;
    char* inputBuffer = new char[BUFFER_SIZE];
    inputFile.rdbuf()->pubsetbuf(inputBuffer, BUFFER_SIZE);

    map<string, int> wordCount;
    int totalWords = 0;
    string currentWord = "";
    char c;
    
    while(inputFile.get(c)){
        if (Isword((unsigned char)c)){
            currentWord += tolower((unsigned char)c);
        }
        else if (!currentWord.empty()){
            string cleanedWord = PointDefis(currentWord);
            if (!cleanedWord.empty()) {
                wordCount[cleanedWord]++;
                totalWords++;
            }
            currentWord = "";
        }
    }
    
    if (!currentWord.empty()){
        string cleanedWord = PointDefis(currentWord);
        if (!cleanedWord.empty()) {
            wordCount[cleanedWord]++;
            totalWords++;
        }
    }
    
    inputFile.close();
    delete[] inputBuffer;

    vector<pair<string, int> > wordList;
    for (map<string, int>::iterator i = wordCount.begin(); i != wordCount.end(); ++i) {
        wordList.push_back(make_pair(i->first, i->second));
    }
    
    sort(wordList.begin(), wordList.end(), ComparePairs);
    
    ofstream outputFile("output.csv");
    if (!outputFile.is_open()) {
        cout << "mistake open output file";
        return 1;
    }
    char* outputBuffer = new char[BUFFER_SIZE];
    outputFile.rdbuf()->pubsetbuf(outputBuffer, BUFFER_SIZE);
    
    outputFile << "Word Count Frequency" << endl;
    
    for (size_t i = 0; i < wordList.size(); i++) {
        float percent = (wordList[i].second * 100.0f) / totalWords;
        outputFile << wordList[i].first << "," << wordList[i].second << "," 
                  << fixed << setprecision(6) << percent << endl;
    }
    outputFile.close();
    delete[] outputBuffer;
    
    return 0;
}