//#include<iostream>
//#include<list>
//#include<string>
//#include"Memory.h"
//using namespace std;
////const int sizer = 11;
////template<class t>
////class hashTable {
////
////	list<t> arr[sizer];
////public:
////	int hashFunction(const string& str) {
////		int hash = 0;
////		for (char c : str) {
////			hash += c;
////		}
////		return (hash % sizer);
////	}
////
////	void insert(string val) {
////
////		int loc = hashFunction(val);
////		arr[loc].push_back(val);
////	}
////
////	bool search(string val) {
////		int loc = hashFunction((val));
////
////		typename list<t>::iterator temp = arr[loc].begin();
////		while (temp != arr[loc].end()) {
////			if (*temp == val)  return true;
////			temp++;
////		}
////		return false;
////	}
////	void del(string val) {
////		int loc = hashFunction(val);
////		typename list<t>::iterator temp = arr[loc].begin();
////		while (temp != arr[loc].end()) {
////			if (*temp == val) {
////				arr[loc].erase(temp); break;
////			}++temp;
////		}
////	}
////
////};
//
//int main() {
//	Memory m;
//	m.traverseAndReadDirectory("D:\\");
//}
//
//
//
//
//
////#include"memory.h"
////
////int main() {
////    Memory memory;
////
////
////
////    vector<string> filepaths = {
////        "D:\\search.txt",
////        "D:\\search2.txt",
////        "D:\\search3.txt",
////        "D:\\search4.txt"
////    };
////    memory.readFiles(filepaths);
////
////    // Example queries
////    vector<string> queries = {
////        "Machine",
////        "display"
////    };
////
////    for (const auto& query : queries) {
////        cout << "Query: " << query << endl;
////        unordered_set<string> results = memory.search(query);
////        memory.displayResults(results);
////        cout << "-----------------" << endl << endl;
////    }
////
////    return 0;
////}
