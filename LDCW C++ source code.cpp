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
