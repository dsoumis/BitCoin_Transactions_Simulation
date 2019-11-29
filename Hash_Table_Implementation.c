#include "Hash_Table_Implementation.h"

unsigned long hash_function(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
} //Hash function from the class of YSBD
void print_specific_transaction_list_of_hashtable(block *HashTable,char* userId,struct time time_begin,struct time time_end,
        struct date date_begin,struct date date_end,int Hashtable1NumOfEntries,short int sender){
    int pos_in_HashTable=hash_function((unsigned char*)userId)%Hashtable1NumOfEntries; //With the hash function find the proper cell in hash table for the current entry
    transaction_node *temp;
    ptr_to_tree_list_node *temp2;
    int sum=0;

    //In the following I analyze all the cases of the input. First I calculate the sum and then print.
    for(int i=0; i<HashTable[pos_in_HashTable].records_in_block; i++){
        if(strcmp(HashTable[pos_in_HashTable].content[i].userID,userId)==0){

            if(time_begin.hour==-1 && date_begin.year==-1){ //if no time nor date were given
                temp=HashTable[pos_in_HashTable].content[i].transaction;
                while (temp!=NULL){
                    temp2=temp->list_of_ptrs_to_tree;
                    while (temp2!=NULL){
                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                        temp2=temp2->next;
                    }
                    temp=temp->next;
                }
            }else if(time_begin.hour!=-1 && date_begin.year==-1){ //if time is given but no date
                temp=HashTable[pos_in_HashTable].content[i].transaction;
                while (temp!=NULL){
                    temp2=temp->list_of_ptrs_to_tree;
                    while (temp2!=NULL){
                        if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                            }
                        }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                            if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                }
                            }
                        }
                        temp2=temp2->next;
                    }
                    temp=temp->next;
                }
            } else if(time_begin.hour==-1 && date_begin.year!=-1){//if date is given but no time
                temp=HashTable[pos_in_HashTable].content[i].transaction;
                while (temp!=NULL){
                    temp2=temp->list_of_ptrs_to_tree;
                    while (temp2!=NULL){
                        if(temp2->ptr_to_tree->transaction.date.year>date_begin.year) {
                            if(temp2->ptr_to_tree->transaction.date.year<date_end.year)
                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                            else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                if(temp2->ptr_to_tree->transaction.date.month<date_end.month)
                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                    if(temp2->ptr_to_tree->transaction.date.day<=date_end.day)
                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                }
                            }
                        }else if(temp2->ptr_to_tree->transaction.date.year==date_begin.year){
                            if(temp2->ptr_to_tree->transaction.date.month>date_begin.month){
                                if(temp2->ptr_to_tree->transaction.date.year<date_end.year)
                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                    if(temp2->ptr_to_tree->transaction.date.month<date_end.month)
                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                    else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                        if(temp2->ptr_to_tree->transaction.date.day<=date_end.day)
                                            sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                    }
                                }
                            }else if(temp2->ptr_to_tree->transaction.date.month==date_begin.month){
                                if(temp2->ptr_to_tree->transaction.date.day>=date_begin.day){
                                    if(temp2->ptr_to_tree->transaction.date.year<date_end.year)
                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                    else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                        if(temp2->ptr_to_tree->transaction.date.month<date_end.month)
                                            sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                        else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                            if(temp2->ptr_to_tree->transaction.date.day<=date_end.day)
                                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                        }
                                    }
                                }
                            }
                        }
                        temp2=temp2->next;
                    }
                    temp=temp->next;
                }
            }else if(time_begin.hour!=-1 && date_begin.year!=-1){ //if both date and time are given
                temp=HashTable[pos_in_HashTable].content[i].transaction;
                while (temp!=NULL){
                    temp2=temp->list_of_ptrs_to_tree;
                    while (temp2!=NULL){
                        if(temp2->ptr_to_tree->transaction.date.year>date_begin.year) {
                            if(temp2->ptr_to_tree->transaction.date.year<date_end.year) {
                                if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                    if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                    else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                        if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                            sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                    }
                                }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                    if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                        if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                            sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                        else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                        }
                                    }
                                }
                            }
                            else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                if(temp2->ptr_to_tree->transaction.date.month<date_end.month) {
                                    if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                        if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                            sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                        else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                        }
                                    }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                        if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                            }
                                        }
                                    }
                                }
                                else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                    if(temp2->ptr_to_tree->transaction.date.day<=date_end.day) {
                                        if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                            }
                                        }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }else if(temp2->ptr_to_tree->transaction.date.year==date_begin.year){
                            if(temp2->ptr_to_tree->transaction.date.month>date_begin.month){
                                if(temp2->ptr_to_tree->transaction.date.year<date_end.year) {
                                    if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                        if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                            sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                        else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                        }
                                    }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                        if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                            }
                                        }
                                    }
                                }
                                else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                    if(temp2->ptr_to_tree->transaction.date.month<date_end.month) {
                                        if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                            }
                                        }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                }
                                            }
                                        }
                                    }
                                    else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                        if(temp2->ptr_to_tree->transaction.date.day<=date_end.day) {
                                            if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                }
                                            }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                    if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                    else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                        if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                            sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }else if(temp2->ptr_to_tree->transaction.date.month==date_begin.month){
                                if(temp2->ptr_to_tree->transaction.date.day>=date_begin.day){
                                    if(temp2->ptr_to_tree->transaction.date.year<date_end.year) {
                                        if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                            }
                                        }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                }
                                            }
                                        }
                                    }
                                    else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                        if(temp2->ptr_to_tree->transaction.date.month<date_end.month) {
                                            if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                    sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                }
                                            }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                    if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                    else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                        if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                            sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                    }
                                                }
                                            }
                                        }
                                        else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                            if(temp2->ptr_to_tree->transaction.date.day<=date_end.day) {
                                                if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                                    if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                        sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                    else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                        if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                            sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                    }
                                                }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                        if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                            sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                        else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                            if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                                sum+=temp2->ptr_to_tree->transaction.amount_of_transaction;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        temp2=temp2->next;
                    }
                    temp=temp->next;
                }
            }
            printf("Sum of transactions of %s is %d\n",userId,sum);


            if(time_begin.hour==-1 && date_begin.year==-1){ //if no time nor date were given
                temp=HashTable[pos_in_HashTable].content[i].transaction;
                while (temp!=NULL){
                    temp2=temp->list_of_ptrs_to_tree;
                    while (temp2!=NULL){
                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                        temp2=temp2->next;
                    }
                    temp=temp->next;
                }
            }else if(time_begin.hour!=-1 && date_begin.year==-1){
                temp=HashTable[pos_in_HashTable].content[i].transaction;
                while (temp!=NULL){
                    temp2=temp->list_of_ptrs_to_tree;
                    while (temp2!=NULL){
                        if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                            }
                        }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                            if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                }
                            }
                        }
                        temp2=temp2->next;
                    }
                    temp=temp->next;
                }
            } else if(time_begin.hour==-1 && date_begin.year!=-1){
                temp=HashTable[pos_in_HashTable].content[i].transaction;
                while (temp!=NULL){
                    temp2=temp->list_of_ptrs_to_tree;
                    while (temp2!=NULL){
                        if(temp2->ptr_to_tree->transaction.date.year>date_begin.year) {
                            if(temp2->ptr_to_tree->transaction.date.year<date_end.year)
                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                            else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                if(temp2->ptr_to_tree->transaction.date.month<date_end.month)
                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                    if(temp2->ptr_to_tree->transaction.date.day<=date_end.day)
                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                }
                            }
                        }else if(temp2->ptr_to_tree->transaction.date.year==date_begin.year){
                            if(temp2->ptr_to_tree->transaction.date.month>date_begin.month){
                                if(temp2->ptr_to_tree->transaction.date.year<date_end.year)
                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                    if(temp2->ptr_to_tree->transaction.date.month<date_end.month)
                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                    else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                        if(temp2->ptr_to_tree->transaction.date.day<=date_end.day)
                                            specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                    }
                                }
                            }else if(temp2->ptr_to_tree->transaction.date.month==date_begin.month){
                                if(temp2->ptr_to_tree->transaction.date.day>=date_begin.day){
                                    if(temp2->ptr_to_tree->transaction.date.year<date_end.year)
                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                    else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                        if(temp2->ptr_to_tree->transaction.date.month<date_end.month)
                                            specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                        else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                            if(temp2->ptr_to_tree->transaction.date.day<=date_end.day)
                                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                        }
                                    }
                                }
                            }
                        }
                        temp2=temp2->next;
                    }
                    temp=temp->next;
                }
            }else if(time_begin.hour!=-1 && date_begin.year!=-1){
                temp=HashTable[pos_in_HashTable].content[i].transaction;
                while (temp!=NULL){
                    temp2=temp->list_of_ptrs_to_tree;
                    while (temp2!=NULL){
                        if(temp2->ptr_to_tree->transaction.date.year>date_begin.year) {
                            if(temp2->ptr_to_tree->transaction.date.year<date_end.year) {
                                if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                    if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                    else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                        if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                            specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                    }
                                }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                    if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                        if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                            specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                        else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                        }
                                    }
                                }
                            }
                            else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                if(temp2->ptr_to_tree->transaction.date.month<date_end.month) {
                                    if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                        if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                            specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                        else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                        }
                                    }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                        if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                            }
                                        }
                                    }
                                }
                                else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                    if(temp2->ptr_to_tree->transaction.date.day<=date_end.day) {
                                        if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                            }
                                        }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }else if(temp2->ptr_to_tree->transaction.date.year==date_begin.year){
                            if(temp2->ptr_to_tree->transaction.date.month>date_begin.month){
                                if(temp2->ptr_to_tree->transaction.date.year<date_end.year) {
                                    if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                        if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                            specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                        else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                        }
                                    }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                        if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                            }
                                        }
                                    }
                                }
                                else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                    if(temp2->ptr_to_tree->transaction.date.month<date_end.month) {
                                        if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                            }
                                        }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                }
                                            }
                                        }
                                    }
                                    else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                        if(temp2->ptr_to_tree->transaction.date.day<=date_end.day) {
                                            if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                }
                                            }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                    if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                    else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                        if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                            specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }else if(temp2->ptr_to_tree->transaction.date.month==date_begin.month){
                                if(temp2->ptr_to_tree->transaction.date.day>=date_begin.day){
                                    if(temp2->ptr_to_tree->transaction.date.year<date_end.year) {
                                        if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                            if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                            else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                            }
                                        }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                            if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                }
                                            }
                                        }
                                    }
                                    else if(temp2->ptr_to_tree->transaction.date.year==date_end.year){
                                        if(temp2->ptr_to_tree->transaction.date.month<date_end.month) {
                                            if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                                if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                    specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                }
                                            }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                                if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                    if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                    else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                        if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                            specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                    }
                                                }
                                            }
                                        }
                                        else if(temp2->ptr_to_tree->transaction.date.month==date_end.month){
                                            if(temp2->ptr_to_tree->transaction.date.day<=date_end.day) {
                                                if(temp2->ptr_to_tree->transaction.time.hour>time_begin.hour) {
                                                    if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                        specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                    else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                        if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                            specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                    }
                                                }else if(temp2->ptr_to_tree->transaction.time.hour==time_begin.hour){
                                                    if(temp2->ptr_to_tree->transaction.time.minute>=time_begin.minute){
                                                        if(temp2->ptr_to_tree->transaction.time.hour<time_end.hour)
                                                            specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                        else if(temp2->ptr_to_tree->transaction.time.hour==time_end.hour){
                                                            if(temp2->ptr_to_tree->transaction.time.minute<=time_end.minute)
                                                                specific_print_ptrs_to_tree_list(temp2,userId,sender);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        temp2=temp2->next;
                    }
                    temp=temp->next;
                }
            }
        }
    }
}

//Initialize the hash tables with senderHashtable1NumOfEntries/receiverHashtable1NumOfEntries buckets of size bucketSize
block* initialize_hashtable(int Hashtable1NumOfEntries,size_t bucketSize){
    block *HashTable;
    HashTable= malloc((size_t)Hashtable1NumOfEntries*bucketSize); //Create positions for the hashtable
    if(HashTable == NULL){ //Error checking
        perror("Memory not allocated.");
        exit(-1);
    }

    int number_of_records_in_block=(int) (bucketSize-sizeof(int)-sizeof(block *))/(int) sizeof(block_content);//See struct hash_block in Structures.h.Number of records that are allowed in a block

    for(int i=0; i<Hashtable1NumOfEntries; i++){
        HashTable[i].records_in_block=0;
        HashTable[i].next=NULL;
        HashTable[i].content=malloc(number_of_records_in_block * sizeof(block_content));
        for(int j=0; j<number_of_records_in_block; j++){
            HashTable[i].content[j].transaction=NULL;
        }
    }

    return HashTable;
}

void insert_in_hashtable(block *HashTable,int Hashtable1NumOfEntries, char* userId,size_t bucketSize){
    int pos_in_HashTable=hash_function((unsigned char*)userId)%Hashtable1NumOfEntries; //With the hash function find the proper cell in hash table for the current entry
    if(pos_in_HashTable<0 || pos_in_HashTable>Hashtable1NumOfEntries){
        printf("WTF!");
        exit(-1);
    }
    int number_of_records_in_block=(int) (bucketSize-sizeof(int)-sizeof(block *))/(int) sizeof(block_content);//See struct hash_block in Structures.h.Number of records that are allowed in a block
    //printf("no of records %d\n",number_of_records_in_block);
    block *ht;
    for(int i=0; i<HashTable[pos_in_HashTable].records_in_block; i++){ //If user already exists
        if(strcmp(HashTable[pos_in_HashTable].content[i].userID,userId)==0)
            return;
    }
    if(HashTable[pos_in_HashTable].records_in_block<number_of_records_in_block){ //If the entry can be entered at the first block of the cell of the hash table
        //printf("%s in pos %d with %d-%d\n",userId,pos_in_HashTable,HashTable[pos_in_HashTable].records_in_block,number_of_records_in_block);
        strcpy(HashTable[pos_in_HashTable].content[HashTable[pos_in_HashTable].records_in_block].userID,userId);
        HashTable[pos_in_HashTable].records_in_block++;
        return;



    }else{ //If the first block is full
        ht=HashTable[pos_in_HashTable].next;
        if(ht==NULL){ //If no overflow block has been created yet
            ht=malloc(bucketSize);
            if(ht == NULL){
                perror("Memory not allocated.");
                exit(-1);
            }

            ht->content=malloc(number_of_records_in_block * sizeof(block_content));
            if(ht->content == NULL){
                perror("Memory not allocated.");
                exit(-1);
            }
            for(int i=0; i<number_of_records_in_block; i++) {
                ht->content[i].transaction=NULL;
            }
            ht->records_in_block=0;
            HashTable[pos_in_HashTable].next=ht; //Connect the first block with current
        }else {
            for(int i=0; i<ht->records_in_block; i++){
                if(strcmp(ht->content[i].userID,userId)==0)
                    return;
            }
            while (ht->records_in_block == number_of_records_in_block) {
                if (ht->next == NULL) { //If all blocks are full create a new one

                    ht->next = malloc(bucketSize);
                    if (ht->next == NULL) {
                        perror("Memory not allocated.");
                        exit(-1);
                    }

                    ht->next->content = malloc(number_of_records_in_block * sizeof(block_content));
                    if (ht->next->content == NULL) {
                        perror("Memory not allocated.");
                        exit(-1);
                    }
                    for (int i = 0; i < number_of_records_in_block; i++) {
                        ht->next->content[i].transaction=NULL;
                    }
                    ht->next->records_in_block = 0;
                }
                ht = ht->next;
                for(int i=0; i<ht->records_in_block; i++){
                    if(strcmp(ht->content[i].userID,userId)==0)
                        return;
                }
            }
        }
        //printf("%s in oveflow pos %d\n",userId,pos_in_HashTable);
        strcpy(ht->content[ht->records_in_block].userID,userId);
        ht->records_in_block++;
        return;
    }

}
void insert_specific_transaction_list_in_hashtable(block *HashTable,int Hashtable1NumOfEntries, char* userId,size_t bucketSize,tree_node** treeNode,int number_of_treenodes){
    int pos_in_HashTable=hash_function((unsigned char*)userId)%Hashtable1NumOfEntries; //With the hash function find the proper cell in hash table for the current entry
    block *ht;
    for(int i=0; i<HashTable[pos_in_HashTable].records_in_block; i++){
        if(strcmp(userId,HashTable[pos_in_HashTable].content[i].userID)==0){
            insert_in_transaction_list(&HashTable[pos_in_HashTable].content[i].transaction,treeNode,number_of_treenodes);
        }
    }
    ht=HashTable[pos_in_HashTable].next;
    while(ht!=NULL){
        for(int i=0; i<ht->records_in_block; i++){
            if(strcmp(userId,HashTable[pos_in_HashTable].content[i].userID)==0){
                printf("In overflow block %d is %s\n",pos_in_HashTable,userId);
                insert_in_transaction_list(&ht->content[i].transaction,treeNode,number_of_treenodes);
            }
        }
        ht=ht->next;
    }
}
transaction_node* find_specific_transaction_list_in_hashtable(block *HashTable,int Hashtable1NumOfEntries, char* userId,size_t bucketSize){
    int pos_in_HashTable=hash_function((unsigned char*)userId)%Hashtable1NumOfEntries; //With the hash function find the proper cell in hash table for the current entry
    int number_of_records_in_block=(int) (bucketSize-sizeof(int)-sizeof(block *))/(int) sizeof(block_content);//See struct hash_block in Structures.h.Number of records that are allowed in a block
    block *ht;
    for(int i=0; i<number_of_records_in_block; i++){
        if(strcmp(userId,HashTable[pos_in_HashTable].content[i].userID)==0){
            return HashTable[pos_in_HashTable].content[i].transaction;
        }
    }
    ht=HashTable[pos_in_HashTable].next;
    while(ht!=NULL){
        for(int i=0; i<number_of_records_in_block; i++){
            if(strcmp(userId,HashTable[pos_in_HashTable].content[i].userID)==0){
                //printf("In overflow block %d is %s\n",pos_in_HashTable,userId);
                return ht->content[i].transaction;
            }
        }
        ht=ht->next;
    }
    return NULL;
}

void delete_hashtable(block *HashTable,int Hashtable1NumOfEntries){
    block *temp,*ht;
    for(int i=0; i<Hashtable1NumOfEntries; i++){
        for(int j=0; j<HashTable[i].records_in_block; j++){
            delete_transaction_list(&HashTable[i].content[j].transaction);//first delete the transaction list
        }
        free(HashTable[i].content);
        ht=HashTable[i].next;
        while(ht!=NULL){
            for(int j=0; j<ht->records_in_block; j++){
                delete_transaction_list(&ht->content[j].transaction);//first delete the transaction list
            }
            free(ht->content);
            temp=ht;
            ht=ht->next;
            free(temp);
        }
    }
    free(HashTable);
}

void initialize_tree_hashtable(tree_block *HashTable){
    for(int i=0; i<10; i++){
        HashTable[i].next=NULL;
        HashTable[i].records_in_block=0;
        for(int j=0; j<10; j++) {
            HashTable[i].root->tree_node=NULL;
        }
    }
}
void insert_in_tree_hashtable(tree_block *HashTable,char* userid,int bitcoinId,int bitcoinvalue){
    char bitcoinID_to_str[50];
    sprintf(bitcoinID_to_str,"%d",bitcoinId);
    int pos_in_HashTable=hash_function((unsigned char*)bitcoinID_to_str)%10; //With the hash function find the proper cell in hash table for the current entry
    if(pos_in_HashTable<0 || pos_in_HashTable>10){
        printf("WTF!");
        exit(-1);
    }



    tree_block *ht;
    if(HashTable[pos_in_HashTable].records_in_block<10){ //If the entry can be entered at the first block of the cell of the hash table
        HashTable[pos_in_HashTable].root[HashTable[pos_in_HashTable].records_in_block].bitcoinID=bitcoinId;

        tree_node* node = malloc(sizeof(tree_node));
        strcpy(node->userID,userid); //Copy the values of the transaction
        strcpy(node->received_from,"noone");
        node->transaction.amount_of_transaction=bitcoinvalue;
        node->transaction.date.day=0;
        node->transaction.date.month=0;
        node->transaction.date.year=0;
        node->transaction.time.hour=0;
        node->transaction.time.minute=0;
        strcpy(node->transaction.transactionID,"nothing");
        node->left=NULL;
        node->right=NULL;
        HashTable[pos_in_HashTable].root[HashTable[pos_in_HashTable].records_in_block].tree_node=node;
        HashTable[pos_in_HashTable].records_in_block++;
    }else{ //If the first block is full
        ht=HashTable[pos_in_HashTable].next;
        if(ht==NULL){ //If no overflow block has been created yet
            ht=malloc(sizeof(tree_block));
            if(ht == NULL){
                perror("Memory not allocated.");
                exit(-1);
            }
            ht->records_in_block=0;
            HashTable[pos_in_HashTable].next=ht; //Connect the first block with current
        }else {
            while (ht->records_in_block == 10) {
                if (ht->next == NULL) { //If all blocks are full create a new one

                    ht->next = malloc(sizeof(tree_block));
                    if (ht->next == NULL) {
                        perror("Memory not allocated.");
                        exit(-1);
                    }
                    ht->next->records_in_block = 0;
                }
                ht = ht->next;
            }
        }
        ht->root[ht->records_in_block].bitcoinID=bitcoinId;
        tree_node* node = malloc(sizeof(tree_node));
        strcpy(node->userID,"noone"); //Copy the values of the transaction
        strcpy(node->received_from,"noone");
        node->transaction.amount_of_transaction=bitcoinvalue;
        node->transaction.date.day=0;
        node->transaction.date.month=0;
        node->transaction.date.year=0;
        node->transaction.time.hour=0;
        node->transaction.time.minute=0;
        strcpy(node->transaction.transactionID,"nothing");
        node->left=NULL;
        node->right=NULL;
        ht->root[ht->records_in_block].tree_node=node;
        ht->records_in_block++;
    }
}
void print_tree_hashtabble(tree_block *HashTable){
    tree_block* ht;
    for(int i=0; i<10; i++){
        for(int j=0; j<HashTable[i].records_in_block; j++){
            printf("Root with bitcoin %d and amount %d and user %s\n",HashTable[i].root[j].bitcoinID,HashTable[i].root[j].tree_node->transaction.amount_of_transaction,HashTable[i].root[j].tree_node->userID);
        }
        ht=HashTable[i].next;
        while (ht!=NULL){
            for(int j=0; j<ht->records_in_block; j++){
                printf("Root with bitcoin %d and amount %d and user %s\n",ht->root[j].bitcoinID,ht->root[j].tree_node->transaction.amount_of_transaction,ht->root[j].tree_node->userID);
            }
            ht=ht->next;
        }
    }
}
tree_node* find_tree_with_specific_bitcoin(tree_block *HashTable,int bitcoinID){
    char bitcoinID_to_str[50];
    sprintf(bitcoinID_to_str,"%d",bitcoinID);
    int pos_in_HashTable=hash_function((unsigned char*)bitcoinID_to_str)%10; //With the hash function find the proper cell in hash table for the current entry
    if(pos_in_HashTable<0 || pos_in_HashTable>10){
        printf("WTF!");
        exit(-1);
    }
    for(int i=0; i<HashTable[pos_in_HashTable].records_in_block; i++){
        if(bitcoinID==HashTable[pos_in_HashTable].root[i].bitcoinID) { //if bitcoinid matches the one we want return the first node of the tree
            return HashTable[pos_in_HashTable].root[i].tree_node;
        }
    }
    tree_block *ht;
    ht=HashTable[pos_in_HashTable].next; //to overflow blocks
    while (ht!=NULL){
        for(int i=0; i<ht->records_in_block; i++){
            if(bitcoinID==ht->root[i].bitcoinID)//if bitcoinid matches the one we want return the first node of the tree
                return ht->root[i].tree_node;
        }
        ht=ht->next;
    }
    return NULL;
}
void delete_tree_hashtable(tree_block *HashTable){
    tree_block *temp,*ht;
    for(int i=0; i<10; i++){
        for(int j=0; j<HashTable[i].records_in_block; j++){
            //free tree
            delete_tree(HashTable[i].root[j].tree_node);
        }
        ht=HashTable[i].next;
        while(ht!=NULL){
            for(int j=0; j<ht->records_in_block; j++){
                //free tree
                delete_tree(ht->root[j].tree_node);
            }
            temp=ht;
            ht=ht->next;
            free(temp);
        }
    }
}

void initialize_wallet_hashtable(wallet_block *HashTable){
    for(int i=0; i<10; i++){
        HashTable[i].next=NULL;
        HashTable[i].records_in_block=0;
        for(int j=0; j<10; j++) {
            HashTable[i].wallet[j].list_of_bitcoins = NULL;
            HashTable[i].wallet[j].balance = 0;
        }
    }
}
void insert_in_wallet_hashtable(wallet_block *HashTable,char* userId,unsigned int bitcoinid,unsigned int amount,bool new_entry){
    int pos_in_HashTable=hash_function((unsigned char*)userId)%10; //With the hash function find the proper cell in hash table for the current entry
    if(pos_in_HashTable<0 || pos_in_HashTable>10){
        printf("WTF!");
        exit(-1);
    }

    if(new_entry==false){ //only add bitcoin to user and modify the balance
        wallet_block *ht;
        for(int k=0; k<10; k++){//check if bitcoin already exists
            for(int i=0; i<HashTable[k].records_in_block; i++){
                if(find_in_list_of_bitcoins(HashTable[k].wallet[i].list_of_bitcoins,bitcoinid)==1){
                    printf("Bitcoin %d already exists!Abort.\n",bitcoinid);
                    return;
                }
            }
            ht=HashTable[k].next;
            while (ht!=NULL){
                for(int i=0; i<ht->records_in_block; i++){
                    if(find_in_list_of_bitcoins(ht->wallet[i].list_of_bitcoins,bitcoinid)==1){
                        printf("Bitcoin %d already exists!Abort.\n",bitcoinid);
                        return;
                    }
                }
                ht=ht->next;
            }
        }



        for(int i=0; i<HashTable[pos_in_HashTable].records_in_block; i++) {

            if(strcmp(HashTable[pos_in_HashTable].wallet[i].userID,userId)==0){
                HashTable[pos_in_HashTable].wallet[i].balance+=amount;
                insert_in_list_of_bitcoins(&HashTable[pos_in_HashTable].wallet[i].list_of_bitcoins,bitcoinid,amount);
                return;
            }
        }

        ht=HashTable[pos_in_HashTable].next;
        while (ht!=NULL){
            for(int i=0; i<ht->records_in_block; i++) {
                if(strcmp(ht->wallet[i].userID,userId)==0){
                    ht->wallet[i].balance+=amount;
                    insert_in_list_of_bitcoins(&ht->wallet[i].list_of_bitcoins,bitcoinid,amount);
                    return;
                }
            }
            ht=ht->next;
        }
        return;
    }


    wallet_block *ht;
    for(int i=0; i<HashTable[pos_in_HashTable].records_in_block; i++){ //Check if the userID or bitcoin already exists
        if(strcmp(HashTable[pos_in_HashTable].wallet[i].userID,userId)==0){
            printf("UserID %s already exists! Abort!\n",userId);
            return;
        }
    }
    if(HashTable[pos_in_HashTable].records_in_block<10){ //If the entry can be entered at the first block of the cell of the hash table.
        HashTable[pos_in_HashTable].records_in_block++;
        strcpy(HashTable[pos_in_HashTable].wallet[HashTable[pos_in_HashTable].records_in_block-1].userID,userId); //the free cell of wallet is the number of records in the block -1 as we count from 0
    }else{ //If the first block is full
        ht=HashTable[pos_in_HashTable].next;
        if(ht==NULL){ //If no overflow block has been created yet
            ht=malloc(sizeof(wallet_block));
            if(ht == NULL){
                perror("Memory not allocated.");
                exit(-1);
            }
            ht->records_in_block=0;
            HashTable[pos_in_HashTable].next=ht; //Connect the first block with current
        }else {
            while (ht->records_in_block == 10) {
                for(int i=0; i<ht->records_in_block; i++){ //Check if the userID already exists
                    if(strcmp(ht->wallet[i].userID,userId)==0){
                        printf("UserID already exists! Abort!\n");
                        return;
                    }
                }
                if (ht->next == NULL) { //If all blocks are full create a new one

                    ht->next = malloc(sizeof(wallet_block));
                    if (ht->next == NULL) {
                        perror("Memory not allocated.");
                        exit(-1);
                    }
                    ht->next->records_in_block = 0;
                }
                ht = ht->next;
            }
        }
        ht->records_in_block++;
        strcpy(ht->wallet[ht->records_in_block-1].userID,userId);
        ht->wallet[ht->records_in_block-1].balance=0;
        ht->wallet[ht->records_in_block-1].list_of_bitcoins=NULL;
    }
}
void print_balance_of_user(wallet_block *HashTable, char* userid){
    int pos_in_HashTable=hash_function((unsigned char*)userid)%10; //With the hash function find the proper cell in hash table for the current entry
    for(int i=0; i<HashTable[pos_in_HashTable].records_in_block; i++){
        if(strcmp(userid,HashTable[pos_in_HashTable].wallet[i].userID)==0){
            printf("The balance of %s is %d\n",userid,HashTable[pos_in_HashTable].wallet[i].balance);
            return;
        }
    }
    wallet_block *ht;
    ht=HashTable[pos_in_HashTable].next;
    while (ht!=NULL){
        for(int i=0; i<ht->records_in_block; i++){
            if(strcmp(userid,ht->wallet[i].userID)==0){
                printf("The balance of %s is %d\n",userid,ht->wallet[i].balance);
                return;
            }
        }
        ht=ht->next;
    }
}
void print_wallet_hashtabble(wallet_block *HashTable){
    wallet_block* ht;
    for(int i=0; i<10; i++){
        for(int j=0; j<HashTable[i].records_in_block; j++){
            printf("User %s at pos %d with balance %d has:\n",HashTable[i].wallet[j].userID,i,HashTable[i].wallet[j].balance);
            print_list_of_bitcoins(HashTable[i].wallet[j].list_of_bitcoins);
        }
        ht=HashTable[i].next;
        while (ht!=NULL){
            for(int j=0; j<ht->records_in_block; j++){
                printf("User %s at pos %d with balance %d has:\n",ht->wallet[j].userID,i,ht->wallet[j].balance);
                print_list_of_bitcoins(ht->wallet[j].list_of_bitcoins);
            }
            ht=ht->next;
        }
    }
}
void transaction_in_wallet_hashtable_and_all_structures(wallet_block *walletHashTable,char* sender,char* receiver,block* senderhashtable,
        block* receiverhashtable,int senderHashtable1NumOfEntries,int receiverHashtable1NumOfEntries,size_t bucketSize,struct transaction transaction,tree_block *treehashtable){
    if(strcmp(sender,receiver)==0){
        printf("There can not be a transaction between one user!!Abort.\n");
        return;
    }
    int pos_in_HashTable=hash_function((unsigned char*)sender)%10; //With the hash function find the proper cell in hash table for the current entry
    int pos_in_rec=hash_function((unsigned char*)receiver)%10; //With the hash function find the proper cell in hash table for the current entry
    wallet_block *ht;
    bitcoin_info *bitcoins_of_transaction=NULL,*temp=NULL;
    for (int i = 0; i < walletHashTable[pos_in_HashTable].records_in_block; i++) {
        if (strcmp(walletHashTable[pos_in_HashTable].wallet[i].userID, sender) == 0) { //find the sender's position
            if (walletHashTable[pos_in_HashTable].wallet[i].balance >= transaction.amount_of_transaction) { //if user's balance is enough for the amount of transaction

                walletHashTable[pos_in_HashTable].wallet[i].balance -= transaction.amount_of_transaction; //reduce the balance

                insert_in_hashtable(senderhashtable,senderHashtable1NumOfEntries,sender,bucketSize);//Insert the sender in senderHashtable
                insert_in_hashtable(receiverhashtable,receiverHashtable1NumOfEntries,receiver,bucketSize);//Insert the receiver in receiverHashtable

                //find max bitcoin(s) to use for the transaction
                transaction_in_list_of_bitcoins(&walletHashTable[pos_in_HashTable].wallet[i].list_of_bitcoins,&bitcoins_of_transaction,transaction.amount_of_transaction);
                temp=bitcoins_of_transaction;
                //calculate the length of list to create the array for the transaction list. As many bitcoins as many tree nodes
                int number_of_bitcoins=length_of_bitcoin_list(bitcoins_of_transaction);
                tree_node **array_for_transaction=malloc(number_of_bitcoins* sizeof(tree_node));
                int k=0;
                while (k<walletHashTable[pos_in_rec].records_in_block){
                    if (strcmp(walletHashTable[pos_in_rec].wallet[k].userID, receiver) == 0) { //find the receiver's position
                        walletHashTable[pos_in_rec].wallet[k].balance += transaction.amount_of_transaction; //increase the balance of the receiver
                        break;
                    }
                    k++;
                }
                for(int j=0; j<number_of_bitcoins; j++){
                    insert_in_list_of_bitcoins_transaction(&walletHashTable[pos_in_rec].wallet[k].list_of_bitcoins,temp->bitcoinID,temp->amount); //Modify the list of bitcoins of receiver
                    //find tree(s) with specific bitcoin(s) and insert the transaction
                    array_for_transaction[j]=insert_in_tree(find_tree_with_specific_bitcoin(treehashtable,temp->bitcoinID),
                            sender, receiver,temp->amount,transaction.date,transaction.time,transaction.transactionID);
                    temp=temp->next;
                }

                insert_specific_transaction_list_in_hashtable(senderhashtable,senderHashtable1NumOfEntries,sender,bucketSize,array_for_transaction,number_of_bitcoins);//update user's transaction list
                insert_specific_transaction_list_in_hashtable(receiverhashtable,receiverHashtable1NumOfEntries,receiver,bucketSize,array_for_transaction,number_of_bitcoins);

                free(array_for_transaction);
                delete_list_of_bitcoins(&bitcoins_of_transaction);
                return;
            }else{
                printf("Sender %s doesn't have enough money to send to %s for this transaction! Abort.\n",sender,receiver);
                return;
            }
        }
    }




    ht=walletHashTable[pos_in_HashTable].next;
    while(ht!=NULL){
        for (int i = 0; i < ht->records_in_block; i++) {
            if (strcmp(ht->wallet[i].userID, sender) == 0) { //find the sender's position
                if (ht->wallet[i].balance >= transaction.amount_of_transaction) { //if user's balance is enough for the amount of transaction

                    ht->wallet[i].balance -= transaction.amount_of_transaction; //reduce the balance

                    insert_in_hashtable(senderhashtable,senderHashtable1NumOfEntries,sender,bucketSize);//Insert the transcation in sender Hash table
                    insert_in_hashtable(receiverhashtable,receiverHashtable1NumOfEntries,receiver,bucketSize);//Insert the transcation in receiver Hash table

                    //find max bitcoin(s) to use for the transaction
                    transaction_in_list_of_bitcoins(&ht->wallet[i].list_of_bitcoins,&bitcoins_of_transaction,transaction.amount_of_transaction);
                    temp=bitcoins_of_transaction;
                    //calculate the length of list to create the array for the transaction list. As many bitcoins as many tree nodes
                    int number_of_bitcoins=length_of_bitcoin_list(bitcoins_of_transaction);
                    tree_node **array_for_transaction=malloc(number_of_bitcoins* sizeof(tree_node));
                    for(int j=0; j<number_of_bitcoins; j++){

                        //find tree(s) with specific bitcoin(s) and insert the transaction
                        array_for_transaction[j]=insert_in_tree(find_tree_with_specific_bitcoin(treehashtable,temp->bitcoinID), sender, receiver,temp->amount,transaction.date,transaction.time,transaction.transactionID);
                        temp=temp->next;
                    }

                    transaction_node* sender_transaction_list=find_specific_transaction_list_in_hashtable(senderhashtable,senderHashtable1NumOfEntries,sender,bucketSize);
                    transaction_node* receiver_transaction_list=find_specific_transaction_list_in_hashtable(receiverhashtable,receiverHashtable1NumOfEntries,receiver,bucketSize);

                    insert_in_transaction_list(&sender_transaction_list,array_for_transaction,number_of_bitcoins);
                    insert_in_transaction_list(&receiver_transaction_list,array_for_transaction,number_of_bitcoins);
                    free(array_for_transaction);
                    delete_list_of_bitcoins(&bitcoins_of_transaction);
                }else{
                    printf("Sender %s doesn't have enough money to send to %s for this transaction! Abort.\n",sender,receiver);
                    return;
                }
            }
        }
        ht=ht->next;
    }

    printf("User was not found!\n");

}

void delete_wallet_hashtable(wallet_block *HashTable){
    wallet_block *temp,*ht;
    for(int i=0; i<10; i++){
        for(int j=0; j<HashTable[i].records_in_block; j++){
            //free bitcoin list
            delete_list_of_bitcoins(&HashTable[i].wallet[j].list_of_bitcoins);
        }
        ht=HashTable[i].next;
        while(ht!=NULL){
            for(int j=0; j<ht->records_in_block; j++){
                //free bitcoin list
                delete_list_of_bitcoins(&ht->wallet[j].list_of_bitcoins);
            }
            temp=ht;
            ht=ht->next;
            free(temp);
        }
    }
}

