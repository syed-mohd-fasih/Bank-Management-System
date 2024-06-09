# Bank Management System

Welcome to the Bank Management System, a console-based application to manage customer bank accounts. This system allows you to add, delete, and manage customer records, perform transactions, and modify account settings. Below is a detailed guide on how to use this system.

## Table of Contents
1. [Features](#features)
2. [Getting Started](#getting-started)
3. [Usage](#usage)
    - [Main Menu](#main-menu)
    - [Add a New Record](#add-a-new-record)
    - [Delete an Existing Record](#delete-an-existing-record)
    - [Display Data](#display-data)
    - [Admin Login](#admin-login)
    - [Withdraw Cash](#withdraw-cash)
    - [Deposit Cash](#deposit-cash)
    - [Account Settings](#account-settings)
    - [Exit the Program](#exit-the-program)
4. [File Structure](#file-structure)
5. [Compilation and Execution](#compilation-and-execution)

## Features
- **Add New Records**: Input new customer data into the system.
- **Delete Records**: Remove existing customer data from the system.
- **Display Data**: View customer data.
- **Admin Functions**: View all customer data (admin only).
- **Transactions**: Perform withdrawals and deposits.
- **Settings**: Change account names.
- **Secure Access**: Password-protected access to the system.

## Getting Started
To get started with the Bank Management System, you need to have a C compiler installed on your machine. The code is designed for a Windows environment and uses `conio.h` and `windows.h` for console input and output.

## Usage

### Main Menu
The main menu provides several options:
1. Add a new record
2. Delete an existing record
3. Display data
4. Admin login
5. Withdraw cash
6. Deposit cash
7. Enter settings of a user
8. Exit the program

### Add a New Record
1. Select option 1 from the main menu.
2. Follow the prompts to enter the customer's name, ID, account type, age, balance, and password.
3. The account number is automatically generated.

### Delete an Existing Record
1. Select option 2 from the main menu.
2. Enter the account name and password of the account to be deleted.
3. Confirm the deletion.

### Display Data
1. Select option 3 from the main menu.
2. Enter the account name and password to view the account details.

### Admin Login
1. Select option 4 from the main menu.
2. Enter the admin password (`3456`) to view all customer records.

### Withdraw Cash
1. Select option 5 from the main menu.
2. Enter the account name and password.
3. Enter the amount to withdraw (must be within the account's balance and withdrawal limits).

### Deposit Cash
1. Select option 6 from the main menu.
2. Enter the account name and password.
3. Enter the amount to deposit (must be within the account's deposit limits).

### Account Settings
1. Select option 7 from the main menu.
2. Enter the account name and password.
3. Choose to change the account name.

### Exit the Program
1. Select option 8 from the main menu to exit the program.

## File Structure
- **customers.txt**: Stores all customer data.
- **update.txt**: Temporarily stores data during updates.

## Compilation and Execution
To compile and run the program, follow these steps:
1. Open a terminal (command prompt) in the directory containing the source code.
2. Run the following command to compile the program:
   ```sh
   gcc -o bank_management_system bank_management_system.c
   ```
3. Execute the compiled program:
   ```sh
   bank_management_system.exe
   ```

## Additional Information
- **Password Protection**: The system requires a password to access. The default password is `password`.
- **Admin Password**: The default admin password is `3456`.
- **Data Storage**: Customer data is stored in a text file named `customers.txt`.

Feel free to explore and modify the code to suit your requirements. If you have any questions or need further assistance, please refer to the code comments for detailed explanations of each function.

Happy Banking!