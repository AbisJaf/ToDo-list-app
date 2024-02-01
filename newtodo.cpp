#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

class TaskBase
{
protected:
public:
    char task_name[80];
    int task_no;
    int check;
    int priority;
    char due_date[11];
    TaskBase() : task_no(0), check(0), priority(0) {}

    virtual void createTask() = 0;
    virtual void showTask() = 0;
    virtual void checkTask() = 0;

    int getTaskNo() const { return task_no; }
    int getCheck() const { return check; }
    int getPriority() const { return priority; }
    const char *getDueDate() const { return due_date; }
    const char *getTaskName() const { return task_name; }
};

class TaskCategorization : public TaskBase
{
private:
    string category;

public:
    TaskCategorization() : category("") {}

    void createTask() override;
    void showTask() override;
    void checkTask() override;

    const string &getCategory() const { return category; }
};
class TaskPrioritization : public TaskBase
{
public:
    void createTask() override;
    void showTask() override;
    void checkTask() override;
};

class TaskSearchFilter : public TaskBase
{
public:
    void createTask() override;
    void showTask() override;
    void checkTask() override;
};

class TaskManagement : public TaskBase
{
public:
    void createTask() override;
    void showTask() override;
    void checkTask() override;
};

class TaskPriorityLevel : public TaskBase
{
public:
    void createTask() override;
    void showTask() override;
    void checkTask() override;
};

class TaskDisplayManager : public TaskBase
{
public:
    void createTask() override;
    void showTask() override;
    void checkTask() override;
};

class TaskManager
{
    static void displayEditMenu();

public:
    static void writeTask(TaskBase *task);
    static void readTask(int s = 0);
    static void removeTask();
    static void modifyTask(int);
    static void getch();
    static int retTaskNo();
    static void searchTasks();
    static void editTask(int);
};

void TaskCategorization::createTask()
{
    TaskBase::createTask();
    cout << "\n\t\tEnter category: ";
    cin.ignore();
    getline(cin, category);
}

void TaskCategorization::showTask()
{
    TaskBase::showTask();
    cout << " (Category: " << category << ")\n";
}

void TaskCategorization::checkTask()
{
    TaskBase::checkTask();
    // Additional actions for TaskCategorization can be added here
}

void TaskManager::writeTask(TaskBase *task)
{
    ofstream file;
    system("cls");
    task->createTask();
    file.open("tasks.dat", ios::app | ios::binary);
    file.write(reinterpret_cast<char *>(task), sizeof(TaskBase));
    file.close();
}


void TaskManager::editTask(int n)
{
    TaskBase *task = nullptr;
    fstream file;
    int flag = 0;

    file.open("tasks.dat", ios::binary | ios::out | ios::in);
    if (!file)
    {
        cout << "!!!! Error : Failed to open the file !!!!";
        return;
    }

    while (file.read(reinterpret_cast<char *>(task), sizeof(TaskBase)) && flag == 0)
    {
        if (task->getTaskNo() == n)
        {
            int choice;
            do
            {
                system("cls");
                task->showTask();
                displayEditMenu();
                cout << "\n\tEnter your choice (1-4): ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    task->createTask(); // You can modify the task details using the createTask function
                    break;
                case 2:
                    cout << "\nEnter new priority (1-High, 2-Medium, 3-Low): ";
                    cin >> task->priority;
                    break;
                case 3:
                    cout << "\nEnter new due date (YYYY-MM-DD): ";
                    cin.ignore();
                    cin.getline(task->due_date, 11);
                    break;
                case 4:
                    flag = 1; // Exit the edit loop
                    break;
                default:
                    cout << "\n\tInvalid Choice! Please try again.";
                }
            } while (choice != 4);

            int pos = (-1) * sizeof(TaskBase);
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char *>(task), sizeof(TaskBase));
            flag = 1;
        }
    }

    file.close();

    if (flag == 0)
    {
        cout << "\n\n\t\t\t!!!!!!Not Found!!!!!!";
        getch();
    }
}

void TaskManager::displayEditMenu()
{
    cout << "\n\n\t\t\tEdit Menu:";
    cout << "\n\t\t\t1. Edit Task Name";
    cout << "\n\t\t\t2. Edit Priority";
    cout << "\n\t\t\t3. Edit Due Date";
    cout << "\n\t\t\t4. Exit";
}

void TaskManager::readTask(int s)
{
    TaskBase *task = nullptr;
    ifstream file;
    int total = 0, completed = 0;

    file.open("tasks.dat", ios::binary);
    system("cls");
    cout << "\n\n\t\t   Task No. \tTask title";
    cout << "\n\t\t  ==================================\n";

    while (file.read(reinterpret_cast<char *>(task), sizeof(TaskBase)))
    {
        task->showTask();
        total++;
        if (task->getCheck() == 1)
            completed++;
    }

    file.close();

    if (s == 1)
    {
        cout << "\n\n\t\t\t======================";
        cout << "\n\t\t\tTotal Tasks ------ " << setw(2) << total;
        cout << "\n\t\t\tCompleted   ------ " << setw(2) << completed;
        cout << "\n\t\t\tRemaining   ------ " << setw(2) << total - completed;
        cout << "\n\t\t\t======================";
    }
}

int TaskManager::retTaskNo()
{
    TaskBase *task = nullptr;
    ifstream file;
    int taskNum;

    file.open("tasks.dat", ios::binary);

    if (!file)
    {
        taskNum = 0;
    }
    else
    {
        while (file.read(reinterpret_cast<char *>(task), sizeof(TaskBase)))
        {
            taskNum = task->getTaskNo();
        }
    }

    file.close();
    return taskNum;
}

void TaskManager::modifyTask(int n)
{
    TaskBase *task = nullptr;
    fstream file;
    int flag = 0;

    file.open("tasks.dat", ios::binary | ios::out | ios::in);
    if (!file)
    {
        cout << "!!!! Error : Failed to open the file !!!!";
        return;
    }

    while (file.read(reinterpret_cast<char *>(task), sizeof(TaskBase)) && flag == 0)
    {
        if (task->getTaskNo() == n)
        {
            task->checkTask();
            int pos = (-1) * sizeof(TaskBase);
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char *>(task), sizeof(TaskBase));
            flag = 1;
        }
    }

    file.close();

    if (flag == 0)
    {
        cout << "\n\n\t\t\t!!!!!!Not Found!!!!!!";
        getch();
    }
}

void TaskManager::removeTask()
{
    TaskBase *task = nullptr;
    fstream ifile, ofile;
    int flag = 0;
    int n;

    ifile.open("tasks.dat", ios::binary | ios::in);
    ofile.open("temp.dat", ios::binary | ios::out);

    if (!ifile)
    {
        cout << "!!!! Error : Failed to open the file !!!!";
        return;
    }

    ifile.seekg(0, ios::beg);

    cout << "\n\n\t\t\t-1 ---- Remove completed tasks";
    cout << "\n\t\t\t-2 ---- Remove all tasks";
    cout << "\n\t\t\t 0 ---- Exit";
    cout << "\n\n\t\tEnter [Task No.] to remove tasks : ";
    cin >> n;

    if (n == -1)
    {
        while (ifile.read(reinterpret_cast<char *>(task),
                          sizeof(TaskBase)))
        {
            if (task->getCheck() == 0)
            {
                ofile.write(reinterpret_cast<char *>(task), sizeof(TaskBase));
                flag = 1;
            }
        }
    }
    else if (n == -2)
    {
        flag = 1; // Set flag to indicate removing all tasks
    }
    else if (n == 0)
    {
        flag = 2; // Set flag to indicate exit without removing tasks
    }
    else
    {
        while (ifile.read(reinterpret_cast<char *>(task), sizeof(TaskBase)))
        {
            if (task->getTaskNo() != n)
            {
                ofile.write(reinterpret_cast<char *>(task), sizeof(TaskBase));
                flag = 1;
            }
        }
    }

    ifile.close();
    ofile.close();

    if (flag == 0)
    {
        cout << "\n\n\t\t\t!!!!!!Not Found!!!!!!";
        getch();
    }
    else if (flag == 1)
    {
        remove("tasks.dat");
        rename("temp.dat", "tasks.dat");
    }

    // For flag == 2, do nothing (exit without removing tasks)
}

void TaskManager::getch()
{
    char ch;
    cout << "\n";
    cin.ignore();
    ch = getchar();
}

void TaskManager::searchTasks()
{
    int choice;
    string keyword;
    cout << "\n\n\t\t\t1. Search by Task Name";
    cout << "\n\t\t\t2. Search by Priority";
    cout << "\n\t\t\t3. Search by Due Date";
    cout << "\n\t\t\t4. Back to Main Menu";
    cout << "\n\n\tEnter choice (1-4): ";
    cin >> choice;

    if (choice == 4)
        return;

    cout << "\n\tEnter search keyword: ";
    cin.ignore();
    getline(cin, keyword);

    TaskBase *task = nullptr;
    ifstream file;
    int count = 0;

    file.open("tasks.dat", ios::binary);
    system("cls");
    cout << "\n\n\t\t   Task No. \tTask title";
    cout << "\n\t\t  ==================================\n";

    while (file.read(reinterpret_cast<char *>(task), sizeof(TaskBase)))
    {
        bool match = false;

        switch (choice)
        {
        case 1:
            match = (strstr(task->getTaskName(), keyword.c_str()) != nullptr);
            break;
        case 2:
            match = (task->getPriority() == stoi(keyword));
            break;
        case 3:
            match = (strstr(task->getDueDate(), keyword.c_str()) != nullptr);
            break;
        }

        if (match)
        {
            task->showTask();
            count++;
        }
    }

    file.close();

    if (count == 0)
    {
        cout << "\n\n\t\t\tNo matching tasks found.";
    }
    else
    {
        cout << "\n\n\t\t\t======================";
        cout << "\n\t\t\tTotal Matching Tasks: " << count;
        cout << "\n\t\t\t======================";
    }

    getch();
}

int main()
{
    char ch;

    do
    {
        system("cls");
        cout << "\n\n\t\t\t\tMain Menu";
        cout << "\n\n\t\t\t1. Add Task";
        cout << "\n\t\t\t2. Show Tasks";
        cout << "\n\t\t\t3. Manage Tasks";
        cout << "\n\t\t\t4. Remove Tasks";
        cout << "\n\t\t\t5. Search and Filter Tasks";
        cout << "\n\t\t\t6. Edit Task";
        cout << "\n\t\t\t7. Exit";
        cout << "\n\n\n\t\t\tChoose Option (1-7) :  ";
        cin >> ch;

        TaskBase *task = nullptr;
        int n; // Declare variable outside the switch to avoid redeclaration error

        switch (ch)
        {
        case '1':
            cout << "\n\t1. Task Categorization\n\t2. Task Prioritization\n\t3. Task Search Filter\n\t4. Task Management\n\t5. Task Priority Level\n\t6. Task Display Manager\n";
            cout << "\n\tChoose Task Type (1-6): ";
            int type;
            cin >> type;
            switch (type)
            {
            case 1:
                task = new TaskCategorization();
                break;
            case 2:
                task = new TaskPrioritization();
                break;
            case 3:
                task = new TaskSearchFilter();
                break;
            case 4:
                task = new TaskManagement();
                break;
            case 5:
                task = new TaskPriorityLevel();
                break;
            case 6:
                task = new TaskDisplayManager();
                break;
            default:
                cout << "\n\tInvalid Task Type! Please try again.";
                continue;
            }
            TaskManager::writeTask(task);
            break;
        case '2':
            TaskManager::readTask(1);
            TaskManager::getch();
            break;
        case '3':
            do
            {
                system("cls");
                TaskManager::readTask(); // Assuming you want to display tasks before managing
                cout << "\n\n\t\t\t[✓] ---- Completed";
                cout << "\n\t\t\t[ ] ---- Not Completed";
                cout << "\n\n\tEnter [Task No.] to check/uncheck task ( 0 for exit): ";
                cin >> n;
                if (n > 0)
                    TaskManager::modifyTask(n);
            } while (n != 0);
            break;
        case '4':
            TaskManager::removeTask();
            break;
        case '5':
            TaskManager::searchTasks();
            break;
        case '6':
            cout << "\n\n\t\t\t--- Edit Task ---";
            cout << "\n\n\t\t\tEnter [Task No.] to edit task: ";
            cin >> n;
            TaskManager::editTask(n);
            break;
        case '7':
            exit(0);
        default:
            cout << "\n\t\t\t!!!!!! Invalid Input !!!!!!!";
        }
    } while (ch != '7');

    return 0;
}
