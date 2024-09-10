#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to sort the characters of a string
string sortString(const string &str) {
    string sorted_str = str;
    sort(sorted_str.begin(), sorted_str.end());
    return sorted_str;
}

// Function to check if two words are anagrams
bool areAnagrams(const string &word1, const string &word2) {
    return sortString(word1) == sortString(word2);
}

// Function to create a frequency map of characters in a string
unordered_map<char, int> createFrequencyMap(const string &str) {
    unordered_map<char, int> freq_map;
    for (char ch : str) {
        freq_map[ch]++;
    }
    return freq_map;
}

// Function to check if one word is a sub-anagram of another
bool isSubAnagram(const string &word1, const string &word2) {
    unordered_map<char, int> freq_map1 = createFrequencyMap(word1);
    unordered_map<char, int> freq_map2 = createFrequencyMap(word2);

    for (const auto &pair : freq_map2) {
        if (freq_map1[pair.first] < pair.second) {
            return false;
        }
    }
    return true;
}

// Function to find and return all anagrams or sub-anagrams in the file
vector<string> findAnagramsOrSubAnagrams(const string &word, const string &filename, bool findSubAnagrams) {
    ifstream file(filename);
    vector<string> results;
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return results;
    }

    while (getline(file, line)) {
        if ((findSubAnagrams && isSubAnagram(word, line)) || (!findSubAnagrams && areAnagrams(word, line))) {
            results.push_back(line);
        }
    }

    file.close();
    return results;
}

int main() {
    string word, filename;
    char choice;

    // Get the word from the user
    cout << "Enter a word: ";
    cin >> word;

    // Get the filename from the user
    cout << "Enter the filename containing the list of words: ";
    cin >> filename;

    // Get the user's choice for anagrams or sub-anagrams
    cout << "Do you want to find (a)nagrams or (s)ub-anagrams? (Enter 'a' or 's'): ";
    cin >> choice;

    bool findSubAnagrams = (choice == 's');

    // Find anagrams or sub-anagrams in the file
    vector<string> results = findAnagramsOrSubAnagrams(word, filename, findSubAnagrams);

    // Output the results with numbering
    if (results.empty()) {
        cout << "No " << (findSubAnagrams ? "sub-anagrams" : "anagrams") << " found for the word '" << word << "' in the file."
             << endl;
    } else {
        cout << (findSubAnagrams ? "Sub-anagrams" : "Anagrams") << " found for the word '" << word << "':" << endl;
        int count = 1; // Initialize counter
        for (const string &result : results) {
            cout << count << ". " << result << endl; // Print with numbering
            ++count; // Increment counter
        }
    }

    return 0;
}
