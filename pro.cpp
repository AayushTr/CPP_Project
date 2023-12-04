 #include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

struct User {
    string username;
    string password;
    string userType;

    User(string name, string pass, string type) : username(name), password(pass), userType(type) {}
};

struct HouseHelper {
    string name;
    string address;
    string contactNumber;
    string skills;

    HouseHelper* prev;
    HouseHelper* next;

    HouseHelper(string n, string addr, string contact, string s)
        : name(n), address(addr), contactNumber(contact), skills(s), prev(nullptr), next(nullptr) {}
};

struct CustomerRequest {
    string name;
    string address;
    string contactNumber;
    string requiredSkills;
    string customService;
    string timingSlot;
    string facility;
};

class UserManager {
private:
    list<User> users;

public:
    void RegisterUser() {
        string username, password, userType;
        cout << "\t\tEnter User Name: ";
        getline(cin, username);
        cout << "\t\tEnter Password: ";
        getline(cin, password);
        cout << "\t\tEnter User Type (helper or customer): ";
        getline(cin, userType);

        User newUser(username, password, userType);
        users.push_back(newUser);

        WriteUserDataToFile();

        cout << "\t\tUser Registered Successfully ....." << endl;
    }

    bool LoginUser(string name, string pass) {
        for (const auto& user : users) {
            if (user.username == name && user.password == pass) {
                cout << "\t\tLogin Successfully...." << endl;
                return true;
            }
        }
        cout << "\t\tInvalid User Name or Password..." << endl;
        return false;
    }

    void ShowUser() {
        cout << "\t\t---Users List---" << endl;
        for (const auto& user : users) {
            cout << "\t\t" << user.username << " - " << user.userType << endl;
        }
    }

    void SearchUser(string username) {
        for (const auto& user : users) {
            if (user.username == username) {
                cout << "\t\tUser Found - Type: " << user.userType << endl;
                return;
            }
        }
        cout << "\t\tUser not found." << endl;
    }

    void DeleteUser(string username) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->username == username) {
                users.erase(it);
                WriteUserDataToFile();
                cout << "\t\tUser Removed Successfully...." << endl;
                return;
            }
        }

        
        cout << "\t\tUser not found." << endl;
    }
     void WriteUserDataToFile() {
        ofstream outFile("user_data.txt");
        if (outFile.is_open()) {
            for (const auto& user : users) {
                outFile << user.username << ',' << user.password << ',' << user.userType << '\n';
            }
            outFile.close();
        } else {
            cerr << "Error: Unable to open user data file for writing." << endl;
        }
    }

    void ReadUserDataFromFile() {
        ifstream inFile("user_data.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string username, password, userType;
                getline(ss, username, ',');
                getline(ss, password, ',');
                getline(ss, userType);

                User newUser(username, password, userType);
                users.push_back(newUser);
            }
            inFile.close();
        } else {
            cerr << "Warning: User data file not found. Creating a new one." << endl;
        }
    }
};


class HouseHelperManager {
private:
    list<HouseHelper> helpers;

public:
    void AddHelper(const HouseHelper& newHelper) {
        helpers.push_back(newHelper);

        // Update the file after adding a new helper
        WriteHelperDataToFile();

        cout << "Helper Added Successfully." << endl;
    }

    // New function to write helper data to file
    void WriteHelperDataToFile() {
        ofstream outFile("helper_data.txt");
        if (outFile.is_open()) {
            for (const auto& helper : helpers) {
                outFile << helper.name << ',' << helper.address << ',' << helper.contactNumber
                        << ',' << helper.skills << '\n';
            }
            outFile.close();
        } else {
            cerr << "Error: Unable to open helper data file for writing." << endl;
        }
    }

    // New function to read helper data from file
    void ReadHelperDataFromFile() {
        ifstream inFile("helper_data.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string name, address, contactNumber, skills;
                getline(ss, name, ',');
                getline(ss, address, ',');
                getline(ss, contactNumber, ',');
                getline(ss, skills);

                HouseHelper newHelper(name, address, contactNumber, skills);
                helpers.push_back(newHelper);
            }
            inFile.close();
        } else {
            cerr << "Warning: Helper data file not found. Creating a new one." << endl;
        }
    }
};

void searchByLocation(const list<HouseHelper>& helpers, const string& location) {
    cout << "Search results for location: " << location << endl;
    bool found = false;
    for (const auto& helper : helpers) {
        if (helper.address.find(location) != string::npos) {
            cout << "Name: " << helper.name << endl;
            cout << "Address: " << helper.address << endl;
            cout << "Contact Number: " << helper.contactNumber << endl;
            cout << "Skills: " << helper.skills << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No helpers found in the location: " << location << endl;
    }
}

void searchBySkill(const list<HouseHelper>& helpers, const string& skill) {
    cout << "Search results for skill: " << skill << endl;
    bool found = false;
    for (const auto& helper : helpers) {
        if (helper.skills.find(skill) != string::npos) {
            cout << "Name: " << helper.name << endl;
            cout << "Address: " << helper.address << endl;
            cout << "Contact Number: " << helper.contactNumber << endl;
            cout << "Skills: " << helper.skills << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No helpers found with the skill: " << skill << endl;
    }
}

void bookAppointment(const HouseHelper& helper) {
    cout << "Booking an appointment with the selected helper..." << endl;
    cout << "Helper Details:" << endl;
    cout << "Name: " << helper.name << endl;
    cout << "Address: " << helper.address << endl;
    cout << "Contact Number: " << helper.contactNumber << endl;
    cout << "Skills: " << helper.skills << endl;
}

int main() {
    UserManager usermanage;
    HouseHelperManager helperManager;

    

    int op;
    char choice;
    do {
        system("cls");
        cout << "\n\n\t\t1. Register User " << endl;
        cout << "\t\t2. Login " << endl;
        cout << "\t\t3. Show User List " << endl;
        cout << "\t\t4. Search User " << endl;
        cout << "\t\t5. Delete User" << endl;
        cout << "\t\t6. Exit" << endl;
        cout << "\t\tEnter Your Choice : ";
        cin >> op;
        cin.ignore();
        switch (op) {
            case 1: {
                usermanage.RegisterUser();
                break;
            }
            case 2: {
                string username, password;
                cout << "\t\tEnter User: ";
                cin >> username;
                cout << "\t\tEnter Password: ";
                cin >> password;
                usermanage.LoginUser(username, password);
                break;
            }
            case 3: {
                usermanage.ShowUser();
                break;
            }
            case 4: {
                string username;
                cout << "\t\tEnter User Name: ";
                cin >> username;
                usermanage.SearchUser(username);
                break;
            }
            case 5: {
                string username;
                cout << "\t\tEnter User Name: ";
                cin >> username;
                usermanage.DeleteUser(username);
                break;
            }
            case 6:
                exit(1);
        }
        cout << "\t\tDo You Want to Continue [Yes/ No] ? :";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    list<HouseHelper> helpers = {
        // Hard-coded helper data
        {"John Doe", "123 Main St", "123-456-7890", "Cooking, Cleaning"},
        {"Jane Smith", "456 Oak Ave", "987-654-3210", "Laundry, Organizing"},
        {"Robert Johnson", "789 Elm St", "456-789-1230", "Cooking, Gardening"},
    {"Lisa Williams", "345 Pine Ave", "789-123-4560", "Cleaning, Babysitting"},
    {"Amit Patel", "567 Cedar St", "234-567-8901", "Cooking, Laundry"},
    {"Sneha Gupta", "789 Walnut Ave", "345-678-9012", "Cooking, Cleaning"},
    {"Rahul Sharma", "901 Maple Ave", "456-789-0123", "Cleaning, Gardening"},
    {"Priya Singh", "234 Birch St", "567-890-1234", "Cooking, Babysitting"},
    {"Sanjay Kumar", "678 Pine St", "678-901-2345", "Cooking, Laundry"},
    {"Anjali Desai", "890 Elm St", "789-012-3456", "Cleaning, Organizing"},
    {"Rajesh Gupta", "432 Pine St", "890-123-4567", "Cooking, Gardening"},
    {"Pooja Verma", "654 Oak Ave", "901-234-5678", "Cooking, Babysitting"},
    {"Vikram Singh", "876 Maple Ave", "012-345-6789", "Cleaning, Laundry"},
    {"Neha Patel", "987 Elm St", "210-987-6543", "Cooking, Organizing"},
    {"Arun Sharma", "109 Pine St", "321-876-5432", "Cooking, Cleaning"},
    {"Divya Kapoor", "210 Cedar St", "432-765-4321", "Cleaning, Babysitting"},
    {"Ganesh Iyer", "543 Walnut Ave", "543-654-3210", "Cooking, Laundry"},
    {"Meera Reddy", "765 Maple Ave", "654-543-2109", "Cooking, Gardening"},
    {"Aakash Khan", "987 Birch St", "765-432-1098", "Cleaning, Organizing"},
    {"Vijay Reddy", "234 Oak Ave", "876-543-2101", "Cooking, Babysitting"},
    {"Mala Gupta", "876 Pine St", "109-543-7654", "Cooking, Laundry"},
    {"Sanjana Iyer", "432 Cedar St", "543-210-9876", "Cleaning, Gardening"},
    {"Kishan Patel", "567 Walnut Ave", "432-987-6543", "Cooking, Organizing"},
    {"Nandini Rao", "321 Elm St", "876-654-3210", "Cooking, Cleaning"},
    {"Suresh Menon", "109 Maple Ave", "765-210-8765", "Cleaning, Babysitting"},
    {"Leela Khanna", "654 Birch St", "543-987-2106", "Cooking, Laundry"},
    {"Kartik Kumar", "876 Cedar St", "876-543-0987", "Cooking, Gardening"},
    {"Ranjit Sharma", "987 Pine St", "109-876-5432", "Cleaning, Organizing"},
    {"Ananya Verma", "210 Oak Ave", "432-210-7654", "Cooking, Gardening"},
    {"Vivek Mehta", "345 Maple Ave", "543-987-6540", "Cooking, Cleaning"},
    {"Deepa Iyer", "543 Elm St", "432-654-0987", "Laundry, Organizing"},
    {"Harish Patel", "210 Pine St", "876-098-7654", "Cleaning, Babysitting"},
    {"Ritu Kapoor", "987 Walnut Ave", "543-876-2109", "Cooking, Gardening"},
    {"Sarita Jain", "234 Cedar St", "432-765-1098", "Cooking, Organizing"},
    {"Rajiv Das", "567 Birch St", "876-210-6543", "Cleaning, Laundry"},
    {"Kavita Singh", "345 Oak Ave", "543-654-8765", "Cooking, Cleaning"},
    {"Ashok Reddy", "654 Pine St", "210-098-5432", "Cooking, Babysitting"},
    {"Madhu Gupta", "432 Maple Ave", "765-543-2106", "Cleaning, Gardening"},
    {"Kiran Iyer", "109 Elm St", "543-210-9876", "Cooking, Organizing"},
    {"Deepak Verma", "876 Cedar St", "432-987-6540", "Cooking, Laundry"},
    {"Neelam Patel", "789 Walnut Ave", "876-654-0987", "Cooking, Cleaning"},
    {"Ramesh Sharma", "210 Pine St", "432-098-7654", "Cleaning, Gardening"},
    {"Maya Kapoor", "987 Birch St", "543-765-1098", "Cooking, Babysitting"},
    {"Ajay Kumar", "456 Oak Ave", "765-210-6543", "Cooking, Organizing"},
    {"Kirti Iyer", "876 Cedar St", "543-654-8765", "Laundry, Gardening"},
    {"Sudhir Rao", "654 Pine St", "210-987-5432", "Cooking, Cleaning"},
    {"Anita Mehta", "321 Maple Ave", "432-210-6540", "Cleaning, Organizing"},
    {"Rohit Gupta", "543 Elm St", "543-098-0987", "Cooking, Laundry"},
    {"Shreya Khanna", "987 Walnut Ave", "876-210-1098", "Cooking, Babysitting"},
    {"Sarvesh Patel", "234 Cedar St", "765-654-6543", "Cooking, Cleaning"},
    {"Nisha Verma", "876 Pine St", "109-543-6540", "Laundry, Gardening"},
    {"Vijay Menon", "789 Oak Ave", "432-765-7654", "Cleaning, Organizing"},
    {"Nandini Kapoor", "456 Elm St", "543-210-2106", "Cooking, Gardening"},
    {"Arjun Sharma", "567 Maple Ave", "654-543-9876", "Cooking, Laundry"},
    {"Sunita Iyer", "210 Pine St", "876-987-6540", "Cooking, Cleaning"},
    {"Rajesh Das", "654 Cedar St", "432-210-1098", "Babysitting, Organizing"}
        // ... (remaining helper data)
    };

    string searchLocation;
    cout << "Enter a location to search for: ";
    cin.ignore();
    getline(cin, searchLocation);

    // Search for helpers by location
    searchByLocation(helpers, searchLocation);

    // Search for helpers by skill
    string searchSkill;
    cout << "Enter a skill to search for: ";
    getline(cin, searchSkill);
    searchBySkill(helpers, searchSkill);

    // Selecting a helper and booking an appointment
    string selectedHelperName;
    cout << "Enter the name of the selected helper to book an appointment: ";
    getline(cin, selectedHelperName);

    bool foundHelper = false;
    for (const auto& helper : helpers) {
        if (helper.name == selectedHelperName) {
            bookAppointment(helper);
            foundHelper = true;
            break;
        }
    }

    if (!foundHelper) {
        cout << "Helper not found." << endl;
    }

    CustomerRequest customerRequest;
    cout << "\nEnter your customization details:\n";
    cout << "Enter your required skills: ";
    getline(cin, customerRequest.requiredSkills);
    cout << "Enter your custom service request (if any): ";
    getline(cin, customerRequest.customService);
    cout << "Enter your preferred timing slot: ";
    getline(cin, customerRequest.timingSlot);
    cout << "Enter the facility you require: ";
    getline(cin, customerRequest.facility);

    // Display the entered information
    cout << "\nCustomer Request Details:" << endl;
    cout << "Required Skills: " << customerRequest.requiredSkills << endl;
    cout << "Custom Service Request: " << customerRequest.customService << endl;
    cout << "Preferred Timing Slot: " << customerRequest.timingSlot << endl;
    cout << "Required Facility: " << customerRequest.facility << endl;

    return 0;
}