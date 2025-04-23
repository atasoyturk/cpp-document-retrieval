#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;
struct Node {
	string word;
	vector <string> docIDs; 
	Node* next;
	Node(const string& name) : word(name), next(nullptr) {}
};

class WordList {
private:
	Node* head;

	struct WordCount {
		string word;
		int count;
	};

public:
	WordList() : head(nullptr) {}

	void addWord(const string& word, const string& filename) {
		string cleanedWord = cleanWord(word);
		Node* current = head;
		Node* prev = nullptr;

		if (cleanedWord.empty()) return; 

		while (current != nullptr && current->word < cleanedWord) {
			prev = current;
			current = current->next;
		}
		if (current != nullptr && current->word ==cleanedWord) {
			bool found = false;
			
			for (const string& docID : current->docIDs) {
				if (docID == filename) {
					found = true;
					break;
				}
			}
			if (!found) {
				current->docIDs.push_back(filename);
			}

		}
		else {
			Node* newNode = new Node(cleanedWord);
			newNode->docIDs.push_back(filename);
			if (prev == nullptr) {
				head = newNode;
			}
			else {
				prev->next = newNode;
			}
			newNode->next = current;
		}

	}

	void searchWord(const string& word) const {
		string cleanedWord = cleanWord(word);
		Node* current = head;

		while (current != nullptr) {
			if (current->word == cleanedWord) {
				cout << "Word: " << current->word << endl;
				cout << "Document IDs: ";
				for (const string& docID : current->docIDs) {
					cout << docID << " ";
				}
				cout << endl;
				return;
			}
			current = current->next;
		}
		cout << "Word not found." << endl;
	}

	void printTopWords(int maxResults = 10) {
		vector<pair<string,int>> wordCounts;

		Node* current = head;
		while (current != nullptr) {
			wordCounts.push_back({ current->word, (int)current->docIDs.size() });
			current = current->next;
		}

		sort(wordCounts.begin(), wordCounts.end(),
			[](auto& a, auto& b) { return a.second > b.second; });


		cout << "\nTop 10 Words: " << maxResults << " Word:\n";
		for (int i = 0; i < maxResults && i < wordCounts.size(); i++) {
			cout << i + 1 << ". " << wordCounts[i].first
				<< " (" << wordCounts[i].second << " times)\n";
		}
	}

	void printBottomWords(int maxResults = 10) {
		vector<pair<string, int>> wordCounts;

		Node* current = head;
		while (current != nullptr) {
			wordCounts.push_back({ current->word, (int)current->docIDs.size() });
			current = current->next;
		}

		sort(wordCounts.begin(), wordCounts.end(),
			[](auto& a, auto& b) { return a.second < b.second; });

		cout << "Least 10 Words: \n " << maxResults << "Words: \n";
		for (int i = 0; i < maxResults && i < wordCounts.size(); i++) {
			cout << i + 1 << ". " << wordCounts[i].first
				<< " (" << wordCounts[i].second << " times)\n";
		}
	}

	~WordList() {
		Node* current = head;
		while (current != nullptr) {
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		}
	}
	string cleanWord(const string& word)const {
		
	string result;
    for (char c : word) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                result += tolower(c);
        }
    }
    return result;
			
	}
};

void showLoadingMessage() {
	cout << "Reading files";
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 3; ++j) {
			cout << ".";
			cout.flush();
			this_thread::sleep_for(chrono::milliseconds(500));
		}
		cout << "\b\b\b   \b\b\b";
		cout.flush();
	}
	
	cout << endl;
	
}

void processFiles(WordList& list) {
	const string path = "data/sample_docs";
	int opened_files = 0;

	for (int i = 1; i <= 100; ++i) {
		string filename = to_string(i) + ".txt";
		string fullPath = path + filename;

		
		ifstream file(fullPath);
		if (!file.is_open()) {
			cerr << "Error opening file: " << filename << endl;
			continue;

		}

		opened_files++;
		string line;

		while (getline(file, line)) {
			istringstream iss(line);
			string word;
			while (iss >> word) {
				list.addWord(word, filename);

			}
		}
		file.close();

		if (i % 100 == 0 || i == 100) {
			
			cout << "\nNumber of files read successfully: " << opened_files << endl;
			showLoadingMessage();
		}
	}
}
void option1(WordList& list) {
	string wantedWord;
	while (true) {
		cout << "Enter a word to search for (quit for q): ";
		cin >> wantedWord;

		if (wantedWord == "q") {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return;
		}

		list.searchWord(wantedWord);
	}
	
}
void showMenu(WordList& wordList) {
	int choice;
	do {
		cout << "\n\t\t----------------------------------" << endl;
		cout << "\t\t|Simple Document Retrieval System|" << endl;
		cout << "\t\t|*index creation time: 30 Minutes|" << endl;
		cout << "\t\t----------------------------------" << endl;
		cout << "\t1. Enter a single keyword to list the document(s)(file names)" << endl;
		cout << "\t2. Print the top 10 words that appeared most frequently" << endl;
		cout << "\t3. Print the top 10 words that appeared least frequently" << endl;
		cout << "\t4. Exit" << endl;

		cout << "\tPlease select an option: ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Buffer temizleme

		switch (choice) {
		case 1:
			option1(wordList);
			break;
		case 2:
			wordList.printTopWords(10);
			break;
		case 3:
			wordList.printBottomWords(10);
			break;
		case 4:
			cout << "Exiting the program." << endl;
			return; 
		default:
			cout << "Invalid option! Please try again." << endl;
		}
	} while (true); 
	
}

int main() {
	WordList wordList;

	cout << "Progress may be slow at the beginning, please wait." << endl;
	showLoadingMessage();
	processFiles(wordList);

	showMenu(wordList);
	return 0;
}
