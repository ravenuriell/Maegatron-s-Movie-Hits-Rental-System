#include "Maegatron.h"
using namespace std;

int main() {
    int ch = 0, c = 0;
    Maegatron hits;

    hits.vidLoad();
    hits.custLoad();
    hits.load_vidRent();

    while (true) {
        system("cls");
        cout << "...............................\n";
        cout << " MAEGATRON'S MOVIE HITS RENTAL\n";
        cout << "...............................\n";
        cout << "[1] Insert a New Video\n";
        cout << "[2] Rent a Video\n";
        cout << "[3] Return a Video\n";
        cout << "[4] Show Video Details\n";
        cout << "[5] Display all videos\n";
        cout << "[6] Check Video Availability\n";
        cout << "[7] Customer's Maintenance\n";
        cout << "[8] Exit Program\n";
        cout << "...............................\n";
        cout << "Enter Choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            hits.insertMovie();
            break;
        case 2:
            hits.displayList();
            hits.vidRent();
            break;
        case 3:
            hits.returnVid();
            break;
        case 4:
            hits.vidDetails();
            break;
        case 5:
            hits.displayList();
            break;
        case 6:
            hits.availability();
            break;
        case 7:
            cout << "[1] Add New Customer\n";
            cout << "[2] Show Customer Details\n";
            cout << "[3] List of Videos Rented by a Customer\n";
            cout << "Enter choice: ";
            cin >> c;
            if (c == 1) hits.newCustomer();
            else if (c == 2) hits.custDetails();
            else if (c == 3) hits.custRentedList();
            else cout << "Invalid option!\n";
            break;
        case 8:
            hits.save_vidRent();
            hits.custSave();
            hits.vidSave();
            cout << "Thank you for using Maegatron's Movie Hits Rental!\n";
            return 0;
        default:
            cout << "Invalid input!\n";
        }
        system("pause");
    }
}
