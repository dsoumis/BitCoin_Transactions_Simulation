#ifndef BITCOINS_HASH_TABLE_IMPLEMENTATION_H
#define BITCOINS_HASH_TABLE_IMPLEMENTATION_H

#include "Structures.h"
#include "List_Implementation.h"
#include "Tree_Implementation.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
block* initialize_hashtable(int Hashtable1NumOfEntries,size_t bucketSize);
void insert_in_hashtable(block *HashTable,int Hashtable1NumOfEntries, char* userId,size_t bucketSize);
transaction_node*  find_specific_transaction_list_in_hashtable(block *HashTable,int Hashtable1NumOfEntries, char* userId,size_t bucketSize);
void delete_hashtable(block *HashTable,int Hashtable1NumOfEntries);
void initialize_wallet_hashtable(wallet_block *HashTable);
void initialize_tree_hashtable(tree_block *HashTable);
void insert_in_tree_hashtable(tree_block *HashTable,char* userid,int bitcoinId,int bitcoinvalue);
tree_node* find_tree_with_specific_bitcoin(tree_block *HashTable,int bitcoinID);
void print_tree_hashtabble(tree_block *HashTable);
void delete_tree_hashtable(tree_block *HashTable);
void insert_in_wallet_hashtable(wallet_block *HashTable,char* userId,unsigned int bitcoinid,unsigned int amount,bool new_entry);
void transaction_in_wallet_hashtable_and_all_structures(wallet_block *walletHashTable,char* sender,char* receiver,block* senderhashtable,
                                                        block* receiverhashtable,int senderHashtable1NumOfEntries,int receiverHashtable1NumOfEntries,size_t bucketSize,struct transaction transaction,tree_block *treehashtable);
void print_wallet_hashtabble(wallet_block *HashTable);
void delete_wallet_hashtable(wallet_block *HashTable);
void print_specific_transaction_list_of_hashtable(block *HashTable,char* userId,struct time time_begin,struct time time_end,
                                                           struct date date_begin,struct date date_end,int Hashtable1NumOfEntries,short int sender);
void print_balance_of_user(wallet_block *HashTable, char* userid);
#endif //BITCOINS_HASH_TABLE_IMPLEMENTATION_H
