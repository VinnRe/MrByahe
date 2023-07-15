#define MAX_SIZE 32
#include <iostream>
#include <windows.h>
#include <ctime>
#include <chrono> // To get the execution time and it is more modern and robust time measurement functionality
#include <iomanip>
//#include <thread>

using namespace std;

const string ANSI_RESET = "\u001b[0m";
const string ANSI_RED = "\u001b[31m";
const string ANSI_ORANGE = "\u001b[33m";
const string ANSI_GREEN = "\u001b[32m";

class Bus { //node
public:
    Bus* next;
    string name;
    string route;
    string departure;
    string busType;
    string arrivalTime;
    string departureTime;
    int passengerOnBoard;
    int fare;
};

class ParkingLot {
public:
    Bus* bus;
};

class mainTerminal {
public:
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
                "\t\t\t\t     /_/    \\_\\ \\__,_| \\__,_|  |____/  \\__,_||___/\n";


        SetConsoleTextAttribute(hConsole, currentColor);
        cout << "\n\t\t\t  ====================================================================\n";
    }

    void addBus(Bus** head, int& totalBuses, ParkingLot* parkingLot){ //combination of add bus and insert node
        string name, route, departure, busType, busTypeChoice;
        int passengerSize, fare;
        auto startTime = chrono::steady_clock::now();
        cin.ignore(); // Clear the input buffer
        system("CLS");
        addBusText();


        if (totalBuses >= 8) { //if the maximum bus is reached
            cout << "\n\t\t\t  Maximum number of buses reached. Cannot add more buses." << endl;
            Sleep(1000);
            return;
        }

        int parkingNum;
        bool validParkingNum = false;

        do{
            cout << "\t\t\t  Enter the parking number (1-8): ";
            while(!(cin >> parkingNum)){ //error-handler
                cout << "\n\t\t\t  Invalid Input!" << endl << endl;
                cout << "\t\t\t  Please input again: ";
                cin.clear();
                while(cin.get() != '\n');
            }

            if(parkingNum >= 1 && parkingNum <= 8){
                if(parkingLot[parkingNum - 1].bus == NULL){
                    validParkingNum = true;
                }
                else{
                    cout << "\n\t\t\t  Parking Slot " << parkingNum << " is already occupied!" << endl;
                    Sleep(1000);
                    return;
                }
            }
            else{
                cout << "\n\t\t\t  Invalid Parking Number! Please Try Again!" << endl << endl;
                cin.clear();
                cin.ignore();
            }
        } while(!validParkingNum);

        cin.ignore();

        Bus* newBus = new Bus();

        cout << "\n\t\t\t  Please provide the information to the following:";
        cout << "\n\t\t\t  Bus Name: ";
        getline(cin, newBus->name);

        bool choice = false;
        do{
            cout << "\t\t\t  Bus Type [1] Regular [2] Air-conditioned: ";
            cin >> busTypeChoice;

            if(busTypeChoice == "1"){
                choice = true;
                newBus->busType = "Regular";
            } else if(busTypeChoice == "2"){
                choice = true;
                newBus->busType = "Air-conditioned";
            } else{
                cout << "\t\t\t  --------------------------------";
                cout << "\n\t\t\t  Invalid Input! Please Try Again!" << endl;
                cin.clear();
                cin.ignore();
            }
        } while(!choice);
        cin.ignore();

        cout << "\t\t\t  Route: ";
        getline(cin, newBus->route);

        cout << "\t\t\t  Time of Departure: ";
        getline(cin, newBus->departure);

        newBus->arrivalTime = getCurrentTime();

        bool validFare = false; //error-handler if user input in fare is not int
        do{
            cout << "\t\t\t  Fare: ";
            if(cin >> fare){
                validFare = true;
                newBus->fare = fare;
            } else{
                cout << "\t\t\t  --------------------------------";
                cout << "\n\t\t\t  Invalid Input! Please Try Again!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        cout << "\n\t\t\t  Bus was successfully added to Parking Slot " << parkingNum << "!" << endl;
        auto endTime = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "\n\t\t\t  Execution Time: " << duration.count() << " ms" << endl;
        totalBuses++;
        cout << "\t\t\t  Press any key to go back: ";
        cin.ignore();
        cin.get();
    }

    void removeBusText(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Get the current console color
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        WORD currentColor = consoleInfo.wAttributes;

        // Set color to blue
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

        cout << "\t\t           _____                                          ____              \n"
                "\t\t          |  __ \\                                        |  _ \\             \n"
                "\t\t          | |__) |  ___  _ __ ___    ___  __   __  ___   | |_) | _   _  ___ \n"
                "\t\t          |  _  /  / _ \\| '_ ` _ \\  / _ \\ \\ \\ / /  / _ \\ |  _ < | | | |/ __|\n"
                "\t\t          | | \\ \\ |  __/| | | | | || (_) | \\ V / |   __/ | |_) || |_| |\\__ \\\n"
                "\t\t          |_|  \\_\\ \\___||_| |_| |_| \\___/   \\_/    \\___| |____/  \\__,_||___/\n";

        SetConsoleTextAttribute(hConsole, currentColor);
        cout << "\n\t\t\t ====================================================================\n";
    }

    void removeBus(Bus** head, int& totalBuses, ParkingLot* parkingLot, Bus** historyList){
        int parkingNum;

        auto startTime = chrono::steady_clock::now();
        system("CLS");
        removeBusText();

        cout << "\t\t\t Enter the parking slot number (1-8) to remove the bus: ";
        while(!(cin >> parkingNum)){ //error-handler
            cout << "\n\t\t\t Invalid Input!" << endl << endl;
            cout << "\t\t\t Please input again: ";
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

                cout << "\n\t\t\t Bus has been successfully departed!" << endl;
                totalBuses--;
            }
            else {
                cout << "\n\t\t\t There is no bus in parking slot " << parkingNum << "." << endl;
            }
        }
        else {
            cout << "\n\t\t\t Invalid parking slot number!" << endl << endl;
        }

        auto endTime = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "\n\t\t\t Execution Time: " << duration.count() << " ms" << endl;
        cout << "\t\t\t Press any key to go back: ";
        cin.ignore();
        cin.get();
    }

    void departBusDisplay() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Get the current console color
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        WORD currentColor = consoleInfo.wAttributes;

        // Set color to blue
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        cout << "\t\t\t\t    _____                             _     ____              " << endl;
        cout << "\t\t\t\t   |  __ \\                           | |   |  _ \\             " << endl;
        cout << "\t\t\t\t   | |  | |  ___  _ __    __ _  _ __ | |_  | |_) | _   _  ___ " << endl;
        cout << "\t\t\t\t   | |  | | / _ \\| '_ \\  / _` || '__|| __| |  _ < | | | |/ __|" << endl;
        cout << "\t\t\t\t   | |__| ||  __/| |_) || (_| || |   | |_  | |_) || |_| |\\__ \\" << endl;
        cout << "\t\t\t\t   |_____/  \\___|| .__/  \\__,_||_|    \\__| |____/  \\__,_||___/" << endl;
        cout << "\t\t\t\t                 | |                                          " << endl;
        cout << "\t\t\t\t                 |_|                                          " << endl;
        SetConsoleTextAttribute(hConsole, currentColor);

        cout << "\n\t\t\t  ====================================================================\n";
    }

    void mainTerminal::departBus(int parkingNum) {
        auto startTime = std::chrono::steady_clock::now();
        system("CLS");
        departBusDisplay();

        // CODE

        auto endTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        cout << "\t\t\tExecution Time: " << duration.count() << " ms" << endl;
        cout << "\n\t\t\tPress any key to go back: ";
        cin.ignore();
        cin.get();
    }

    void displayBus(const Bus* bus, const ParkingLot* parkingLot, int numParkingSlots) { //will be used in the edit bus
        int parkingNum = 0;

        for(int i = 0; i < numParkingSlots; i++){
            if(parkingLot[i].bus == bus){
                parkingNum = i + 1;
                break;
            }
        }

        cout << "\t\t\t  Currently at Parking Slot No: " << parkingNum;
        cout << "\n\t\t\t  Bus Type: " << bus->busType;
        cout << "\n\t\t\t  Route: " << bus->route;
        cout << "\n\t\t\t  Departure Time: " << bus->departure;
        cout << "\n\t\t\t  Passengers on Board: " << bus->passengerOnBoard;
        cout << "\n\t\t\t  Fare: Php " << bus->fare;
        cout << "\n\t\t\t  ====================================================================\n";
    }

    void editBusText() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Get the current console color
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        WORD currentColor = consoleInfo.wAttributes;

        // Set color to blue
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        cout << "\t\t\t\t        ______      _  _  _     ____              \n"
                "\t\t\t\t       |  ____|    | |(_)| |   |  _ \\             \n"
                "\t\t\t\t       | |__     __| | _ | |_  | |_) | _   _  ___ \n"
                "\t\t\t\t       |  __|   / _` || || __| |  _ < | | | |/ __|\n"
                "\t\t\t\t       | |____ | (_| || || |_  | |_) || |_| |\\__ \\\n"
                "\t\t\t\t       |______| \\__,_||_| \\__| |____/  \\__,_||___/\n";

        SetConsoleTextAttribute(hConsole, currentColor);
        cout << "\n\t\t\t  ====================================================================\n";
    }

    void editBus(Bus* head, ParkingLot* parkingLot, int numParkingSlots, int totalBuses) { //allows the user to edit
        string busTypeChoice;
        Bus* curr = head;
        int busNo = 1;
        int maxPassengers;
        int temp = 0;

        auto startTime = chrono::steady_clock::now();
        system("CLS");
        editBusText();

        if (head == NULL) { //display if the list is empty
            cout << "\t\t\t  There is no bus to edit." << endl;
            Sleep(1000);
            return;
        }

        while (curr != NULL) { //display until the last node
            displayBus(curr, parkingLot, numParkingSlots);
            curr = curr->next;
            busNo++;
        }

        int parkingNum;
        cout << "\t\t\t  Enter the parking slot number you want to edit (1-8): ";
        while (!(cin >> parkingNum)) { //error-handler
            cout << "\n\t\t\t  Invalid Input!" << endl << endl;
            cout << "\t\t\t  Please input again: ";
            cin.clear();
            while (cin.get() != '\n');
        }

        if (parkingNum >= 1 && parkingNum <= numParkingSlots) {
            Bus* busToEdit = parkingLot[parkingNum - 1].bus; //find the bus
            if (busToEdit != NULL) {
                bool isEdit = true;
                while(isEdit){

                    cout << "\n\t\t\t  Select the detail you want to edit:";
                    cout << "\n\t\t\t  [1] Route";
                    cout << "\n\t\t\t  [2] Bus Type";
                    cout << "\n\t\t\t  [3] Departure Time";
                    cout << "\n\t\t\t  [4] Fare";
                    cout << "\n\t\t\t  [5] Add Passengers";
                    cout << "\n\t\t\t  [6] Remove Passengers";
                    cout << "\n\t\t\t  [7] Go Back";
                    cout << "\n\n\t\t\t  Your Choice: ";

                    string choice;
                    cin >> choice;

                    cin.ignore(); // Clear the input buffer

                    if(choice == "1") {
                        cout << "\n\t\t\t  Enter new route: ";
                        getline(cin, busToEdit->route);
                        cout << "\n\t\t\t  Route updated successfully!" << endl;
                        break;
                    }
                    else if(choice == "2"){
                        bool btypeChoice = false;
                        do {
                            cout << "\n\t\t\t  Bus Type [1] Regular [2] Air-conditioned: ";
                            cin >> busTypeChoice;

                            if (busTypeChoice == "1") {
                                busToEdit->busType = "Regular";
                                cout << "\n\t\t\t  Bus type updated successfully!" << endl;
                                btypeChoice = true;
                                isEdit = false;
                            }
                            else if (busTypeChoice == "2") {
                                busToEdit->busType = "Air-conditioned";
                                cout << "\n\t\t\t  Bus type updated successfully!" << endl;
                                btypeChoice = true;
                                isEdit = false;
                            }
                            else {
                                cout << "\n\t\t\t  Invalid Input! Please Try Again!" << endl;
                                cin.clear();
                                cin.ignore();
                            }
                        } while (!btypeChoice);
                    }
                    else if(choice == "3"){
                        cout << "\n\t\t\t  Enter new Departure Time: ";
                        getline(cin, busToEdit->departure);
                        cout << "\n\t\t\t  Departure Time updated successfully!" << endl;
                        break;
                    }
                    else if(choice == "4"){
                        cout << "\n\t\t\t  Enter new fare: ";
                        cin >> busToEdit->fare;
                        cout << "\n\t\t\t  Fare updated successfully!" << endl;
                        break;
                    }
                    else if(choice == "5"){
                        cout << "\n\t\t\t  Add how many passengers on board: ";
                        while(!(cin >> temp)){ //error-handler
                            cout << "\n\t\t\t  Invalid Input!" << endl << endl;
                            cout << "\t\t\t  Please input again: ";
                            cin.clear();
                            while(cin.get() != '\n');
                        }

                        if (temp > 0 && (busToEdit->passengerOnBoard + temp) <= MAX_SIZE) {
                            busToEdit->passengerOnBoard += temp;
                            cout << "\n\t\t\t  Added " << temp << " passengers on board" << endl;
                            cout << "\n\t\t\t  Current passengers on board: " << busToEdit->passengerOnBoard << endl;
                            temp = 0;
                        }
                        else if ((busToEdit->passengerOnBoard + temp) > MAX_SIZE) {
                            cout << "\n\t\t\t  Cannot add passengers because the bus has reached its maximum capacity." << endl;
                        }
                        else {
                            cout << "\t\t\t  Invalid input!" << endl;
                        }
                        break;
                    }
                    else if(choice == "6"){
                        cout << "\n\t\t\t  Remove how many passengers on board: ";
                        while(!(cin >> temp)){ //error-handler
                            cout << "\n\t\t\t  Invalid Input!" << endl << endl;
                            cout << "\t\t\t  Please input again: ";
                            cin.clear();
                            while(cin.get() != '\n');
                        }
                        if ((busToEdit->passengerOnBoard - temp) > 0) {
                            busToEdit->passengerOnBoard -= temp;
                            cout << "\n\t\t\t  Removed " << temp << " passengers on board" << endl;
                            cout << "\n\t\t\t  Current passengers on board: " << busToEdit->passengerOnBoard << endl;
                            temp = 0;
                        }
                        else if ((busToEdit->passengerOnBoard - temp) < 0) {
                            cout << "\n\t\t\t  Cannot remove passengers below the amount of passengers on board." << endl;
                        }
                        else {
                            cout << "\n\t\t\t  Cannot remove passengers in an empty bus." << endl;
                        }
                        break;
                    }
                    else if(choice == "7"){
                        break;
                    }
                    else{
                        cout << "\n\t\t\t  Invalid Input! Please Try Again!" << endl;
                    }
                }
            }
            else {
                cout << "\n\t\t\t  There is no bus in parking slot " << parkingNum << "." << endl;
            }
        }
        else {
            cout << "\n\t\t\t  Invalid parking slot number!" << endl << endl;
        }

        auto endTime = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "\n\t\t\t  Execution Time: " << duration.count() << " ms" << endl;
        cout << "\n\t\t\t  Press any key to go back: ";
        cin.ignore();
        cin.get();
    }

    void historyText() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Get the current console color
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        WORD currentColor = consoleInfo.wAttributes;

        // Set color to blue
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout << "\t\t\t\t ____                _    _  _       _                       \n"
                "\t\t\t\t|  _ \\              | |  | |(_)     | |                      \n"
                "\t\t\t\t| |_) | _   _  ___  | |__| | _  ___ | |_   ___   _ __  _   _ \n"
                "\t\t\t\t|  _ < | | | |/ __| |  __  || |/ __|| __| / _ \\ | '__|| | | |\n"
                "\t\t\t\t| |_) || |_| |\\__ \\ | |  | || |\\__ \\| |_ | (_) || |   | |_| |\n"
                "\t\t\t\t|____/  \\__,_||___/ |_|  |_||_||___/ \\__| \\___/ |_|    \\__, |\n"
                "\t\t\t\t                                                        __/ |\n"
                "\t\t\t\t                                                       |___/  \n";
        SetConsoleTextAttribute(hConsole, currentColor);

        cout << "\t\t\t    ===================================================================" << endl;
    }

    void history(Bus* historyList){ //displays the most removed bus, from newest to oldest
        auto startTime = chrono::steady_clock::now();

        system("CLS");
        historyText();

        Bus* curr = historyList;
        int busNo = 1;

        if(curr == NULL){
            cout << "\t\t\t    No Bus Departure History available." << endl;
        }
        else {
            while (curr != NULL) {
                cout << "\t\t\t    Bus No." << busNo << ": " << curr->name << endl;
                cout << "\t\t\t    Route: " << curr->route << endl;
                cout << "\t\t\t    Expected Departure Time: " << curr->departure << endl;
                cout << "\t\t\t    Fare: Php " << curr->fare << endl;
                cout << "\t\t\t    Time of Arrival: " << curr->arrivalTime << endl;
                cout << "\t\t\t    Time of Departure: " << curr->departureTime << endl;
                cout << "\t\t\t    ===================================================================" << endl;

                curr = curr->next;
                busNo++;
            }
        }

        auto endTime = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "\t\t\t    Execution Time: " << duration.count() << " ms" << endl;
        cout << "\n\t\t\t    Press any key to go back: ";
        cin.ignore();
        cin.get();
    }

    void specificBusText(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Get the current console color
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        WORD currentColor = consoleInfo.wAttributes;

        // Set color to blue
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout << "\t         _____                     _   __  _         ____                _____          __        " << endl;
        cout << "\t        / ____|                   (_) / _|(_)       |  _ \\              |_   _|        / _|       " << endl;
        cout << "\t       | (___   _ __    ___   ___  _ | |_  _   ___  | |_) | _   _  ___    | |   _ __  | |_   ___  " << endl;
        cout << "\t        \\___ \\ | '_ \\  / _ \\ / __|| ||  _|| | / __| |  _ < | | | |/ __|   | |  | '_ \\ |  _| / _ \\ " << endl;
        cout << "\t        ____) || |_) ||  __/| (__ | || |  | || (__  | |_) || |_| |\\__ \\  _| |_ | | | || |  | (_) |" << endl;
        cout << "\t       |_____/ | .__/  \\___| \\___||_||_|  |_| \\___| |____/  \\__,_||___/ |_____||_| |_||_|   \\___/ " << endl;
        cout << "\t               | |                                                                                " << endl;
        cout << "\t               |_|                                                                                " << endl;

        SetConsoleTextAttribute(hConsole, currentColor);
        cout << "\t  ===================================================================================================" << endl;
    }

    void specificBus(ParkingLot* parkingLot, int numParkingSlots) { //display the specified bus
        auto startTime = chrono::steady_clock::now();
        system("CLS");
        specificBusText();

        int parkingNum;
        cout << "\t  Enter the parking slot number (1-8) to display the bus: ";
        while(!(cin >> parkingNum)){ //error-handler
            cout << "\n\t  Invalid Input!" << endl << endl;
            cout << "\t  Please input again: ";
            cin.clear();
            while(cin.get() != '\n');
        }

        if (parkingNum >= 1 && parkingNum <= numParkingSlots) {
            if (parkingLot[parkingNum - 1].bus != NULL) {
                cout << "\n\t  Bus Name: " << parkingLot[parkingNum - 1].bus->name;
                cout << "\n\t  Route: " << parkingLot[parkingNum - 1].bus->route;
                cout << "\n\t  Bus Type: " << parkingLot[parkingNum - 1].bus->busType;
                cout << "\n\t  Departure Time: " << parkingLot[parkingNum - 1].bus->departure;
                cout << "\n\t  Fare: Php " << parkingLot[parkingNum - 1].bus->fare;
                cout << "\n\t  Passengers on Board: " << parkingLot[parkingNum - 1].bus->passengerOnBoard;
                cout << "\n\t  Time of Arrival: " << parkingLot[parkingNum - 1].bus->arrivalTime << endl;
            }
            else {
                cout << "\n\t  There is no bus in parking slot " << parkingNum << "." << endl;
            }
        }
        else {
            cout << "\n\t  Invalid parking slot number!" << endl;
        }

        auto endTime = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "\t  Execution Time: " << duration.count() << " ms" << endl;
        cout << "\n\t  Press any key to go back: ";
        cin.ignore();
        cin.get();
    }

    void displayAllText() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Get the current console color
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        WORD currentColor = consoleInfo.wAttributes;

        // Set color to blue
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout << "\t\t\t               _  _   ____                _____          __        " << endl;
        cout << "\t\t\t        /\\    | || | |  _ \\              |_   _|        / _|       " << endl;
        cout << "\t\t\t       /  \\   | || | | |_) | _   _  ___    | |   _ __  | |_   ___  " << endl;
        cout << "\t\t\t      / /\\ \\  | || | |  _ < | | | |/ __|   | |  | '_ \\ |  _| / _ \\ " << endl;
        cout << "\t\t\t     / ____ \\ | || | | |_) || |_| |\\__ \\  _| |_ | | | || |  | (_) |" << endl;
        cout << "\t\t\t    /_/    \\_\\|_||_| |____/  \\__,_||___/ |_____||_| |_||_|   \\___/ " << endl;

        SetConsoleTextAttribute(hConsole, currentColor);
        cout << "\t\t\t =====================================================================" << endl;
    }

    void displayAll(Bus* head, Bus* historyList) {
        auto startTime = chrono::steady_clock::now();

        system("CLS");
        displayAllText();


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
                cout << "\t\t\t Bus No." << busNo << ": " << curr->name;
                cout << "\n\t\t\t Bus Type: " << curr->busType;
                cout << "\n\t\t\t Route: " << curr->route;
                cout << "\n\t\t\t Expected Departure Time: " << curr->departure;
                cout << "\n\t\t\t Fare: Php " << curr->fare;
                cout << "\n\t\t\t Time of Arrival: " << curr->arrivalTime;
                cout << "\n\t\t\t Passengers on Board: " << curr->passengerOnBoard;
                cout << "\n\t\t\t =====================================================================" << endl;

                busNo++;
                busesDisplayed = true;
            }
            curr = curr->next;
        }

        if (!busesDisplayed) {
            cout << "\t\t\t There are no buses to display." << endl;
        }

        auto endTime = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "\n\t\t\t Execution Time: " << duration.count() << " ms" << endl;
        cout << "\t\t\t Press any key to go back: ";
        cin.ignore();
        cin.get();
    }

    void mergeSort(Bus** headRef) {
        Bus* head = *headRef;

        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Bus* left;
        Bus* right;
        split(head, &left, &right);

        mergeSort(&left);
        mergeSort(&right);

        *headRef = merge(left, right);
    }

    void displaySortedBusesText() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Get the current console color
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        WORD currentColor = consoleInfo.wAttributes;

        // Set color to blue
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout << "\t\t\t\t      _____               _     ____              \n"
                "\t\t\t\t     / ____|             | |   |  _ \\             \n"
                "\t\t\t\t    | (___    ___   _ __ | |_  | |_) | _   _  ___ \n"
                "\t\t\t\t     \\___ \\  / _ \\ | '__|| __| |  _ < | | | |/ __|\n"
                "\t\t\t\t     ____) || (_) || |   | |_  | |_) || |_| |\\__ \\\n"
                "\t\t\t\t    |_____/  \\___/ |_|    \\__| |____/  \\__,_||___/\n";

        SetConsoleTextAttribute(hConsole, currentColor);

        cout << "\t\t\t\t======================================================" << endl;
    }

    void displaySortedBuses(Bus* head) {
        // ADD EXECUTION TIME HERE BUT SHOULD INCLUDE THE ALGO TIME
        system("CLS");
        displaySortedBusesText();

        cout << "\t\t\t\tSorted Buses by Passenger Count:" << endl;

        Bus* curr = head;
        int busNo = 1;

        if (curr == NULL) {
            cout << "\n\t\t\t\tNo buses to display." << endl;
        }
        else {
            while (curr != NULL) {
                cout << "\t\t\t\tBus No." << busNo << ": " << curr->name << endl;
                cout << "\t\t\t\tRoute: " << curr->route << endl;
                cout << "\t\t\t\tEstimated Departure Time: " << curr->departure << endl;
                cout << "\t\t\t\tFare: Php " << curr->fare << endl;
                cout << "\t\t\t\tPassengers on Board: " << curr->passengerOnBoard << endl;
                cout << "\t\t\t\tArrival Time: " << curr->arrivalTime << endl;
                cout << "\t\t\t\t======================================================" << endl;

                curr = curr->next;
                busNo++;
            }
        }

        cout << "\n\t\t\t\tPress any key to go back: ";
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
private:
    Bus* merge(Bus* left, Bus* right) {
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;

        Bus* head;
        if (left->passengerOnBoard >= right->passengerOnBoard) {
            head = left;
            left = left->next;
        } else {
            head = right;
            right = right->next;
        }

        Bus* current = head;

        while (left != nullptr && right != nullptr) {
            if (left->passengerOnBoard >= right->passengerOnBoard) {
                current->next = left;
                left = left->next;
            } else {
                current->next = right;
                right = right->next;
            }
            current = current->next;
        }

        if (left != nullptr)
            current->next = left;
        else
            current->next = right;

        return head;
    }

    void split(Bus* source, Bus** frontRef, Bus** backRef) {
        Bus* slow = source;
        Bus* fast = source->next;

        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = nullptr;
    }
};


void logoHeader(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Get the current console color
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD currentColor = consoleInfo.wAttributes;
    // Set color to blue
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "\t\t\t\t   __  __            ____                 _           \n"
            "\t\t\t\t  |  \\/  |          |  _ \\               | |          \n"
            "\t\t\t\t  | \\  / | _ __     | |_) | _   _   __ _ | |__    ___ \n"
            "\t\t\t\t  | |\\/| || '__|    |  _ < | | | | / _` || '_ \\  / _ \\\n"
            "\t\t\t\t  | |  | || |    _  | |_) || |_| || (_| || | | ||  __/\n"
            "\t\t\t\t  |_|  |_||_|   (_) |____/  \\__, | \\__,_||_| |_| \\___|\n"
            "\t\t\t\t                             __/ |                    \n"
            "\t\t\t\t                            |___/                     \n";
    SetConsoleTextAttribute(hConsole, currentColor);
}

void mainMenu(){
    cout << "\n\t\t\t  ====================================================================\n";
    cout << "\t\t\t  | [1] Add Bus                                [6] Edit Bus          |\n";
    cout << "\t\t\t  | [2] Remove Bus                             [7] Sort Buses        |\n";
    cout << "\t\t\t  | [3] Depart Bus                             [8] History           |\n";
    cout << "\t\t\t  | [4] Display Specific Bus Information       [9] Exit              |\n";
    cout << "\t\t\t  | [5] Display All Buses Information                                |\n";
    cout << "\t\t\t  ====================================================================\n";
}

void color_coding(Bus* head) {
    Bus* curr = head;
    double occupancyPercentage = static_cast<double>(curr->passengerOnBoard) / MAX_SIZE;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD defaultColor = consoleInfo.wAttributes;

    
    if (occupancyPercentage == 1.0) {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    } else if (occupancyPercentage >= 0.5) {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    } else {
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    }

}

void centerBusDisplay(const string& text, int width) {

    if (text.length() > 12) {
        int leftPadding = (width - 12) / 2;
        int rightPadding = width - 12 - leftPadding;
        cout << string(leftPadding, ' ') << text.substr(0, 12) << "... ";
    } else {
        int leftPadding = (width - text.length()) / 2;
        int rightPadding = width - text.length() - leftPadding;
        cout << string(leftPadding, ' ') << text << string(rightPadding, ' ');
    }
}


void busDisplay(ParkingLot* parkingLot, int numParkingSlots) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD defaultColor = consoleInfo.wAttributes;

    const int parkingLotWidth = 20;

    cout << "\t\t  +--------------------+--------------------+--------------------+--------------------+         "<< endl;
    cout << "\t\t  |                    |                    |                    |                    |         "<< endl;
    cout << "\t\t  |                    |                    |                    |                    |         "<< endl;
    cout << "\t\t  |    Parking No.1    |   Parking No. 2    |   Parking No. 3    |   Parking No. 4    |         "<< endl;


    if (parkingLot[0].bus != nullptr) {
        cout << "\t\t  |";
        color_coding(parkingLot[0].bus);
        centerBusDisplay(parkingLot[0].bus->name, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "\t\t  |                    |";
    }

    if (parkingLot[1].bus != nullptr) {
        color_coding(parkingLot[1].bus);
        centerBusDisplay(parkingLot[1].bus->name, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    if (parkingLot[2].bus != nullptr) {
        color_coding(parkingLot[2].bus);
        centerBusDisplay(parkingLot[2].bus->name, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    if (parkingLot[3].bus != nullptr) {
        color_coding(parkingLot[3].bus);
        centerBusDisplay(parkingLot[3].bus->name, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    cout << endl;

    if (parkingLot[0].bus != nullptr) {
        cout << "\t\t  |";
        color_coding(parkingLot[0].bus);
        centerBusDisplay(parkingLot[0].bus->route, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "\t\t  |                    |";
    }

    if (parkingLot[1].bus != nullptr) {
        color_coding(parkingLot[1].bus);
        centerBusDisplay(parkingLot[1].bus->route, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    if (parkingLot[2].bus != nullptr) {
        color_coding(parkingLot[2].bus);
        centerBusDisplay(parkingLot[2].bus->route, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    if (parkingLot[3].bus != nullptr) {
        color_coding(parkingLot[3].bus);
        centerBusDisplay(parkingLot[3].bus->route, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    cout << endl;
    cout << "\t\t  |                    |                    |                    |                    |         " << endl;
    cout << "\t\t  |                    |                    |                    |                    |         " << endl;
    cout << "\t\t  |                    |                    |                    |                    |         " << endl;
    cout << "\t\t  +--------------------+--------------------+--------------------+--------------------+         " << endl;
    cout << "\t\t  |                                                                                   |         "<< endl;
    cout << "\t\t  |                                                                                   |         "<< endl;
    cout << "\t\t  +--------------------+--------------------+--------------------+--------------------+         "<< endl;
    cout << "\t\t  |                    |                    |                    |                    |         "<< endl;
    cout << "\t\t  |                    |                    |                    |                    |         "<< endl;
    cout << "\t\t  |   Parking No. 5    |   Parking No. 6    |    Parking No. 7   |   Parking No. 8    |         "<< endl;
  
    if (parkingLot[4].bus != nullptr) {
        cout << "\t\t  |";
        color_coding(parkingLot[4].bus);
        centerBusDisplay(parkingLot[4].bus->name, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "\t\t  |                    |";
    }

    if (parkingLot[5].bus != nullptr) {
        color_coding(parkingLot[5].bus);
        centerBusDisplay(parkingLot[5].bus->name, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    if (parkingLot[6].bus != nullptr) {
        color_coding(parkingLot[6].bus);
        centerBusDisplay(parkingLot[6].bus->name, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    if (parkingLot[7].bus != nullptr) {
        color_coding(parkingLot[7].bus);
        centerBusDisplay(parkingLot[7].bus->name, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    cout << endl;

    if (parkingLot[4].bus != nullptr) {
        cout << "\t\t  |";
        color_coding(parkingLot[4].bus);
        centerBusDisplay(parkingLot[4].bus->route, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "\t\t  |                    |";
    }

    if (parkingLot[5].bus != nullptr) {
        color_coding(parkingLot[5].bus);
        centerBusDisplay(parkingLot[5].bus->route, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    if (parkingLot[6].bus != nullptr) {
        color_coding(parkingLot[6].bus);
        centerBusDisplay(parkingLot[6].bus->route, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    if (parkingLot[7].bus != nullptr) {
        color_coding(parkingLot[7].bus);
        centerBusDisplay(parkingLot[7].bus->route, parkingLotWidth);
        SetConsoleTextAttribute(hConsole, defaultColor);
        cout << "|";
    } else {
        cout << "                    |";
    }

    cout << endl;
    cout << "\t\t  |                    |                    |                    |                    |         " << endl;
    cout << "\t\t  |                    |                    |                    |                    |         " << endl;
    cout << "\t\t  |                    |                    |                    |                    |         " << endl;
    cout << "\t\t  +--------------------+--------------------+--------------------+--------------------+         " << endl;
    cout << "\t\t  +--------------------+--------------------+--------------------+--------------------+" << endl;
    cout << "\t\t  |                              PASSENGERS ON BOARD                                  |" << endl;
    cout << "\t\t  +--------------------+--------------------+--------------------+--------------------+" << endl;
    cout << "\t\t  |       FULL = " << ANSI_RED << "RED" << ANSI_RESET << "      |        HALF-FULL = "<< ANSI_ORANGE << "ORANGE"<< ANSI_RESET <<"        |       LOW = "<< ANSI_GREEN << "GREEN"<< ANSI_RESET << "      |" << endl;
    cout << "\t\t  +--------------------+--------------------+--------------------+--------------------+" << endl;
}

int main()
{
    const int numParkingSlots = 8; //number of parking slots
    Bus* head = NULL; //linked list for add bus
    int totalBuses = 0;
    string choice;
    mainTerminal mT;
    ParkingLot parkingLot[numParkingSlots]; //array of parking slots
    Bus* historyList = NULL; //linked list for history
    auto startTime = chrono::steady_clock::now();
    for (int i = 0; i < numParkingSlots; i++) {
        parkingLot[i].bus = NULL; // Initialize all parking slots to NULL
    }

    bool isMain = true;
    while (isMain) {
        system("CLS");
        logoHeader();
        busDisplay(parkingLot, numParkingSlots);
        mainMenu();

        cout << "\t\t\t  Your Choice: ";
        cin >> choice;

        if (choice == "1") {
            mT.addBus(&head, totalBuses, parkingLot);
        }
        else if (choice == "2") {
            mT.removeBus(&head, totalBuses, parkingLot, &historyList);
        }
        else if (choice == "3") {
            mT.departBus(numParkingSlots);
        }
        else if (choice == "4") {
            mT.specificBus(parkingLot, numParkingSlots);
        }
        else if (choice == "5") {
            mT.displayAll(head, historyList);
        }
        else if (choice == "6") {
            mT.editBus(head, parkingLot, numParkingSlots, totalBuses);
        }
        else if (choice == "7") {
            auto startTime = chrono::steady_clock::now();
            mT.mergeSort(&head);
            auto endTime = chrono::steady_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
            cout << "\n\t\t\t  Buses sorted by Passenger Count!" << endl;
            cout << "\t\t\t  Execution Time: " << duration.count() << " ms" << endl;
            Sleep(1000);
            mT.displaySortedBuses(head); // Display the sorted buses
        }
        else if (choice == "8") {
            mT.history(historyList);
        }
        else if (choice == "9") {
            isMain = false;
        }
        else {
            cout << "\n\t\t\tInvalid Input! Please Try Again!";
            Sleep(1000);
        }
    }

    mT.freeMemory(head, historyList); //to free memory and avoid memory leaks
    auto endTime = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
    cout << "\t\t\t  Execution Time: " << duration.count() << " ms" << endl;
    return 0;
}
