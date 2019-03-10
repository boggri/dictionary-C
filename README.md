# dictionary-C
Programe that upload .txt dictionary file and check another texts in .txt format for words that isn't in the dictionari.

It uses trie data structure to upload dictionari in the RAM. And recursion to unload and free the mamory in heap.

directory ```kays/``` contains expected result of our output.

derectory ```dictionaries/``` contains 2 dictionaries small and large.

directory ```texts/``` contains texts that we wont to check.

to start the programe type: ```./speller texts/text_that_you_want_to_check.txt``` (in that case programe will upload by default large dictionary)

to start small dictionnary type: ```./speller dictionaries/small texts/text_that_you_want_to_check.txt```
