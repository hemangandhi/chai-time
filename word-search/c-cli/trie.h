
#ifndef __TRIE_INCL
#define __TRIE_INCL

typedef struct _TrieNode {
    struct _TrieNode * left, child;
    int words_ending_here;
    char edge_from_parent;
} TrieNode;

TrieNode * emptyTrie();
const char * addWord(const char * word, TrieNode * trie);
TrieNode * childAtChar(char c, TrieNode * trie);
void deleteTrie(TrieNode * whomst);

#endif
