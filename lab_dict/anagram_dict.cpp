/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include<unordered_map>
using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::sort;
using std::unordered_map;
/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
		ifstream wordsFile(filename);
		string word;
		if(wordsFile.is_open()){
			while(std::getline(wordsFile,word)){
				string w1=word;
				sort(w1.begin(),w1.end());
				dict[w1].push_back(word);
			}

		}
		
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
		for(unsigned int i=0;i<words.size();i++){
			string w1=words[i];
			sort(w1.begin(),w1.end());
			dict[w1].push_back(words[i]);
		}
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
	  string w1=word;
		sort(w1.begin(),w1.end());
    if(dict.find(w1)==dict.end() || dict.find(w1)->second.size()==0){
			return vector<string>();
		} else{
			return dict.find(w1)->second;
		}
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
	
		vector<vector<string>> all_anagrams;
		//unordered_map<string,bool> visited;
		for(map<string,vector<string>>::const_iterator it=dict.begin();it!=dict.end();it++){
			if(it->second.size()>=2){
				all_anagrams.push_back(it->second);
			}
		}

    return all_anagrams;
}
