# Student-Management-system

👇

📌 Project Title: Student Information System (SIS)
🎯 Objective

This project is designed to manage student records using file handling in C.
It allows users to:

Store student details
Modify records
Delete and recover data
Search for specific students
🧠 Concepts Used
Structures (struct)
File Handling (fopen, fread, fwrite)
Loops and Conditions
Functions
Binary Files
📂 Data Structures Used
1. struct Student

Stores student information:

rollno → Unique ID
name → Student name
clas → Class
city → City
2. struct SIS_ID

Used for auto-generating roll numbers

⚙️ Modules Description
🔹 1. main()
Displays menu
Takes user choice
Calls appropriate function
Runs in infinite loop
🔹 2. autoid()
Generates unique roll number
Reads last ID from file
Increments it by 1

👉 Ensures no duplicate roll numbers

🔹 3. addStudent()
Takes input:
Name
Class
City
Automatically assigns roll number
Stores data in:
SIS.bin (main file)
SIS_ID.bin (ID tracking)
🔹 4. showStudent()
Reads all records from file
Displays student list
Shows message if no data found
🔹 5. searchStudent()
Takes roll number input
Searches in file
Displays matching record
🔹 6. modifyStudent()
Finds student by roll number
Updates:
Name
Class
City
Uses temporary file (temp.bin)
Replaces original file after modification
🔹 7. deleteStudent()
Deletes student record
Instead of permanent deletion:
Moves record to Recycle Bin
File used: SIS_REC.bin

👉 Works like real system recycle bin ♻️

🔹 8. showRecycle()
Displays deleted records
Reads from recycle file
🔹 9. recycleRecover()
Recovers deleted student
Moves record back to main file
📁 Files Used
File Name	Purpose
SIS.bin	Main student database
SIS_ID.bin	Stores last used ID
SIS_REC.bin	Recycle bin (deleted data)
temp.bin	Temporary file for update
🔄 Program Flow
User selects option
System performs operation
Data is stored/updated in files
User returns to menu
🚀 Key Features

✔ Auto-generated Roll Number
✔ File-based storage (no database needed)
✔ Modify & Search functionality
✔ Recycle Bin system (advanced feature 🔥)
✔ Data recovery support

⚠️ Limitations
No password/security
Works only in console
No sorting/filtering
No validation of input
📈 Future Enhancements
Add login system 🔐
GUI interface (using graphics)
Connect with MySQL database
Add sorting (by name/marks)
Add marks & result system
🧾 Conclusion

This project demonstrates a complete CRUD system (Create, Read, Update, Delete) using C programming and file handling.
It is a strong mini-project for exams, viva, and practicals.
