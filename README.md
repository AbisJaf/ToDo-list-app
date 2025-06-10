C++ Task Manager
A simple command-line task management application built in C++. This project allows users to add, view, manage (mark as complete/incomplete), remove, search, and edit tasks. Tasks are stored persistently in a binary file.

Features
Add Tasks: Create new tasks with a name, priority (High, Medium, Low), and a due date.
View Tasks: Display a list of all tasks, showing their completion status, task number, name, priority, and due date. Includes a summary of total, completed, and remaining tasks.
Manage Tasks: Mark tasks as complete or incomplete.
Remove Tasks: Delete individual tasks, all completed tasks, or all tasks.
Search and Filter: Find tasks by name, priority, or due date.
Edit Tasks: Modify existing task details, including name, priority, and due date.
Persistent Storage: All tasks are saved to a binary file (tasks.dat), ensuring data is not lost when the application closes.
Getting Started
Prerequisites
You will need a C++ compiler (like g++ included with MinGW on Windows or Xcode on macOS) to compile and run this project.

How to Compile and Run
Clone the repository:

Bash

git clone https://github.com/AbisJaf/ToDo-list-app.git
cd ToDo-list-app


Compile the source code:

Bash

g++ todolist.cpp -o ToDo-list-app

Run the application:

Bash

./ToDo-list-app
Usage
When you run the application, you'll be presented with a main menu:

        Main Menu

        1. Add Task
        2. Show Tasks
        3. Manage Tasks
        4. Remove Tasks
        5. Search and Filter Tasks
        6. Edit Task
        7. Exit


        Choose Option (1-7) :
Simply enter the number corresponding to the action you want to perform and follow the on-screen prompts.

Examples
Adding a Task:

Choose option 1.
Enter the task name.
Enter the priority (1 for High, 2 for Medium, 3 for Low).
Enter the due date in YYYY-MM-DD format.
Managing Tasks (Marking as Complete/Incomplete):

Choose option 3.
The current list of tasks will be displayed.
Enter the Task No. of the task you want to check/uncheck. Enter 0 to return to the main menu.
Searching Tasks:

Choose option 5.
Select a search criterion (Task Name, Priority, or Due Date).
Enter your search keyword.
