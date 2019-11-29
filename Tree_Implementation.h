#ifndef BITCOINS_TREE_IMPLEMENTATION_H
#define BITCOINS_TREE_IMPLEMENTATION_H

#include "Structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
tree_node* insert_in_tree(tree_node* root_node,char* senderId,char *ReceiverId,int amount,struct date date,struct time time,char* transactionID);
void printPreorder(tree_node* node);
void delete_tree(tree_node* node);
void bitcoinstatus(tree_node* node,int *number_of_transactions,int *unspent_amount);
void tracecoin(tree_node* node);
#endif
