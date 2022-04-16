// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h> 
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"
#include <ctype.h> 

int totalWords = 0; 

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 150000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //hash the word to obtain a hash value 
    int hashValue = hash(word);
    
    //access the linked list at that hash table at that particular index in your hash table
    node *n = table[hashValue]; 
    
    //traverse through the linked list looking for the word 
    while (n != NULL)
    {

        //if the word matches 
        if (strcasecmp(word, n -> word) == 0)
        {
            return true;
        }
        
        //if the word isn't found yet 
        n = n -> next; 
    
    }
    
    return false;

}

/* Hashes word to a number Hash Table by Daniel J. Bernstein: http://www.cse.yorku.ca/~oz/hash.html "djb2"  
and by u/SocratesSatisfied Simplified Hash Function https://www.reddit.com/r/cs50/comments/eo4zro/good_hash_function_for_speller/?utm_source=share&utm_medium=web2x&context=3 */
unsigned int hash(const char *word)
{

    unsigned long hash = 5381;
    int c = *word;
    c = tolower(c);

    while (*word != 0)

    {

        hash = ((hash << 5) + hash) + c;
        c = *word++;
        c = tolower(c);

    }

    return hash % N;

}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //open up the dictionary file 
    FILE *ptr = fopen(dictionary, "r");
    
    //if the return value is null 
    if (ptr == NULL)
    {
        return false; 
    }
    
    //temp word
    char tempWord[LENGTH + 1]; 
    
    //reads strings from file into word until the end of file 
    while (fscanf(ptr, "%s", tempWord) == 1)
    {
        //creates a new node to insert the word from the dictionary 
        node *n = malloc(sizeof(node));
        
        if (n == NULL)
        {
            return false; 
        }
        
        //copies the word into the new node 
        strcpy(n -> word, tempWord);
        
        //gets the hash value 
        int hashValue = hash(tempWord);
        
        //puts the node into the location of the hash value 
        n -> next = table[hashValue];  
        
        //update the pointer equal to whatever n is
        table[hashValue] = n;

        totalWords++;

    }
    
    fclose(ptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (totalWords > 0)
    {
        return totalWords;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) //https://www.reddit.com/r/cs50/comments/lrgexp/speller_has_no_output/: u/stuPenndous
    {
        //sets the cursor to the hash table
        node *cursor = table[i];
        node *tmp = cursor; 
        
        while (cursor != NULL)
        {
            //points the tmp to the next node 
            //Line 149 taken from: https://www.facebook.com/groups/cs50/permalink/1707640692716302/: User Anthony Richards
            cursor = cursor -> next; 
            free(tmp); 
            tmp = cursor; 
            
        }
        
    }

    return true; 
}

