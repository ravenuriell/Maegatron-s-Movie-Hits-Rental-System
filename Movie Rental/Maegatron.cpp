#include "Maegatron.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  


using namespace std;

void Maegatron::videoIDGenerate() {
    ++tempCode;
    mov.id = tempCode;
}

void Maegatron::customerIDGenerate() {
    ++tempCustomer;
    cust.cID = tempCustomer;
}

void Maegatron::insertMovie() {
    videoIDGenerate();
    cout << "Enter Movie Title: ";
    cin.ignore();
    getline(cin, mov.title);
    cout << "Enter Movie Genre: ";
    getline(cin, mov.genre);
    cout << "Enter Movie Production: ";
    getline(cin, mov.production);
    cout << "Enter Number of Copies: ";
    cin >> mov.copies;
    vid.push_back(mov);
}

void Maegatron::vidDetails() {
    int id;
    cout << "Enter Video ID: ";
    cin >> id;
    for (const auto& v : vid) {
        if (v.id == id) {
            cout << "ID: " << v.id << endl;
            cout << "Title: " << v.title << endl;
            cout << "Genre: " << v.genre << endl;
            cout << "Production: " << v.production << endl;
            cout << "Available Copies: " << v.copies << endl;
            return;
        }
    }
    cout << "Video ID not found!" << endl;
}

void Maegatron::displayList() {
    cout << left << setw(6) << "ID" << setw(20) << "Title" << setw(15) << "Genre"
         << setw(20) << "Production" << setw(10) << "Copies" << endl;
    cout << "--------------------------------------------------------------\n";
    for (const auto& v : vid) {
        cout << left << setw(6) << v.id << setw(20) << v.title
             << setw(15) << v.genre << setw(20) << v.production
             << setw(10) << v.copies << endl;
    }
}

void Maegatron::availability() {
    int id;
    cout << "Enter Video ID: ";
    cin >> id;
    for (const auto& v : vid) {
        if (v.id == id) {
            cout << "Available Copies: " << v.copies << endl;
            return;
        }
    }
    cout << "Video ID not found!" << endl;
}

void Maegatron::vidSave() {
    ofstream out("video.txt");
    out << tempCode << endl;
    for (const auto& v : vid) {
        out << v.id << ',' << v.title << ',' << v.genre << ','
            << v.production << ',' << v.copies << endl;
    }
    out.close();
}

void Maegatron::vidLoad() {
    ifstream in("video.txt");
    if (!in) return;
    string line;
    getline(in, line);
    tempCode = stoi(line);
    while (getline(in, line)) {
        stringstream ss(line);
        string s;
        getline(ss, s, ','); mov.id = stoi(s);
        getline(ss, mov.title, ',');
        getline(ss, mov.genre, ',');
        getline(ss, mov.production, ',');
        getline(ss, s, ','); mov.copies = stoi(s);
        vid.push_back(mov);
    }
    in.close();
}

void Maegatron::newCustomer() {
    customerIDGenerate();
    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, cust.name);
    cout << "Enter Customer Address: ";
    getline(cin, cust.address);
    customer.push_back(cust);
}

void Maegatron::custDetails() {
    int id;
    cout << "Enter Customer ID: ";
    cin >> id;
    for (const auto& c : customer) {
        if (c.cID == id) {
            cout << "ID: " << c.cID << endl;
            cout << "Name: " << c.name << endl;
            cout << "Address: " << c.address << endl;
            return;
        }
    }
    cout << "Customer ID not found!" << endl;
}

void Maegatron::custRentedList() {
    int id;
    cout << "Enter Customer ID: ";
    cin >> id;
    cout << "Rented Video IDs: ";
    for (const auto& rentRec : stk) {
        if (rentRec.cust_ID == id) {
            cout << rentRec.vid_ID << " ";
        }
    }
    cout << endl;
}

void Maegatron::custSave() {
    ofstream out("customer.txt");
    out << tempCustomer << endl;
    for (const auto& c : customer) {
        out << c.cID << ',' << c.name << ',' << c.address << endl;
    }
    out.close();
}

void Maegatron::custLoad() {
    ifstream in("customer.txt");
    if (!in) return;
    string line;
    getline(in, line);
    tempCustomer = stoi(line);
    while (getline(in, line)) {
        stringstream ss(line);
        string s;
        getline(ss, s, ','); cust.cID = stoi(s);
        getline(ss, cust.name, ',');
        getline(ss, cust.address, ',');
        customer.push_back(cust);
    }
    in.close();
}

void Maegatron::vidRent() {
    cout << "Enter Customer ID: ";
    cin >> r.cust_ID;
    cout << "Enter Video ID: ";
    cin >> r.vid_ID;

    for (auto& v : vid) {
        if (v.id == r.vid_ID) {
            if (v.copies > 0) {
                v.copies--;
                rent.push(r);
                stk.push_back(r);
                cout << "Video rented successfully!\n";
                return;
            } else {
                cout << "Video not available!\n";
                return;
            }
        }
    }
    cout << "Video ID not found!\n";
}

void Maegatron::save_vidRent() {
    ofstream out("rent.txt");
    for (const auto& r : stk) {
        out << r.vid_ID << ',' << r.cust_ID << endl;
    }
    out.close();
}

void Maegatron::load_vidRent() {
    ifstream in("rent.txt");
    if (!in) return;
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string s;
        getline(ss, s, ','); r.vid_ID = stoi(s);
        getline(ss, s, ','); r.cust_ID = stoi(s);
        rent.push(r);
        stk.push_back(r);
    }
    in.close();
}

void Maegatron::returnVid() {
    int vidID, custID;
    cout << "Enter Customer ID: ";
    cin >> custID;
    cout << "Enter Video ID: ";
    cin >> vidID;

    bool found = false;
    vector<CustomerRent> tempStack;

    while (!rent.empty()) {
        CustomerRent top = rent.top();
        rent.pop();
        if (top.vid_ID == vidID && top.cust_ID == custID && !found) {
            found = true;
            for (auto& v : vid) {
                if (v.id == vidID) {
                    v.copies++;
                    break;
                }
            }
        } else {
            tempStack.push_back(top);
        }
    }

    for (auto it = tempStack.rbegin(); it != tempStack.rend(); ++it) {
        rent.push(*it);
    }

    if (found) {
        stk.erase(remove_if(stk.begin(), stk.end(), [vidID, custID](const CustomerRent& r) {
            return r.vid_ID == vidID && r.cust_ID == custID;
        }), stk.end());
        cout << "Video returned successfully.\n";
    } else {
        cout << "Rental record not found.\n";
    }
}
