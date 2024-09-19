//Carlos Moreno, CS162, Program 5: Summer List, Submission #1

//A program that takes in user input to make a wish list of summer activities and
//includes functionality for adding more, viewing all, searching, and starting over
// the list gets sorted by the the item priority levels assigned by the user.

#include "summer.h"

// A function that builds a new node of the wish list with user input
item* buildItem() {
    char userInput[SIZE] = {0};
    char userDesc[SIZE] = {0};
    char userPlan = 'n';
    item *newItem = new item;
    cout << "Title of the wish: " << endl;
    cin.get(userInput, SIZE, '\n');
    cin.ignore(100, '\n');
    newItem->title = new char[strlen(userInput) + 1];
    strcpy(newItem->title, userInput);
    cout << "Description of the wish:  " << endl;
    cin.get(userDesc, SIZE, '\n');
    cin.ignore(100, '\n');
    newItem->description = new char[strlen(userDesc) + 1];
    strcpy(newItem->description, userDesc);
    cout << "Priority rank from 1-3: " << endl;
    cin >> newItem->priority;
    cin.ignore(100, '\n');
    cout << "Is the wish already planned? (y/n): " << endl;
    cin >> userPlan;
    cin.ignore(100, '\n');
    if (userPlan == 'y' || userPlan == 'Y') {
        newItem->isPlanned = true;
    }
    else {
        newItem->isPlanned = false;
    }
    newItem->next = nullptr;

    return newItem;
}

//a function that traverses and then appends to the end of the linked list
void append(item *head) {
    item *temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = buildItem();
}

//a function that displays the info from one wish item
void display(item *current) {
    cout << current->title << "\n" << current->description << endl;
    if (current->priority == 1) {
        cout << "High priority." << endl;
    }
    if (current->priority == 2) {
        cout << "Medium priority." << endl;
    }
    if (current->priority == 3) {
        cout << "low priority." << endl;
    }
    if (current->isPlanned) {
        cout << "Wish is planned." << endl;
    }
    else {
        cout << "Wish is not planned." << endl;
    }
}

//A function that traverses the list and displays each node
void displayAll(item *head){
    item *temp = head;
    cout << "All Items: " << endl;
    while (temp) {
        cout << "" << endl;
        display(temp);
        temp = temp->next;
    }
}

//Gets user input and displays all nodes of that priority level
void findPriority(item *head, int priority) {
    item *temp = head;
    if (priority == 1) {
        cout << "All high priority items:" << endl;
    }
    if (priority == 2){
        cout << "All medium priority items:" << endl;
    }
    else {
        cout << "All low priority items:" << endl;
    }
    while (temp) {
        if (temp->priority == priority){
            cout << "" << endl;
            display(temp);
        }
        temp = temp->next;
    }
}

//used to copy over parts of an item node in orderPriority
void copy(item *&destination, item *&source){
    destination->title = new char[strlen(source->title) + 1];
    strcpy(destination->title, source->title);
    destination->description = new char[strlen(source->description) + 1];
    strcpy(destination->description, source->description);
    destination->priority = source->priority;
    destination->isPlanned = source->isPlanned;
}

//takes in the LLL and returns one that is ordered
void orderPriority(item *&head){
    item *current = head;
    while (current->next) {
        if (current->next->priority < current->priority){
            item *temp = new item;
            copy(temp, current);
            copy(current, current->next);
            current = current->next;
            copy(current, temp);
            delete temp;
            current = head;
        }
        else {
            current = current->next;
        }
    }
}

//deletes all of the items of the LLL
void deleteAll(item *head){
    item *current = head;
    item *next = nullptr;
    while (current){
        next = current->next;
        delete[] current->title;
        delete[] current->description;
        delete current;
        current = next;
    }
}

//functionailty options for user to choose from and execute
void menu(item *&head){
    int userInput = 0;
    int priorityLevel = 0;
    while (userInput != 5) {
        cout << "\nMenu:\n1. Add a new item\n2. Display all\n"
            << "3. Find by priority level\n4. Start over\n5. Quit"
            << "\n\nYour choice: " << endl;
        cin >> userInput;
        cin.ignore(100, '\n');
        switch (userInput) {
            case 1:
                append(head);
                orderPriority(head);
                break;
            case 2:
                displayAll(head);
                break;
            case 3:
                cout << "What priority level do you want to "
                     <<"display? (1-3): " << endl;
                cin >> priorityLevel;
                cin.ignore(100, '\n');
                findPriority(head, priorityLevel);
                break;
            case 4:
                deleteAll(head);
                head = nullptr;
                head = buildItem();
                break;
        }
    }
}


int main(){
    cout << "Welcome" << endl;
    cout << "This program allows you to make a wishlist "
         << "of summer activites." << endl;
    item *wishList = buildItem();
    menu(wishList);
    deleteAll(wishList);
    cout << "Goodbye" << endl;

    return 0;
}