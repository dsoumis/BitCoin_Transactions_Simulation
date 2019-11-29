#include "List_Implementation.h"
void insert_in_ptrs_to_tree_list(ptr_to_tree_list_node **list,tree_node **treeNode,int number_of_treenodes){
    ptr_to_tree_list_node *temp;
    //First node in order to initialize the head of the list
    temp=malloc(sizeof(ptr_to_tree_list_node));
    if(temp == NULL){
        perror("Memory not allocated.");
        exit(-1);
    }
    temp->ptr_to_tree=treeNode[0];
    temp->next=NULL;
    *list=temp;
    /* ///////////////////////////////////////////////////// */
    for(int i=1; i<number_of_treenodes; i++){
        while(temp->next!=NULL) {
            temp = temp->next;
        }
        temp->next=malloc(sizeof(ptr_to_tree_list_node));
        if(temp->next == NULL){
            perror("Memory not allocated.");
            exit(-1);
        }
        temp->next->ptr_to_tree=treeNode[i];
        temp->next->next=NULL;
    }

}

//give an array of tree nodes as one transaction can happen with more than one bitcoins
void insert_in_transaction_list(transaction_node** list, tree_node** treeNode,int number_of_treenodes){
    transaction_node *temp=*list;
    if(temp==NULL) {
        //First node in order to initialize the head of the list
        temp = malloc(sizeof(transaction_node));
        if (temp == NULL) {
            perror("Memory not allocated.");
            exit(-1);
        }
        temp->list_of_ptrs_to_tree = NULL;
        temp->next = NULL;
        insert_in_ptrs_to_tree_list(&temp->list_of_ptrs_to_tree, treeNode, number_of_treenodes);
        *list = temp;
    }else {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = malloc(sizeof(transaction_node));
        if (temp->next == NULL) {
            perror("Memory not allocated.");
            exit(-1);
        }
        temp->next->list_of_ptrs_to_tree = NULL;
        temp->next->next = NULL;
        insert_in_ptrs_to_tree_list(&temp->next->list_of_ptrs_to_tree, treeNode, number_of_treenodes);

    }
}
void specific_print_ptrs_to_tree_list(ptr_to_tree_list_node* list,char* userId, short int sender){
    if (list->ptr_to_tree->transaction.date.day / 10 == 0)
        printf("In transaction(id) %s at 0%d-", list->ptr_to_tree->transaction.transactionID,
               list->ptr_to_tree->transaction.date.day);
    else
        printf("In transaction(id) %s at %d-", list->ptr_to_tree->transaction.transactionID,
               list->ptr_to_tree->transaction.date.day);
    if (list->ptr_to_tree->transaction.date.month / 10 == 0)
        printf("0%d-", list->ptr_to_tree->transaction.date.month);
    else
        printf("%d-", list->ptr_to_tree->transaction.date.month);
    printf("%d", list->ptr_to_tree->transaction.date.year);
    if (list->ptr_to_tree->transaction.time.hour / 10 == 0)
        printf(" and 0%d:", list->ptr_to_tree->transaction.time.hour);
    else
        printf(" and %d:", list->ptr_to_tree->transaction.time.hour);
    if (list->ptr_to_tree->transaction.time.minute / 10 == 0)
        printf("0%d", list->ptr_to_tree->transaction.time.minute);
    else
        printf("%d", list->ptr_to_tree->transaction.time.minute);
    if (sender == 1)
        printf(" %s sent to %s %d\n", userId, list->ptr_to_tree->userID,
               list->ptr_to_tree->transaction.amount_of_transaction);
    else {
        printf(" %s received from %s %d\n", userId, list->ptr_to_tree->received_from,
               list->ptr_to_tree->transaction.amount_of_transaction);
    }
}
void print_transaction_list(transaction_node* list, short int sender){
    transaction_node *temp=list;
    ptr_to_tree_list_node *temp2;
    printf("Printing transaction list\n");
    while (temp!=NULL){
        temp2=temp->list_of_ptrs_to_tree;
        printf("NODE:\n");
        while (temp2!=NULL){
            if(sender==1)
                printf("Send to %s\n",temp2->ptr_to_tree->userID);
            else
                printf("Received from %s\n",temp2->ptr_to_tree->received_from);
            temp2=temp2->next;
        }
        temp=temp->next;
    }
}
void delete_ptrs_to_tree_list(ptr_to_tree_list_node **list){
    ptr_to_tree_list_node *temp;
    while (*list!=NULL){
        temp=*list;
        *list=(*list)->next;
        free(temp);
    }
}
void find_in_list(transaction_node* list){
    transaction_node *temp=list;
    ptr_to_tree_list_node *temp2;
    while (temp!=NULL){
        printf("Transaction\n");
        temp2=temp->list_of_ptrs_to_tree;
        while(temp2!=NULL){
            printf("%s\n",temp2->ptr_to_tree->userID);
            temp2=temp2->next;
        }
        temp=temp->next;
    }
}
void delete_transaction_list(transaction_node **list){
    transaction_node *temp;
    while (*list!=NULL){
        temp=*list;
        *list=(*list)->next;
        delete_ptrs_to_tree_list(&temp->list_of_ptrs_to_tree); //First delete the list of pointers to tree for this specific transaction
        free(temp); //Then delete the node of the transaction list
    }
}


void insert_in_list_of_bitcoins_transaction(bitcoin_info** list,unsigned int bitcoinid, unsigned int amount){
    bitcoin_info *temp=*list;
    if(temp==NULL) {
        //First node in order to initialize the head of the list
        temp = malloc(sizeof(bitcoin_info));
        if (temp == NULL) {
            perror("Memory not allocated.");
            exit(-1);
        }
        temp->bitcoinID=bitcoinid;
        temp->amount=amount;
        temp->next=NULL;
        *list = temp;
    }else {
        if(temp->bitcoinID==bitcoinid){
            //printf("Bitcoin %d already exists just increasing the amount.\n",bitcoinid);
            temp->amount+=amount;
            return;
        }
        while (temp->next != NULL) {
            temp = temp->next;
            if(temp->bitcoinID==bitcoinid){
                //printf("Bitcoin %d already exists just increasing the amount.\n",bitcoinid);
                temp->amount+=amount;
                return;
            }
        }
        temp->next = malloc(sizeof(bitcoin_info));
        if (temp->next == NULL) {
            perror("Memory not allocated.");
            exit(-1);
        }
        temp->next->bitcoinID=bitcoinid;
        temp->next->amount=amount;
        temp->next->next=NULL;
    }
}
void insert_in_list_of_bitcoins(bitcoin_info** list,unsigned int bitcoinid, unsigned int amount){
    bitcoin_info *temp=*list;
    if(temp==NULL) {
        //First node in order to initialize the head of the list
        temp = malloc(sizeof(bitcoin_info));
        if (temp == NULL) {
            perror("Memory not allocated.");
            exit(-1);
        }
        temp->bitcoinID=bitcoinid;
        temp->amount=amount;
        temp->next=NULL;
        *list = temp;
    }else {
        if(temp->bitcoinID==bitcoinid){
            printf("Bitcoin %d already exists.Abort.\n",bitcoinid);
            exit(-1);
        }
        while (temp->next != NULL) {
            temp = temp->next;
            if(temp->bitcoinID==bitcoinid){
                printf("Bitcoin %d already exists.Abort.\n",bitcoinid);
                exit(-1);
            }
        }
        temp->next = malloc(sizeof(bitcoin_info));
        if (temp->next == NULL) {
            perror("Memory not allocated.");
            exit(-1);
        }
        temp->next->bitcoinID=bitcoinid;
        temp->next->amount=amount;
        temp->next->next=NULL;
    }
}
void print_list_of_bitcoins(bitcoin_info* list){
    bitcoin_info* temp=list;
    while (temp!=NULL){
        printf("Bitcoin %d Amount %d\n",temp->bitcoinID,temp->amount);
        temp=temp->next;
    }
}
void remove_bitcoin_from_list_of_bitcoins(bitcoin_info** list,int bitcoinId){
    bitcoin_info *temp=*list;
    bitcoin_info *help;
    if(bitcoinId==(*list)->bitcoinID){
        (*list)=(*list)->next;
        free(temp);
        return;
    }else{
        while(bitcoinId!=temp->next->bitcoinID && temp->next!=NULL){
            if(bitcoinId==temp->next->bitcoinID){ //Delete the middle node
                help=temp->next;
                temp->next=temp->next->next;
                free(help);
                return;
            }
            temp=temp->next;
        }
    }
    if(bitcoinId==temp->bitcoinID)
        free(temp);
}
void transaction_in_list_of_bitcoins(bitcoin_info** list,bitcoin_info **bitcoins_of_transaction,int amount){
    *bitcoins_of_transaction=NULL;
    bitcoin_info *temp=*list;
    int max=0,tmp;
    bitcoin_info *maxnode=NULL;
    if(temp==NULL){printf("Something is wrong..\n");exit(-1);}
    while (amount>0) {
        while (temp != NULL) {
            if (temp->amount > max) { //Find the bitcoin with the greatest amount of money
                max = temp->amount;
                maxnode = temp;
            }
            temp = temp->next;
        }
        tmp=maxnode->amount;
        maxnode->amount -= amount; //Remove the amount from the bitcoin

        //printf("Bitcoin %d is used %d %d\n",maxnode->bitcoinID,amount,amount-tmp);
        if((amount-tmp)<=0) {
            insert_in_list_of_bitcoins_transaction(bitcoins_of_transaction, maxnode->bitcoinID,(unsigned int)amount); //save the bitcoins to a list.
        }
        else { //if the amount of the bitcoin isn't enough, we use as amount the amount that it had
            insert_in_list_of_bitcoins_transaction(bitcoins_of_transaction, maxnode->bitcoinID,(unsigned int)tmp); //save the bitcoins to a list.
            //printf("Removing bitcoin!\n");
            remove_bitcoin_from_list_of_bitcoins(list,maxnode->bitcoinID);
        }
        amount-=tmp; //the amount that it is left. if it is >0 we have to find another bitcoin to pay

        temp=*list; //The process is repeated if more than one bitcoins are required
        max=0;
    }
}
void delete_list_of_bitcoins(bitcoin_info **list){
    bitcoin_info *temp;
    while (*list!=NULL){
        temp=*list;
        *list=(*list)->next;
        free(temp);
    }
}
short int find_in_list_of_bitcoins(bitcoin_info *list,int bitcoinID){
    bitcoin_info *temp=list;
    while(temp!=NULL){
        if(temp->bitcoinID==bitcoinID)
            return 1;
        temp=temp->next;
    }
    return 0;
}
int length_of_bitcoin_list(bitcoin_info* list){
    bitcoin_info *temp=list;
    int counter=0;
    while(temp!=NULL){ //parse the list and count the nodes in it
        counter++;
        temp=temp->next;
    }
    return counter;
}

void insert_in_list_of_strings(list_of_strings **list, char* string){
    list_of_strings *temp=*list;
    if(temp==NULL) {
        //First node in order to initialize the head of the list
        temp = malloc(sizeof(list_of_strings));
        if (temp == NULL) {
            perror("Memory not allocated.\n");
            exit(-1);
        }
        strcpy(temp->string,string);
        temp->next=NULL;
        *list = temp;
    }else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = malloc(sizeof(list_of_strings));
        if (temp->next == NULL) {
            perror("Memory not allocated.\n");
            exit(-1);
        }
        strcpy(temp->next->string,string);
        temp->next->next=NULL;
    }
}
void print_list_of_strings(list_of_strings *list){
    list_of_strings *temp=list;
    while (temp!=NULL){
        puts(temp->string);
        temp=temp->next;
    }
}
void delete_list_of_strings(list_of_strings **list){
    list_of_strings *temp;
    while (*list!=NULL){
        temp=*list;
        *list=(*list)->next;
        free(temp);
    }
}