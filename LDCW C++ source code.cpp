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

    distance = getAutomaticDistance();
    deliveryFee = calculateDeliveryFee(distance);

    for (int i = 0; i < itemCount; i++) {
        subtotal += cart[i].price;
    }

    cout << "\nDo you have a promo code? (Enter code or press 'Enter' to skip): ";
    cin.clear();
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, promoInput);

    if (!promoInput.empty()) {
        applyPromoEngine(promoInput, subtotal, discount, deliveryFee);
    }

    sstAmount = calculateSST(subtotal - discount);
    totalFinalBill = (subtotal - discount) + sstAmount + deliveryFee;

    if (totalFinalBill < 0.0) totalFinalBill = 0.0;

    cout << "\n==========================================" << endl;
    cout << "             FINAL ORDER RECEIPT          " << endl;
    cout << "==========================================" << endl;
    cout << fixed << setprecision(2);

    for (int i = 0; i < itemCount; i++) {
        cout << left << setw(32) << cart[i].name << "RM " << cart[i].price << endl;
        if (!cart[i].customOptions.empty()) {
            cout << "  * Preferences: " << cart[i].customOptions << endl;
        }
    }

    cout << "------------------------------------------" << endl;
    cout << left << setw(32) << "Cart Subtotal:" << "RM " << subtotal << endl;

    if (discount > 0.0) {
        cout << left << setw(32) << "Voucher Discount:" << "-RM " << discount << endl;
    }

    string distStr = to_string(distance);
    distStr = distStr.substr(0, distStr.find(".") + 3);
    cout << left << setw(32) << ("Delivery Fee (" + distStr + " km):") << "RM " << deliveryFee << endl;
    cout << left << setw(32) << "SST Government Tax (6%):" << "RM " << sstAmount << endl;
    cout << "------------------------------------------" << endl;
    cout << left << setw(32) << "TOTAL AMOUNT DUE:" << "RM " << totalFinalBill << endl;
    cout << "==========================================" << endl;

    simulatePaymentGateway(totalFinalBill);

    return 0;
}


void displayHeader() {
    cout << "==================================================" << endl;
    cout << "     MALAYSIAN ONLINE FOOD DELIVERY SYSTEM        " << endl;
    cout << "==================================================" << endl;
}

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

double getAutomaticDistance() {
    cout << "\n[GPS System] Synchronizing with local telecommunication masts..." << endl;
    cout << "[GPS System] Retrieving user coordinate points via device location API..." << endl;

    double simulatedDistance = 4.25;

    cout << "[GPS System] SUCCESS: Current delivery distance auto-calculated: " << simulatedDistance << " km" << endl;
    return simulatedDistance;
}

double calculateDeliveryFee(double distance) {
    if (distance <= 2.0) return 3.00;
    else if (distance > 2.0 && distance <= 5.0) return 5.00;
    else if (distance > 5.0 && distance <= 10.0) return 8.00;
    else return 12.00;
}

bool processLocalDelights(CartItem &item) {
    string prompt = "\n--- Local Malaysian Delights ---\n1. Char Siew Rice (RM 9.50)\n2. Wonton Noodles (RM 8.50)\n3. Pan Mee Dry (RM 10.00)\n4. Go Back to Main Menu\nEnter choice (1-4): ";
    int choice = getBoundedInteger(prompt, 1, 4);

    if (choice == 4) {
        return false;
    }

    if (choice == 1) { item.name = "Char Siew Rice"; item.price = 9.50; }
    else if (choice == 2) { item.name = "Wonton Noodles"; item.price = 8.50; }
    else { item.name = "Pan Mee Dry"; item.price = 10.00; }

    item.customOptions = "Standard Serving";
    return true;
}

bool processFastFood(CartItem &item) {
    string prompt = "\n--- Fast Food Burgers & Combos ---\n1. Spicy Chicken Burger Combo (RM 15.50)\n2. Ayam Goreng McD Spicy Combo (RM 17.00)\n3. Go Back to Main Menu\nEnter choice (1-3): ";
    int choice = getBoundedInteger(prompt, 1, 3);

    if (choice == 3) {
        return false;
    }

    if (choice == 1) {
        item.name = "Spicy Chicken Burger Combo";
        item.price = 15.50;

        int custom = getBoundedInteger("Exclude lettuce? (1 for Yes, 0 for No): ", 0, 1);
        if (custom == 1) item.customOptions = "No Lettuce Customization";
        else item.customOptions = "Standard Recipe";
    } else {
        item.name = "Ayam Goreng McD Spicy Combo";
        item.price = 17.00;
        item.customOptions = "Standard Recipe";
    }
    return true;
}

bool processBeverages(CartItem &item) {
    string prompt = "\n--- Beverages & Milk Tea ---\n1. White Peach Oolong Milk Tea (RM 12.00)\n2. Snowy Coco Oreo Smoothie (RM 13.50)\n3. Go Back to Main Menu\nEnter choice (1-3): ";
    int choice = getBoundedInteger(prompt, 1, 3);

    if (choice == 3) {
        return false;
    }

    if (choice == 1) { item.name = "White Peach Oolong Milk Tea"; item.price = 12.00; }
    else { item.name = "Snowy Coco Oreo Smoothie"; item.price = 13.50; }

    int sugar = getBoundedInteger("\nSelect Sugar Level:\n1. Normal Sugar\n2. Less Sweet\n3. Slightly Sweet\nEnter choice (1-3): ", 1, 3);
    int ice = getBoundedInteger("Select Ice Level:\n1. Normal Ice\n2. Less Ice\n3. No Ice\nEnter choice (1-3): ", 1, 3);

    string sugarStr = (sugar == 2) ? "Less Sweet" : (sugar == 3) ? "Slightly Sweet" : "Normal Sugar";
    string iceStr = (ice == 2) ? "Less Ice" : (ice == 3) ? "No Ice" : "Normal Ice";

    item.customOptions = sugarStr + ", " + iceStr;
    return true;
}

void applyPromoEngine(string code, double subtotal, double &discount, double &deliveryFee) {
    if (code == "MAKAN5") {
        if (subtotal >= 10.00) {
            discount = 5.00;
            cout << "[SUCCESS] Flat RM 5.00 discount applied smoothly!" << endl;
        } else {
            cout << "[REJECTED] 'MAKAN5' requires a minimum spending threshold of RM 10.00." << endl;
        }
    } else if (code == "FREEDEL") {
        deliveryFee = 0.00;
        cout << "[SUCCESS] Shipping promo applied! Delivery fee has been completely waived." << endl;
    } else {
        cout << "[NOTICE] Invalid voucher code entered. Proceeding without discount profiles." << endl;
    }
}

double calculateSST(double amount) {
    const double SST_RATE = 0.06;
    return amount * SST_RATE;
}

void simulatePaymentGateway(double finalBill) {
    cout << "\n>>> SECURE DIGITAL PAYMENT GATEWAY <<<" << endl;
    cout << "Select your preferred settlement pathway:" << endl;
    cout << "1. Digital Bank Account (Seamless Online Transfer)" << endl;
    cout << "2. Local FPX Primary Bank Node" << endl;
    cout << "3. Cash On Delivery (COD)" << endl;
    cout << "4. Cancel Transaction & Exit" << endl;

    int payChoice = getBoundedInteger("Select payment method (1-4): ", 1, 4);

    if (payChoice == 4) {
        cout << "\n[ABORTED] Secure checkout session ended. Transaction has been voided. Goodbye!" << endl;
        exit(0);
    }

    cout << "\nProcessing transaction of RM " << finalBill << " ... please wait." << endl;
    cout << "[SUCCESS] Secure transaction authenticated successfully!" << endl;
    cout << "Rider assigned to kitchen hub. Thank you for your order!" << endl;
}
