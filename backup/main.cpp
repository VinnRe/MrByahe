#include <iostream>
#include <windows.h>
#define MAX_SIZE 32

using namespace std;

class Bus{ //node
public:
    Bus* next;
    string name;
    string route;
    string departure;
    string busType;
    int passengerOnBoard;
    int fare;
};

class ParkingLot{
public:
    Bus* bus;
};

void addBus(Bus** head, int& totalBuses, ParkingLot* parkingLot){ //combination of add bus and insert node
    string name, route, departure, busType, busTypeChoice;
    int fare;
    cin.ignore(); // Clear the input buffer

    system("CLS");
    cout << "---ADD BUS---" << endl;

    if (totalBuses >= 8) { //if the maximum bus is reached
        cout << "\nMaximum number of buses reached. Cannot add more buses." << endl;
        Sleep(1000);
        return;
    }

    int parkingNum;
    bool validParkingNum = false;

    do{
        cout << "Enter the parking number (1-8): ";
        if(cin >> parkingNum && parkingNum >= 1 && parkingNum <= 8){
            if(parkingLot[parkingNum - 1].bus == NULL){
                validParkingNum = true;
            }
            else{
                cout << "\nParking Slot " << parkingNum << " is already occupied!" << endl;
                Sleep(1000);
                return;
            }
        }
        else{
            cout << "\nInvalid Parking Number! Please Try Again!" << endl << endl;
            cin.clear();
            cin.ignore();
        }
    } while(!validParkingNum);

    cin.ignore();

    Bus* newBus = new Bus();

    cout << "\nPlease provide the information to the following:";
    cout << "\nBus Name: ";
    getline(cin, newBus->name);

    bool choice = false;
    do{
        cout << "Bus Type [1] Regular [2] Air-conditioned: ";
        cin >> busTypeChoice;

        if(busTypeChoice == "1"){
            choice = true;
            newBus->busType = "Regular";
        } else if(busTypeChoice == "2"){
            choice = true;
            newBus->busType = "Air-conditioned";
        } else{
            cout << "--------------------------------";
            cout << "\nInvalid Input! Please Try Again!" << endl;
            cin.clear();
            cin.ignore();
        }
    } while(!choice);
    cin.ignore();

    cout << "Route: ";
    getline(cin, newBus->route);

    cout << "Time of Departure: ";
    getline(cin, newBus->departure);

    bool validFare = false; //error-handler if user input in fare is not int
    do{
        cout << "Fare: ";
        if(cin >> fare){
            validFare = true;
            newBus->fare = fare;
        } else{
            cout << "--------------------------------";
            cout << "\nInvalid Input! Please Try Again!" << endl;
            cin.clear();
            cin.ignore();
        }
    } while(!validFare);

    newBus->next = NULL;

    if (*head == nullptr) {
        *head = newBus;
    } else {
        Bus* current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newBus;
    }

    parkingLot[parkingNum - 1].bus = newBus;
    cout << "\nBus was successfully added to Parking Slot " << parkingNum << "!";

    totalBuses++;
    cin.ignore();
    cout << endl;
    Sleep(1000); //for time delay
}

void removeBus(Bus** head, int& totalBuses, ParkingLot* parkingLot, Bus** historyList){
    int parkingNum;

    system("CLS");
    cout << "---REMOVE BUS---" << endl;
    cout << "Enter the parking slot number (1-8) to remove the bus: ";
    while(!(cin >> parkingNum)){ //error-handler
        cout << "\nInvalid Input!" << endl << endl;
        cout << "Please input again: ";
        cin.clear();
        while(cin.get() != '\n');
    }

    if (parkingNum >= 1 && parkingNum <= 8) {
        if (parkingLot[parkingNum - 1].bus != NULL) {
            Bus* removedBus = parkingLot[parkingNum - 1].bus;
            parkingLot[parkingNum - 1].bus = NULL;

            //Add the remove bus to the history
            removedBus->next = *historyList;
            *historyList = removedBus;

            cout << "\nBus has been successfully departed!" << endl;
            totalBuses--;
        }
        else {
            cout << "\nThere is no bus in parking slot " << parkingNum << "." << endl;
        }
    }
    else {
        cout << "\nInvalid parking slot number!" << endl << endl;
    }

    cout << "\nPress any key to go back: ";
    cin.ignore();
    cin.get();
}

void displayBus(const Bus* bus) { //will be used in the edit bus
    cout << "\nBus Name: " << bus->name;
    cout << "\nBus Type: " << bus->busType;
    cout << "\nRoute: " << bus->route;
    cout << "\nDeparture Time: " << bus->departure;
    cout << "\nPassengers on Board: " << bus->passengerOnBoard;
    cout << "\nFare: Php " << bus->fare << endl;
}

void editBus( Bus* head, ParkingLot* parkingLot, int numParkingSlots, int totalBuses){ //allows the user to edit
    string busTypeChoice;
    Bus* curr = head;
    int busNo = 1;
    int maxPassengers;
    int temp = 0;

    system("CLS");

    if(head == NULL){ //display if the list is empty
        cout << "There is no bus to edit." << endl;
        Sleep(1000);
        return;
    }

    while(curr != NULL){ //display until the last node
        displayBus(curr);
        curr = curr->next;
        busNo++;
    }

    int parkingNum;
    cout << "\nEnter the parking slot number you want to edit (1-8): ";
    while(!(cin >> parkingNum)){ //error-handler
        cout << "\nInvalid Input!" << endl << endl;
        cout << "Please input again: ";
        cin.clear();
        while(cin.get() != '\n');
    }

    if(parkingNum >= 1 && parkingNum <= numParkingSlots){
        Bus* busToEdit = parkingLot[parkingNum - 1].bus; //find the bus
        if(busToEdit != NULL){
            cout << "\nSelect the detail you want to edit:";
            cout << "\n[1] Route";
            cout << "\n[2] Bus Type";
            cout << "\n[3] Departure Time";
            cout << "\n[4] Fare";
            cout << "\n[5] Add Passengers";
            cout << "\n[6] Remove Passengers";
            cout << "\nYour Choice: ";

            int choice;
            cin >> choice;

            cin.ignore(); // Clear the input buffer
            bool ch = false;
            switch (choice) {
                case 1:
                    cout << "\nEnter new route: ";
                    getline(cin, busToEdit->route);
                    cout << "Route updated successfully!" << endl;
                    break;
                case 2:
                    
                    do{
                        cout << "Bus Type [1] Regular [2] Air-conditioned: ";
                        cin >> busTypeChoice;

                        if(busTypeChoice == "1"){
                            ch = true;
                            busToEdit->busType = "Regular";
                        } else if(busTypeChoice == "2"){
                            ch = true;
                            busToEdit->busType = "Air-conditioned";
                        } else{
                            cout << "--------------------------------";
                            cout << "\nInvalid Input! Please Try Again!" << endl;
                            cin.clear();
                            cin.ignore();
                        }
                    } while(!choice);
                    cout << "Bus type updated successfully!" << endl;
                    break;
                case 3:
                    cout << "\nEnter new Departure Time: ";
                    cin >> busToEdit->departure;
                    cout << "\nDeparture Time updated successfully!" << endl;
                    break;
                case 4:
                    cout << "\nEnter new fare: ";
                    cin >> busToEdit->fare;
                    cout << "\nFare updated successfully!" << endl;
                    break;
                case 5:
                    cout << "Add how many passengers on board: ";
                    cin >> temp;
                    busToEdit->passengerOnBoard += temp;
                    cout << "Added " << temp << " passengers on board";
                    cout << "Current passengers on board: " << busToEdit->passengerOnBoard;
                    temp = 0;
                    break;
                case 6: 
                    cout << "Remove how many passengers on board: ";
                    cin >> temp;
                    busToEdit->passengerOnBoard -= temp;
                    cout << "Removed " << temp << " passengers on board" << endl;
                    cout << "Current passengers on board: " << busToEdit->passengerOnBoard;
                    temp = 0;
                    break;
                default:
                    cout << "\nInvalid choice!" << endl;
                    break;
            }
        }
        else{
            cout << "\nThere is no bus in parking slot " << parkingNum << "." << endl;
        }
    }
    else{
        cout << "\nInvalid parking slot number!" << endl << endl;
    }

    cout << "\nPress any key to go back: ";
    cin.ignore();
    cin.get();
}

void history(Bus* historyList){
    system("CLS");
    cout << "Bus Departure History:" << endl;

    Bus* curr = historyList;
    int busNo = 1;

    if(curr == NULL){
        cout << "\nNo Bus Departure History available." << endl;
    }
    else {
        while (curr != NULL) {
            cout << "\n------------------------" << endl;
            cout << "Bus No." << busNo << ": " << curr->name << endl;
            cout << "Route: " << curr->route << endl;
            cout << "Departure Time: " << curr->departure << endl;
            cout << "Fare: Php " << curr->fare;

            curr = curr->next;
            busNo++;
        }
    }

    cout << "\n------------------------" << endl;
    cout << "\nPress any key to go back: ";
    cin.ignore();
    cin.get();
}

void displayParkingLot(ParkingLot* parkingLot, int numParkingSlots){ //sample display
    system("CLS");
    cout << "Terminal Map:\n"; //for simulation only
    for (int i = 0; i < numParkingSlots; i++) {
        cout << "\nParking Slot " << i + 1 << ": ";
        if (parkingLot[i].bus != NULL) {
            cout << "Bus Name: " << parkingLot[i].bus->name << " | Route: " << parkingLot[i].bus->route << endl;
        }
        else {
            cout << " " << endl;
        }
    }
}

void specificBus(ParkingLot* parkingLot, int numParkingSlots){ //display the specified bus
    system("CLS");
    cout << "Enter the parking slot number (1-8): ";
    int parkingNum;
    cin >> parkingNum;

    if (parkingNum >= 1 && parkingNum <= numParkingSlots) {
        if (parkingLot[parkingNum - 1].bus != NULL) {
            cout << "\nBus Name: " << parkingLot[parkingNum - 1].bus->name;
            cout << "\nRoute: " << parkingLot[parkingNum - 1].bus->route ;
            cout << "\nBus Type: " << parkingLot[parkingNum - 1].bus->busType;
            cout << "\nDeparture Time: " << parkingLot[parkingNum - 1].bus->departure;
            cout << "\nFare: Php " << parkingLot[parkingNum - 1].bus->fare << endl;
            cout << "\nPassengers on Board: " << parkingLot[parkingNum - 1].bus->passengerOnBoard;
        } else {
            cout << "\nThere is no bus in parking slot " << parkingNum << "." << endl;
        }
    } else {
        cout << "\nInvalid parking slot number!" << endl;
    }

    cout << "\nPress any key to go back: ";
    cin.ignore();
    cin.get();
}

void displayAll(Bus* head, int numBus){
    Bus* curr = head;
    int busNo = 1;

    system("CLS");

    if(head == NULL){ //display if the list is empty
        cout << "There is no bus to display." << endl;
        Sleep(1000);
        return;
    }

    while(curr != NULL){ //display until the last node
        cout << "\nBus No." << busNo << ": " << curr->name;
        cout << "\nBus Type: " << curr->busType;
        cout << "\nRoute: " << curr->route;
        cout << "\nDeparture Time: " << curr->departure;
        cout << "\nFare: Php " << curr->fare << endl;
        cout << "\nPassengers on Board: " << curr->passengerOnBoard;
        curr = curr->next;
        busNo++;
    }

    cout << "\nPress any key to go back: ";
    cin.ignore();
    cin.get();
}

void mainDisplay(){
    cout << "";
}

void freeMemory(Bus* head, Bus* historyList) { //to prevent memory leaks
    while (head != nullptr) {
        Bus* temp = head;
        head = head->next;
        delete temp;
    }

    while (historyList != nullptr) {
        Bus* temp = historyList;
        historyList = historyList->next;
        delete temp;
    }
}

int main()
{
    const int numParkingSlots = 8; //number of parking slots
    Bus* head = NULL; //linked list for add bus
    int totalBuses = 0;
    string choice;
    ParkingLot parkingLot[numParkingSlots]; //array of parking slots
    Bus* historyList = NULL; //linked list for history

    for (int i = 0; i < numParkingSlots; i++) {
        parkingLot[i].bus = NULL; // Initialize all parking slots to NULL
    }

    bool isMain = true;
    while(isMain){
        system("CLS");

        displayParkingLot(parkingLot, numParkingSlots); //simulation for specific display

        //choices for simulation only
        cout << "\n[1] Add Bus";
        cout << "\n[2] Remove Bus";
        cout << "\n[3] Display Specific Bus Information"; //optional
        cout << "\n[4] Display All Buses Information"; //simulation for display all
        cout << "\n[5] Edit Bus Information";
        cout << "\n[6] History";
        cout << "\n[7] Exit";
        cout << "\nYour Choice: ";
        cin >> choice;

        if(choice == "1"){
            addBus(&head, totalBuses, parkingLot);
        }
        else if(choice == "2"){
            removeBus(&head, totalBuses, parkingLot, &historyList);
        }
        else if(choice == "3"){
            specificBus(parkingLot, numParkingSlots);
        }
        else if(choice == "4"){
            displayAll(head, totalBuses);
        }
        else if (choice == "5"){
            editBus(head, parkingLot, numParkingSlots, totalBuses);
        }
        else if(choice == "6"){
            history(historyList);
        }
        else if(choice == "7"){
            isMain = false;
        }
        else{
            cout << "\nInvalid Input! Please Try Again!";
            Sleep(1000);
        }
    }

    freeMemory(head, historyList); //to free memory and avoid memory leaks

    return 0;
}
