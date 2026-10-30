
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Item {
    int id;
    string itemName;
    string category;
    string location;
    string description;
    string status;
};

Item items[500];
int itemCount = 0;
int nextId = 1;

void saveData() {
    ofstream file("items.txt");

    for (int i = 0; i < itemCount; i++) {
        file << items[i].id << '\n'
             << items[i].itemName << '\n'
             << items[i].category << '\n'
             << items[i].location << '\n'
             << items[i].description << '\n'
             << items[i].status << '\n';
    }

    file.close();
}

void loadData() {
    ifstream file("items.txt");
    itemCount = 0;

    while (itemCount < 500 &&
           file >> items[itemCount].id) {
        file.ignore();

        getline(file, items[itemCount].itemName);
        getline(file, items[itemCount].category);
        getline(file, items[itemCount].location);
        getline(file, items[itemCount].description);
        getline(file, items[itemCount].status);

        if (file) {
            if (items[itemCount].id >= nextId)
                nextId = items[itemCount].id + 1;

            itemCount++;
        }
    }

    file.close();
}

void studentLogin() {
    string name, studentId;

    cout << "\n--- Student Login ---\n";
    cout << "Enter student name: ";
    getline(cin, name);

    cout << "Enter student ID: ";
    getline(cin, studentId);

    if (name.empty() || studentId.empty()) {
        cout << "Invalid details!\n";
    } else {
        cout << "Welcome, " << name << "!\n";
    }
}

void reportItem(string itemStatus) {
    if (itemCount >= 500) {
        cout << "Record limit reached!\n";
        return;
    }

    Item newItem;

    newItem.id = nextId++;
    newItem.status = itemStatus;

    cout << "\nEnter item name: ";
    getline(cin, newItem.itemName);

    cout << "Enter category: ";
    getline(cin, newItem.category);

    cout << "Enter location: ";
    getline(cin, newItem.location);

    cout << "Enter description: ";
    getline(cin, newItem.description);

    if (newItem.itemName.empty()) {
        cout << "Item name cannot be empty!\n";
        nextId--;
        return;
    }

    items[itemCount] = newItem;
    itemCount++;

    saveData();

    cout << "\nItem reported successfully!\n";
    cout << "Your Item ID is: " << newItem.id << '\n';
}

void searchItem() {
    string keyword;
    bool found = false;

    cout << "\nEnter item name to search: ";
    getline(cin, keyword);

    for (int i = 0; i < itemCount; i++) {
        if (items[i].itemName.find(keyword) != string::npos) {
            cout << "\nItem ID: " << items[i].id;
            cout << "\nName: " << items[i].itemName;
            cout << "\nCategory: " << items[i].category;
            cout << "\nLocation: " << items[i].location;
            cout << "\nDescription: " << items[i].description;
            cout << "\nStatus: " << items[i].status << '\n';
            found = true;
        }
    }

    if (!found)
        cout << "No matching item found.\n";
}

void autoMatch() {
    bool found = false;

    cout << "\n--- Lost and Found Matches ---\n";

    for (int i = 0; i < itemCount; i++) {
        if (items[i].status == "Lost") {
            for (int j = 0; j < itemCount; j++) {
                if (items[j].status == "Found" &&
                    items[i].itemName == items[j].itemName) {

                    cout << "\nPossible Match Found!\n";
                    cout << "Lost Item ID: " << items[i].id;
                    cout << "\nFound Item ID: " << items[j].id;
                    cout << "\nItem Name: " << items[i].itemName << '\n';

                    found = true;
                }
            }
        }
    }

    if (!found)
        cout << "No matching records found.\n";
}

void viewAllRecords() {
    if (itemCount == 0) {
        cout << "\nNo records available.\n";
        return;
    }

    cout << "\n--- All Item Records ---\n";

    for (int i = 0; i < itemCount; i++) {
        cout << "\nID: " << items[i].id;
        cout << "\nName: " << items[i].itemName;
        cout << "\nCategory: " << items[i].category;
        cout << "\nLocation: " << items[i].location;
        cout << "\nDescription: " << items[i].description;
        cout << "\nStatus: " << items[i].status << '\n';
    }
}

void deleteRecord() {
    int id;
    bool found = false;

    cout << "\nEnter Item ID to delete: ";
    cin >> id;
    cin.ignore();

    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == id) {
            for (int j = i; j < itemCount - 1; j++) {
                items[j] = items[j + 1];
            }

            itemCount--;
            saveData();

            cout << "Record deleted successfully!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found.\n";
}

void itemStatistics() {
    int lost = 0, found = 0;

    for (int i = 0; i < itemCount; i++) {
        if (items[i].status == "Lost")
            lost++;
        else if (items[i].status == "Found")
            found++;
    }

    cout << "\n--- Item Statistics ---\n";
    cout << "Total Records: " << itemCount;
    cout << "\nLost Items: " << lost;
    cout << "\nFound Items: " << found << '\n';
}

void exportReport() {
    ofstream file("Lost_Found_Report.txt");

    if (!file) {
        cout << "Unable to create report!\n";
        return;
    }

    file << "SMART CAMPUS LOST AND FOUND REPORT\n";
    file << "=================================\n\n";

    for (int i = 0; i < itemCount; i++) {
        file << "Item ID: " << items[i].id << '\n';
        file << "Name: " << items[i].itemName << '\n';
        file << "Category: " << items[i].category << '\n';
        file << "Location: " << items[i].location << '\n';
        file << "Description: " << items[i].description << '\n';
        file << "Status: " << items[i].status << "\n\n";
    }

    file.close();
    cout << "Report exported successfully!\n";
}

int main() {
    loadData();

    int choice;

    do {
        cout << "\n========== SMART CAMPUS LOST & FOUND ==========\n";
        cout << "1. Student Login\n";
        cout << "2. Report Lost Item\n";
        cout << "3. Report Found Item\n";
        cout << "4. Search Item\n";
        cout << "5. Auto Match Lost and Found\n";
        cout << "6. View All Records\n";
        cout << "7. Delete Record\n";
        cout << "8. Item Statistics\n";
        cout << "9. Export Report\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                studentLogin();
                break;

            case 2:
                reportItem("Lost");
                break;

            case 3:
                reportItem("Found");
                break;

            case 4:
                searchItem();
                break;

            case 5:
                autoMatch();
                break;

            case 6:
                viewAllRecords();
                break;

            case 7:
                deleteRecord();
                break;

            case 8:
                itemStatistics();
                break;

            case 9:
                exportReport();
                break;

            case 10:
                cout << "Thank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 10);

    return 0;
}
