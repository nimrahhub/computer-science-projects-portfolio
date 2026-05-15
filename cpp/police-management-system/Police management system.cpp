 #include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>
#include <array>

using namespace std;

// Criminal Record Structure
struct CriminalRecord {
    string id;
    string name;
    string crime;
    string punishment;
    string arrestDate;
    string status;
};

// Police Officer Structure
struct PoliceOfficer {
    string badgeNumber;
    string name;
    string rank;
};

// Database Manager Class
class RecordManager {
private:
    vector<CriminalRecord> criminals;
    vector<PoliceOfficer> officers;
    unordered_map<string, int> idIndexMap;
    stack<CriminalRecord> deletedRecords;
    queue<CriminalRecord> recentlyViewed;
    array<string, 2> adminCredentials = {{ "admin", "police123"}};
    string currentUser;

    void loadRecords();
    void saveRecords();
    void displayRecord(const CriminalRecord& record);
    bool idExists(const string& id);

public:
    RecordManager() {
        loadRecords();
    }

    ~RecordManager() {
        saveRecords();
    }

    void login();
    void mainMenu();
    void addRecord();
    void viewRecords();
    void searchRecord();
    void editRecord();
    void deleteRecord();
    void undoDelete();
    void viewRecent();
    void manageOfficers();
};

void RecordManager::loadRecords() {
    ifstream file("criminal_records.txt");
    if (file) {
        CriminalRecord record;
        while (getline(file, record.id)) {
            getline(file, record.name);
            getline(file, record.crime);
            getline(file, record.punishment);
            getline(file, record.arrestDate);
            getline(file, record.status);
            criminals.push_back(record);
            idIndexMap[record.id] = criminals.size() - 1;
        }
        file.close();
    }

    ifstream officerFile("officers.txt");
    if (officerFile) {
        PoliceOfficer officer;
        while (getline(officerFile, officer.badgeNumber)) {
            getline(officerFile, officer.name);
            getline(officerFile, officer.rank);
            officers.push_back(officer);
        }
        officerFile.close();
    }
}

void RecordManager::saveRecords() {
    ofstream file("criminal_records.txt");
    for (const auto& record : criminals) {
        file << record.id << "\n"
             << record.name << "\n"
             << record.crime << "\n"
             << record.punishment << "\n"
             << record.arrestDate << "\n"
             << record.status << "\n";
    }
    file.close();

    ofstream officerFile("officers.txt");
    for (const auto& officer : officers) {
        officerFile << officer.badgeNumber << "\n"
                    << officer.name << "\n"
                    << officer.rank << "\n";
    }
    officerFile.close();
}

bool RecordManager::idExists(const string& id) {
    return idIndexMap.count(id) > 0;
}

void RecordManager::displayRecord(const CriminalRecord& record) {
    cout << "\n========================================" << endl;
    cout << "ID: " << record.id << endl;
    cout << "Name: " << record.name << endl;
    cout << "Crime: " << record.crime << endl;
    cout << "Punishment: " << record.punishment << endl;
    cout << "Arrest Date: " << record.arrestDate << endl;
    cout << "Status: " << record.status << endl;
    cout << "========================================" << endl;
}

void RecordManager::login() {
    int attempts = 0;
    while (attempts < 3) {
        system("cls");
        cout << "\n  POLICE RECORD MANAGEMENT SYSTEM - LOGIN" << endl;
        cout << "  ======================================" << endl;

        string username, password;
        cout << "\n  Username: ";
        cin >> username;
        cout << "  Password: ";

        char ch;
        password = "";
        while ((ch = _getch()) != 13) {
            if (ch == 8 && !password.empty()) {
                password.pop_back();
                cout << "\b \b";
            } else if (ch != 8) {
                password.push_back(ch);
                cout << '*';
            }
        }

        if (username == adminCredentials[0] && password == adminCredentials[1]) {
            currentUser = username;
            cout << "\n\n  Login successful! Welcome, " << username << "!" << endl;
            cout << "\n  Press any key to continue...";
            _getch();
            return;
        } else {
            attempts++;
            cout << "\n\n  Invalid credentials. Attempts remaining: " << 3 - attempts << endl;
            cout << "  Press any key to try again...";
            _getch();
        }
    }
    cout << "\n\n  Maximum login attempts reached. System exiting..." << endl;
    exit(0);
}

void RecordManager::mainMenu() {
    while (true) {
        system("cls");
        cout << "\n  POLICE RECORD MANAGEMENT SYSTEM" << endl;
        cout << "  ===============================" << endl;
        cout << "  Logged in as: " << currentUser << endl << endl;

        cout << "  1. Add New Criminal Record" << endl;
        cout << "  2. View All Records" << endl;
        cout << "  3. Search Record" << endl;
        cout << "  4. Edit Record" << endl;
        cout << "  5. Delete Record" << endl;
        cout << "  6. Manage Police Officers" << endl;
        cout << "  7. Undo Last Delete (Stack)" << endl;
        cout << "  8. View Recently Viewed (Queue)" << endl;
        cout << "  9. Exit System" << endl;

        cout << "\n  Enter your choice (1-9): ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: addRecord(); break;
            case 2: viewRecords(); break;
            case 3: searchRecord(); break;
            case 4: editRecord(); break;
            case 5: deleteRecord(); break;
            case 6: manageOfficers(); break;
            case 7: undoDelete(); break;
            case 8: viewRecent(); break;
            case 9:
                saveRecords();
                cout << "\n  Saving data... Goodbye!" << endl;
                exit(0);
            default:
                cout << "\n  Invalid choice. Please try again." << endl;
                cout << "  Press any key to continue...";
                _getch();
        }
    }
}

// The remaining member functions (addRecord, viewRecords, etc.) remain unchanged from your original code.


//*********************************************************
//**************** RECORD MANAGEMENT **********************
//*********************************************************

void RecordManager::addRecord() {
    system("cls");
    cout << "\n  ADD NEW CRIMINAL RECORD" << endl;
    cout << "  =======================" << endl;

    CriminalRecord newRecord;

    cout << "\n  Enter Criminal ID: ";
    cin >> newRecord.id;

    if (idExists(newRecord.id)) {
        cout << "\n  Error: A record with this ID already exists!" << endl;
        _getch();
        return;
    }

    cin.ignore();
    cout << "  Enter Full Name: ";
    getline(cin, newRecord.name);
    cout << "  Enter Crime: ";
    getline(cin, newRecord.crime);
    cout << "  Enter Punishment: ";
    getline(cin, newRecord.punishment);
    cout << "  Enter Arrest Date (DD/MM/YYYY): ";
    getline(cin, newRecord.arrestDate);
    cout << "  Enter Status (In Custody/Released/Wanted): ";
    getline(cin, newRecord.status);

    criminals.push_back(newRecord);
    idIndexMap[newRecord.id] = criminals.size() - 1;

    saveRecords();

    cout << "\n  Record added successfully!" << endl;
    _getch();
}

void RecordManager::viewRecords() {
    system("cls");
    cout << "\n  CRIMINAL RECORDS DATABASE" << endl;
    cout << "  =========================" << endl;

    if (criminals.empty()) {
        cout << "\n  No records found in the database." << endl;
    } else {
        for (const auto& record : criminals) {
            displayRecord(record);
            if (recentlyViewed.size() == 5) recentlyViewed.pop();
            recentlyViewed.push(record);
            cout << "  Press any key for next record...";
            _getch();
        }
    }

    cout << "\n  End of records." << endl;
    _getch();
}

void RecordManager::searchRecord() {
    system("cls");
    cout << "\n  SEARCH CRIMINAL RECORDS" << endl;
    cout << "  =======================" << endl;

    cout << "\n  1. Search by ID" << endl;
    cout << "  2. Search by Name" << endl;
    cout << "  3. Search by Crime" << endl;
    cout << "  4. Back to Main Menu" << endl;

    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 4) return;

    string searchTerm;
    cout << "\n  Enter search term: ";
    getline(cin, searchTerm);

    vector<CriminalRecord> results;

    switch (choice) {
        case 1:
            if (idIndexMap.count(searchTerm)) {
                results.push_back(criminals[idIndexMap[searchTerm]]);
            }
            break;
        case 2:
            for (const auto& r : criminals)
                if (r.name.find(searchTerm) != string::npos)
                    results.push_back(r);
            break;
        case 3:
            for (const auto& r : criminals)
                if (r.crime.find(searchTerm) != string::npos)
                    results.push_back(r);
            break;
        default:
            cout << "\n  Invalid choice." << endl;
            _getch();
            return;
    }

    if (results.empty()) {
        cout << "\n  No matching records found." << endl;
    } else {
        for (const auto& r : results) {
            displayRecord(r);
            if (recentlyViewed.size() == 5) recentlyViewed.pop();
            recentlyViewed.push(r);
        }
    }
    _getch();
}

void RecordManager::editRecord() {
    system("cls");
    cout << "\n  EDIT CRIMINAL RECORD" << endl;

    cout << "\n  Enter Criminal ID to edit: ";
    string id;
    cin >> id;
    cin.ignore();

    if (!idIndexMap.count(id)) {
        cout << "\n  Record not found!" << endl;
        _getch();
        return;
    }

    CriminalRecord& record = criminals[idIndexMap[id]];
    displayRecord(record);

    cout << "\n  1. Name\n  2. Crime\n  3. Punishment\n  4. Arrest Date\n  5. Status\n  6. Cancel\n";
    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1: getline(cin, record.name); break;
        case 2: getline(cin, record.crime); break;
        case 3: getline(cin, record.punishment); break;
        case 4: getline(cin, record.arrestDate); break;
        case 5: getline(cin, record.status); break;
        case 6: return;
        default: cout << "\n  Invalid choice."; break;
    }

    saveRecords();
    cout << "\n  Record updated." << endl;
    _getch();
}

void RecordManager::deleteRecord() {
    system("cls");
    cout << "\n  DELETE CRIMINAL RECORD" << endl;
    cout << "  =====================" << endl;

    cout << "\n  Enter Criminal ID to delete: ";
    string id;
    cin >> id;

    if (!idIndexMap.count(id)) {
        cout << "\n  Record not found!" << endl;
        _getch();
        return;
    }

    CriminalRecord& rec = criminals[idIndexMap[id]];
    displayRecord(rec);

    cout << "\n  Confirm delete? (Y/N): ";
    char c;
    cin >> c;
    if (toupper(c) == 'Y') {
        deletedRecords.push(rec);
        criminals.erase(criminals.begin() + idIndexMap[id]);
        idIndexMap.erase(id);
        // Rebuild map
        idIndexMap.clear();
        for (int i = 0; i < criminals.size(); ++i)
            idIndexMap[criminals[i].id] = i;
        saveRecords();
        cout << "\n  Record deleted.";
    } else {
        cout << "\n  Deletion cancelled.";
    }
    _getch();
}

void RecordManager::undoDelete() {
    if (deletedRecords.empty()) {
        cout << "\n  No deletion to undo.";
    } else {
        CriminalRecord rec = deletedRecords.top();
        deletedRecords.pop();
        criminals.push_back(rec);
        idIndexMap[rec.id] = criminals.size() - 1;
        saveRecords();
        cout << "\n  Deletion undone.";
    }
    _getch();
}

void RecordManager::viewRecent() {
    if (recentlyViewed.empty()) {
        cout << "\n  No recently viewed records.";
    } else {
        queue<CriminalRecord> temp = recentlyViewed;
        while (!temp.empty()) {
            displayRecord(temp.front());
            temp.pop();
        }
    }
    _getch();
}

void RecordManager::manageOfficers() {
    while (true) {
        system("cls");
        cout << "\n  POLICE OFFICER MANAGEMENT" << endl;
        cout << "  ========================" << endl;

        cout << "\n  1. Add New Officer" << endl;
        cout << "  2. View All Officers" << endl;
        cout << "  3. Back to Main Menu" << endl;

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                PoliceOfficer officer;
                cout << "\n  Enter Badge Number: ";
                getline(cin, officer.badgeNumber);
                cout << "  Enter Officer Name: ";
                getline(cin, officer.name);
                cout << "  Enter Rank: ";
                getline(cin, officer.rank);
                officers.push_back(officer);
                saveRecords();
                cout << "\n  Officer added!";
                break;
            }
            case 2: {
                if (officers.empty()) cout << "\n  No officers found.";
                else {
                    for (const auto& o : officers) {
                        cout << "\nBadge: " << o.badgeNumber << "\nName: " << o.name << "\nRank: " << o.rank << "\n-------------------";
                    }
                }
                break;
            }
            case 3: return;
            default: cout << "\n  Invalid option.";
        }
        _getch();
    }
}

//*********************************************************
//**************** MAIN FUNCTION **************************
//*********************************************************

int main() {
    RecordManager system;
    system.login();
    system.mainMenu();
    return 0;
}
