/*
Mason Gross
Vector lab part 2
Extra: Possible use of a txt file in place of manual insertion
and writes the new restaurant order to the txt file.
*/

#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
using namespace std;
void printVector(vector<string>& vect);
int findIndex(vector<string>& v, string val);
tuple<int, string> prompts(vector<string>& vect, int prompt);

int main() {
    int user_int = 0;
    string user_string = "";
    tuple<int, string> receiver;
    string file = user_string;
    string text;
    vector<string> restaurants(0);
    cout << "Restaurant Ranker: " << endl;
    while(true) {
        cout << "Do you wish to get the starter restaurants through a file or manual?" << endl;
        cin >> user_string;
        if(user_string == "file") {
            cout << "Input file name: ";
            cin >> file;
            ifstream MyReadFile(file);
            while (getline (MyReadFile, text)) {
                restaurants.push_back(text);
            }
            MyReadFile.close();
            break;
        } else if (user_string == "manual") {
            cout << "Starting manual input..." << endl;
            cout << "How many restaurants do you want to rank?" << endl;
            cin >> user_int;
            vector<string> restaurants(user_int);
            for(int i = 0; i < restaurants.size(); i++) {
                cout << "What is your restaurant ranked: " << i + 1 << "?" << endl;
                cin >> user_string;
                restaurants[i] = user_string;
            }
            break;
        } else {
            cout << "Not a valid input." << endl;
        }
    }
    cout << "Current list:" << endl;
    printVector(restaurants);
    while(true) {
        cout << "Do you want to make an edit to your list?" << endl;
        cout << "1: Insert a new restaurant" << endl;
        cout << "2: Replace a restaurant" << endl;
        cout << "3: Erase a restraurant" << endl;
        cout << "4: End & Finalize the list" << endl;
        cin >> user_int;
        if(user_int == 1) {
            auto [receive_int, receive_string] = prompts(restaurants, 1);
            restaurants.insert(restaurants.begin() + (receive_int - 1), receive_string);
        }
        else if(user_int == 2) {
            auto [receive_int, receive_string] = prompts(restaurants, 2);
            restaurants[receive_int] = receive_string;
        }
        else if(user_int == 3) {
            auto [receive_int, receive_string] = prompts(restaurants, 3);
            if(receive_int == 0 && receive_string == "") {
                cout << "Rejected deletion." << endl;
            } else {
                restaurants.erase(restaurants.begin() + receive_int);
            }
        }
        else if(user_int == 4) {
            printVector(restaurants);
            break;
        } else {
            cout << "Not a valid integer." << endl;
        }

    }
    ofstream MyWriteFile(file);
    for(auto itr = restaurants.begin(); itr != restaurants.end(); ++itr) {
        MyWriteFile << *itr << "\n";
    }
    MyWriteFile.close();
    return 0;
}

tuple<int, string> prompts(vector<string>& vect, int prompt) {
    int u1 = 0;
    string u2 = "";
    string storage = "";
    if(prompt == 1) {
        cout << "What restaurant would you like to insert?" << endl;
        cin >> u2;
        cout << "Where would you like to insert " << u2 << "?" << endl;
        cin >> u1;
        return {u1, u2};
    } else if (prompt == 2) {
        cout << "Which restaurant would you like to replace?" << endl;
        cin >> u2;
        u1 = findIndex(vect, u2);
        storage = u2;
        cout << "What would you like to replace " << u2 << " with?" << endl;
        cin >> u2;
        cout << "Replacing " << storage << " with " << u2 << "." << endl;
        return {u1, u2};
    } else if (prompt == 3) {
        cout << "Which restaurant would you like to delete?" << endl;
        cin >> u2;
        u1 = findIndex(vect, u2);
        storage = u2;
        cout << "Are you sure you want to delete " << u2 << "?" << endl;
        cin >> u2;
        if(u2 == "yes") {
            cout << "Deleting..." << storage << endl;
            return {u1, u2};
        } else if (u2 == "no") {
            cout << "Going back..." << endl;
            return {0, ""};
        } else {
            cout << "Invalid input\nGoing back..." << endl;
            return {0, ""};
        }
    }
    return {0,""};
}

int findIndex(vector<string>& v, string val) {
    int count = 0;
    for(auto itr = v.begin(); itr != v.end(); ++itr) {
      
        if (*itr == val) {
            return count;
        }
        count += 1;
    }
  	
  	return -1;
}

void printVector(vector<string>& vect) {
    int count = 1;
    for(auto itr = vect.begin(); itr != vect.end(); ++itr) {
        cout << count << ": " << *itr << endl;
        count += 1;
    }
}