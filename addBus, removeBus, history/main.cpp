#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

class Bus{ //node
public:
    Bus* next;
    string name;
    string route;
    string departure;
    string busType;
    string arrivalTime;
    string departureTime;
    int passengerSize;
    int fare;
};

class ParkingLot{
public:
    Bus* bus;
};

string getCurrentTime() { //to get the real time
    time_t currentTime;
    struct tm* localTime;
    char timeBuffer[80];
    time(&currentTime);
    localTime = localtime(&currentTime);
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localTime);
    return timeBuffer;
}

void addBusText(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get the current console color
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD currentColor = consoleInfo.wAttributes;

    // Set color to blue
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

    cout << "\t\t\t\t                    _      _    ____              \n"
            "\t\t\t\t         /\\        | |    | |  |  _ \\             \n"
            "\t\t\t\t        /  \\     __| |  __| |  | |_) | _   _  ___ \n"
            "\t\t\t\t       / /\\ \\   / _` | / _` |  |  _ < | | | |/ __|\n"
            "\t\t\t\t      / ____ \\ | (_| || (_| |  | |_) || |_| |\\__ \\\n"
            "\t\t\t\t     /_/    \\_\\ \\__,_| \\__,_|  |____/  \\__,_||___/\n\n";

    SetConsoleTextAttribute(hConsole, currentColor);
}

void addBus(Bus** head, int& totalBuses, ParkingLot* parkingLot){ //combination of add bus and insert node
    string name, route, departure, busType, busTypeChoice;
    int passengerSize, fare;
    cin.ignore(); // Clear the input buffer

    system("CLS");
    addBusText();

    if (totalBuses >= 8) { //if the maximum bus is reached
        cout << "\nMaximum number of buses reached. Cannot add more buses." << endl;
        Sleep(1000);
        return;
    }

    int parkingNum;
    bool validParkingNum = false;

    do{
        cout << "Enter the parking number (1-8): ";
        while(!(cin >> parkingNum)){ //error-handler
            cout << "\nInvalid Input!" << endl << endl;
            cout << "Please input again: ";
            cin.clear();
            while(cin.get() != '\n');
        }

        if(parkingNum >= 1 && parkingNum <= 8){
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

    newBus->arrivalTime = getCurrentTime();

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

void removeBusText(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get the current console color
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD currentColor = consoleInfo.wAttributes;

    // Set color to blue
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

    cout << "\t\t\t      _____                                          ____              \n"
            "\t\t\t     |  __ \\                                        |  _ \\             \n"
            "\t\t\t     | |__) |  ___  _ __ ___    ___  __   __  ___   | |_) | _   _  ___ \n"
            "\t\t\t     |  _  /  / _ \\| '_ ` _ \\  / _ \\ \\ \\ / /  / _ \\ |  _ < | | | |/ __|\n"
            "\t\t\t     | | \\ \\ |  __/| | | | | || (_) | \\ V / |   __/ | |_) || |_| |\\__ \\\n"
            "\t\t\t     |_|  \\_\\ \\___||_| |_| |_| \\___/   \\_/    \\___| |____/  \\__,_||___/\n\n";

    SetConsoleTextAttribute(hConsole, currentColor);
}

void removeBus(Bus** head, int& totalBuses, ParkingLot* parkingLot, Bus** historyList){
    int parkingNum;

    system("CLS");
    removeBusText();

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

            removedBus->departureTime = getCurrentTime();

            // Remove the bus from the head list
            Bus* current = *head;
            Bus* prev = nullptr;

            while (current != nullptr) {
                if (current == removedBus) {
                    if (prev == nullptr) {
                        *head = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    break;
                }
                prev = current;
                current = current->next;
            }

            // Add the removed bus to the history
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


void history(Bus* historyList){ //displays the most removed bus, from newest to oldest
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
            cout << "Expected Departure Time: " << curr->departure << endl;
            cout << "Fare: Php " << curr->fare << endl;
            cout << "Time of Arrival: " << curr->arrivalTime << endl;
            cout << "Time of Departure: " << curr->departureTime;

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

void displayAll(Bus* head, Bus* historyList) {
    system("CLS");
    cout << "Buses Information:" << endl;

    Bus* curr = head;
    int busNo = 1;
    bool busesDisplayed = false; // Flag to track if any non-removed buses were displayed

    while (curr != NULL) {
        bool busRemoved = false;
        Bus* historyCurr = historyList;

        while (historyCurr != NULL) {
            if (historyCurr == curr) {
                busRemoved = true;
                break;
            }
            historyCurr = historyCurr->next;
        }

        if (!busRemoved) {
            cout << "\nBus No." << busNo << ": " << curr->name;
            cout << "\nBus Type: " << curr->busType;
            cout << "\nRoute: " << curr->route;
            cout << "\nExpected Departure Time: " << curr->departure;
            cout << "\nFare: Php " << curr->fare;
            cout << "\nTime of Arrival: " << curr->arrivalTime << endl;

            busNo++;
            busesDisplayed = true;
        }
        curr = curr->next;
    }

    if (!busesDisplayed) {
        cout << "\nThere are no buses to display." << endl;
    }

    cout << "\nPress any key to go back: ";
    cin.ignore();
    cin.get();
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
        cout << "\n[3] Edit Bus Information"; //optional
        cout << "\n[4] Display All Buses Information"; //simulation for display all
        cout << "\n[5] History";
        cout << "\n[6] Exit";
        cout << "\nYour Choice: ";
        cin >> choice;

        if(choice == "1"){
            addBus(&head, totalBuses, parkingLot);
        }
        else if(choice == "2"){
            removeBus(&head, totalBuses, parkingLot, &historyList);
        }
        else if(choice == "3"){
            //edit bus
        }
        else if(choice == "4"){
            displayAll(head, historyList);
        }
        else if(choice == "5"){
            history(historyList);
        }
        else if(choice == "6"){
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
