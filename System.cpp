#include <iostream>

#include <fstream>

#include <vector>

#include <cstring>

#include <cstdlib>

#include <ctime>

#include <chrono>
#include<opencv2.opencv.hpp>
#include <fprint/fprint.h>

using namespace std;

// Function to read a string from the console and mask it with asterisks

string maskedInput(const string& prompt) {

    string input;

    cout << prompt;

    char c;

    while ((c = getch()) != '\r') {

        if (c == '\b' && !input.empty()) {

            input.pop_back();

            cout << "\b \b";

        } else if (isalnum(c) || ispunct(c)) {

            input.push_back(c);

            cout << "*";

        }

    }

    return input;

}

// Function to load IDs and names from a file into a vector of pairs

vector<pair<string, string>> loadIdNames(const string& filename) {

    vector<pair<string, string>> idNames;

    ifstream file(filename);

    if (!file) {

        cerr << "Error: Could not open " << filename << " for reading.\n";

        exit(EXIT_FAILURE);

    }

    string id, name;

    while (file >> id >> name) {

        idNames.emplace_back(id, name);

    }

    file.close();

    return idNames;

}

// Function to save the ID of a voter who has already voted

void saveVoterId(const string& voterId, const string& filename) {

    ofstream file(filename, ios::app);

    if (!file) {

        cerr << "Error: Could not open " << filename << " for writing.\n";

        exit(EXIT_FAILURE);

    }

    file << voterId << endl;

    file.close();

}

// Function to check if a voter has already voted

bool voterHasVoted(const string& voterId, const string& filename) {

    ifstream file(filename);

    if (!file) {

        cerr << "Error: Could not open " << filename << " for reading.\n";

        exit(EXIT_FAILURE);

    }

    string id;

    while (file >> id) {

        if (id == voterId) {

            return true;

        }

    }

    file.close();

    return false;

}

// Function to record a vote for a candidate

void recordVote(int candidateIndex, const vector<string>& candidateNames, vector<int>& votes) {

    if (candidateIndex >= 0 && candidateIndex < candidateNames.size()) {

        votes[candidateIndex]++;

        cout << "Vote recorded for " << candidateNames[candidateIndex] << ".\n";

    } else {

        cout << "Invalid candidate index.\n";

    }

}

// Function to print the election results

void printResults(const vector<string>& candidateNames, const vector<int>& votes) {

    int maxVotes = *max_element(votes.begin(), votes.end());

    cout << "Election Results:\n";

    for (size_t i = 0; i < candidateNames.size(); i++) {

        cout << "  " << candidateNames[i] << ": " << votes[i] << " vote";

        if (votes[i] != 1) {

            cout << "s";

        }

        if (votes[i] == maxVotes) {

            cout << " (winner)";

        }

        cout << ".\n";

    }

}

int main() {

    const string idFile = "ids.txt";

    const string voteFile = "votes.txt";

    const string voterFile = "voters.txt";

   
// Load voter IDs and names from file

vector<pair<string, string>> idNames = loadIdNames(idFile);
// Load candidate names from file

vector<string> candidateNames;

ifstream candidateFile("candidates.txt");

if (!candidateFile) {

    cerr << "Error: Could not open candidates.txt for reading.\n";

    exit(EXIT_FAILURE);

}

string name;

while (getline(candidateFile, name)) {

    candidateNames.push_back(name);

}

candidateFile.close();

// Initialize votes for each candidate to 0

vector<int> votes(candidateNames.size(), 0);

// Prompt user for voter ID and verify it is valid

bool validVoter = false;

string voterId;

while (!validVoter) {

    voterId = maskedInput("Enter your voter ID: ");

    for (const auto& idName : idNames) {

        if (idName.first == voterId) {

            validVoter = true;

            cout << "\nWelcome, " << idName.second << "!\n";

            break;

        }

    }

    if (!validVoter) {

        cout << "\nInvalid voter ID. Please try again.\n";

    }

}

// Check if voter has already voted

if (voterHasVoted(voterId, voteFile)) {

    cout << "Error: You have already voted in this election.\n";

    exit(EXIT_FAILURE);

}

// Prompt user to select a candidate to vote for

int candidateIndex = -1;

while (candidateIndex < 0 || candidateIndex >= candidateNames.size()) {

    cout << "Candidates:\n";

    for (size_t i = 0; i < candidateNames.size(); i++) {

        cout << "  " << i + 1 << ". " << candidateNames[i] << endl;

    }

    cout << "Enter the number of the candidate you would like to vote for: ";

    cin >> candidateIndex;

    candidateIndex--;

}

// Record vote and save voter ID

recordVote(candidateIndex, candidateNames, votes);

saveVoterId(voterId, voteFile);

// Print election results

printResults(candidateNames, votes);

return 0;


}
