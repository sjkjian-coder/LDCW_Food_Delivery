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

int main() {
    CartItem cart[MAX_CART_SIZE];
    int itemCount = 0;

    int mainCategoryChoice = 0;
    double distance = 0.0;
    double deliveryFee = 0.0;
    double subtotal = 0.0;
    double discount = 0.0;
    double sstAmount = 0.0;
    double totalFinalBill = 0.0;
    string promoInput = "";

    displayHeader();

    while (itemCount < MAX_CART_SIZE) {
        mainCategoryChoice = getBoundedInteger(
            "\nSelect an option from the menu:\n1. Local Malaysian Delights\n2. Fast Food Burgers & Combos\n3. Beverages & Milk Tea\n4. Proceed to Checkout & Payment\n5. Cancel Order & Exit\nEnter choice (1-5): ",
            1, 5
        );

        if (mainCategoryChoice == 4) {
            break;
        }
        else if (mainCategoryChoice == 5) {
            cout << "\nOrder cancelled successfully. Thank you for visiting!" << endl;
            return 0;
        }

        bool itemAddedSuccessfully = false;
        switch (mainCategoryChoice) {
            case 1:
                itemAddedSuccessfully = processLocalDelights(cart[itemCount]);
                if (itemAddedSuccessfully) itemCount++;
                break;
            case 2:
                itemAddedSuccessfully = processFastFood(cart[itemCount]);
                if (itemAddedSuccessfully) itemCount++;
                break;
            case 3:
                itemAddedSuccessfully = processBeverages(cart[itemCount]);
                if (itemAddedSuccessfully) itemCount++;
                break;
        }

        if (itemAddedSuccessfully) {
            cout << "\n[SUCCESS] Item added to your cart. Current cart size: " << itemCount << "/" << MAX_CART_SIZE << endl;
        } else {
            cout << "\n[NOTICE] Returned to main hub. No items were added to your cart." << endl;
        }

        if (itemCount >= MAX_CART_SIZE) {
            cout << "\n[NOTICE] Your shopping cart is full (Max 10 items reached). Proceeding to checkout automatically." << endl;
            break;
        }
    }

    if (itemCount == 0) {
        cout << "\nCheckout failed. No items found in your shopping cart." << endl;
        return 0;
    }
