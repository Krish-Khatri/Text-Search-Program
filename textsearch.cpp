/* 
* Krish Khatri
* CWID: 11883418
* CS 101-001
* 1/18/2019
*
* This program reads words from a given file and outputs
* the total number of words read, the number of unique words
* and reports every word that matches a user-inputted word.
* 
* User-inputted words can have a wildcard character '?' where
* the character '?' has the ability to match any character, including
* and empty character.
*/

#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

string parseWords(ifstream & FILE)
{
    string str;
    char k;

    //Creates Words From The File
    while(FILE.get(k))
    {
        if(isalpha(k))
        {
            str += tolower(k);
        }
        else
        {
            break;
        }
    }
    return str;
}

bool match(string query, string word)
{
    int numofPrefixQuestion = 0;

    for(int i = 0; (unsigned)i < query.length(); i++)
    {
        if(isalpha(query[i]))
        {
            break;
        }
        numofPrefixQuestion++;
    }
    
    string substring;
    for(int i = 0; (unsigned)i < query.length(); i++)
    {
        if(query[i] == '?')
        {

        }
        else
        {   
            if(isalpha(query[i]))
            {
                substring += query[i];
            }
            if(query[i+1] == '?')
            {
                break;
            }            
        }
    }

    if(substring.empty())
    {
        if(word.length() <= (unsigned)numofPrefixQuestion)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        int initialPos = 0;

        while(1)
        {
            size_t pos;
            pos = word.find(substring,initialPos);
            if((unsigned)pos == string::npos)
            {
                return false;
            }
            
            if(pos > (unsigned)numofPrefixQuestion)
            {
                return false;
            }
            
            size_t posInQuery;
            posInQuery = query.find(substring) + (substring.length());
            size_t posInWord;
            posInWord = pos + substring.length();

            string substring1, substring2;
            substring1 = query.substr(posInQuery,query.length());
            substring2 = word.substr(posInWord, word.length());
            if(match(substring1,substring2))
            return true;
            initialPos = posInWord;
        }
    }
    return false;
}

void searchForWord(unordered_map<string, int> words, string searchWord, vector<string> inputText)
{
    string matchedArr[words.size()];
    int count = 0;
    for(int i = 0; (unsigned)i < inputText.size(); i++) 
    {
        string word = inputText[i];

        bool isMatch = match(searchWord,word);
        bool matched = false;

        
        for(int j = 0; j < count; j++)
        {
            if(word == matchedArr[j])
            {
                matched = true;
            }
        }        

        if(!matched && isMatch) 
        {
            //number of times the word matched occurs
            int numOfTimes = 0;

            //if the word is a match count the # of times it occurs
            for(unordered_map<string, int>::iterator z = words.begin(); z != words.end(); z++)
            {
                if(word.compare(z -> first) == 0) 
                {
                    numOfTimes = z -> second;
                }
            }

            if(numOfTimes == 1)
            {
               cout << "The word "<< word << " appears " << numOfTimes << " time in the document" << endl;
            }
            else
            {
                cout << "The word "<< word << " appears " << numOfTimes << " times in the document" << endl;
            }
            matchedArr[count++] = word;
        }
    }

}

int main(int argc, char const *argv[])
{   
    // Checks if the file name is given by user
    if(argc != 2)
    {
        cout << "Input: a.exe filename" << endl;
        return 1;
    }
    else
    {   
        ifstream read_File (argv[1]);
        //Checks if the file can be opened
        if(!read_File)
        {
            cout << "File: " << argv[1] << " cannot be opened" << endl;
            return 0;
        }

        string inputWords;
        unordered_map<string, int> words;
        vector<string> inputText;

        while(!read_File.eof())
        {   
            //Calls functions responsible for getting words from file
            inputWords = parseWords(read_File);
            if(!inputWords.empty())
            {
                inputText.push_back(inputWords);
                //Checks if the word already exists in the map and if so, add one to the count
                if(words.count(inputWords) > 0)
                {
                    words[inputWords]++;
                }
                //Puts word into map if it already doesn't exist and sets it count to 1
                else
                {
                    words[inputWords] = 1;
                }
            }
        }
        //Map only stores one word regardless of how many times it appears in the file
        int uniqueNumWords = words.size();

        int numberOfWords = 0;
        //Adds all counts together
        for(unordered_map<string,int>::iterator i = words.begin(); i != words.end(); i++)
        {
            numberOfWords += i -> second;
        }
        cout << "The number of words found in this file was " << numberOfWords << '\n';
        cout << "The number of unique words found in the file was " << uniqueNumWords << '\n';
        
        string searchStr;
        
        while(1)
        {
            cout << "\nPlease enter a word: ";
            cin >> searchStr;

            if(cin.eof())
            {
                cout << '\n';
                break;
            }
        
            for(int i = 0; (unsigned)i < searchStr.length(); i++)
            {
                searchStr[i] = tolower(searchStr[i]);
            }
            //Calls function responsible for finding how many occurences of user-inputted word exists in the file.
            searchForWord(words, searchStr, inputText);
        }
        read_File.close();
    }
}
