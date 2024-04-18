#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET 26

// Trie structure
struct Trie
{	
struct Trie *children[ALPHABET];
int count;
};

// Initializes a trie structure
struct Trie *createTrie()
{
  struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
  if (pTrie) {
      pTrie->count = 0;
      for (int i = 0; i < ALPHABET; i++) {
          pTrie->children[i] = NULL;
      }
  }
  return pTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
  struct Trie *current = pTrie;
  int len = strlen(word);//get length
  for (int i = 0; i < len; i++) {
      int index = word[i] - 'a';//get index
      if (!current->children[index]) {
          current->children[index] = createTrie();//create trie for the index
      }
      current = current->children[index];
  }
  current->count++;//update count
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
  struct Trie *current = pTrie;
  int len = strlen(word);
  for (int i = 0; i < len; i++) {
      int index = word[i] - 'a';
      if (!current->children[index]) {
          return 0; //if word isnt found
      }
      current = current->children[index];
  }
  return current->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
for (int i = 0; i < ALPHABET; i++) 
{
  deallocateTrie(pTrie->children[i]);
} 
free(pTrie);

return pTrie;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
  FILE *file = fopen(filename, "r");
  if (!file) {
      perror("Error opening file");
      exit(EXIT_FAILURE);
  }

  int count = 0;
  char word[256];
  while (fscanf(file, "%s", word) != EOF) {
      pInWords[count] = strdup(word);
      count++;
  }

  fclose(file);
  return count;
}

int main(void)
{
  char *inWords[256];

  //read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i=0;i<numWords;++i)
  {
    printf("%s\n",inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i=0;i<numWords;i++)
  {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i=0;i<5;i++)
  {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}