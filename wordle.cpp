#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void printResult(string word, string guess, int numEach[26]) {
	int yellow[26];
	int green[5];
	for (int i = 0; i < 26; i++) {
		yellow[i] = numEach[i];
	}
	for (int i = 0; i < 5; i++) {
		if (word[i] == guess[i]) {
			green[i] = 1;
			yellow[guess[i] - 'a']--;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (green[i] == 1) {
			cout << "\033[92m";
		} else if (yellow[guess[i] - 'a'] > 0) {
			cout << "\033[93m";
			yellow[guess[i] - 'a']--;
		} else {
			cout << "\033[37m";
		}
		cout << guess[i];
	}
	cout << "\033[0m | ";
	return;
}

int main() {
	vector<string> wordList;
	vector<string> guessList;
	string str;
	ifstream wordsIn("wordleanswers.txt");
	while (getline(wordsIn, str)) {
		if(str.size() > 0) {
			wordList.push_back(str);
			guessList.push_back(str);
		}
	}
	wordsIn.close();
	ifstream guessesIn("wordleguesses.txt");
	while (getline(guessesIn, str)) {
		if(str.size() > 0) guessList.push_back(str);
	}
	guessesIn.close();
	srand(time(0));
	string word = wordList[rand() % wordList.size()];
	string guess;
	string previousGuess = "-----";
	int numEach[26];
	for (int i = 0; i < 26; i++) {
		numEach[i] = 0;
		for (int j = 0; j < 5; j++) {
			if (word[j] == 'a' + i) numEach[i]++;
		}
	}
	cout << "----- | ";
	for (int i = 0; i < 6; i++) {
		cin >> guess;
		if (guess.length() != 5) {
			cout << "\033[91mMust be 5 letters\033[0m\n";
			printResult(word, previousGuess, numEach);
			i--;
		} else if (!count(guessList.begin(), guessList.end(), guess)) {
			cout << "\033[91mNot in word list\033[0m\n";
			printResult(word, previousGuess, numEach);
			i--;
		} else {
			printResult(word, guess, numEach);
			previousGuess = guess;
		}
		if (word == guess) {
			cout << "Completed " << (i + 1) << "/6\n";
			return 0;
		}
	}
	cout << "The word was: " << word << "\n";
	return 0;
}
