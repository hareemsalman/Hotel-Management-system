#include <iostream>
#include <string>
using namespace std;

const int MAX_ROOMS = 100;
const int MAX_GUESTS = 100;
const int MAX_MENU_ITEMS = 100;

class HotelManagementSystem {
private:
    int room_number[MAX_ROOMS];
    char room_type[MAX_ROOMS]; 
    double room_price[MAX_ROOMS];
    char room_status[MAX_ROOMS]; 

    int guest_id[MAX_GUESTS];  
    int guest_room[MAX_GUESTS]; 
    int guest_days[MAX_GUESTS];
    double guest_total[MAX_GUESTS];
    double guest_food[MAX_GUESTS];

    string menu_name[MAX_MENU_ITEMS]; 
    double menu_price[MAX_MENU_ITEMS];

    int room_count = 0, guest_count = 0, menu_count = 0;

public:
    void addRoom() {
        if (room_count >= MAX_ROOMS) {
            cout << "Cannot add more rooms!\n";
            return;
        }
        cout << "Enter room number (integer): ";
        cin >> room_number[room_count];
        cout << "Enter room type ('S' for Single, 'D' for Double): ";
        cin >> room_type[room_count];
        cout << "Enter price per night: ";
        cin >> room_price[room_count];
        room_status[room_count] = 'A'; 
        room_count++;
        cout << "Room added successfully!\n";
    }

    void viewRooms() {
        if (room_count == 0) {
            cout << "No rooms available.\n";
            return;
        }
        cout << "Room Details:\n";
        for (int i = 0; i < room_count; i++) {
            cout << "Room Number: " << room_number[i] << " | Type: " << room_type[i]
                 << " | Price: $" << room_price[i] << " | Status: " << (room_status[i] == 'A' ? "Available" : "Booked") << endl;
        }
    }

    void bookRoom() {
        int room;
        cout << "Enter room number (integer): ";
        cin >> room;

        for (int i = 0; i < room_count; i++) {
            if (room_number[i] == room) {
                if (room_status[i] == 'A') {
                    if (guest_count >= MAX_GUESTS) {
                        cout << "Guest limit reached!\n";
                        return;
                    }
                    guest_id[guest_count] = guest_count + 1; 
                    cout << "Enter number of days: ";
                    cin >> guest_days[guest_count];

                    guest_room[guest_count] = room;
                    guest_total[guest_count] = guest_days[guest_count] * room_price[i];
                    guest_food[guest_count] = 0;
                    room_status[i] = 'B'; 
                    guest_count++;

                    cout << "Room booked! Total Cost: $" << guest_total[guest_count - 1] << endl;
                    return;
                } else {
                    cout << "Room is already booked!\n";
                    return;
                }
            }
        }
        cout << "Room not found!\n";
    }

    void viewGuests() {
        if (guest_count == 0) {
            cout << "No guests found.\n";
            return;
        }
        cout << "Guest Details:\n";
        for (int i = 0; i < guest_count; i++) {
            cout << "Guest ID: " << guest_id[i] << " | Room: " << guest_room[i]
                 << " | Days: " << guest_days[i] << " | Room Cost: $" << guest_total[i]
                 << " | Food Bill: $" << guest_food[i]
                 << " | Total Bill: $" << guest_total[i] + guest_food[i] << endl;
        }
    }

    void checkoutGuest() {
        int room;
        cout << "Enter room number (integer) to checkout: ";
        cin >> room;

        for (int i = 0; i < guest_count; i++) {
            if (guest_room[i] == room) {
                for (int j = 0; j < room_count; j++) {
                    if (room_number[j] == room) {
                        room_status[j] = 'A'; 
                        break;
                    }
                }
                for (int j = i; j < guest_count - 1; j++) {
                    guest_id[j] = guest_id[j + 1];
                    guest_room[j] = guest_room[j + 1];
                    guest_days[j] = guest_days[j + 1];
                    guest_total[j] = guest_total[j + 1];
                    guest_food[j] = guest_food[j + 1];
                }
                guest_count--;
                cout << "Guest checked out! Room now available.\n";
                return;
            }
        }
        cout << "Room not found!\n";
    }

    void addMenuItem() {
        if (menu_count >= MAX_MENU_ITEMS) {
            cout << "Menu is full!\n";
            return;
        }
        string item_name;
        cout << "Enter item name: ";
        cin >> item_name;
        menu_name[menu_count] = item_name; 
        cout << "Enter price: ";
        cin >> menu_price[menu_count];
        menu_count++;
        cout << "Item added!\n";
    }

    void viewMenu() {
        if (menu_count == 0) {
            cout << "Menu is empty!\n";
            return;
        }
        cout << "Menu Items:\n";
        for (int i = 0; i < menu_count; i++) {
            cout << i + 1 << ". Item: " << menu_name[i] << " - $" << menu_price[i] << endl;
        }
    }

    void orderFood() {
        int room;
        cout << "Enter room number (integer): ";
        cin >> room;

        for (int i = 0; i < guest_count; i++) {
            if (guest_room[i] == room) {
                viewMenu();
                if (menu_count == 0) {
                    cout << "No items available.\n";
                    return;
                }
                int choice;
                cout << "Enter item number (0 to stop): ";
                while (true) {
                    cin >> choice;
                    if (choice == 0) break;
                    if (choice > 0 && choice <= menu_count) {
                        guest_food[i] += menu_price[choice - 1];
                        cout << "Added item: " << menu_name[choice - 1] << ". Current food bill: $" << guest_food[i] << endl;
                    } else {
                        cout << "Invalid choice!\n";
                    }
                }
                cout << "Order complete. Total food bill: $" << guest_food[i] << endl;
                return;
            }
        }
        cout << "Room not found!\n";
    }

    void mainMenu() {
        while (true) {
            cout << "\n=== Hotel Management System ===\n";
            cout << "1. Add Room\n2. View Rooms\n3. Book Room\n4. View Guests\n";
            cout << "5. Checkout Guest\n6. Add Menu Item\n7. View Menu\n8. Order Food\n9. Exit\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1: addRoom(); break;
                case 2: viewRooms(); break;
                case 3: bookRoom(); break;
                case 4: viewGuests(); break;
                case 5: checkoutGuest(); break;
                case 6: addMenuItem(); break;
                case 7: viewMenu(); break;
                case 8: orderFood(); break;
                case 9: cout << "Thank you for using the Hotel Management System... Goodbye!\n"; return;
                default: cout << "Invalid choice. Try again!\n";
            }
        }
    }
};

int main() {
    HotelManagementSystem system;
    system.mainMenu();
    return 0;
}
