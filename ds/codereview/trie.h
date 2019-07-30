/******************************************
*                _____  __     _   ___    *
*               (  _  )(  )   / ) / _ \   *
*    |\---/|     )(_)(  )(__ / _ \\_  /   *
*    | ,_, |    (_____)(____)\___/ (_/    *
*     \_`_/-..----.                       *
*  ___/ `   ' ,""+ \                      *
* (__...'   __\    |`.___.';              *
*  (_,...'(_,.`__)/'.....+                *
*                                         *
*             Exersice: TRIE              *
******************************************/
#ifndef OL69_TRIE_H
#define OL69_TRIE_H

#include <stdint.h> /* uint32_t */

typedef struct trie trie_t;

enum status_trie {SUCCESS = 0, FAILURE, M_FAIL};
typedef enum found {FALSE, TRUE} found_t;


/*num of bits is the number of bits that aren't masked by DHCP */
trie_t *TrieCreate(uint32_t num_of_bits);

/* returns num_of_bits given to the TrieCreate */
size_t TrieNumOfBits(const trie_t *trie);

void TrieDestroy(trie_t *trie);

/* Insert trie and an ip to insert */
/* returns status SUCCESS if succeeded */
/* returns status FAILURE if failed */
enum status_trie TrieInsert(trie_t *trie, uint32_t ip);

/* Removes ip Address from trie */
/* returns SUCCESS or FAILURE if couldn't remove */
enum status_trie TrieRemove(trie_t *trie, uint32_t ip);


/* If insert Failed, ask for another ip */
/* If succeeded, no need to use this function */
/* returns 0 address as a failure becuase 0 address always taken. */
uint32_t TrieNextFreeIp(const trie_t *trie);

/* count taken ip's */
uint32_t TrieCount(const trie_t * trie);

/* returns FALSE if found and ip is already taken */
/* returns TRUE if ip is free to use */
found_t TrieFind(const trie_t *trie, uint32_t ip);

/* if given trie is NULL behavior will be undefined at all functions*/

#endif /* OL69_TRIE_H */


