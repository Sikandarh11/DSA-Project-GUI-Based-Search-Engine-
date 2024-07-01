#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <thread>
#include <mutex>
#include <cctype>
#include <filesystem>
#include <exception>
#include <queue>

namespace fs = std::filesystem;
using namespace std;

//const int sizer = 1000;

class node {
public:
    string filename;
    int wordfrequency;
    node(const string& filename, int wordfrequency) : filename(filename), wordfrequency(wordfrequency) {}
    node(string filename) : filename(filename), wordfrequency(1) {}
};

struct Hash {
    size_t operator()(const node* node) const {
        return hash<string>()(node->filename) ^ hash<int>()(node->wordfrequency);
    }
};

struct KeyEqual {
    bool operator()(const node* lhs, const node* rhs) const {
        return lhs->filename == rhs->filename;
    }
};

struct NodeComparator {
    bool operator()(const node* lhs, const node* rhs) const {
        if (lhs->wordfrequency != rhs->wordfrequency) {
            return lhs->wordfrequency < rhs->wordfrequency;
        }
        else {
            return lhs->filename > rhs->filename;
        }
    }
};

class Memory {
private:
    unordered_map<string, priority_queue<node*, vector<node*>, NodeComparator>> index;
    unordered_map<string, priority_queue<node*, vector<node*>, NodeComparator>> history;
    mutex indexmutex;

    string normalizeword(const string& word) {
        string normalized;
        for (char ch : word) {
            if (isalpha(static_cast<unsigned char>(ch))) {
                normalized += tolower(static_cast<unsigned char>(ch));
            }
        }
        return normalized;
    }

    vector<string> splitandfilter(const string& sentence) {
        unordered_set<string> ignorewords = { "is", "am", "are", "was", "were", "be", "being", "been",
                                              "do", "does", "did", "have", "has", "had", "will",
                                              "shall", "would", "should", "can", "could", "may",
                                              "might", "must" };

        istringstream iss(sentence);
        unordered_set<string> seenwords;
        vector<string> words;
        string word;

        while (iss >> word) {
            word = normalizeword(word);
            if (!word.empty() && ignorewords.find(word) == ignorewords.end() && seenwords.find(word) == seenwords.end()) {
                words.push_back(word);
                seenwords.insert(word);
            }
        }
        return words;
    }
    void readfile(const string& filepath) {
        ifstream inputfile(filepath);
        if (!inputfile.is_open()) {
            cerr << "Failed to open file: " << filepath << endl;
            return;
        }

        string line;
        while (getline(inputfile, line)) {
            vector<string> words = splitandfilter(line);
            lock_guard<mutex> guard(indexmutex);
            for (const auto& word : words) {
                if (index.find(word) != index.end()) {
                    bool found = false;
                    priority_queue<node*, vector<node*>, NodeComparator> temp;
                    while (!index[word].empty()) {
                        node* n = index[word].top();
                        index[word].pop();
                        if (n->filename == filepath) {
                            n->wordfrequency++;
                            found = true;
                        }
                        temp.push(n);
                    }
                    if (!found) {
                        temp.push(new node(filepath));
                    }
                    index[word] = temp;
                }
                else {
                    priority_queue<node*, vector<node*>, NodeComparator> temp;
                    temp.push(new node(filepath));
                    index[word] = temp;
                }
            }
        }
        inputfile.close();
    }

    priority_queue<node*, vector<node*>, NodeComparator> searchsinglekeyword(const string& keyword) {
        lock_guard<mutex> guard(indexmutex);
        if (index.find(keyword) != index.end()) {
            return index[keyword];
        }
        return {};
    }

    priority_queue<node*, vector<node*>, NodeComparator> searchand(const vector<string>& keywords) {
        if (keywords.empty()) return {};

        priority_queue<node*, vector<node*>, NodeComparator> result = searchsinglekeyword(keywords[0]);
        for (size_t i = 1; i < keywords.size(); ++i) {
            priority_queue<node*, vector<node*>, NodeComparator> temp = searchsinglekeyword(keywords[i]);
            priority_queue<node*, vector<node*>, NodeComparator> intersection;
            while (!result.empty() && !temp.empty()) {
                node* n1 = result.top();
                node* n2 = temp.top();
                if (n1->filename == n2->filename) {
                    intersection.push(n1);
                    result.pop();
                    temp.pop();
                }
                else if (n1->filename < n2->filename) {
                    result.pop();
                }
                else {
                    temp.pop();
                }
            }
            result = intersection;
        }
        return result;
    }

    priority_queue<node*, vector<node*>, NodeComparator> searchor(const vector<string>& keywords) {
        priority_queue<node*, vector<node*>, NodeComparator> result;
        for (const auto& keyword : keywords) {
            priority_queue<node*, vector<node*>, NodeComparator> temp = searchsinglekeyword(keyword);
            while (!temp.empty()) {
                result.push(temp.top());
                temp.pop();
            }
        }
        return result;
    }

public:
    string DirectoryPaths(const string& result) {
        istringstream iss(result);
        unordered_set<string> rootDirectories;
        string filename;

        while (getline(iss, filename, ',')) { 
            size_t pos = filename.find_last_of("\\");
            if (pos != string::npos) {
                string root_directory = filename.substr(0, pos);
                rootDirectories.insert(root_directory);
            }
        }

        
        string rootDirectoriesStr;
        for (const auto& dir : rootDirectories) {
            if (!rootDirectoriesStr.empty()) {
                rootDirectoriesStr += ","; // Separator for multiple directories
            }
            rootDirectoriesStr += dir;
        }
        cout <<endl<< rootDirectoriesStr<<endl;
        return (rootDirectoriesStr);
    }


    priority_queue<node*, vector<node*>, NodeComparator> search(const string& query) {
        vector<string> words = splitandfilter(query);
        vector<string> keywords;
        bool andOperation = false, orOperation = false;

        for (const auto& word : words) {
            if (word == "and") {
                andOperation = true;
            }
            else if (word == "or") {
                orOperation = true;
            }
            else {
                keywords.push_back(word);
            }
        }
        priority_queue<node*, vector<node*>, NodeComparator> result;
        if (andOperation) {
            result = searchand(keywords);
        }
        else if (orOperation) {
            result = searchor(keywords);
        }
        else if (keywords.size() == 1) {
            result = searchsinglekeyword(keywords[0]);
        }
        else {
            result = searchand(keywords);
        }

        
        history[query] = result;
      
        return result;
    }
    
    unordered_map<string, priority_queue<node*, vector<node*>, NodeComparator>> get_history() {
		return history;
	}
   

    void readfiles(const vector<string>& filepaths) {
        vector<thread> threads;
        for (const auto& filepath : filepaths) {
            threads.emplace_back(&Memory::readfile, this, filepath);
        }
        for (auto& t : threads) {
            t.join();
        }
    }

    vector<string> traverseandreaddirectory(const string& directorypath) {
        vector<string> filepaths;
        int i = 0;
        try {
            for (const auto& entry : fs::recursive_directory_iterator(directorypath)) {
                if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                    cout << i << " " << entry.path().string() << endl;
                    filepaths.push_back(entry.path().string());
                    i++;
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            cerr << "Filesystem error: " << e.what() << endl;
        }
        catch (const exception& e) {
            cerr << "General error: " << e.what() << endl;
        }
        catch (...) {
            cerr << "Failed to open directory: " << directorypath << endl;
        }

        
            return filepaths;
    }

};
