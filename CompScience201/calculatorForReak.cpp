#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
using namespace std;

// Function Prototypes
void displayMainMenu();
void performArithmeticOperations();
void performNumberConversions();

// Arithmetic Functions
double add(double, double);
double subtract(double, double);
double multiply(double, double);
double divide(double, double);

// Conversion Functions
string decToBin(int);
string decToOct(int);
string decToHex(int);
int binToDec(string);
int octToDec(string);
int hexToDec(string);

// Helper Functions
bool isValidBinary(string);
bool isValidOctal(string);
bool isValidHex(string);

int main() {
    int choice;
    do {
        displayMainMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            performArithmeticOperations();
            break;
        case 2:
            performNumberConversions();
            break;
        case 3:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Please choose again.\n";
        }
    } while (choice != 3);

    return 0;
}

void displayMainMenu() {
    cout << "\n===== MAIN MENU =====\n";
    cout << "1. Arithmetic Operations\n";
    cout << "2. Number Base Conversions\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void performArithmeticOperations() {
    int choice;
    double num1, num2;
    do {
        cout << "\n-- Arithmetic Operations --\n";
        cout << "1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Return to Main Menu\nChoice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 4) {
            cout << "Enter two numbers: ";
            cin >> num1 >> num2;
        }

        switch (choice) {
        case 1:
            cout << "Result: " << add(num1, num2) << endl;
            break;
        case 2:
            cout << "Result: " << subtract(num1, num2) << endl;
            break;
        case 3:
            cout << "Result: " << multiply(num1, num2) << endl;
            break;
        case 4:
            if (num2 != 0)
                cout << "Result: " << divide(num1, num2) << endl;
            else
                cout << "Error: Division by zero!\n";
            break;
        case 5:
            return;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);
}

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) { return a / b; }

void performNumberConversions() {
    int choice, decVal;
    string input;
    do {
        cout << "\n-- Number Base Conversions --\n";
        cout << "1. Decimal to Binary\n2. Decimal to Octal\n3. Decimal to Hexadecimal\n";
        cout << "4. Binary to Decimal\n5. Octal to Decimal\n6. Hexadecimal to Decimal\n7. Return to Main Menu\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter decimal number: ";
            cin >> decVal;
            cout << "Binary: " << decToBin(decVal) << endl;
            break;
        case 2:
            cout << "Enter decimal number: ";
            cin >> decVal;
            cout << "Octal: " << decToOct(decVal) << endl;
            break;
        case 3:
            cout << "Enter decimal number: ";
            cin >> decVal;
            cout << "Hexadecimal: " << decToHex(decVal) << endl;
            break;
        case 4:
            cout << "Enter binary number: ";
            cin >> input;
            if (isValidBinary(input))
                cout << "Decimal: " << binToDec(input) << endl;
            else
                cout << "Invalid binary number!\n";
            break;
        case 5:
            cout << "Enter octal number: ";
            cin >> input;
            if (isValidOctal(input))
                cout << "Decimal: " << octToDec(input) << endl;
            else
                cout << "Invalid octal number!\n";
            break;
        case 6:
            cout << "Enter hexadecimal number: ";
            cin >> input;
            if (isValidHex(input))
                cout << "Decimal: " << hexToDec(input) << endl;
            else
                cout << "Invalid hexadecimal number!\n";
            break;
        case 7:
            return;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 7);
}

string decToBin(int num) {
    string result;
    if (num == 0) return "0";
    while (num > 0) {
        result = to_string(num % 2) + result;
        num /= 2;
    }
    return result;
}

string decToOct(int num) {
    string result;
    if (num == 0) return "0";
    while (num > 0) {
        result = to_string(num % 8) + result;
        num /= 8;
    }
    return result;
}

string decToHex(int num) {
    string result, hexDigits = "0123456789ABCDEF";
    if (num == 0) return "0";
    while (num > 0) {
        result = hexDigits[num % 16] + result;
        num /= 16;
    }
    return result;
}

int binToDec(string bin) {
    int result = 0;
    for (char c : bin) {
        result = result * 2 + (c - '0');
    }
    return result;
}

int octToDec(string oct) {
    int result = 0;
    for (char c : oct) {
        result = result * 8 + (c - '0');
    }
    return result;
}

int hexToDec(string hex) {
    int result = 0;
    for (char c : hex) {
        if (isdigit(c))
            result = result * 16 + (c - '0');
        else
            result = result * 16 + (toupper(c) - 'A' + 10);
    }
    return result;
}

bool isValidBinary(string str) {
    for (char c : str) {
        if (c != '0' && c != '1') return false;
    }
    return true;
}

bool isValidOctal(string str) {
    for (char c : str) {
        if (c < '0' || c > '7') return false;
    }
    return true;
}

bool isValidHex(string str) {
    for (char c : str) {
        if (!isdigit(c) && !(toupper(c) >= 'A' && toupper(c) <= 'F')) return false;
    }
    return true;
}