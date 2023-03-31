# C++ code for an electronic voting system. The code performs the following tasks:

Load voter IDs and names from a file.

Load candidate names from a file.

Initialize the votes for each candidate to 0.

Prompt the user for their voter ID and verify that it is valid.

Check if the voter has already voted.

Prompt the user to select a candidate to vote for.

Record the vote and save the voter ID.

Print the election results.

The code uses several C++ standard libraries, including iostream, fstream, vector, cstring, cstdlib, and chrono. It also uses the OpenCV library for image processing and the fprint library for fingerprint authentication.

The code defines several functions, including maskedInput(), which reads a string from the console and masks it with asterisks; loadIdNames(), which loads IDs and names from a file into a vector of pairs; saveVoterId(), which saves the ID of a voter who has already voted; voterHasVoted(), which checks if a voter has already voted; recordVote(), which records a vote for a candidate; and printResults(), which prints the election results.voting-system
