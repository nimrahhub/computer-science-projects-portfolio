#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Structure to represent a food item
struct FoodItem {
    string name;
    float price;
    int quantity;
};

// Structure to represent an order
struct Order {
    string customerName;
    string phoneNumber;
    string address;
    FoodItem items[20]; // Increased size to 20 items
    int numItems;
};

// Function to display menu
void displayMenu(FoodItem menu[], int numItems) {
    cout << "\t\t\t\t+------------------------------+" << endl;
    cout << "\t\t\t\t|          Menu                |" << endl;
    cout << "\t\t\t\t+------------------------------+" << endl;
    for (int i = 0; i < numItems; i++) {
        cout << "\t\t\t\t| " << i + 1 << ". " << menu[i].name << " - Rs. " << menu[i].price  << endl;
    }
    cout << "\t\t\t\t+------------------------------+" << endl;
}

// Function to take order
void takeOrder(Order* order, FoodItem menu[], int numItems) {
    cout << "\t\t\t\t+-----------------------+" << endl;
    cout << "\t\t\t\t|       Tasty Bites     |" << endl;
    cout << "\t\t\t\t+-----------------------+" << endl;
    cout << "\t\t\t\t|     Customer Details  |" << endl;
    cout << "\t\t\t\t+-----------------------+" << endl;
    cout << "\t\t\t\t| Enter customer name: ";
    cin >> order->customerName;

    cout << "\t\t\t\t| Enter phone number: ";
    cin >> order->phoneNumber;

    cout << "\t\t\t\t| Enter address: ";
    cin.ignore(); // Ignore newline character
    getline(cin, order->address);
    cout << "\t\t\t\t+-----------------------+" << endl;

    cout << "\t\t\t\t+-----------------------+" << endl;
    cout << "\t\t\t\t|      Select Items     |" << endl;
    cout << "\t\t\t\t+-----------------------+" << endl;
    displayMenu(menu, numItems); // Display menu here

    int choice;
    do {
        cout << "\t\t\t\t| Enter item number (0 to finalize order, -1 to exit): ";
        cin >> choice;
        if (choice == -1) {
            cout << "\t\t\t\tExiting order process." << endl;
            exit(0);
        } else if (choice > 0 && choice <= numItems) {
            order->items[order->numItems] = menu[choice - 1];
            order->numItems++;
        }
    } while (choice != 0);
}

// Function to display order
void displayOrder(Order order) {
    cout << "\t\t\t\t+-----------------------+" << endl;
    cout << "\t\t\t\t|      Order Summary    |" << endl;
    cout << "\t\t\t\t+-----------------------+" << endl;
    cout << "\t\t\t\t| Customer Name: " << order.customerName  << endl;
    cout << "\t\t\t\t| Phone Number: " << order.phoneNumber << endl;
    cout << "\t\t\t\t| Address: " << order.address << endl;
    cout << "\t\t\t\t+-----------------------+" << endl;
    cout << "\t\t\t\t+---------------------------------+" << endl;
    cout << "\t\t\t\t               Items:              " << endl;
    for (int i = 0; i < order.numItems; i++) {
        cout << "\t\t\t\t\t" << order.items[i].name << " - Rs." << order.items[i].price << endl;
    }
    cout << "\t\t\t\t+---------------------------------+" << endl;
}

// Function to calculate total cost
float calculateTotal(Order order) {
    float total = 0.0;
    for (int i = 0; i < order.numItems; i++) {
        total += order.items[i].price;
    }
    
    // Apply discount of 10% if total is greater than Rs. 500
    if (total > 500) {
        float discountAmount = total * 0.1;
        total -= discountAmount;
        cout << "\t\t\t\t Discount applied (10% off on orders above Rs. 500): Rs. " << discountAmount << endl;
    }
    
    return total;
}

// Function to estimate delivery time
int estimateDeliveryTime() {
    srand(time(0)); // Seed random number generator
    int deliveryTime = rand() % 30 + 15; // Random delivery time between 15 and 45 minutes
    return deliveryTime;
}

// Function to handle payment
void handlePayment(float totalAmount) {
    int paymentMethod;
    cout << "\t\t\t\t+-----------------------------------------------------------+" << endl;
    cout << "\t\t\t\t| Total Cost: Rs. " << totalAmount << endl;
    cout << "\t\t\t\t+-----------------------------------------------------------+" << endl;
    cout << "\t\t\t\t+------------------------------+" << endl;
    cout << "\t\t\t\t| Select payment method:        |" << endl;
    cout << "\t\t\t\t| 1. Online Payment             |" << endl;
    cout << "\t\t\t\t| 2. Pay at Door                |" << endl;
    cout << "\t\t\t\t+------------------------------+" << endl;
    cout << "\t\t\t\tEnter choice: ";
    cin >> paymentMethod;

    if (paymentMethod == 1) {
        int onlineMethod;
        cout << "\t\t\t\t+------------------------------+" << endl;
        cout << "\t\t\t\t| Select online payment method: |" << endl;
        cout << "\t\t\t\t| 1. JazzCash                   |" << endl;
        cout << "\t\t\t\t| 2. EasyPaisa                  |" << endl;
        cout << "\t\t\t\t| 3. Credit Card                |" << endl;
        cout << "\t\t\t\t+------------------------------+" << endl;
        cout << "\t\t\t\tEnter choice: ";
        cin >> onlineMethod;

        if (onlineMethod == 3) {
            string cardNumber, cardPassword;
            cout << "\t\t\t\tEnter Credit Card Number: ";
            cin >> cardNumber;
            cout << "\t\t\t\tEnter Credit Card Password: ";
            cin >> cardPassword;
            cout << "\t\t\t\tProcessing payment..." << endl;
            cout << "\t\t\t\tPayment successful. Rs. " << totalAmount << " has been charged." << endl;
        } else {
            cout << "\t\t\t\tProcessing payment via selected method..." << endl;
            cout << "\t\t\t\tPayment successful. Rs. " << totalAmount << " has been charged." << endl;
        }
    } else {
        cout << "\t\t\t\tPlease pay Rs. " << totalAmount << " at the door upon delivery." << endl;
    }
}

int main() {

    FoodItem menu[] = {
        {"Zinger Burger", 300.0, 10},
        {"Egg Burger", 200.0, 10},
        {"Fries", 50.0, 10},
        {"Coke", 70.0, 10},
        {"Pepsi", 70.0, 10},
        {"Chicken Sandwich", 150.0, 10},
        {"Ice cream", 90.0, 10},
        {"Zinger Shawarma", 300.0, 10},
        {"Chicken Shawarma", 200.0, 10}
    };
    int numItems = sizeof(menu) / sizeof(menu[0]);

    Order order;
    order.numItems = 0;
    takeOrder(&order, menu, numItems);
    
    cout << "\t\t\t\t+------------------------------+" << endl;
    cout << "\t\t\t\t|       Tasty Bites            |" << endl;
    cout << "\t\t\t\t+------------------------------+" << endl;
    
    displayOrder(order);

    float totalCost = calculateTotal(order);
    handlePayment(totalCost);

    cout << "\t\t\t\t+------------------------------+" << endl;
    cout << "\t\t\t\t|      Delivery Time: " << estimateDeliveryTime() << " min" << " |" << endl;
    cout << "\t\t\t\t+------------------------------+" << endl;
    
    return 0;
}
