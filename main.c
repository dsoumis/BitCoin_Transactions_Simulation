#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Hash_Table_Implementation.h"
#include "List_Implementation.h"
#include "Structures.h"
#include "Tree_Implementation.h"
#define bufferSize 1024
#define PATH_MAX 4096
int transaction_increasing_number;
struct last_transaction{
    struct date date;
    struct time time;
};
struct last_transaction last_transaction;
bool valid_transaction(struct transaction transaction){
    if(transaction.date.year>last_transaction.date.year) {
        last_transaction.date.day=transaction.date.day;
        last_transaction.date.month=transaction.date.month;
        last_transaction.date.year=transaction.date.year;
        last_transaction.time.hour=transaction.time.hour;
        last_transaction.time.minute=transaction.time.minute;
        return true;
    }else if(transaction.date.year==last_transaction.date.year) {
        if (transaction.date.month > last_transaction.date.month) {
            last_transaction.date.day=transaction.date.day;
            last_transaction.date.month=transaction.date.month;
            last_transaction.date.year=transaction.date.year;
            last_transaction.time.hour=transaction.time.hour;
            last_transaction.time.minute=transaction.time.minute;
            return true;
        } else if (transaction.date.month == last_transaction.date.month) {
            if (transaction.date.day > last_transaction.date.day) {
                last_transaction.date.day=transaction.date.day;
                last_transaction.date.month=transaction.date.month;
                last_transaction.date.year=transaction.date.year;
                last_transaction.time.hour=transaction.time.hour;
                last_transaction.time.minute=transaction.time.minute;
                return true;
            } else if(transaction.date.day == last_transaction.date.day){
                if(transaction.time.hour>last_transaction.time.hour){
                    last_transaction.date.day=transaction.date.day;
                    last_transaction.date.month=transaction.date.month;
                    last_transaction.date.year=transaction.date.year;
                    last_transaction.time.hour=transaction.time.hour;
                    last_transaction.time.minute=transaction.time.minute;
                    return true;
                } else if(transaction.time.hour==last_transaction.time.hour){
                    if(transaction.time.minute>last_transaction.time.minute) {
                        last_transaction.date.day=transaction.date.day;
                        last_transaction.date.month=transaction.date.month;
                        last_transaction.date.year=transaction.date.year;
                        last_transaction.time.hour=transaction.time.hour;
                        last_transaction.time.minute=transaction.time.minute;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
void assign_values_from_arguments(char **argv,int* bitCoinValue,int* senderHashtable1NumOfEntries,int* receiverHashtable1NumOfEntries,size_t* bucketSize,
        char** bitCoinBalancesFile,char** transactionsFile){
    int i = 1;
    while (strcmp(argv[i], "-a") != 0) {
        i++;
    }
    i++;

    strcpy(*bitCoinBalancesFile,argv[i]);
    i = 1;
    while (strcmp(argv[i], "-t") != 0) {
        i++;
    }
    i++;

    strcpy(*transactionsFile,argv[i]);

    i = 1;
    while (strcmp(argv[i], "-v") != 0) {
        i++;
    }
    i++;

    (*bitCoinValue)=atoi(argv[i]);


    i = 1;
    while (strcmp(argv[i], "-h1") != 0) {
        i++;
    }
    i++;
    (*senderHashtable1NumOfEntries)=atoi(argv[i]);

    i = 1;
    while (strcmp(argv[i], "-h2") != 0) {
        i++;
    }
    i++;
    *receiverHashtable1NumOfEntries=atoi(argv[i]);

    i = 1;
    while (strcmp(argv[i], "-b") != 0) {
        i++;
    }
    i++;
    *bucketSize=(size_t)atoi(argv[i]);
}

void orders(wallet_block *walletHashTable,block* senderHashTable,block *receiverHashTable,tree_block* treehashtable,int senderHashtable1NumOfEntries,int receiverHashtable1NumOfEntries,size_t bucketsize,int bitcoinvalue){
    char str1[200],buffer[bufferSize],*temp_str;
    char sender[50],receiver[50];
    struct transaction transaction;
    printf("Waiting for orders..\n");
    scanf("%s",str1);
    while(strcmp(str1,"/exit")!=0){
        if(strcmp(str1,"/requestTransaction")==0){
            scanf ("%[^\n]%*c", buffer);

            bool date_given;
            if(strchr(buffer,':')!=NULL) //Date and time are given
                date_given=true;
            else
                date_given=false;
            sprintf(transaction.transactionID,"TransactionID%d",transaction_increasing_number);
            transaction_increasing_number++;

            temp_str=strtok(buffer," "); //divide by space

            strcpy(sender,temp_str);

            temp_str=strtok(NULL," "); //divide by space
            strcpy(receiver,temp_str);

            temp_str=strtok(NULL," "); //divide by space
            transaction.amount_of_transaction=atoi(temp_str);
            if(date_given==true) {
                temp_str = strtok(NULL, "-"); //divide by space
                transaction.date.day = atoi(temp_str);

                temp_str = strtok(NULL, "-"); //divide by space
                transaction.date.month = atoi(temp_str);

                temp_str = strtok(NULL, " "); //divide by space
                transaction.date.year = atoi(temp_str);

                temp_str = strtok(NULL, ":");
                transaction.time.hour = atoi(temp_str);

                temp_str = strtok(NULL, " ");
                transaction.time.minute = atoi(temp_str);
            }else{
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                transaction.date.day=tm.tm_mday;
                transaction.date.month=tm.tm_mon + 1;
                transaction.date.year=tm.tm_year + 1900;
                transaction.time.hour=tm.tm_hour;
                transaction.time.minute=tm.tm_min;
            }
            if(valid_transaction(transaction)==true) {
                printf("Transaction %s %s %s %d %d-%d-%d %d:%d\n", transaction.transactionID, sender, receiver,
                       transaction.amount_of_transaction,
                       transaction.date.day, transaction.date.month, transaction.date.year, transaction.time.hour,
                       transaction.time.minute);

                transaction_in_wallet_hashtable_and_all_structures(walletHashTable, sender, receiver, senderHashTable,
                                                                   receiverHashTable, senderHashtable1NumOfEntries,
                                                                   receiverHashtable1NumOfEntries,
                                                                   bucketsize, transaction, treehashtable);
            } else
                printf("Invalid transaction because last transaction was %d-%d-%d %d:%d\n",last_transaction.date.day,last_transaction.date.month,last_transaction.date.year,
                        last_transaction.time.hour,last_transaction.time.minute);
        } else if(strcmp(str1,"/requestTransactions")==0){
            scanf ("%[^\n]%*c", buffer);
            list_of_strings *list_of_strings=NULL,*temp_list;

            if(strchr(buffer,';')!=NULL){ //if ; exists in buffer then it is not an inputfile
                while(strchr(buffer,';')!=NULL) {
                    temp_str = strtok(buffer, ";");
                    insert_in_list_of_strings(&list_of_strings, temp_str);
                    while ((temp_str = strtok(NULL, ";")) != NULL) {
                        if (strlen(temp_str) > 4)
                            insert_in_list_of_strings(&list_of_strings, temp_str);
                    }
                    temp_list = list_of_strings;
                    while (temp_list != NULL) {
                        sprintf(transaction.transactionID, "TransactionID%d", transaction_increasing_number);
                        transaction_increasing_number++;

                        temp_str = strtok(temp_list->string, " "); //divide by space
                        strcpy(sender, temp_str);

                        temp_str = strtok(NULL, " "); //divide by space
                        strcpy(receiver, temp_str);

                        temp_str = strtok(NULL, " "); //divide by space
                        transaction.amount_of_transaction = atoi(temp_str);

                        temp_str = strtok(NULL, "-"); //divide by space
                        transaction.date.day = atoi(temp_str);

                        temp_str = strtok(NULL, "-"); //divide by space
                        transaction.date.month = atoi(temp_str);

                        temp_str = strtok(NULL, " "); //divide by space
                        transaction.date.year = atoi(temp_str);

                        temp_str = strtok(NULL, ":");
                        transaction.time.hour = atoi(temp_str);

                        temp_str = strtok(NULL, " ");
                        transaction.time.minute = atoi(temp_str);
                        if(valid_transaction(transaction)==true) {
                            printf("Transaction %s %s %s %d %d-%d-%d %d:%d\n", transaction.transactionID, sender,
                                   receiver,
                                   transaction.amount_of_transaction,
                                   transaction.date.day, transaction.date.month, transaction.date.year,
                                   transaction.time.hour, transaction.time.minute);
                            transaction_in_wallet_hashtable_and_all_structures(walletHashTable, sender, receiver,
                                                                               senderHashTable, receiverHashTable,
                                                                               senderHashtable1NumOfEntries,
                                                                               receiverHashtable1NumOfEntries,
                                                                               bucketsize, transaction, treehashtable);
                        }else
                            printf("Invalid transaction because last transaction was %d-%d-%d %d:%d\n",last_transaction.date.day,last_transaction.date.month,last_transaction.date.year,
                                   last_transaction.time.hour,last_transaction.time.minute);
                        temp_list = temp_list->next;
                    }
                    delete_list_of_strings(&list_of_strings);
                    printf("If you want to exit requestTransactions press any key+enter except ; else give another transaction\n");
                    scanf ("%[^\n]%*c", buffer);
                }
            }else{//if ; doesn't exist in buffer then it is an inputfile
                temp_str=strtok(buffer," ");
                FILE *fptr;
                if ((fptr = fopen(temp_str, "r")) == NULL){
                    perror("Error! opening file");
                    // Program exits if file pointer returns NULL.
                    exit(1);
                }
                while (fgets(buffer,bufferSize, fptr)!=NULL) {//read from input file
                    temp_str=strtok(buffer,";");
                    insert_in_list_of_strings(&list_of_strings,temp_str);
                    while((temp_str=strtok(NULL,";"))!=NULL) {
                        if(strlen(temp_str)>4)
                            insert_in_list_of_strings(&list_of_strings, temp_str);
                    }
                }
                print_list_of_strings(list_of_strings);
                temp_list=list_of_strings;
                while(temp_list!=NULL) {
                    sprintf(transaction.transactionID,"TransactionID%d",transaction_increasing_number);
                    transaction_increasing_number++;
                    temp_str = strtok(temp_list->string, " "); //divide by space
                    strcpy(sender, temp_str);

                    temp_str = strtok(NULL, " "); //divide by space
                    strcpy(receiver, temp_str);

                    temp_str = strtok(NULL, " "); //divide by space
                    transaction.amount_of_transaction = atoi(temp_str);

                    temp_str = strtok(NULL, "-"); //divide by space
                    transaction.date.day = atoi(temp_str);

                    temp_str = strtok(NULL, "-"); //divide by space
                    transaction.date.month = atoi(temp_str);

                    temp_str = strtok(NULL, " "); //divide by space
                    transaction.date.year = atoi(temp_str);

                    temp_str = strtok(NULL, ":");
                    transaction.time.hour = atoi(temp_str);

                    temp_str = strtok(NULL, " ");
                    transaction.time.minute = atoi(temp_str);
                    if(valid_transaction(transaction)==true) {
                        printf("Transaction %s %s %s %d %d-%d-%d %d:%d\n", transaction.transactionID, sender, receiver,
                               transaction.amount_of_transaction, transaction.date.day, transaction.date.month,
                               transaction.date.year, transaction.time.hour, transaction.time.minute);
                        transaction_in_wallet_hashtable_and_all_structures(walletHashTable, sender, receiver,
                                                                           senderHashTable, receiverHashTable,
                                                                           senderHashtable1NumOfEntries,
                                                                           receiverHashtable1NumOfEntries,
                                                                           bucketsize, transaction, treehashtable);
                    }else
                        printf("Invalid transaction because last transaction was %d-%d-%d %d:%d\n",last_transaction.date.day,last_transaction.date.month,last_transaction.date.year,
                               last_transaction.time.hour,last_transaction.time.minute);
                    temp_list=temp_list->next;
                }
                delete_list_of_strings(&list_of_strings);
                fclose(fptr);
            }


        }else if(strcmp(str1,"/findEarnings")==0){
            scanf ("%[^\n]%*c", buffer);
            bool flag1=false,flag2=false,error=false;
            char *receiver_earnings,*temp_str2;
            //count how many times a character exists in buffer
            int counts[256] = { 0 };
            size_t len = strlen(buffer);
            for (int i = 0; i < len; i++) {
                counts[(int)(buffer[i])]++;
            }
            for (int i = 0; i < 256; i++) {
                if(i==':'&&counts[i]==1){ //Time1 can not exist solo there must be 2
                    printf("Error time!\n");
                    error=true;
                    break;
                }
                if(i=='-'&&counts[i]==2){ //Date1 can not exist solo there must be 6
                    printf("Error date!\n");
                    error=true;
                    break;
                }
                if(i==':'&&counts[i]==2)
                    flag1=true;
                if(i=='-'&&counts[i]==4){
                    flag2=true;
                }
            }
            struct time time_begin,time_end;
            struct date date_begin,date_end;
            if(error==false) {
                if (flag1 == true && flag2 == true) {
                    receiver_earnings = strtok(buffer, " ");
                    temp_str2 = strtok(NULL, ":");
                    time_begin.hour = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    time_begin.minute = atoi(temp_str2);

                    temp_str2 = strtok(NULL, "-");
                    date_begin.day = atoi(temp_str2);
                    temp_str2 = strtok(NULL, "-");
                    date_begin.month = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    date_begin.year = atoi(temp_str2);

                    temp_str2 = strtok(NULL, ":");
                    time_end.hour = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    time_end.minute = atoi(temp_str2);

                    temp_str2 = strtok(NULL, "-");
                    date_end.day = atoi(temp_str2);
                    temp_str2 = strtok(NULL, "-");
                    date_end.month = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    date_end.year = atoi(temp_str2);

                    print_specific_transaction_list_of_hashtable(receiverHashTable, receiver_earnings,
                                                                          time_begin, time_end, date_begin, date_end,
                                                                          receiverHashtable1NumOfEntries, 2);
                } else if (flag1 == false && flag2 == true) {
                    receiver_earnings = strtok(buffer, " ");
                    time_begin.hour = -1;
                    time_end.hour = -1;
                    temp_str2 = strtok(NULL, "-");
                    date_begin.day = atoi(temp_str2);
                    temp_str2 = strtok(NULL, "-");
                    date_begin.month = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    date_begin.year = atoi(temp_str2);
                    temp_str2 = strtok(NULL, "-");
                    date_end.day = atoi(temp_str2);
                    temp_str2 = strtok(NULL, "-");
                    date_end.month = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    date_end.year = atoi(temp_str2);

                    print_specific_transaction_list_of_hashtable(receiverHashTable, receiver_earnings,
                                                                          time_begin, time_end, date_begin, date_end,
                                                                          receiverHashtable1NumOfEntries, 2);
                } else if (flag1 == true && flag2 == false) {
                    receiver_earnings = strtok(buffer, " ");
                    date_begin.year = -1;
                    date_end.year = -1;
                    temp_str2 = strtok(NULL, ":");
                    time_begin.hour = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    time_begin.minute = atoi(temp_str2);
                    temp_str2 = strtok(NULL, ":");
                    time_end.hour = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    time_end.minute = atoi(temp_str2);
                    print_specific_transaction_list_of_hashtable(receiverHashTable, receiver_earnings,
                                                                          time_begin, time_end, date_begin, date_end,
                                                                          receiverHashtable1NumOfEntries, 2);
                } else if (flag1 == false && flag2 == false) {
                    receiver_earnings = strtok(buffer, " ");
                    receiver_earnings = strtok(receiver_earnings, " ");
                    date_begin.year = -1;
                    time_begin.hour = -1;
                    print_specific_transaction_list_of_hashtable(receiverHashTable, receiver_earnings,
                                                                          time_begin, time_end, date_begin, date_end,
                                                                          receiverHashtable1NumOfEntries, 2);
                }
            }
        }else if(strcmp(str1,"/findPayments")==0){
            scanf ("%[^\n]%*c", buffer);
            bool flag1=false,flag2=false,error=false;
            char *sender_payments,*temp_str2;
            //count how many times a character exists in buffer
            int counts[256] = { 0 };
            size_t len = strlen(buffer);
            for (int i = 0; i < len; i++) {
                counts[(int)(buffer[i])]++;
            }
            for (int i = 0; i < 256; i++) {
                if(i==':'&&counts[i]==1){ //Time1 can not exist solo there must be 2
                    printf("Error time!\n");
                    error=true;
                    break;
                }
                if(i=='-'&&counts[i]==2){ //Date1 can not exist solo there must be 6
                    printf("Error date!\n");
                    error=true;
                    break;
                }
                if(i==':'&&counts[i]==2)
                    flag1=true;
                if(i=='-'&&counts[i]==4){
                    flag2=true;
                }
            }
            struct time time_begin,time_end;
            struct date date_begin,date_end;
            if(error==false) {
                if (flag1 == true && flag2 == true) {
                    sender_payments = strtok(buffer, " ");
                    temp_str2 = strtok(NULL, ":");
                    time_begin.hour = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    time_begin.minute = atoi(temp_str2);

                    temp_str2 = strtok(NULL, "-");
                    date_begin.day = atoi(temp_str2);
                    temp_str2 = strtok(NULL, "-");
                    date_begin.month = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    date_begin.year = atoi(temp_str2);

                    temp_str2 = strtok(NULL, ":");
                    time_end.hour = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    time_end.minute = atoi(temp_str2);

                    temp_str2 = strtok(NULL, "-");
                    date_end.day = atoi(temp_str2);
                    temp_str2 = strtok(NULL, "-");
                    date_end.month = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    date_end.year = atoi(temp_str2);

                    print_specific_transaction_list_of_hashtable(senderHashTable, sender_payments,
                                                                          time_begin, time_end, date_begin, date_end,
                                                                          senderHashtable1NumOfEntries, 1);
                } else if (flag1 == false && flag2 == true) {
                    sender_payments = strtok(buffer, " ");
                    time_begin.hour = -1;
                    time_end.hour = -1;
                    temp_str2 = strtok(NULL, "-");
                    date_begin.day = atoi(temp_str2);
                    temp_str2 = strtok(NULL, "-");
                    date_begin.month = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    date_begin.year = atoi(temp_str2);
                    temp_str2 = strtok(NULL, "-");
                    date_end.day = atoi(temp_str2);
                    temp_str2 = strtok(NULL, "-");
                    date_end.month = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    date_end.year = atoi(temp_str2);

                    print_specific_transaction_list_of_hashtable(senderHashTable, sender_payments,
                                                                          time_begin, time_end, date_begin, date_end,
                                                                          senderHashtable1NumOfEntries, 1);
                } else if (flag1 == true && flag2 == false) {
                    sender_payments = strtok(buffer, " ");
                    date_begin.year = -1;
                    date_end.year = -1;
                    temp_str2 = strtok(NULL, ":");
                    time_begin.hour = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    time_begin.minute = atoi(temp_str2);
                    temp_str2 = strtok(NULL, ":");
                    time_end.hour = atoi(temp_str2);
                    temp_str2 = strtok(NULL, " ");
                    time_end.minute = atoi(temp_str2);
                    print_specific_transaction_list_of_hashtable(senderHashTable, sender_payments,
                                                                          time_begin, time_end, date_begin, date_end,
                                                                          senderHashtable1NumOfEntries, 1);
                } else if (flag1 == false && flag2 == false) {
                    sender_payments = strtok(buffer, " ");
                    sender_payments = strtok(sender_payments, " ");
                    date_begin.year = -1;
                    time_begin.hour = -1;
                    print_specific_transaction_list_of_hashtable(senderHashTable, sender_payments,
                                                                          time_begin, time_end, date_begin, date_end,
                                                                          senderHashtable1NumOfEntries, 1);
                }
            }
        }else if(strcmp(str1,"/walletStatus")==0){
            scanf("%s",sender); //walletID
            print_balance_of_user(walletHashTable,sender);
        }else if(strcmp(str1,"/bitCoinStatus")==0){
            int bitcoin,number_of_transactions=0,unspent_amount=bitcoinvalue;
            scanf("%s",str1);
            bitcoin=atoi(str1);
            bitcoinstatus(find_tree_with_specific_bitcoin(treehashtable,bitcoin),&number_of_transactions,&unspent_amount);
            printf("%d %d %d\n",bitcoin,number_of_transactions,unspent_amount);
        }else if(strcmp(str1,"/traceCoin")==0){
            int bitcoin;
            scanf("%s",str1);
            bitcoin=atoi(str1);
            tracecoin(find_tree_with_specific_bitcoin(treehashtable,bitcoin));
            printf("\n");
        }
        printf("Waiting for orders..\n");
        scanf("%s",str1);
    }
}

void bitcoinbalancefile_to_wallet(char* bitCoinBalancesFile,wallet_block *walletHashTable,unsigned int bitcoinvalue,tree_block* treehashtable){
    char buffer[bufferSize],*temp_str,user[50];

    FILE *fptr;
    if ((fptr = fopen(bitCoinBalancesFile, "r")) == NULL){
        perror("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }
    while (1) {
        fscanf(fptr, "%[^\n]\n", buffer); //read line by line

        if((temp_str=strtok(buffer," "))!=NULL) //divide by space
            sscanf(temp_str,"%s",user);

        insert_in_wallet_hashtable(walletHashTable,user,0,0,true);




        while((temp_str=strtok(NULL," "))!=NULL){
            if(strcmp(temp_str,"\n")!=3) { //3 was the empty length
                insert_in_wallet_hashtable(walletHashTable, user, atoi(temp_str), bitcoinvalue, false);
                insert_in_tree_hashtable(treehashtable,user,atoi(temp_str),bitcoinvalue);
            }
        }
        if (feof(fptr))
            break;
    }
    fclose(fptr);
}

void transactionfile_to_hash(char* transactionsFile,wallet_block *walletHashTable,block* senderHashTable,block *receiverHashTable,tree_block* treehashtable,
        int senderHashtable1NumOfEntries,int receiverHashtable1NumOfEntries,size_t bucketSize){
    char buffer[bufferSize],*temp_str,sender[50],receiver[50];
    struct transaction transaction;

    FILE *fptr;
    if ((fptr = fopen(transactionsFile, "r")) == NULL){
        perror("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }
    last_transaction.date.day=0;
    last_transaction.date.month=0;
    last_transaction.date.year=0;
    last_transaction.time.hour=0;
    last_transaction.time.minute=0;
    while (1) {
        fscanf(fptr, "%[^\n]\n", buffer); //read line by line
        temp_str=strtok(buffer," "); //divide by space
        strcpy(transaction.transactionID,temp_str);

        temp_str=strtok(NULL," "); //divide by space
        strcpy(sender,temp_str);

        temp_str=strtok(NULL," "); //divide by space
        strcpy(receiver,temp_str);

        temp_str=strtok(NULL," "); //divide by space
        transaction.amount_of_transaction=atoi(temp_str);

        temp_str=strtok(NULL,"-"); //divide by space
        transaction.date.day=atoi(temp_str);

        temp_str=strtok(NULL,"-"); //divide by space
        transaction.date.month=atoi(temp_str);

        temp_str=strtok(NULL," "); //divide by space
        transaction.date.year=atoi(temp_str);

        temp_str=strtok(NULL,":");
        transaction.time.hour=atoi(temp_str);

        temp_str=strtok(NULL," ");
        transaction.time.minute=atoi(temp_str);

        printf("Transaction %s %s %s %d %d-%d-%d %d:%d\n",transaction.transactionID,sender,receiver,transaction.amount_of_transaction,transaction.date.day,transaction.date.month,transaction.date.year,transaction.time.hour,transaction.time.minute);
        transaction_in_wallet_hashtable_and_all_structures(walletHashTable,sender,receiver,senderHashTable,receiverHashTable,senderHashtable1NumOfEntries,receiverHashtable1NumOfEntries,
                bucketSize,transaction,treehashtable);
        valid_transaction(transaction);
        if (feof(fptr)) {
            break;
        }
    }
    fclose(fptr);
}

int main(int argc,char** argv){
    if(argc<13 || argc>13){
        printf("Not correctly executed!\n");
        exit(1);
    }
    transaction_increasing_number=0;
    char  *bitCoinBalancesFile,*transactionsFile;
    bitCoinBalancesFile=malloc(PATH_MAX);
    transactionsFile=malloc(PATH_MAX);
    int bitCoinValue,senderHashtable1NumOfEntries,receiverHashtable1NumOfEntries;
    size_t bucketSize;
    assign_values_from_arguments(argv,&bitCoinValue,&senderHashtable1NumOfEntries,&receiverHashtable1NumOfEntries,&bucketSize,&bitCoinBalancesFile,&transactionsFile);
    block *senderHashTable=initialize_hashtable(senderHashtable1NumOfEntries,bucketSize);
    block *receiverHashTable=initialize_hashtable(receiverHashtable1NumOfEntries,bucketSize);
    //printf("Arguments: %d %d %d %d %s %s\n",bitCoinValue,senderHashtable1NumOfEntries,receiverHashtable1NumOfEntries,(int)bucketSize,bitCoinBalancesFile,transactionsFile);

    tree_block tree_hashtable[10];//10 initial buckets in the tree hash table
    wallet_block wallet_hashtable[10]; //10 initial buckets in the wallet hash table
    initialize_wallet_hashtable(wallet_hashtable);
    initialize_tree_hashtable(tree_hashtable);

    bitcoinbalancefile_to_wallet(bitCoinBalancesFile,wallet_hashtable,(unsigned int)bitCoinValue,tree_hashtable);
    //print_tree_hashtabble(tree_hashtable);
    transactionfile_to_hash(transactionsFile,wallet_hashtable,senderHashTable,receiverHashTable,tree_hashtable,senderHashtable1NumOfEntries,receiverHashtable1NumOfEntries,bucketSize);
    //print_wallet_hashtabble(wallet_hashtable);

    //transaction_node *ss;
    //ss=find_specific_transaction_list_in_hashtable(senderHashTable,senderHashtable1NumOfEntries,"richard",bucketSize);
    //ss->next=NULL;
    //print_transaction_list(ss,1);
    //printf("\n\n");
    //printPreorder(find_tree_with_specific_bitcoin(tree_hashtable,541));
    orders(wallet_hashtable,senderHashTable,receiverHashTable,tree_hashtable,senderHashtable1NumOfEntries,receiverHashtable1NumOfEntries,bucketSize,bitCoinValue);
    //printPreorder(find_tree_with_specific_bitcoin(tree_hashtable,541));
    //print_transaction_list(ss,1);


    free(bitCoinBalancesFile);
    free(transactionsFile);
    delete_wallet_hashtable(wallet_hashtable);
    delete_hashtable(senderHashTable,senderHashtable1NumOfEntries);
    delete_hashtable(receiverHashTable,receiverHashtable1NumOfEntries);
    delete_tree_hashtable(tree_hashtable);
    return 2;
}

