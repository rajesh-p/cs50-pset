/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>


#define SIZE 50
#define dictsize 5000

//define count variable
int wordcount =0;

typedef struct node
{
    // the value to store in this node
    char word[SIZE+1];

    // the link to the next node in the list
    struct node* next;
}
node;

node* head = NULL;

//hashtable assign
node* hashtable[dictsize];

//
#include "dictionary.h"

//write hashable function
int hv(char* str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++) != 0)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % dictsize;
}



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    
    // TODO
    char *wordC = malloc(strlen(word)+1);
    strcpy(wordC,word);
    
    for(int i = 0; wordC[i]; i++){
        wordC[i] = tolower(wordC[i]);
    }
    
    int index = hv(wordC);

    for (node*  ptr = hashtable[index]; ptr != NULL; ptr = ptr->next)
    {
        //printf("%s\n", ptr->word);
        if(!(strcmp(ptr->word,wordC))) {
            return true;
        }
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    int hash_index = 0;
    
    char f_word[50];

    
    FILE* fp = fopen(dictionary, "r");
    if(fp == NULL) {
        return false;
    }
    else {
        while (fscanf(fp, "%s", f_word) != EOF)
        {
            //create new node
            node *new = malloc(sizeof(node));
            
            hash_index = hv(f_word);
            
            //head = hashtable[hash_index];
            
            //printf("%d ", hash_index);
            if(hashtable[hash_index] == NULL) {
                
                hashtable[hash_index] = new;
                strcpy(new->word,f_word);
                new->next = NULL;
                //printf("%s ", new->word);
                wordcount++;
            }
            else {
                // printf("%s ", temp->word);
                new->next = hashtable[hash_index];
                hashtable[hash_index] = new;
                strcpy(new->word,f_word);
                wordcount++;
            }
            
        }
        //return true;
        fclose(fp);
        return(true);
    }
    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return wordcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    for(int i=0; i < dictsize; i++) {
        if(hashtable[i]->next != NULL)
        {
            for (node*  ptr = hashtable[i]; ptr != NULL; ptr = ptr->next)
            {
                free(ptr);
            }
        }
    }
    
    return true;
}
