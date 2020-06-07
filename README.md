# Text-Search-Program
A Text Search Program with Wild Card Capabilities. The program reads words from a
given file. Each word has to consist strictly of the letters A-Z and a-z. Any whitespace, punctuation, digit, etc. will separate words.
An example would be this!is A&Word. This text would represent the 4 words this, is, A, and
Word. Each word should be converted to lower case so that only lower case letters remain.
Once all words have been read, the program will output the total number of words, total number of distinct words
and will then prompt the user to enter a word and it will report how many occurrences of the given word are in the file.
This will continue until the user enters a EOF character (Ctrl^C).

This word search also has wild card capabilities.
When the user enters a word to search for, a ‘?’ character may be present as some of the
letters for the search. This special character represents the ability to match any character,
including the empty character. For example, colo?r matches both "color" and "colour". This
query should report every word that matches. This means that the '?' must not be in the source input file.
