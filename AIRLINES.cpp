#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>  
#include <cstdio>
using namespace std;

struct Passenger {
    string firstName;
    string lastName;
    string ID;
    string phoneNumber;
    int seatNumber;
};

bool isIDExists(const string& searchID) {
    ifstream infile("passengers.txt");
    if (!infile) {
        cout << "\t\t\t\t\tError opening file!" << endl;
        return false;
    }

    Passenger passenger;

    while (infile >> passenger.firstName
                  >> passenger.lastName
                  >> passenger.ID
                  >> passenger.phoneNumber
                  >> passenger.seatNumber) {
        if (passenger.ID == searchID) {
            infile.close();
            return true;
        }
    }

    infile.close();
    return false;
}

bool isSeatBooked(int seatNumber) {
    ifstream infile("passengers.txt");
    if (!infile) {
        cout << "\t\t\t\t\tError opening file!" << endl;
        return false;
    }

    Passenger passenger;

    while (infile >> passenger.firstName
                  >> passenger.lastName
                  >> passenger.ID
                  >> passenger.phoneNumber
                  >> passenger.seatNumber) {
        if (passenger.seatNumber == seatNumber) {
            infile.close();
            return true;
        }
    }

    infile.close();
    return false;
}

bool hasOnlyLetters(const string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

bool hasOnlyDigits(const string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

void cancelReservation() {
    string searchID;
    cout << "\t\t\t\t\tEnter ID to search for passenger: ";
    cin >> searchID;

    ifstream infile("passengers.txt");
    if (!infile) {
        cout << "\t\t\t\t\tError opening file!" << endl;
        return;
    }

    ofstream outfile("temp.txt");
    if (!outfile) {
        cout << "\t\t\t\t\tError opening file!" << endl;
        infile.close();
        return;
    }

    Passenger passenger;
    bool found = false;

    while (infile >> passenger.firstName
                  >> passenger.lastName
                  >> passenger.ID
                  >> passenger.phoneNumber
                  >> passenger.seatNumber) {
        if (passenger.ID == searchID) {
            found = true;
            cout << "\t\t\t\t\tReservation for passenger with ID "
                 << passenger.ID << " cancelled!" << endl;
            continue; // Skip writing canceled reservation to temp.txt
        }

        outfile << passenger.firstName << " "
                << passenger.lastName << " "
                << passenger.ID << " "
                << passenger.phoneNumber << " "
                << passenger.seatNumber << endl;
    }

    infile.close();
    outfile.close();

    // Remove the existing passengers.txt file
    if (remove("passengers.txt") != 0) {
        cout << "\t\t\t\t\tError deleting file!" << endl;
        return;
    }

    // Rename the temp.txt file to passengers.txt
    if (rename("temp.txt", "passengers.txt") != 0) {
        cout << "\t\t\t\t\tError renaming file!" << endl;
        return;
    }

    if (!found) {
        cout <<"\t\t\t\t\tPASSENGER NOT FOUND....!" << endl;
    }
}


void makeReservation() {
    ofstream outfile("passengers.txt", ios::app);
    if (!outfile) {
        cout << "\t\t\t\t\tError opening file!" << endl;
        return;
    }

    Passenger passenger;

    while (true) {
        cout << "\t\t\t\t\tEnter first name : ";
        cin >> passenger.firstName;
        if (!hasOnlyLetters(passenger.firstName)) {
            cout << "\t\t\t\t\tERROR : FIRST NAME SHOULD CONTAIN ONLY LETTERS.....!" << endl;
        } else {
            break;
        }
    }

    while (true) {
        cout << "\t\t\t\t\tEnter last Name : ";
        cin >> passenger.lastName;
        if (!hasOnlyLetters(passenger.lastName)) {
            cout << "\t\t\t\t\tERROR : LAST NAME SHOULD CONTAIN ONLY LETTERS.....!" << endl;
        } else {
            break;
        }
    }

    while (true) {
        cout << "\t\t\t\t\tEnter ID (1 to 100): ";
        cin >> passenger.ID;
        if (!hasOnlyDigits(passenger.ID)) {
            cout << "\t\t\t\t\tERROR : ID SHOULD CONTAIN ONLY NUMBERS.....!" << endl;
        } else {
            int id;
            stringstream ss(passenger.ID);
            if (!(ss >> id) || id < 1 || id > 100) {
                cout << "\t\t\t\t\tERROR : ID SHOULD BE BETWEEN 1 TO 100 ." << endl;
            } else if (isIDExists(passenger.ID)) {
                cout << "\t\t\t\t\tERROR : ID ALREADY EXIST.....!" << endl;
            } else {
                break;
            }
        }
    }

    while (true) {
        cout << "\t\t\t\t\tEnter phone number : ";
        cin >> passenger.phoneNumber;
        if (!hasOnlyDigits(passenger.phoneNumber)) {
            cout << "\t\t\t\t\tERROR : PHONE NUMBER SHOULD CONTAIN ONLY NUMBERS....!" << endl;
        } else if (passenger.phoneNumber.length() != 10) {
            cout << "\t\t\t\t\tERROR : PHONE NUMBER SHOULD BE 10 DIGITS LONG....!" << endl;
        } else {
            break;
        }
    }

    while (true) {
        cout << "\t\t\t\t\tEnter seat number (1 to 100): ";
        string seatNumberStr;
        cin >> seatNumberStr;
        if (!hasOnlyDigits(seatNumberStr)) {
            cout << "\t\t\t\t\tERROR : SEAT NUMBER SHOULD CONTAIN ONLY NUMBERS....! " << endl;
        } else {
            int seatNumber;
            stringstream ss(seatNumberStr);
            if (!(ss >> seatNumber) || seatNumber < 1 || seatNumber > 100) {
                cout << "\t\t\t\t\tERROR : INVALID SEAT NUMBER \n\t\t\t\t\tSEAT NUMBER SHOULD BE BETWEEN 1 TO 100" << endl;
            } else if (isSeatBooked(seatNumber)) {
                cout << "\t\t\t\t\tERROR : SEAT ALREADY BOOKED ..!\n\t\t\t\t\tPLEASE CHOOSE DIFFERENT SEAT" << endl;
            } else {
                passenger.seatNumber = seatNumber;
                break;
            }
        }
    }

    outfile << passenger.firstName << " "
            << passenger.lastName << " "
            << passenger.ID << " "
            << passenger.phoneNumber << " "
            << passenger.seatNumber << endl;

    outfile.close();

    cout << "\t\t\t\t\tReservation made successfully!" << endl;
}
void changeReservation() {
    string searchID;
    cout << "\t\t\t\t\tEnter ID to search for passenger: ";
    cin >> searchID;

    ifstream infile("passengers.txt");
    if (!infile) {
        cout << "\t\t\t\t\tError opening file!" << endl;
        return;
    }

    ofstream outfile("temp.txt");
    if (!outfile) {
        cout << "\t\t\t\t\tError opening file!" << endl;
        infile.close();
        return;
    }

    Passenger passenger;
    bool found = false;

    while (infile >> passenger.firstName
                  >> passenger.lastName
                  >> passenger.ID
                  >> passenger.phoneNumber
                  >> passenger.seatNumber) {
        if (passenger.ID == searchID) {
            found = true;
            cout <<"\t\t\t\t\tEnter new first name: ";
            cin >> passenger.firstName;
            cout <<"\t\t\t\t\tEnter new last name: ";
            cin >> passenger.lastName;
            cout <<"\t\t\t\t\tEnter new phone number: ";
            cin >> passenger.phoneNumber;
            cout <<"\t\t\t\t\tEnter new seat number (1 to 100): ";
            string seatNumberStr;
            cin >> seatNumberStr;
            if (!hasOnlyDigits(seatNumberStr)) {
                cout << "\t\t\t\t\tError: Seat number should contain only numbers." << endl;
            } else {
                int seatNumber;
                stringstream ss(seatNumberStr);
                if (!(ss >> seatNumber) || seatNumber < 1 || seatNumber > 100) {
                    cout << "\t\t\t\t\tError: Invalid seat number! Seat number should be between 1 and 100." << endl;
                } else if (isSeatBooked(seatNumber)) {
                    cout << "\t\t\t\t\tError: Seat already booked! Please choose a different seat." << endl;
                } else {
                    passenger.seatNumber = seatNumber;
                }
            }
        }

        outfile << passenger.firstName << " "
                << passenger.lastName << " "
                << passenger.ID << " "
                << passenger.phoneNumber << " "
                << passenger.seatNumber << endl;
    }

    infile.close();
    outfile.close();

    // Remove the existing passengers.txt file
    if (remove("passengers.txt") != 0) {
        cout << "\t\t\t\t\tError deleting file!" << endl;
        return;
    }

    // Rename the temp.txt file to passengers.txt
    if (rename("temp.txt", "passengers.txt") != 0) {
        cout << "\t\t\t\t\tError renaming file!" << endl;
        return;
    }

    if (!found) {
        cout <<"\t\t\t\t\tPassenger not found!" << endl;
    } else {
        cout <<"\t\t\t\t\tReservation changed successfully!" << endl;
    }
}


void searchPassenger() {
    string searchID;
    cout <<"\t\t\t\t\tEnter ID to search for passenger: ";
    cin >> searchID;

    ifstream infile("passengers.txt");
    if (!infile) {
        cout <<"\t\t\t\t\tError opening file!" << endl;
        return;
    }

    Passenger passenger;
    bool found = false;

    while (infile >> passenger.firstName
                  >> passenger.lastName
                  >> passenger.ID
                  >> passenger.phoneNumber
                  >> passenger.seatNumber) {
        if (passenger.ID == searchID) {
            found = true;
            cout <<"\t\t\t\t\tPassenger found!" << endl;
            cout <<"\t\t\t\t\tFirst Name: " << passenger.firstName << endl;
            cout <<"\t\t\t\t\tLast Name: " << passenger.lastName << endl;
            cout <<"\t\t\t\t\tID: " << passenger.ID << endl;
            cout <<"\t\t\t\t\tPhone Number: " << passenger.phoneNumber << endl;
            cout <<"\t\t\t\t\tSeat Number: " << passenger.seatNumber << endl;
            break;
        }
    }

    infile.close();

    if (!found) {
        cout <<"\t\t\t\t\tPassenger not found!" << endl;
    }
}

void displayPassengers() {
    ifstream infile("passengers.txt");
    if (!infile) {
        cout <<"\t\t\t\t\tError opening file!" << endl;
        return;
    }

    Passenger passenger;
    int count = 0;

    while (infile >> passenger.firstName
                  >> passenger.lastName
                  >> passenger.ID
                  >> passenger.phoneNumber
                  >> passenger.seatNumber) {
        cout <<"\t\t\t\t\t-------------------------------" << endl;
        cout <<"\t\t\t\t\tPassenger " << ++count << ":" << endl;
        cout <<"\t\t\t\t\tFirst Name: " << passenger.firstName << endl;
        cout <<"\t\t\t\t\tLast Name: " << passenger.lastName << endl;
        cout <<"\t\t\t\t\tID: " << passenger.ID << endl;
        cout <<"\t\t\t\t\tPhone Number: " << passenger.phoneNumber << endl;
        cout <<"\t\t\t\t\tSeat Number: " << passenger.seatNumber << endl;
        cout <<"\t\t\t\t\t-------------------------------" << endl;
    }

    infile.close();

    if (count == 0) {
        cout <<"\t\t\t\t\tNo passengers found!" << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\t\t\t\t\t = = =KINGFISHER AIRLINES= = =  " << endl;
        cout << "\n\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t1. MAKE A RESERVATION" << endl;
        cout << "\n\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t2. CANCEL RESERVATION" << endl;
        cout << "\n\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t3. MODIFY RESERVATION" << endl;
        cout << "\n\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t4. SEARCH PASSENGERS" << endl;
        cout << "\n\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t5. DISPLAY PASSENGERS" << endl;
        cout << "\n\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\t6. QUIT" << endl;
        cout << "\n\t\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t\tENTER YOUR CHOICE : ";
        cin >> choice;

        switch (choice) {
            case 1:
                makeReservation();
                break;
            case 2:
                cancelReservation();
                break;
            case 3:
                changeReservation();
                break;
            case 4:
                searchPassenger();
                break;
            case 5:
                displayPassengers();
                break;
            case 6:
                return 0;
            default:
                cout << "\t\t\t\t\tINVALID CHOICE...! " << endl;
                break;
        }
    }

    return 0;
}

