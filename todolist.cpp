#include<iostream>
#include<string>
#include<fstream>

using namespace std;

struct todolist
{
    int id;
    string task;
};

int ID = 0;

void banner();    
void addTask();
void showTask();
int searchTask();
void deleteTask();
void updateTask();

int main()
{
    system("cls");
    while(true)
    {
        banner();
        cout<<"\n\t1. Add Task";
        cout<<"\n\t2. Show Task";
        cout<<"\n\t3. Search Task";
        cout<<"\n\t4. Delete Task";
        cout<<"\n\t5. Update Task";
        cout<<"\n\t6. Exit";

        int choice;
        cout<<"\n\tEnter Choice: ";
        cin>>choice;

        switch (choice)
        {
            case 1: 
                addTask();
                break;
            
            case 2: 
                showTask();
                break;

            case 3: 
                searchTask();
                break;

            case 4: 
                deleteTask();
                break;

            case 5: 
                updateTask();
                break;

            case 6:
                return 0;

            default :
                cout << "Invalid choice! Please try again.\n";
        }     
    }

    return 0;
}

void banner()
{
    system("cls");
    cout << "_________________________________\n";
    cout << "\t    My ToDo List    \n";
    cout << "_________________________________\n";
}

void addTask()
{
    system("cls");
    banner();
    todolist todo;
    cout << "Enter new Task: ";
    cin.ignore();
    getline(cin, todo.task);
    char save;
    cout << "Save? (y/n): ";
    cin >> save;
    if(save == 'y')
    {
        ID++;
        ofstream fout;
        fout.open("todo.txt", ios::app);
        fout << "\n" << ID;
        fout << "\n" << todo.task;
        fout.close();

        char more;
        cout << "Add more tasks? (y/n): ";
        cin >> more;
        if(more == 'y')
        {
            addTask();
        }
        else
        {
            system("cls");
            cout << "Added Successfully!\n";
            return;
        }
    }
}

void showTask()
{
    system("cls");
    banner();
    todolist todo;
    ifstream fin("todo.txt");
    cout << "Tasks:\n";
    while (fin >> todo.id)
    {
        fin.ignore();
        getline(fin, todo.task);

        if (!todo.task.empty())
        {
            cout << "\t" << todo.id << ": " << todo.task << endl;
        }
        else
        {
            cout << "\tEmpty!\n";
        }
    }
    fin.close();
    char exit;
    cout << "\nExit? (y/n): ";
    cin >> exit;
    if (exit != 'y')
    {
        showTask();
    }
}

int searchTask()
{
    system("cls");
    banner();
    int id;
    cout << "Enter task id: ";
    cin >> id;
    todolist todo;
    ifstream fin("todo.txt");
    while (!fin.eof())
    {
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if(todo.id == id)
        {
            system("cls");
            cout << "\t" << todo.id << ": " << todo.task << endl;
            return id;
        }
    }
    system("cls");
    cout << "Not Found\n";
    return 0;
}

void deleteTask()
{
    system("cls");
    int id = searchTask();
    if(id != 0)
    {
        char del;
        cout << "\nDelete? (y/n): ";
        cin >> del;
        if(del == 'y')
        {
            todolist todo;
            ofstream tempFile;
            tempFile.open("temp.txt");
            ifstream fin;
            fin.open("todo.txt");
            int index = 1;
            while(!fin.eof())
            {
                fin >> todo.id;
                fin.ignore();
                getline(fin, todo.task);
                if(todo.id != id)
                {
                    tempFile << "\n" << index;
                    tempFile << "\n" << todo.task;
                    index++;
                    ID--;
                }
            }
            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
            system("cls");
            cout << "\nDeleted successfully!\n";
        }
        else
        {
            system("cls");
            cout << "Not Deleted!\n";
        }
    }
}

void updateTask()
{
    system("cls");
    int id = searchTask();
    if(id != 0)
    {
        char update;
        cout << "\nUpdate? (y/n): ";
        cin >> update;
        if(update == 'y')
        {
            todolist todo;
            ofstream tempFile;
            tempFile.open("temp.txt");
            ifstream fin;
            fin.open("todo.txt");
            int index = 1;
            while(!fin.eof())
            {
                fin >> todo.id;
                fin.ignore();
                getline(fin, todo.task);
                if(todo.id == id)
                {
                    system("cls");
                    cout << "Enter new task description: ";
                    cin.ignore();
                    getline(cin, todo.task);
                    tempFile << "\n" << id;
                    tempFile << "\n" << todo.task;
                }
                else
                {
                    tempFile << "\n" << index;
                    tempFile << "\n" << todo.task;
                    index++;
                }
            }
            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
            system("cls");
            cout << "Updated successfully!\n";
        }
        else
        {
            system("cls");
            cout << "Not Updated!\n";
        }
    }
}
