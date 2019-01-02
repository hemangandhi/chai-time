
#include "trie.h"
#include <stdlib.h>

TrieNode * emptyTrie(){
    TrieNode * rv = malloc(sizeof(TrieNode));
    if(rv){
        rv->left = NULL;
        rv->child = rv;
        rv->words_ending_here = 0;
        rv->edge_from_parent = '\0';
    }
    return rv;
}

TrieNode * childAtChar(char c, TrieNode * trie){
    TrieNode * candidate = trie->child;
    for(;candidate != NULL && candidate->edge_from_parent != c; candidate = candidate->left);
    return candidate;
}

const char * addWord(const char * word, TrieNode * trie){
    for(;*word != '\0'; word++){
        TrieNode * thingy = childAtChar(*word, trie);
        if(!thingy){
            TrieNode * new = malloc(sizeof(TrieNode));
            if(!new) return word;

            new->left = trie->child;
            new->child = new;
            trie->child = new;
            new->edge_from_parent = *word;
            trie = new;
        }else{
            trie = thingy;
        }
    }
    trie->words_ending_here++;
    return word;
}

void deleteTrie(TrieNode * whomst){
    //just a technicality in case whomst isn't the root.
    for(TrieNode * lc = whomst->left; lc != NULL;){
        if(lc->child == lc){
            TrieNode * t = lc->left;
            free(lc);
            lc = t;
        }else{
            TrieNode * heir = whomst->child;
            whomst->child = lc->child;
            lc->child = heir;
            lc = lc->left;
        }
    }

    for(TrieNode * whomstdve = whomst->child; whomst->child != whomst; whomstdve = whomst->child){
        for(TrieNode * lc = whomstdve->left; lc != NULL;){
            if(lc->child == lc){
                TrieNode * t = lc->left;
                free(lc);
                lc = t;
            }else{
                TrieNode * heir = whomstdve->child;
                whomstdve->child = lc->child;
                lc->child = heir;
                lc = lc->left;
            }
        }

        //we are now sure whomstdve has no immediate left (sibling) nodes.
        whomst->child = whomstdve->child;
        free(whomstdve);
    }
    free(whomst);
}
