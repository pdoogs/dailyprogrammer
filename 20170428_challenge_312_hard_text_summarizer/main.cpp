// This solution reads each sentence word by word, increasing the sentence's score if 
// a word isn't in a stop list (therefore an important word).
// The sentences are stored in a set ranked by score and the 2 highest scoring 
// sentences are printed.
//
// O(n * ln(n)) in words

#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

set<char> endOfSentenceChars = { '.', '?', '!' };
set<char> spaceChars = { ' ', '\t', '\n', '\r' };
const int NUM_SENTENCES_TO_OUTPUT = 2;

struct Sentence
{
   vector<string> words;
   int score;

   void Write() const {
      cout << words[0];
      for (size_t j = 1; j < words.size(); j++)
         cout << " " << words[j];
   }
};

bool operator < (const Sentence & a, const Sentence & b) { return a.score < b.score; }

void main(int argc, char * argv[])
{
   // read the stop words
   ifstream stopFile("stopwords.txt");
   set<string> stopSet;
   while (!stopFile.eof())
   {
      string s;
      stopFile >> s;
      stopSet.insert(s); // O(ln(n))
   }
   
   ifstream input("input.txt");
   set<Sentence> sentences;
   Sentence currSentence;
   string currString;

   string s;
   while (input >> s)
   {
      if (endOfSentenceChars.find(s.back()) != endOfSentenceChars.end())
      {
         currSentence.words.push_back(s);
         sentences.insert(currSentence); // O(ln(n))

         string withoutPunctuation = s.substr(0, s.size() - 2);
         if (stopSet.find(s) == stopSet.end())
         {
            // not in stop set, increase this sentence's score
            currSentence.score++;
         }

         currSentence.words.clear(); // this word ends the sentence, reset for next word
         s.clear();
      }
      else
      {
         if (stopSet.find(s) == stopSet.end())
         {
            // not in stop set, increase this sentence's score
            currSentence.score++;
         }
         currSentence.words.push_back(s);
      }
   }

   // if we have less sentences then required for a summary, provide no output
   if (sentences.size() <= NUM_SENTENCES_TO_OUTPUT)
   {
      return;
   }

   // skip to last NUM_SENTENCES_TO_OUTPUT number of sentences (highest rank)
   int numToSkip = sentences.size() - NUM_SENTENCES_TO_OUTPUT - 1;
   for (int i = 0; i < numToSkip; i++) { sentences.erase(sentences.begin()); }

   // write the sentences
   while (!sentences.empty())
   {
      sentences.begin()->Write();
      cout << " ";
      sentences.erase(sentences.begin());
   }
}