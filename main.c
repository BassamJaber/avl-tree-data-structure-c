/** ------------------------------------------------------**/
/** |  Student Name :Bassam Jaber                       | **/
/** |  ID Number : 1100413                              | **/
/** |  Project # 3 ( AVL Tree & Hashing)                | **/
/** |  SuperViser : Dr.Iyad Jaber                       | **/
/** ------------------------------------------------------**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
/** ------------------------------------------------------**/
/** |         Data Structure Of The Projects            | **/
/** ------------------------------------------------------**/

typedef struct node *treeptr;                             //pointer To the struct node that form the tree nodes
typedef struct customer *Customer;                        //pointer To the struct customer that form the array element

//Customer Struct that form the element of the  dynamic array in the nodes of the Avl Tree
struct customer
{
  long customerID;
  char customerName[80];
  double balance;
  int flag;                                    //flag=0 (not filled ) flag =1 ( filled) flag=2 ( deleted)
};

//AVl node Struct that form the node of the Avl tree that contain the banks
struct node
{
    char bankName[80];
    char bankLocation[30];
    long branchID;
    int numOfCustomers;
    int hashTableSize;
    Customer hashTable;                                //the Address of the Dynamic Array that Contain Customer Information
    treeptr left,right;
    int height;
};
typedef treeptr AVL;

/** ------------------------------------------------------**/
/** |               AVL Tree Functions                  | **/
/** ------------------------------------------------------**/

int getMax(int,int);                                   //function That return The Maximum Of two Elements
treeptr SRLR(treeptr);                                 //Single Rotate Left To Right to balance Avl Tree
treeptr SRRL(treeptr);                                 //Single Rotate Right To Left to Balance AVL Tree
int getHeight(treeptr);                                //Calculate the Hieght Of The Tree
treeptr DRRL(treeptr);                                 //double Rotate Right To Left To Balance AVL Tree
treeptr DRLR(treeptr);                                 //Double Rotate Left TO Right To Balance AVl Tree
treeptr findMin(treeptr);                              //Find Minimum Node In Th AVL Tree
treeptr findMax(treeptr);                              //Find Maximum Element In AVL Tree
treeptr insert(AVL,char[],char[],long);                //Insert Node To The AVL Tree
treeptr find(AVL,char[]);                              //Find A Specific Node In The AVL Tree
treeptr temp;                                          //Variable That Hold A Node For Using In Functions
void printTreeInOrder(treeptr);                        //Print AVL Tree In Order (Sorted) ( left root right)
void printTreePreOrder(treeptr);                       // Print AVL Tree PRe Order  (root left right)
void printTreePostOrder(treeptr);                      //Print AVl Tree Post Order  (left right Root)
/** ------------------------------------------------------**/
/** |             Read From File Function               | **/
/** ------------------------------------------------------**/
void BankTokenizer(char []);                            //Function That Tokenize the String into Bank node Elements
void CustomerTokenizer(char []);                        //Function That Tokenize The String Into Customer node Elements
void readFromFile( );                                   //Function That Open File and prepare EVery Thing To be Done
int countNumOfBank(char[]);                             // Function that Count The Number Of Banks In The File
void countCustomer(char[],int[],int);                   // Function That Count The Number Of Customers In Each Bank
treeptr TR;                                             // Variable That Hold the Tree Result After rading File
void toUpperCase(char []);                              //Function That Convert the String Into Upper Case
void toLowerCase(char []);                              //Function That Convert The String Into Lower Case
void trim(char[]);                                      //function That Trim the String Spaces ind Clean  it
/** ------------------------------------------------------**/
/** |                 Hashing Function                  | **/
/** ------------------------------------------------------**/
int getNextPrime(int);                                  //function That Find The First Prime After Specific Number
int isPrime(int);                                       //Function That Test If the Number Is Prime Or Not
void insertCustomer(treeptr);                           // Function That Insert A Customer Into Hash Table
void setHashSizeAndNumOfCus(int,treeptr);               //Function That Set The Number OF Customers And Create Hash Table
int getHashKey(long ,treeptr);                          //Function That Find The Key Of First Empty Node Quadratically
void printHashTable(treeptr);                           //Function That Print The Hash Table
void printHash(treeptr);                                //Function That Operate And Organize The Hashing Print
void printToFile();                                     // Function That Print The Tree Sorted Into File
void printHashTableFile(treeptr);                       // Function That Print The Hash Into File
void printHashFile(treeptr);                            //Function That Organiza The Hash Operation
void reHash(int,treeptr);                               // Function That re fill the Customer In New Table And Free The old
void printSpace(int);                                   //Function That PRint Spaces To Make Tables
void findCustomer();                                    // Function That Find A Specific Customer
int isIDExist(long ,treeptr);                           // Function That Test If The Id Exist
void caseInsert();                                      // Case Menu For Repeating Insert
/** ------------------------------------------------------**/
/** |               InterFace Function                  | **/
/** ------------------------------------------------------**/
void gotoxy(int,int);
void clrscr();
void printLine();
int menu();
int subMenu();
void mainMenuCase();
void subMenuCase();
/** ------------------------------------------------------**/
/** |                 Code Starts Here                  | **/
/** ------------------------------------------------------**/

int main()
{
    mainMenuCase();
    return 0;
}

// Function That Insert A Customer After Creating Hash Table And Read The File
void insertCustomer(treeptr TR)
{
    clrscr();
    gotoxy(23,3);
    printf("# Insert Customer To Specific Bank #\n\n");
    printLine();

   gotoxy(10,7);
   printf("Enter The Name Of the Bank: ");
   char bankName[80];
   scanf("%s",bankName);
   treeptr bank=find(TR,bankName);
   if(bank==NULL)
     {
         gotoxy(10,10);
         printf("Bank Not Found , Try Again");
     }else {
              char name[80];
              double balance;
              long id;

              gotoxy(10,10);
              printf("Enter The Name Of The Customer: ");
              fflush(stdin);
              gets(name);
              gotoxy(10,12);
              printf("Enter The Customer ID Number: ");
              scanf("%ld",&id);
              gotoxy(10,14);
              printf("Enter The Customer Balance: ");
              scanf("%lf",&balance);


    // Test If The ID Exist Or Not !!
              if(isIDExist(id,bank))
                {
                    gotoxy(10,16);
                    printf("Customer Exist , please Try Again");
                    caseInsert();

                }else {
                         int key;
                         int size=bank->hashTableSize;
                         //Rehashing is needed when the number Of the Current Customers is more Than The half of the table size
                         if(size/2 > bank->numOfCustomers )
                            {
                                key=getHashKey(id,bank);
                                bank->hashTable[key].customerID=id;
                                strcpy(bank->hashTable[key].customerName,name);
                                bank->hashTable[key].balance=balance;
                                bank->hashTable[key].flag=1;
                                bank->numOfCustomers++;
                            }else {
                                     bank->numOfCustomers++;   //Increment The Number Of Customers Then Rehashing
                                     reHash(bank->numOfCustomers,bank);
                                     //after finish rehashing continue inserting customer as before !
                                     key=getHashKey(id,bank);
                                     bank->hashTable[key].customerID=id;
                                     strcpy(bank->hashTable[key].customerName,name);
                                     bank->hashTable[key].balance=balance;
                                     bank->hashTable[key].flag=1;
                                  }

                        gotoxy(10,16);
                        printf("Customer Have Been Added !...");
                        caseInsert();
                      }
           }
}
//Function That Rehashing The TAble And Move The Content To The New Table
void reHash(int numOfCustomers , treeptr T)
{
   int oldHashSize=T->hashTableSize;
   Customer oldHashTable=T->hashTable;
   setHashSizeAndNumOfCus(numOfCustomers,T); //setting the new Size of the Hash Table To move every Thing
   int i;
   int key;

   for(i=0;i<oldHashSize;i++)
     {
         if(oldHashTable[i].flag==1)
            {
              key=getHashKey(oldHashTable[i].customerID,T);
              strcpy(T->hashTable[key].customerName,oldHashTable[i].customerName);
              T->hashTable[key].customerID=oldHashTable[i].customerID;
              T->hashTable[key].balance=oldHashTable[i].balance;
              T->hashTable[key].flag=1;
            }
     }
    free(oldHashTable);
}
// Case Print When FInish Inserting To Choise If Inserting Again Or Back
void caseInsert()
{
     char ch;
    do
    {
      gotoxy(10,20);
      printf("Do you Want To Insert Another Customer Yes <Y> OR No <N>");
      ch=getch();
    }while(!strchr("YynN",ch));

    if((ch-'y')==0||(ch-'Y')==0)
     {insertCustomer(TR);}
    else
    {
      gotoxy(10,22);
      printf("Press Any Key To Return To Main Menu");
    }
}

//Function That Test If The ID Exist When Inserting
int isIDExist(long id ,treeptr bank)
{
     int key=id%bank->hashTableSize;
     int tempKey,i=1;
     tempKey=key;

     /*strncmp(bank->hashTable[tempKey].customerName,name,strlen(name))!=0
       if we want to compare name to*/

      while((bank->hashTable[tempKey].flag!=0)&&(bank->hashTable[tempKey].customerID!=id))
            {
              tempKey=key;
              tempKey+=pow(i,2);
              tempKey=tempKey%bank->hashTableSize;
              i++;
            }

            key=tempKey;

      if((bank->hashTable[key].flag==1)&&((bank->hashTable[tempKey].customerID==id)))
         {
            return 1;
         }else {
            return 0;
               }
    return 1;
}

//Fucnction that Search For A Specific Bank
treeptr find(AVL T, char bankName[])
{
    if(T==NULL)
       return NULL;
    else{ if(strncmp(bankName,T->bankName,strlen(bankName))>0)
             return find(T->right,bankName);
          else
          if( strncmp(bankName,T->bankName,strlen(bankName))<0)
               return find(T->left,bankName);
        }
    return T;
}

//Function That Find A Specific Customer In The Hash Table
void findCustomer(treeptr TR)
{
   clrscr();
   gotoxy(20,5);
   printf("|*| Find A Customer in A Specific Bank|*|");
   gotoxy(10,8);

   printf("Enter The Name Of the Bank:");
   char bankName[80];
   long id;
   scanf("%s",bankName);
   treeptr bank;
   bank=find(TR,bankName);

   if(bank==NULL)
     {
         gotoxy(10,10);
         printf("Bank Not Found , Try Again");
     }else {
               gotoxy(10,10);
               printf("Enter The Name of The Customer :");
               char name[80];
               fflush(stdin);
               gets(name);
               gotoxy(10,12);
               printf("Enter The ID of The Customer : ");
               scanf("%ld",&id);

              int key=id%bank->hashTableSize;

              int tempKey,i=1;
              tempKey=key;
               /*strncmp(bank->hashTable[tempKey].customerName,name,strlen(name))!=0
              if we want to compare name to*/
              while((bank->hashTable[tempKey].flag!=0)&&(bank->hashTable[tempKey].customerID!=id))
              {
                  tempKey=key;
                  tempKey+=pow(i,2);
                  tempKey=tempKey%bank->hashTableSize;
                  i++;
              }

              key=tempKey;
              /*strncmp((bank->hashTable[key].customerName),name,strlen(name)))==0)*/
              if((bank->hashTable[key].flag==1)&&((bank->hashTable[tempKey].customerID==id)))
                 {
                       gotoxy(10,14);
                       printf("Customer ID:%ld",bank->hashTable[key].customerID);
                       gotoxy(10,16);
                       printf("Customer Name:%s",bank->hashTable[key].customerName);
                       gotoxy(10,18);
                       printf("Customer Balance:%0.2f",bank->hashTable[key].balance);
                 }else {
                          gotoxy(10,15);
                          printf("Customer Not Found In This Bank");
                       }
           }
    char ch;
    do
    {
      gotoxy(10,20);
      printf("Do you Want To Search Another Customer Yes <Y> OR No <N>");
      ch=getch();
    }while(!strchr("YynN",ch));

    if((ch-'y')==0||(ch-'Y')==0)
     {findCustomer(TR);}
    else
    {
      gotoxy(10,22);
      printf("Press Any Key To Return To Main Menu");
    }
}

//Function That Insert A Node Into AVL Tree With Inside Balance
treeptr insert(AVL T , char bankName[], char bankLocation[],long branchID)
{
    if(T==NULL)
    {
        T=(treeptr)malloc (sizeof(struct node));
        strcpy(T->bankName,bankName);
        strcpy(T->bankLocation,bankLocation);
        T->branchID=branchID;
        T->left=T->right=NULL;
        T->height=0;
        temp=T;
    }else if(strcmp(bankName,T->bankName)>0)
         {
             T->right=insert(T->right,bankName,bankLocation,branchID);
             if(fabs(getHeight(T->left)-getHeight(T->right))>1)
             {
                 //if The Element Inserted in The Right And it Is Larger Than The Elemnet Of The Right
                 // Of The Node That have Error Then tree Elements Are ine The Same Line we need
                 //Single Rotate Right To Left else It Will Make An Angle So We Need Double Rotate
                 if(strcmp(bankName,T->right->bankName)>0)
                    {
                        T=SRRL(T);
                    }else{
                            T=DRRL(T);
                         }
             }

         }else{
               T->left=insert(T->left,bankName,bankLocation,branchID);
            if(fabs(getHeight(T->left)-getHeight(T->right))>1)
             {
                //if The Element Inserted in The Right And it Is Smallest Than The Elemnet Of The Left
                 // Of The Node That have Error Then tree Elements Are ine The Same Line we need
                 //Single Rotate Left To Right else It Will Make An Angle So We Need Double Rotate
                 if(strcmp(bankName,T->left->bankName)<0)
                    {
                        T=SRLR(T);
                    }else{
                            T=DRLR(T);
                         }
             }
         }
        T->height=getHeight(T);
     return T;
}
/**-------------------------------------------------------------------**/
/**                        Print Data Functions                       **/
/**-------------------------------------------------------------------**/
//Print Spaces To Make Tables When Printing
void printSpace(int x)
{
   int i;
   for(i=0;i<x;i++)
       printf(" ");
}
//Print The Tree Inorder To The Screen
void printTreeInOrder(AVL T)
{
    if(T!=NULL)
    {
        printTreeInOrder(T->left);

        printf("\t%s",T->bankName);
        printSpace((40-strlen(T->bankName)));
        printf("%s",T->bankLocation);
        printSpace((20-strlen(T->bankLocation)));
        printf("%ld\n\n",T->branchID);

        printTreeInOrder(T->right);
    }
}
//print The Tree Into Screen PRe Order
void printTreePreOrder(AVL T)
{
    if(T!=NULL)
    {
        printf("\t%s",T->bankName);
        printSpace((40-strlen(T->bankName)));
        printf("%s",T->bankLocation);
        printSpace((20-strlen(T->bankLocation)));
        printf("%ld\n\n",T->branchID);

        printTreePreOrder(T->left);
        printTreePreOrder(T->right);
    }
}
//Print The Tree PostOrder
void printTreePostOrder(AVL T)
{
    if(T!=NULL)
    {
        printTreePostOrder(T->left);
        printTreePostOrder(T->right);

        printf("\t%s",T->bankName);
        printSpace((40-strlen(T->bankName)));
        printf("%s",T->bankLocation);
        printSpace((20-strlen(T->bankLocation)));
        printf("%ld\n\n",T->branchID);
    }
}
/**------------------------------------------------------------**/
/**                      Tree Functions                        **/
/**------------------------------------------------------------**/
//Single Rotate Left to Right
treeptr SRLR(treeptr k2)
{
    treeptr k1;
    k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;

    k2->height=getMax(getHeight(k2->left),getHeight(k2->right))+1;
    k1->height=getMax(getHeight(k1->left),getHeight(k1->right))+1;

    return k1;
}

//Single Rotate Right To Left
treeptr SRRL(treeptr k2)
{
    treeptr k1;
    k1=k2->right;
    k2->right=k1->left;
    k1->left=k2;

    k2->height=getMax(getHeight(k2->left),getHeight(k2->right))+1;
    k1->height=getMax(getHeight(k1->left),getHeight(k1->right))+1;

    return k1;
}

//double Rotate Left To Right
treeptr DRLR(treeptr k3)
{
    k3->left=SRRL(k3->left);
    return (SRLR(k3));
}
//double Rotate Right To Left
treeptr DRRL(treeptr k3)
{
    k3->right=SRLR(k3->right);
    return (SRRL(k3));
}

// calculate the height of a node
int getHeight(treeptr T)
{
    if(T==NULL)
       return -1;
    else
        return (getMax(getHeight(T->left),getHeight(T->right))+1);
}
// find minimum element in the tree
// minimum is in tha maximum left

treeptr findMin(treeptr T)
{
    if(T==NULL)
       return T;
    else if (T->left!=NULL)
            return findMin(T->left);
         else
         return T;
}
//find maximum element is in the maximum right of the tree
treeptr findMax(treeptr T)
{
  if(T!=NULL)
   {
     while(T->right!=NULL)
          T=T->right;
   }
   return T;
}
//find the max of two numbers
int getMax(int A, int B)
{
    if(A>B)
       return A;
    else
       return B;
}


/**------------------------------------------------------------**/
/**                  Program other Functions                   **/
/**------------------------------------------------------------**/

FILE*pFile;
// print List to a file that determined by a user
void printToFile()
{
  clrscr();
  gotoxy(15,5);
  printf("<*** Print Banks and Customers Infromation To File ***>");
  gotoxy(20,8);
  printf("Enter The Name of The File :");
  gotoxy(20,9);

  char fileName[20];
  scanf("%s",fileName);
  pFile=fopen(fileName,"w");

  printHashTableFile(TR);

  fclose(pFile);
  gotoxy(20,12);
  printf("Banks Infromation Have Been Added To File %s ",fileName);
  gotoxy(20,14);
  printf("Press Any Key To Return To Main Menu");
}
//PRint All Hash Table From ALl Banks Into File
void printHashTableFile(treeptr T)
{
     if(T!=NULL)
    {
        printHashTableFile(T->left);
        fprintf(pFile,"\n%s,",T->bankName);
        fprintf(pFile,"%s,",T->bankLocation);
        fprintf(pFile,"%ld\n",T->branchID);
        printHashFile(T);
        printHashTableFile(T->right);
    }
}
//print The Hash Table Into A File
void printHashFile(treeptr T)
{
    int i;
    for(i=0;i<T->hashTableSize;i++)
        if(T->hashTable[i].flag==1)
           {
               fprintf(pFile,"%ld,",T->hashTable[i].customerID);
               fprintf(pFile,"%s,",T->hashTable[i].customerName);
               fprintf(pFile,"%0.2f\n",T->hashTable[i].balance);
           }
}

//Delete A Customer From A Hash Table
void deleteCustomer()
{
  clrscr();
  gotoxy(18,4);
  printf("|*| Delete A Customer From Specific Bank |*|");

   gotoxy(10,8);
   printf("Enter The Name Of the Bank:");
   char bankName[80];
   scanf("%s",bankName);
   treeptr bank;
   bank=find(TR,bankName);
   if(bank==NULL)
     {
         gotoxy(10,10);
         printf("Bank Not Found , Try Again");
     }else {
              gotoxy(10,10);
              printf("Enter The Name of The Customer :");
              char name[80];
              fflush(stdin);
              gets(name);
              gotoxy(10,12);
              printf("Enter The ID of the Customer :");
              long id;
              scanf("%ld",&id);

              int key=id%bank->hashTableSize;

              int tempKey,i=1;
              tempKey=key;
              //Search For The ID In The Hash Table
              while((bank->hashTable[tempKey].flag!=0)&&(bank->hashTable[tempKey].customerID!=id))
              /*strncmp(bank->hashTable[tempKey].customerName,name,strlen(name))!=0
              if we want to compare name to*/
              {
                  tempKey=key;
                  tempKey+=pow(i,2);
                  tempKey=tempKey%bank->hashTableSize;
                  i++;
              }

              key=tempKey;
              /*strncmp((bank->hashTable[key].customerName),name,strlen(name)))==0)*/
              if((bank->hashTable[key].flag==1)&&((bank->hashTable[tempKey].customerID==id)))
                 {
                    bank->numOfCustomers--;
                    bank->hashTable[key].flag=2;
                    gotoxy(10,15);
                    printf("Customer Have been Deleted ");
                 }else {
                          gotoxy(10,15);
                          printf("Customer Not Found In This Bank");
                       }
           }
     char ch;
    do
    {
      gotoxy(10,18);
      printf("Do you Want To Delete Another Customer Yes <Y> OR No <N>");
      ch=getch();
    }while(!strchr("YynN",ch));

    if((ch-'y')==0||(ch-'Y')==0)
     {deleteCustomer();}
    else
    {
      gotoxy(10,20);
      printf("Press Any Key To Return To Main Menu");
    }

}

//Function That Read Bank & Customers Data From A Specific Bank
void readFromFile()
{
  char fileName[20];
  char string[80];
  FILE*pFile;

  clrscr();
  gotoxy(19,5);
  printf("<*** Scan Bank Information From File ***>");
  gotoxy(10,8);
  printf("Enter The Name Of the File \n");
  gotoxy(10,10);
  scanf("%s",fileName);

  int numBank=countNumOfBank(fileName);
  int customer[numBank];
  countCustomer(fileName,customer,numBank);

  pFile=fopen(fileName,"r");

  int i=0;
  if(pFile==NULL)
     {
        gotoxy(15,13);
        printf("File Does Not Exist");
        gotoxy(15,15);
        printf("Press any Key to Try Again");
     }else
     {
         while( feof(pFile)== 0)
         {
          fgets(string,80,pFile);
          if(string[0]=='#')
             {
                 BankTokenizer(string);
                 setHashSizeAndNumOfCus(customer[i++],temp);
             }else {
                       CustomerTokenizer(string);
                   }
         }
     }
     gotoxy(15,13);
     printf("File Has been read Succesfully ");
     gotoxy(15,15);
     printf("and Data Have Been Inserted into AVL Tree And Hash Table ");
     gotoxy(15,17);
     printf("Press Any Key To Return To Main Menu ");
     fclose(pFile);
}

//Function That Tokenize The String That Contain The Customer InforMation And Insert tit Into Hash Table
void CustomerTokenizer(char string[])
{
  char *result=NULL;

   char customerName [80];
   double balance;
   long customerID=0;
   int count=0;
   result=strtok(string,",");

   while(result!=NULL)
   {
      count++;

       if(count==1)
       {
         customerID=atol(result);
       }else if(count==2)
              {
                strcpy(customerName,result);
              }else if(count==3)
                       {
                         balance=atof(result);
                       }

       result=strtok(NULL,",");
   }
   trim(customerName);


   int key;
   key=getHashKey(customerID,temp);
   temp->hashTable[key].customerID=customerID;
   strcpy((temp->hashTable[key].customerName),customerName);
   temp->hashTable[key].balance=balance;
   temp->hashTable[key].flag=1;
}

//Function That Find The First Empty Space using Quadratic Hashing For Solving Collesions
int getHashKey(long ID,treeptr temp)
{
    int key;
    int i=1;
    key=ID%(temp->hashTableSize);
    int tempKey=key;
    while(temp->hashTable[tempKey].flag==1)
          {
             tempKey=key;
             tempKey+=pow(i,2);
             tempKey=tempKey%temp->hashTableSize;
             i++;
          }
          key=tempKey;
     return key;
}
//Setting The Hash Elements In A Tree Node By Knowing The Number Of customers
void setHashSizeAndNumOfCus(int customerNum,treeptr temp)
{
    if(customerNum!=0)
    {
      temp->numOfCustomers=customerNum;
      temp->hashTableSize=getNextPrime(customerNum*2);
      temp->hashTable=(Customer)malloc((temp->hashTableSize)*sizeof(struct customer));
    }else {
            temp->numOfCustomers=customerNum;
            temp->hashTableSize=1;
            temp->hashTable=(Customer)malloc(sizeof(struct customer));
          }
}

//Function That Find The Next Prime Number After A Number
int getNextPrime(int customerNum)
{
    int i=customerNum;

     while(!isPrime(i))
        i++;
    return i;
}
//test if a Number is Prime OR NOT
int isPrime(int number)
{
   int x ;
   for(x=2;x<=number/2;x++)
       if(number%x==0)
         return 0 ;
return 1;
}

//Count The Number Of Customers In The file Given
void countCustomer(char fileName[],int customer[],int bankNum)
{
  FILE *pFile;
  char string[80];
  int j;
  for(j=0;j<bankNum;j++)
     customer[j]=0;

  pFile=fopen(fileName,"r");

  int index=-1;
  if(pFile!=NULL)
     {
         while( feof(pFile)== 0)
         {
          fgets(string,80,pFile);
          if(string[0]=='#')
             index++;
             else{
                  customer[index]++;
                 }
         }
     }
     fclose(pFile);
}

//Function That Count The Number Of Banks In The File Given
int countNumOfBank(char fileName[])
{
  FILE*pFile;
  char string[80];
  pFile=fopen(fileName,"r");
  int countBank=0;

  if(pFile!=NULL)
     {
         while( feof(pFile)== 0)
         {
          fgets(string,80,pFile);
          if(string[0]=='#')
             countBank++;
         }
     }
     fclose(pFile);

   return countBank;
}
//Function That Tokenize A String to Bank Elements Node And Insert It Into The Tree
void BankTokenizer(char string[])
{
   char *result=NULL;

   char bankName [80];
   char bankLocation [80];
   long BranchID=0;
   int count=0;

   string[0]=' ';
   result=strtok(string,",");


   while(result!=NULL)
   {
      count++;

       if(count==1)
       {
          strcpy(bankName,result);
       }else if(count==2)
              {
                  strcpy(bankLocation,result);
              }else if(count==3)
                       {
                         BranchID=atol(result);
                       }

       result=strtok(NULL,",");
   }
   trim(bankName);
   trim(bankLocation);
   TR=insert(TR,bankName,bankLocation,BranchID);
}


/**------------------------------------------------------------**/
/**                       String Functions                     **/
/**------------------------------------------------------------**/

//Convert A String Into Lower Case

void toLowerCase(char string[])
{
    int i ;
    for(i=0;i<strlen(string);i++)
    {
        if('A'<=string[i] && 'Z'>=string[i])
           string[i]=(char)(string[i]+32);
    }
}

//Convert The String Into Upper Case
void toUpperCase(char string[])
{
    int i ;
    for(i=0;i<strlen(string);i++)
    {
        if('a'<=string[i] && 'z'>=string[i])
           string[i]=(char)(string[i]-32);
    }
}

//Function That Trim A String Spaces (from First And Last)
void trim(char string[])
{
    int i=0;
    char trimString[80];
    //find The Index Of The First Letter In A String
    while(string[i]==' ')
    {
      i++;
    }
    //Move the String Into Another String Without First Spaces
    int j;
    for(j=0;i<strlen(string);i++,j++)
       {
           trimString[j]=string[i];
       }
       trimString[j]='\0';
    i=strlen(trimString)-1;
    //Finish The String by Null After The Last Character
    while(trimString[i]==' ')
    {
        i--;
    }
    trimString[i+1]='\0';
    strcpy(string,trimString);
}


/**-------------------------------------------------------------**/
/**                     Menu & Interface Function               **/
/**-------------------------------------------------------------**/

//Function That Quit The Program
void quite()
{
    clrscr();
    gotoxy(15,8);
    printf("Student Name : Bassam Jaber ");
    gotoxy(15,10);
    printf("Student ID # :1100413 ");
    gotoxy(25,13);
    printf("<****  HAVE A NICE DAY  ****>");
    gotoxy(30,15);
    printf("<**** GoodBye ****>");
    gotoxy(30,20);
    exit(0);
}

//Main Menu Cases When Selecting A choice
void mainMenuCase()
{
     char i;
    char ch;
    system("color 17");
    for( ; ; )
    {
        clrscr();
        i=menu();

        switch(i)
        {
            case 1:readFromFile();
                   break;
            case 2:subMenuCase();
                   break;
            case 3:insertCustomer(TR);
                   break;
            case 4:deleteCustomer();
                   break;
            case 5:findCustomer(TR);
                   break;
            case 6:printToFile();
                   break;
            case 7: quite();
                   break;
        }
        ch=getch();
    }
}
//Print The Banks Pre Order (root left Right)
void preOrder()
{
    clrscr();
    gotoxy(23,3);
    printf("<** Bank Information PreOrder **>\n\n\n");
    printLine();
    printf("\n\tBank Name\t\t\t\tBankLocation\tBranch ID\n");
    printLine();
    printf("\n");
    printTreePreOrder(TR);
    printLine();
    printf("\n");
}
//print The Banks In order
void inOrder()
{
    clrscr();
    gotoxy(23,3);
    printf("<** Bank Information InOrder **>\n\n\n");
    printLine();
    printf("\n\tBank Name\t\t\t\tBankLocation\tBranch ID\n");
    printLine();
    printf("\n");
    printTreeInOrder(TR);
    printLine();
    printf("\n");
}

//print Tree banks postorder
void postOrder()
{
    clrscr();
    gotoxy(23,3);
    printf("<** Bank Information PostOrder **>\n\n\n");
    printLine();
    printf("\n\tBank Name\t\t\t\tBankLocation\tBranch ID\n");
    printLine();
    printf("\n");
    printTreePostOrder(TR);
    printLine();
    printf("\n");
}
//Funtion That Organize The Printing Procedure
void printAllCustomers()
{
    clrscr();
    gotoxy(20,3);
    printf("|*|Customers Data in All Banks |*|\n");
    printHashTable(TR);
    printLine();
    printf("\n Press Any Key To Return to Main Menu");
}

//Function That Print All The Customers In ALL Banks Recursivly
void printHashTable(treeptr T)
{
     if(T!=NULL)
    {
        printHashTable(T->left);
        printf("\n\n\n");
        printLine();
        printf("\n\t%s",T->bankName);
        printSpace((40-strlen(T->bankName)));
        printf("%s",T->bankLocation);
        printSpace((20-strlen(T->bankLocation)));
        printf("%ld\n\n",T->branchID);
        printLine();
        printf("\n");
        printHash(T);
        printHashTable(T->right);
    }
}
//print The Customer Node Elements
void printHash(treeptr T)
{
    int i;
    for(i=0;i<T->hashTableSize;i++)
        if(T->hashTable[i].flag==1)
           {
               printf("\t%ld\t\t",T->hashTable[i].customerID);
               printf("\t%s",T->hashTable[i].customerName);
               printSpace((30-strlen(T->hashTable[i].customerName)));
               printf("%0.2f\n",T->hashTable[i].balance);
           }
}
//Sub menu Cases For Printing The Tree
void subMenuCase()
{
    int i;
    char ch;
    system("color 17");
    for( ; ; )
    {
        clrscr();
        i=subMenu();
        switch(i)
        {
            case 1:preOrder();
                   break;
            case 2:inOrder();
                   break;
            case 3:postOrder();
                   break;
            case 4:printAllCustomers();
                   break;
            case 5:mainMenuCase();
        }
        ch=getch();
    }
}

//Funtion That Print A Line Used For InterFace
void printLine()
{
    int i;
    for(i=0;i<80;i++)
        printf("%c",220);
}

//Cases For Sub Menu When Choosing A Number
int subMenu()
{
    clrscr();
    char ch;
    do
    {
      gotoxy(30,5);
      printf("<**** Sub Menu ****>");
      gotoxy(20,8);
      printf("1-print Banks PreOrder");
      gotoxy(20,10);
      printf("2-print Banks InOrder");
      gotoxy(20,12);
      printf("3-Print Banks PostOrder");
      gotoxy(20,14);
      printf("4-Print All Customers from All Banks");
      gotoxy(20,16);
      printf("Press <5> to Return To Main Menu");
      gotoxy(20,18);
      printf("Enter Your Choice :");
      ch=getch();
    }while(!strchr("12345",ch));

   return (ch-48);
}
//Menu Interface That Contain The Main Menu
int menu()
{
  clrscr();
  char ch;
  do
  {
      gotoxy(31,4);
      printf("<*** Main Menu ***>");
      gotoxy(20,6);
      printf("1- Read Bank Data (From File)");
      gotoxy(20,8);
      printf("2- Print Bank & Customer Information ");
      gotoxy(20,10);
      printf("3- Insert Customer To Specific Bank");
      gotoxy(20,12);
      printf("4- Delete Customer from Specific Bank ");
      gotoxy(20,14);
      printf("5- Search Customer From Specific Bank ");
      gotoxy(20,16);
      printf("6- Print Customer Infromation To File (inOrder)");
      gotoxy(20,18);
      printf("7- Quit");
      gotoxy(20,20);
      printf("Enter Your Choice : ");
      ch=getch();
  }while(!strchr("1234567",ch));

    return (ch-48);
}

//implementation for gotoxy to go to Specific place in the screen
void gotoxy(int x,int y)
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = x;
    Position.Y = y;
    SetConsoleCursorPosition(hOut,Position);
}

//implementation for clear Screen To Clear The Screen
void clrscr()
{
    HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hndl, &csbi);
    DWORD written;
    DWORD N = csbi.dwSize.X * csbi.dwCursorPosition.Y + csbi.dwCursorPosition.X + 1;
    COORD curhome = {0,0};
    FillConsoleOutputCharacter(hndl, ' ', N, curhome, &written);
    csbi.srWindow.Bottom -= csbi.srWindow.Top;
    csbi.srWindow.Top = 0;
    SetConsoleWindowInfo(hndl, TRUE, &csbi.srWindow);
    SetConsoleCursorPosition(hndl, curhome);
}
