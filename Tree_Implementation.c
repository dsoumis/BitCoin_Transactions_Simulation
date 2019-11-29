#include "Tree_Implementation.h"

tree_node* senderPos;
int max;
bool found;
void Postorder(tree_node* node,char* senderId){
    if (node == NULL) {
        return;
    }
    // first recur on left subtree
    Postorder(node->left,senderId);

    // then recur on right subtree
    Postorder(node->right,senderId);
    if(strcmp(node->userID,senderId)==0 && node->left==NULL && node->right==NULL && node->transaction.amount_of_transaction>max) {
        senderPos = node;
        max=node->transaction.amount_of_transaction;
        found=true;
    }

}

tree_node* insert_in_tree(tree_node* root_node,char* senderId,char *ReceiverId,int amount,struct date date,struct time time,char* transactionID){
    if(root_node==NULL){
        printf("NULL ROOT!!\n");
        exit(-1);
    }
    // Allocate memory for new node
    tree_node* node_left = malloc(sizeof(tree_node));
    if(node_left == NULL){
        perror("Memory not allocated.");
        exit(-1);
    }
    strcpy(node_left->userID,ReceiverId); //Copy the values of the transaction
    strcpy(node_left->received_from,senderId);
    node_left->transaction.amount_of_transaction=amount;
    node_left->transaction.date=date;
    node_left->transaction.time=time;
    strcpy(node_left->transaction.transactionID,transactionID);
    node_left->left=NULL;
    node_left->right=NULL;


    max=0;
    found=false;
    Postorder(root_node,senderId); //Find the position of the sender
    if(found==false){
        printf("Invalid sender!\n");
        return NULL;
    }
    strcpy(senderPos->send_to,ReceiverId); //Update the node of the sender to know its receiver
    senderPos->left=node_left;


    if(node_left->transaction.amount_of_transaction<senderPos->transaction.amount_of_transaction){ //If there are left money to the sender
        tree_node* node_right = malloc(sizeof(tree_node));
        if(node_right == NULL){
            perror("Memory not allocated.");
            exit(-1);
        }
        strcpy(node_right->userID,senderId);
        strcpy(node_right->received_from,senderId);
        node_right->transaction.amount_of_transaction=senderPos->transaction.amount_of_transaction-amount; //what's left of the money
        node_right->transaction.date=date;
        node_right->transaction.time=time;
        strcpy(node_right->transaction.transactionID,transactionID);
        node_right->left=NULL;
        node_right->right=NULL;
        senderPos->right=node_right;
    }

    return senderPos->left;

}
void printPreorder(tree_node* node){
    if (node == NULL)
        return;

    /* first print data of node */
    printf("%s %d\n", node->userID,node->transaction.amount_of_transaction);

    /* then recur on left sutree */
    printPreorder(node->left);

    /* now recur on right subtree */
    printPreorder(node->right);
}
void bitcoinstatus(tree_node* node,int *number_of_transactions,int *unspent_amount){
    if (node == NULL)
        return;

    if(strcmp(node->received_from,"noone")!=0 && strcmp(node->received_from,node->userID)!=0) { //if it is not the first node and not the right node of a transaction(the amount left)
        (*number_of_transactions)++;
        (*unspent_amount)-=node->transaction.amount_of_transaction;
    }
    /* then recur on left sutree */
    bitcoinstatus(node->left,number_of_transactions,unspent_amount);

    /* now recur on right subtree */
    bitcoinstatus(node->right,number_of_transactions,unspent_amount);
}

void tracecoin(tree_node* node){
    if (node == NULL)
        return;

    if(strcmp(node->received_from,"noone")!=0 && strcmp(node->received_from,node->userID)!=0) { //if it is not the first node and not the right node of a transaction(the amount left)
        printf("%s %s %s %d ",node->transaction.transactionID,node->received_from,node->userID,node->transaction.amount_of_transaction);
        if (node->transaction.date.day / 10 == 0)
            printf("0%d-",node->transaction.date.day);
        else
            printf("%d-",node->transaction.date.day);
        if (node->transaction.date.month / 10 == 0)
            printf("0%d-",node->transaction.date.month);
        else
            printf("%d-",node->transaction.date.month);
        printf("%d",node->transaction.date.year);
        if (node->transaction.time.hour / 10 == 0)
            printf(" 0%d:",node->transaction.time.hour);
        else
            printf(" %d:",node->transaction.time.hour);
        if (node->transaction.time.minute / 10 == 0)
            printf("0%d",node->transaction.time.minute);
        else
            printf("%d",node->transaction.time.minute);
        printf("\n");
    }
    /* then recur on left sutree */
    tracecoin(node->left);

    /* now recur on right subtree */
    tracecoin(node->right);
}
void delete_tree(tree_node* node){
    if (node == NULL)
        return;

    // first recur on left subtree
    delete_tree(node->left);

    // then recur on right subtree
    delete_tree(node->right);

    free(node);
}
