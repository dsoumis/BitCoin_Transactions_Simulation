#ifndef BITCOINS_LIST_IMPLEMENTATION_H
#define BITCOINS_LIST_IMPLEMENTATION_H

#include "Structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void insert_in_transaction_list(transaction_node** list, tree_node** treeNode,int number_of_treenodes);
void find_in_list(transaction_node* list);
void delete_transaction_list(transaction_node **list);
void insert_in_list_of_bitcoins(bitcoin_info** list,unsigned int bitcoinid, unsigned int amount);
void print_list_of_bitcoins(bitcoin_info* list);
void delete_list_of_bitcoins(bitcoin_info **list);
void transaction_in_list_of_bitcoins(bitcoin_info** list,bitcoin_info **bitcoins_of_transaction_sender,int amount);
int length_of_bitcoin_list(bitcoin_info* list);
void print_transaction_list(transaction_node* list,short int sender);
short int find_in_list_of_bitcoins(bitcoin_info *list,int bitcoinID);
void insert_in_list_of_strings(list_of_strings **list, char* string);
void delete_list_of_strings(list_of_strings **list);
void print_list_of_strings(list_of_strings *list);
void specific_print_ptrs_to_tree_list(ptr_to_tree_list_node* list,char* userId, short int sender);
void insert_in_list_of_bitcoins_transaction(bitcoin_info** list,unsigned int bitcoinid, unsigned int amount);
#endif //BITCOINS_LIST_IMPLEMENTATION_H
