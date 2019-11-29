Introduction 

The program will receive, process, record and answer queries about Bitcoin transactions. Specifically, a set of structures (hash tables, linked lists, trees) that allow the insertion and querying of large volumes of bitCoinTransaction records. Although data will be derived from files, eventually all records will be stored only in the main memory.

Application Interface 

The application will be called bitcoin and will be used as follows: 

./bitcoin -a bitCoinBalancesFile –t transactionsFile -v bitCoinValue –h1 senderHashtableNumOfEntries –h2 receiverHashtableNumOfEntries –b bucketSize

where: 
- The application parameter bitCoinValue is the value (in $) of a bitcoin. 
- The senderHashtable1NumOfEntries parameter is the number of places in a hash table that the application will hold for tracking sender information. 
- The receiverHashtable1NumOfEntries parameter is the number of places in a hash table that the application will hold for locating recipient information. 
- The bucketSize parameter is the number of Bytes that gives the size of each bucket in the hash tables. 
- BitCoinBalancesFile (or another file name) is a file that contains the initial balances of users participating in the bitcoin network. Each line in this file is a list of bitCoin IDs owned by a specific userID. For example if the contents of the file are: 

Mia 123 337 880 667 

Kylian 456 767 898 

Katerina 222 567 003
 
means we initially have three users participating in the network. Mia has four bitcoins, with bitCoinIDs 123, 337, 880, 667, Kylian has three bitcoins with IDs 456, 767, 898, etc.

- TransactionsFile (or another file name) is a file that contains a series of requests (transactions) for processing. Each line in this file describes a transaction with the sender's and the recipient's userIDs and the amount (in $) the sender sends. 

For example if the contents of the file are: 

889 Maria Ronaldo 50 25-12-2018 20:08 

776 Lionel Antonella 150 14-02-2019 10:05 

means we have two transactions where Maria asks to send $ 50 to Ronaldo on the 25-12-2018, 8:08 pm Lionel asks to send Antonella $ 150 on 14-2-2019, 10:05 am.

Specifically, a transaction log / request is an ASCII line of text consisting of the following: 
1. transactionID: a string (may have only digits) that uniquely defines each such transaction. 
2. senderWalletID: a string consisting of letters.
3. receiverWalletID: a string consisting of letters. 
4. value: the amount of the transaction.
5. date: the date the transaction request is made. It should be in DD-MM-YYYY format where DD expresses the day, MM the month, and YYYY the time of request. 
6. time: 24 hour time that the transaction request is made. It should be in the form HH: MM where HH expresses the time and MM the minute.

To begin, the application will need to opens the bitCoinBalancesFile and transactionsFile files, read the lines one by one, and initialize and store the data structures it will use when executing queries. It checks that the data in the files is valid. For example, if in the bitCoinBalancesFile file there are users who own the same bitcoin, it handles the error by presenting the appropriate message and exiting the application. Also, if it finds a transaction that is invalid while processing transactionsFile, then the application should present a message that the transaction is not feasible and is canceled. One such case is when in a transaction, the sender does not have enough money in his wallet to make the transaction.

When the application finishes processing the bitCoinBalancesFile and transactionsFile files, it will wait for user input from the keyboard. The user will be able to give the following commands: 
- / requestTransaction senderWalletID receiverWalletID amount date time 

The user requests that amount of money be sent from user with userID senderWalletID to user with userID receiverWalletID. The date and time should be after the last transaction recorded by the application, otherwise the request is rejected. If no date and time are given, the application uses the current time to record the execution time of the transaction. Also, the application checks if there is enough money to execute the transaction successfully. If available, it updates the appropriate structures (see below) and presents a run-through message to the user with details of the transaction. If not, the application will send a message to the user.

- / requestTransactions senderWalletID receiverWalletID amount date time; 

senderWalletID2 receiverWalletID2 amount2 date2 time2; 

… 

SenderWalletIDn receiverWalletIDn amountn daten timen; 

The user requests a number of transactions to be executed. Transactions are separated by ";". The application checks the validity of each transaction and accordingly updates their data structures and presents a result message to the user.
 - / requestTransactions inputFile
 
 The user requests that transactions described in the inputFile be executed. Transactions are separated by ";" and have the same format as a query by requestTransaction(s). The application checks the validity of each transaction and accordingly, updates the data structures and presents a result message to the user. 
 
 - / findEarnings walletID [time1] [year1] [time2] [year2] 
 
 The application first returns the total amount received by transactions with the userID walletID (by selection in time and / or date range). If there is a definition for [time1] there should be a definition for [time2]. The same applies to the use of non-compulsory
parameters [year1] and [year2]. It then presents all user transaction logs (as recipients) that were successfully executed within that period. If no space is specified then the application will show the complete transaction history where walletID is the recipient.

- / findPayments walletID [time1] [year1] [time2] [year2] 

The application returns the total amount that the user has successfully sent through transactions with userID walletID (with time and / or date range option). It then presents all user transaction logs (as sender) that were successfully executed within the time given in the command line. If no space is specified, then the application will show the complete transaction history where walletID is a sender.

- / walletStatus walletID 

The application returns the current amount that is in the wallet walletID.

- / bitCoinStatus bitCoinID 

The application returns the original value of bitcoin with bitCoinID ID, the number of transactions used, and the amount of unspent bitCoinID (ie not used in a transaction). 
Output example: 124 10 50 
means that bitcoin 124 has been used in 10 transactions while 50 units of its value have not yet been used in a transaction. 
- / traceCoin bitCoinID 

The application returns the transaction history in which bitcoin bitCoinID is involved. 

Example output: 

/ tracecoin 124 

889 Maria Ronaldo 50 25-12-2018 20:08 

776 Lionel Antonella 150 14-02-2019 10:05
 
Maria gave Ronaldo 50 points on 25/12/2018 (via transaction # 889) and Lionel 150 points on Antonella on 14/2/2019 (via transaction # 776). 
- / exit 

Exit the application.Frees up all the cached memory.

Data structures used:
1. Two index tables (senderHashTable and receiverHashTable) that index fast access to successfully executed transaction data. The first hash table essentially provides access to transaction data where walletID is a sender. The second table does the opposite: for each walletID it provides access to transaction data where the walletID is a recipient. Hash tables use buckets to handle walletIDs that show collision (that is, the hash function results in the same hash table element). If more than one bucket is needed to store data, it is dynamically generated and arranged in a list. 
2. For every walletID that is hashed into a senderHashTable element, there is a set of transactions to which it sends. This set is placed in a dynamic linked list. Each node in the list contains access to transaction data. Corresponding structures are also created with the receiverHashTable. 
3. For each walletID, a list that contains access to wallet elements. When the application processes a transaction, it  checks that there is enough money in the sender's wallet before proceeding with the transaction. Where applicable, all appropriate data structures are properly updated when executing the transaction. 
4. A tree for each bitCoinID that holds the entire bitcoin trading history and is dynamically created as they process transactions involving that bitcoin. The root node of the tree will contain the walletID of the original owner of bitCoinID, and the initial value of bitCoinID. To execute a transaction, if some money from bitCoinID (from the sender's wallet) is needed, the application adds a new node (leaf) to the tree containing the recipient's walletID and the amount he received. Also, if there is balance in the bitcoin after the transfer, a second new node should be added that reflects the bitcoin balance remaining in the sender.