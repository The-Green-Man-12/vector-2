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
    string file;
    string text;
    vector<string> restaurants(0);
    cout << "Restaurant Ranker: " << endl;
    while(true) { //Continues to ask until a valid input is given
        cout << "Do you wish to get the starter restaurants through a file or manual?" << endl;
        cin >> user_string;
        if(user_string == "file") { //If user wants to use a file
            cout << "Input file name: ";
            cin >> file;
            ifstream MyReadFile(file);
            while (getline (MyReadFile, text)) {
                restaurants.push_back(text); //Pushes each line of the file into the vector
            }
            MyReadFile.close();
            break;
        } else if (user_string == "manual") {
            cout << "Starting manual input..." << endl;
            cout << "How many restaurants do you want to rank?" << endl;
            cin >> user_int;
            vector<string> restaurants(user_int);
            for(int i = 0; i < restaurants.size(); i++) { //Asks user for each restaurant and pushes it into the vector
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
    while(true) { //Start of loop for editing the list, continues until user is done
        cout << "Do you want to make an edit to your list?" << endl;
        cout << "1: Insert a new restaurant" << endl;
        cout << "2: Replace a restaurant" << endl;
        cout << "3: Erase a restraurant" << endl;
        cout << "4: End & Finalize the list" << endl;
        cin >> user_int;
        if(user_int == 1) { //Inserting
            auto [receive_int, receive_string] = prompts(restaurants, 1);
            restaurants.insert(restaurants.begin() + (receive_int - 1), receive_string);
        }
        else if(user_int == 2) { //Replacing
            auto [receive_int, receive_string] = prompts(restaurants, 2);
            restaurants[receive_int] = receive_string;
        }
        else if(user_int == 3) { //Deleting/erasing
            auto [receive_int, receive_string] = prompts(restaurants, 3);
            if(receive_int == 0 && receive_string == "") {
                cout << "Rejected deletion." << endl;
            } else { //If user inputs "yes" to the prompt, the restaurant is deleted
                restaurants.erase(restaurants.begin() + receive_int);
            }
        }
        else if(user_int == 4) { //End of loop, prints final list
            printVector(restaurants);
            break;
        } else {
            cout << "Not a valid integer." << endl;
        }

    }
    if(file != "") { //If the user used a file, the new list is written to the file, replacing the old list
        ofstream MyWriteFile(file);
        for(auto itr = restaurants.begin(); itr != restaurants.end(); ++itr) {
            MyWriteFile << *itr << "\n";
        }
        MyWriteFile.close();
    }
    return 0;
}

tuple<int, string> prompts(vector<string>& vect, int prompt) {
    int u1 = 0;
    string u2 = "";
    string storage = "";
    if(prompt == 1) { //Insertion
        cout << "What restaurant would you like to insert?" << endl;
        cin >> u2;
        cout << "Where would you like to insert " << u2 << "?" << endl;
        cin >> u1;
        return {u1, u2};
    } else if (prompt == 2) { //Replacement
        cout << "Which restaurant would you like to replace?" << endl;
        cin >> u2;
        u1 = findIndex(vect, u2);
        storage = u2;
        cout << "What would you like to replace " << u2 << " with?" << endl;
        cin >> u2;
        cout << "Replacing " << storage << " with " << u2 << "." << endl;
        return {u1, u2};
    } else if (prompt == 3) { //Deletion/erasing
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
    return {0,""}; //If invalid prompt is given, returns 0 and empty string
}

int findIndex(vector<string>& v, string val) {
    int count = 0;
    for(auto itr = v.begin(); itr != v.end(); ++itr) {
      
        if (*itr == val) { //If the restaurant is found, the index is returned
            return count;
        }
        count += 1;
    }
  	
  	return -1; //If the restaurant is not found, -1 is returned
}

void printVector(vector<string>& vect) {
    int count = 1;
    for(auto itr = vect.begin(); itr != vect.end(); ++itr) {
        cout << count << ": " << *itr << endl;
        count += 1;
    }
}