	//Name:Ashley Ogamba
	//Program 2 – Chocolate Factory
	/*create a chocolate inventory program that helps the company fill orders efficiently!Your boss is so
impressed!You described how you can fill multiple orders while keeping a sound inventory of remaining
chocolate on hand.In addition, you have created a nice printout of the order which adds the cost of tax and
shipping to each order as well as the ability to order more chocolate for the warehouse.*/



#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>
using namespace std;

// Function Declarations
void orderInventory(int& l, int& m, int& s);
void fillOrder(int& l, int& m, int& s, int& o);
void printInventory(int l, int m, int s);
double calculateShipping(int pounds);

int main() {
    int large = 1500;
    int medium = 1200;
    int small = 7000;
    int orderNum = 1;
    char choice;

    while (true) {
        cout << "\nEnter your choice:\n";
        cout << "O  : Order Inventory\n";
        cout << "F  : Fill Order\n";
        cout << "P  : Print Inventory\n";
        cout << "E  : Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (toupper(choice)) {
        case 'O':
            orderInventory(large, medium, small);
            break;
        case 'F':
            fillOrder(large, medium, small, orderNum);
            break;
        case 'P':
            printInventory(large, medium, small);
            break;
        case 'E':
            cout << "Thank you for using my program!" << endl;
            return 0;
        default:
            cout << "WARNING: " << choice << " is an invalid choice. Please try again." << endl;
        }
    }
}

// a. Order Inventory
void orderInventory(int& l, int& m, int& s) {
    int amount;
    char type;
    cout << "Enter the number of bars needed: ";
    cin >> amount;

    cout << "Enter the type (L, M, S): ";
    cin >> type;
    type = toupper(type);

    switch (type) {
    case 'L':
        l += amount;
        cout << "An additional " << amount << " large bars ordered. New total of large bars = " << l << endl;
        break;
    case 'M':
        m += amount;
        cout << "An additional " << amount << " medium bars ordered. New total of medium bars = " << m << endl;
        break;
    case 'S':
        s += amount;
        cout << "An additional " << amount << " small bars ordered. New total of small bars = " << s << endl;
        break;
    default:
        cout << "WARNING: " << type << " is an invalid type. Command ignored." << endl;
    }
}

// b. Fill Order
void fillOrder(int& l, int& m, int& s, int& o) {
    int pounds;
    cout << "Please enter the number of pounds of chocolate you'd like to order: ";
    cin >> pounds;

    int useL = min(pounds / 5, l);
    pounds -= useL * 5;

    int useM = min(pounds / 3, m);
    pounds -= useM * 3;

    int useS = min(pounds, s);
    pounds -= useS;

    int totalUsed = useL * 5 + useM * 3 + useS;
    int poundsShort = pounds;

    if (pounds > 0) {
        cout << "WARNING: Unable to fill order of " << totalUsed + poundsShort
            << " pounds. We are " << poundsShort << " pounds short. We are sorry for the inconvenience." << endl;
        return;
    }

    // Prices
    double largeTot = useL * 41.25;
    double mediumTot = useM * 25.80;
    double smallTot = useS * 13.50;
    double subtotal = largeTot + mediumTot + smallTot;
    double tax = subtotal * 0.072;
    double shipping = calculateShipping(useL * 5 + useM * 3 + useS);
    double totalCost = subtotal + tax + shipping;

    // Update inventory
    l -= useL;
    m -= useM;
    s -= useS;

    // Print receipt
    cout << fixed << setprecision(2);
    cout << "\n     Chocolate Order #" << o << endl;
    cout << "Large Bars: " << setw(4) << useL << setw(9) << useL * 5 << setw(12) << largeTot << endl;
    cout << "Medium Bars:" << setw(4) << useM << setw(9) << useM * 3 << setw(12) << mediumTot << endl;
    cout << "Small Bars: " << setw(4) << useS << setw(9) << useS << setw(12) << smallTot << endl;
    cout << "Sub Total: " << setw(13) << useL * 5 + useM * 3 + useS << setw(12) << subtotal << endl;
    cout << "\nTax Total: " << setw(25) << tax << endl;
    cout << "Shipping: " << setw(25) << shipping << endl;
    cout << "Total Cost: " << setw(25) << totalCost << endl << endl << endl;

    o++; // Increment order number
}

// c. Print Inventory
void printInventory(int l, int m, int s) {
    cout << "\nCurrent Inventory:\n";
    cout << "Large Bars:  " << setw(4) << l << endl;
    cout << "Medium Bars: " << setw(4) << m << endl;
    cout << "Small Bars:  " << setw(4) << s << endl;
}

// d. Shipping Function
double calculateShipping(int pounds) {
    if (pounds <= 10) return 8.25;
    else if (pounds <= 20) return 12.75;
    else if (pounds <= 50) return 15.25;
    else return 19.75;
}

