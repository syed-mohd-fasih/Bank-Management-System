//-------------------------------------------------------------Header Files---------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
//------------------------------------------------------------------Global Variables-----------------------------------------------------
int n = 0;
FILE *dataptr;
//-------------------------------------------------------------Main Structure------------------------------------------------------------
struct Customer {
	char c_name[30];
	char c_type;
	int c_id;
	int c_accno;
	int c_age;
	int c_bal;
	int c_pass;
};
struct Customer c; // Global Structure Variable
//----------------------------------------------------User Defined Functions Declaration------------------------------------------
int menu();
void login();
void input_record();
void display_record();
void show();
void showData();
void delete_record();
void transaction();
void settings();
void load();
void key();
void pass();
int getaccno();
//-----------------Main Function (Just a “Menu” for the user with calls to the already defined functions)-----------
int main(){
	int p=0;
	system("COLOR f4");
	srand(time(NULL));
	login();
	pass();
	int opt;
	while(1){
		opt = menu();
		switch(opt){
			case 1:
				input_record();
				break;
			case 2:
				delete_record();
				break;
			case 3:
				showData();
				break;
				case 4:
					system("CLS");
					printf("\n\n\t\tEnter your password for confirmation that you are admin : ");
					scanf("\n\n\t\t%d", &p);
					if(p==3456)
					{
						display_record();
					}
					else
					{
						printf("\n\nWrong Password!");
						key();
					}
					break;
			case 5:
				transaction(1);
				break;
			case 6:
				transaction(2);
				break;
			case 7:
				settings();
				break;
			case 8:
				exit(0);
			default:
				printf("\nINVALID CHOICE!\n");
					key();
		}
	}
	return 0;
}
//-------------------------------------------------------Welcome Screen----------------------------------------------------------------
void login(){
	int i;
	printf("*\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t********WELCOME TO*********\n     \t\t\t\t*********BANK MANAGEMENT SYSTEM*********\n\n");
	load();
	key();
}
//---------------------------------------------------------------------------------------------------------------------------------------------
void transaction(int choice){
	FILE *newptr;
	char name[20] = {0};
	int pass = 0, i = 0, x, amt, flag=0;
	newptr = fopen("update.txt","a");
	dataptr = fopen("customers.txt", "r");
	system("CLS");
	printf("\n\n\n\n\n\nENTER YOUR ACCOUNT NAME AND PASSWORD: ");
	scanf("%s %d", name, &pass);
	while(fread(&c,sizeof(struct Customer),1,dataptr)){
		x = strcmp(name, c.c_name);
		if(pass == c.c_pass && x == 0){
			flag=1;
			switch(choice){
				case 1:
					printf("\n\t\t\tCURRENT BALANCE: %d", c.c_bal);
					l:
					printf("\n\n\t\t\tENTER THE AMOUNT : ");
					scanf(" %d", &amt);
					if(amt>c.c_bal)
					{
						printf("\n\nAmount can't exceed!\n\n");
						key();
						while(amt>c.c_bal)
						{
							system("CLS");
							printf("\n\t\t\tCURRENT BALANCE: %d", c.c_bal);
							printf("\n\n\t\t\tENTER THE AMOUNT : ");
							scanf(" %d", &amt);
						}
					}
					if(c.c_type == 'J' || c.c_type == 'j'){
						if(amt > 25000 && amt >=0){
							printf("\n\t\t\tWithdaw limit for juniors is 25K, Kindly enter again \n\n");
							goto l;
						}
					}
					else if(c.c_type == 'S' || c.c_type == 'B' ||c.c_type == 's' || c.c_type == 'b'){
						if(amt > 50000 ){
							printf("\n\t\t\tWithdaw limit is 50K, Kindly enter again\n\n");
							goto l;
						}
					}	
					c.c_bal -= amt;
					printf("\n\n\t\t\tPLEASE WAIT WHILE YOUR TRANSACTION IS BEING PROCESSED...\n\n");
					Sleep(100);
					printf("\n\n\t\t\tNEW BALANCE: %d", c.c_bal);
					
					break;
				case 2: 
					printf("\n\t\t\tCURRENT BALANCE: %d", c.c_bal);
					k:
					printf("\n\n\t\t\tENTER THE AMOUNT : ");
					scanf(" %d", &amt);
					if(c.c_type == 'J' || c.c_type == 'j'){
						if(c.c_bal + amt > 75000){
							printf("\n\t\t\tMAX balance limit for juniors is 75K, Kindly enter again \n\n");
							goto k;
						}
						else{
							c.c_bal += amt;
						}
					}
					else if(c.c_type == 'S' || c.c_type == 'B' ||c.c_type == 's' || c.c_type == 'b'){
					
						if(c.c_bal + amt > 500000){
							printf("\n\t\t\tMAX limit is 500K for Business/Saving, Kindly enter again\n\n");
							goto k;
						}
						else{
							c.c_bal += amt;	
						}
					}
					
					printf("\n\n\t\t\tPLEASE WAIT WHILE YOUR TRANSACTION IS BEING PROCESSED...\n\n");
					Sleep(100);
					printf("\n\n\t\t\tNEW BALANCE: %d", c.c_bal);
					break;
			}
		}
		fwrite(&c,sizeof(struct Customer),1,newptr);
	}
	if(flag==0) printf("\n\n\t\t\tNO DATA FOUND!!!!\n\n");
	fclose(dataptr);
	fclose(newptr);
	remove("customers.txt");
	rename("update.txt","customers.txt");
	key();
	return;
}
//----------------------------------------------------Only Changes Name of User Account —------------------------------------
void settings(){
	FILE *newptr;
	newptr = fopen("update.txt","a");
	dataptr = fopen("customers.txt","r");
	int i, flag, choice, x, pass = 0;
	char name[25], input[10];
	system("CLS");
	fflush(stdin);
	printf("\n\n\n\t\tENTER YOUR ACCOUNT NAME AND PASSWORD: ");
	scanf("%s %d", input, &pass);
	while(fread(&c,sizeof(struct Customer),1,dataptr)){
		flag=0;
		x = strcmp(input, c.c_name);
		if(x == 0 && pass==c.c_pass){
			system("CLS");
			printf("\n\n\n\n\n\n\t\tENTER SELECTION : ");
			printf("\n\t\t\t1. CHANGE NAME ");
			printf("\n\t\t\t2. GO BACK TO MAIN MENU ");
			printf("\n\n\t\t\t  Enter Selection: ");
			scanf(" %d", &choice);
			switch(choice){
				case 1:
					printf("\n\n\t\t\tENTER NAME TO CHANGE: ");
					scanf(" %s", name);
					strcpy(c.c_name,name);
					printf("\n\t\tName Changed Successfully!!");
					flag = 1;
					break;
				case 2:
					return;
				default:
					printf("\n\t\t\tYOU ENTERED INVALID!");
					key();
			}
		}
		fwrite(&c, sizeof(struct Customer), 1, newptr);
		if(flag == 1){
			break;
		}
	}
	if(flag==0) printf("\n\n\t\t\tNO DATA FOUND!!!!\n\n");
	key();
	fclose(newptr);
	fclose(dataptr);
	remove("customers.txt");
	rename("update.txt","customers.txt");
	return;
}
//------------------------------------------------------------Menu Screen—------------------------------------------------------------
int menu(){
	system("CLS");
	int choice;
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t%c%c%c%c%c WELCOME TO BANK MANAGEMENT SYSTEM %c%c%c%c%c\n\n", 178,178,178,178,178,178,178,178,178,178);
	printf("\n\t\t\t\t\t[1]  Add a new record\n");
	printf("\t\t\t\t\t[2]  Delete an existing record\n");
	printf("\t\t\t\t\t[3]  Display Data\n ");
	printf("\t\t\t\t\t[4]  Admin Login\n ");
	printf("\t\t\t\t\t[5]  Withdraw Cash\n");
	printf("\t\t\t\t\t[6]  Deposit Cash\n");
	printf("\t\t\t\t\t[7]  Enter settings of a user\n");
	printf("\t\t\t\t\t[8]  Exit the Program\n");
	printf("\n\t\t\t\t\t   Enter your choice: ");
	fflush(stdin);
	scanf("%d", &choice);
	if(choice > 7 && choice < 1){
		printf("\n\t\t\t\t\tINVALID INPUT\n");
		key();
		menu();
	}
	return choice;
}
//----------------------------------------------------------Adds accounts to the file--------------------------------------------------
void input_record(){
	system("CLS");
	dataptr=fopen("customers.txt","a+");
	printf("\n\n\t\t*ENTER THE FOLLOWING*\n\n");
	c.c_accno = getaccno();
	printf("\n\t\tAccount Number : %d\n", c.c_accno);
	printf("\n\t\tEnter Customer Name : ");fflush(stdin);
	scanf("\t\t %s", c.c_name);
	printf("\n\t\tEnter Customer ID[******] : ");fflush(stdin);
	scanf("%d", &c.c_id);
	if(c.c_id > 999999 || c.c_id < 100000){
		printf("\n\t\tInvalid ID, must be in 6 digits.");
		while(c.c_id > 999999 || c.c_id < 100000){
			printf("\n\t\tEnter Customer ID[******] again: ");
			scanf(" %d", &c.c_id);
		}
	}
	x:
	printf("\n\t\tEnter Account type[(S/s) Saving || (B/b) Business || (J/j) Junior] : ");fflush(stdin);
	scanf(" %c", &c.c_type);
	if(c.c_type != 's'&& c.c_type != 'S' && c.c_type != 'b' && c.c_type != 'B' && c.c_type != 'j' && c.c_type != 'J'){
		printf("\n\t\tInvalid input, enter again\n");
		goto x;
	}
	n:
	printf("\n\t\tEnter Customer Age: ");fflush(stdin);
	scanf("%d", &c.c_age);
	if(c.c_age < 18 && (c.c_type == 's' || c.c_type == 'S' || c.c_type == 'b' || c.c_type == 'B')){
		printf("\n\t\tYou should be older than 18!\n\t\t\t\tre enter!\n\n");
		goto n;
	}
	if(c.c_age <= 0){
		printf("\n\t\tYou are not born yet!\n");
			while(c.c_age <= 0){
			printf("\n\t\tEnter Customer Age again : "); fflush(stdin);
			scanf(" %d", &c.c_age);
		}
	}
	if((c.c_type == 'J' || c.c_type == 'j') && c.c_age >= 18){
		printf("\n\t\tJuniors are less than 18!\n");
		while(c.c_age > 18 || c.c_age <= 0){
			printf("\n\t\tEnter Customer Age again : "); fflush(stdin);
			scanf(" %d", &c.c_age);
		}
	}
	p:
	printf("\n\t\tEnter Customer Balance : ");fflush(stdin);
	scanf(" %d", &c.c_bal);
	if(c.c_type == 'j'||c.c_type == 'J'){
		if(c.c_bal > 75000){
			printf("\nSorry, the MAX acc limit for juniors is 75K, kindly re enter\n\n");
			goto p;
		}
	}
	else if(c.c_type == 'B'||c.c_type == 'S'||c.c_type == 's'||c.c_type == 'b'){
		if(c.c_bal > 500000){
			printf("\nSorry, the MAX acc limit for Savings/Business is 500K, kindly re enter\n");
			goto p;
		}
	}
	
	printf("\n\t\tEnter Customer Password : ");fflush(stdin);
	scanf(" %d", &c.c_pass);
	fwrite(&c,sizeof(struct Customer),1,dataptr);
	fclose(dataptr);
	printf("\n\n\t\t\t\tAccount Created Successfully!!\n");
	fflush(stdin);
	key();
}
//------------------------------------------------------Used for convenience in the next function—----------------------------
void show()
{
	printf("\n\nCUSTOMER NAME :  %s\n", c.c_name);
	printf("CUSTOMER ID:  %d\n", c.c_id);
	printf("Account Type : ");
	switch(c.c_type){
			case 's': case 'S':
					printf("Saving\n");
				break;
			case 'b': case 'B':
					printf("Business\n");
				break;	
			case 'J': case 'j':
					printf("Junior\n");
				break;		
		}
		
		printf("CUSTOMER ACCOUNT NO:  %d\n", c.c_accno);
		printf("CUSTOMER AGE:  %d\n", c.c_age);
		printf("CUSTOMER BALANCE:  %d\n", c.c_bal);
}
//------------------------------------------------Used to display data of individual accounts—---------------------------------
void showData()
{
	char name[20] = {0};
	int pass = 0, i = 0, x = 0;
	int count=0;
	FILE *newptr;
	dataptr = fopen("customers.txt","r");
	system("CLS");
	printf("\n\n\n\n\n\nENTER YOUR ACCOUNT NAME AND PASSWORD TO DISPLAY DATA : ");
	scanf("%s %d", name, &pass);
	while(fread(&c,sizeof(struct Customer),1,dataptr)){
		fflush(stdin);
		x = strcmp(name, c.c_name);
		if(pass == c.c_pass && x == 0){
			show();
			count++;
			break;
		}
	}
	
	if(count==0)
	{
		printf("\nNo Record Found!");
		key();
	fclose(dataptr);
		return;
	}
	else
	{
	fclose(dataptr);
	key();
	return;
	}
}
//---------------------------------------------------(Admin Funtion)  Used to display data of all accounts—-----------------
void display_record(){
	system("CLS");
	printf("\n\n");
	int i;
	dataptr=fopen("customers.txt","r");
	while(fread(&c,sizeof(struct Customer),1,dataptr)){
		printf("\n\nCUSTOMER NAME :  %s\n", c.c_name);
		printf("CUSTOMER ID:  %d\n", c.c_id);
		printf("CUSTOMER ACCOUNT TYPE ");
		switch(c.c_type){
			case 's': case 'S':
					printf("Saving\n");
				break;
			case 'b': case 'B':
					printf("Business\n");
				break;	
			case 'J': case 'j':
					printf("Junior\n");
				break;		
		}
		printf("CUSTOMER ACCOUNT NO:  %d\n", c.c_accno);
		printf("CUSTOMER AGE:  %d\n", c.c_age);
		printf("CUSTOMER BALANCE:  %d\n", c.c_bal);
	}
	fclose(dataptr);
	key();
	return;
}
//----------------------------------------------------For customization purposes–---------------------------------------------------
void load(){
	int i,j;
	int a=177,b=219; // 176,175
	printf("\t\t\t\t         ");
	for(j=0;j<25;j++)
		printf("%c",a);
	printf("]\r");
	printf("\t\t\t\tLoading [");
	for(i=0;i<25;i++){
		Sleep(100);
		printf("%c", b);
	}
	printf("]\n\n");
}
//----------------------------------------------------For customization purposes—-------------------------------------------------
void key(){
	printf("\n\n\t\t\t**************** Press any key to continue ****************\n");
	getch();
}
//---------------------------------------------------Used to delete user accounts---------------------------------------------------
void delete_record(){
	char name[20] = {0};
	int pass = 0, i = 0, x = 0;
	int count=0;
	
	FILE *newptr;
	newptr = fopen("update.txt", "a");
	dataptr = fopen("customers.txt","r");
	
	system("CLS");
	printf("\n\n\n\n\n\nENTER YOUR ACCOUNT NAME AND PASSWORD TO DELETE: ");
	scanf("%s %d", name, &pass);
	
	while(fread(&c,sizeof(struct Customer),1,dataptr)){
		fflush(stdin);
		x = strcmp(name, c.c_name);
		if(pass == c.c_pass && x == 0){
			count=1;
			continue;
		}
		else{
			fwrite(&c,sizeof(struct Customer),1,newptr);
		}
	}
	
	if(count==0)
	{
		printf("\nNo Record Found!");
		key();
		fclose(newptr);
	fclose(dataptr);
	remove("customers.txt");
	rename("update.txt", "customers.txt");
		return;
	}
	else
	{
	printf("\n\n\t\t\t\tCustomer Information Deleted Successfully!!\n\n");
	fclose(newptr);
	fclose(dataptr);
	remove("customers.txt");
	rename("update.txt", "customers.txt");
	key();
	return;
	}
}
//----------------------------------------------Randomly assigns an account number --------------------------------------------
int getaccno(){
	int lower=11111, upper=99999;
	int num = (rand() %(upper - lower + 1)) + lower;
	return num;
}
//--------------------------------------------------Access Screen after start up, ----------------------------------------------------
void pass(){
	int i;
	static int count = 0, k = 3;
	char temp[8], keyword[10] = "password";
	system("CLS");
	printf("\n\n\n\n\n\n\t\t\tEnter Password To Enter into the System(Enter -1XXXXXX to exit) : ");
	printf("\n\t\t\t "); fflush(stdin); 
	for(i=0;i<8;i++){
		fflush(stdin);
		temp[i]=getch();
		printf("*");
	}
	if(temp[0]== '-' && temp[1] == '1')
		exit(0);
	int x = strcmp(temp, keyword);
	if(x == 0){
		printf("\n\n\n\t\t\t\t Access Acquired.\n");
		key();
		return;
	}
	else{
		printf("\n\n\n\t\t\t\t Access Denied.\n");
		++count;
		if(count == 3){
			exit(0);
		}
		--k;
		printf("\n\nInvalid pass, please re enter!(%d tries remaining)\nOr Press -1 to Exit program!\n", k);
		key();
		pass();
	}
	system("CLS");
}
//---------------------------------------------------------------------------------------------------------------------------------------------

