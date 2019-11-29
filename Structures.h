#ifndef BITCOINS_HASHTABLE_H
#define BITCOINS_HASHTABLE_H
struct time{
    int hour;
    int minute;
};
struct date{
    int day;
    int month;
    int year;
};
struct transaction{
    int amount_of_transaction;
    char transactionID[50];
    struct date date;
    struct time time;
};
typedef struct tree_node{
    char userID[50],received_from[50],send_to[50];
    struct transaction transaction;
    struct tree_node *left;
    struct tree_node *right;
}tree_node;

typedef struct ptr_to_tree_list{
    tree_node *ptr_to_tree;
    struct ptr_to_tree_list *next;
}ptr_to_tree_list_node;

typedef struct transaction_list_node{
    ptr_to_tree_list_node *list_of_ptrs_to_tree;
    struct transaction_list_node *next;
}transaction_node;

typedef struct block_content{
    char userID[50];
    transaction_node *transaction;
}block_content;

typedef struct hash_block{
    int records_in_block;
    block_content *content; //dynamic array
    struct hash_block *next; //to overflow
}block;


typedef struct tree_root{
    int bitcoinID;
    tree_node *tree_node;
}tree_root;

typedef struct bitcoin{
    unsigned int bitcoinID;
    unsigned int amount;
    struct bitcoin *next;
}bitcoin_info;
typedef struct wallet{
    char userID[50];
    int balance;
    bitcoin_info *list_of_bitcoins;
}wallet;

typedef struct wallet_block{
    int records_in_block;
    wallet wallet[10]; //each block in wallet hash table can have up to 10 wallets before overflow
    struct wallet_block *next; //to overflow
}wallet_block;

typedef struct tree_block{
    int records_in_block;
    tree_root root[10]; //each bucket in tree hash table can have up to 10 trees
    struct tree_block *next; //to overflow
}tree_block;


typedef struct list_of_strings{
    char string[200];
    struct list_of_strings *next;
}list_of_strings;
#endif
