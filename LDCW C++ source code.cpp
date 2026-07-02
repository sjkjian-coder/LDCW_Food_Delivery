#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstdlib>

using namespace std;

const int MAX_CART_SIZE = 10;

struct CartItem {
    string name;
    double price;
    string customOptions;
};

void displayHeader();
void clearInputStream();
int getBoundedInteger(string prompt, int minVal, int maxVal);
double getAutomaticDistance();
double calculateDeliveryFee(double distance);
bool processLocalDelights(CartItem &item);
bool processFastFood(CartItem &item);
bool processBeverages(CartItem &item);
void applyPromoEngine(string code, double subtotal, double &discount, double &deliveryFee);
double calculateSST(double amount);
void simulatePaymentGateway(double finalBill);

void clearInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getBoundedInteger(string prompt, int minVal, int maxVal) {
    int inputVal;
    while (true) {
        cout << prompt;
        cin >> inputVal;

        if (cin.fail() || inputVal < minVal || inputVal > maxVal) {
            cout << "\n[ERROR] Invalid entry! Please enter an integer between "
                 << minVal << " and " << maxVal << ".\n" << endl;
            clearInputStream();
        } else {
            return inputVal;
        }
    }
}
