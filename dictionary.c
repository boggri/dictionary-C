// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> //
#include <string.h> //

#include "dictionary.h"

// Represents size of dictionary
unsigned int size_dict = 0;

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

bool rec_unload(node *ptr); // Prototype of my function. It's here cause it use node type. So we need to declare node first.

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO
        node *temp_ptr = root; // points to root
        if (file == NULL)
        {
            printf("Could not find root\n");
            unload();
            fclose(file);
            size_dict = 0;
            return false;
        }

        for (int i = 0, len = strlen(word); i < len; i++)
        {
            // poot '\'' at the end of node array (27'th symbol or 26 index)
             if (word[i] == '\'')
            {
                word[i] = 'z' + 1;
            }
            int index = word[i] - 'a'; // index of the curent letter in the array
            int last_w = len - 1; //  index of the last latter of the word in the for loop

            if (i != last_w) // if the curent letter isn't the last latter in the word do next
            {
                if (!(temp_ptr->children[index])) // chesk if children in curent node is NULL. If yes, then make malloc
                {
                    temp_ptr->children[index] = malloc(sizeof(node)); // create new node in the heap
                    if (!(temp_ptr->children[index])) // if malloc couldn't allocate the memory
                    {
                        fprintf(stderr, "Out of mamory\n");
                        unload();
                        fclose(file);
                        size_dict = 0;
                        return false;
                    }

                    // Initialize new node
                    temp_ptr->children[index]->is_word = false;
                    for (int j = 0; j < N; j++)
                    {
                        temp_ptr->children[index]->children[j] = NULL;
                    }
                }

                //  temp_ptr start's point to that new plase
                temp_ptr = temp_ptr->children[index];
            }
            else // if it's the last letter
            {
                if (!(temp_ptr->is_word)) // If is_word is false, make it true
                {
                    temp_ptr->is_word = true;
                    temp_ptr = NULL; // temp_ptr become a null-pointer for safety
                }
            }
        }

        // Count of words in dictionary
        size_dict++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (size_dict)
    {
        return size_dict;
    }
    else
    {
        return 0;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    node *ptr = root; // pointer to the root
    if (!ptr)
    {
        printf("Could not find root\n");
        return false;
    }

    int len = strlen(word);
    int last_char = len - 1; // index of the last character in the word
    char tmp_word[len+1];// temporary storage of string
    strcpy(tmp_word, word); // copy word to tmp_word

    // Chainge latters to lowercase and set '\'' to the end of the array index
    for (int i = 0; i < len; i++)
    {
        if (tmp_word[i] == '\'')
        {
            tmp_word[i] = 'z' + 1;
        }
        else if (isupper(tmp_word[i]))
        {
            tmp_word[i] = tolower(tmp_word[i]);
        }
    }

    // Check if the word is in the try
    for (int i = 0; i < len; i++)
    {
        if (i == last_char) // If it's the last character
        {
            if (ptr->is_word) // Check if this word is in the try
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else // If it isn't the last character
        {
            if (!(ptr->children[tmp_word[i] - 'a'])) // If there is no pass through - stop
            {
                return false;
            }
            else // If there is pass through - go
            {
                ptr = ptr->children[tmp_word[i] - 'a'];
            }
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *ptr = root;
    if (!ptr) // Error check
    {
        printf("Dictionari is not loaded\n");
        return false;
    }
    else
    {
        return rec_unload(ptr);
    }
}

bool rec_unload(node *ptr)
{
    for (int i = 0; i < N; i++) // Check each pointer in the node array
    {
        if (ptr->children[i])
        {
            rec_unload(ptr->children[i]); // Recursion (check each child pointer in the node array and delete all try)
        }

        if (i == N - 1) // If it is the last pointer in node - free this node and return true
        {
            free(ptr);
            return true;
        }
    }

    return false;
}
