/*
* Author: Olivia Loris, oloris2021@fit.edu
* Course: CSE 1502, Section 04/05/S04 Spring 2022
* Project: Shopping2.cpp
*/

#include <iostream>
#include <cstdio>
using namespace std;

int main() {

    const int cMenuSize = 9; // How many items in the menu?
    const int cShoppingCartSize = 100; // How big is the invoice?
    const int cMenuTypeCount = 3; // How many items in the menuType enum?

    // misc variables
    int selection;
    float budget;
    float total = 0;
    char continueShopping;
    int itemCount;
    float amtPurchase;
    int qtyItem;
    float shippingCost;

    int itemMap[cMenuSize];
    int shoppingCart[cShoppingCartSize][2]; // col1 = menu id, col2 = qty purchased
    int shoppingCartPointer = 0;

    enum menuTypes {fruit, vegetable, beverage};
    float menuTypeShippingCost[cMenuTypeCount] = {3.50f, 2.0f, 5.50f};
    string menuTypeLabelsSingular[cMenuTypeCount] = {"fruit", "vegetable", "beverage"};
    string menuTypeLabelsPlural[cMenuTypeCount] = {"Fruits", "Vegetables", "Beverages"};

    int menuItemType[cMenuSize] = {fruit, fruit, fruit, 
                                   vegetable, vegetable, vegetable,
                                   beverage, beverage, beverage};

    string menuItemLabel[cMenuSize] = {"Fuji Apples", "Watermelon", "Strawberries",
                                       "Red Cabbage", "Zucchini", "Beets",
                                       "Apple Juice", "Orange Juice", "Coconut Water"};
                                       
    string menuItemEach[cMenuSize] = {"3 lb", "each", "16 oz",
                                      "each", "each", "1 lb",
                                      "64 fl oz", "64 fl oz", "33.8 fl oz"};

    float menuItemPrice[cMenuSize] = {4.77f, 7.88f, 2.42f,
                                      2.97f, 0.81f, 2.44f,
                                      2.88f, 5.54f, 3.47f};

    enum selections {
        cancel = 0, selection1, selection2, selection3
    };
    
    // Start the Main Program
    cout << "Welcome to Panther Grocery Store." << endl;
    cout << "Please enter shopping budget ($): ";
    cin >> budget;
    
    cout << endl << "================================================================";
    cout << endl << endl;

    // ###### Menu & Selection Section ###### 
    for(int loopMenuType = 0; loopMenuType < cMenuTypeCount; loopMenuType++) {
        do {
            // Output Item Menu
            cout << "Panther " << menuTypeLabelsPlural[loopMenuType] << endl 
                << "----------------" << endl;
            itemCount = 0;  // reset for the number selection in the menu.
            for(int i = 0; i < cMenuSize; i++) {
                if(menuItemType[i] == loopMenuType) {
                    // record the row num for each item
                    itemMap[itemCount] = i;
                    // generate menu line
                    cout << ++itemCount << " " << menuItemLabel[i] 
                         << " (" << menuItemEach[i] << ") (";
                    printf("$%'.2f)\n", menuItemPrice[i]);
                }
            }

            // Get their selection
            do {
                cout << "Please select your " << menuTypeLabelsSingular[loopMenuType] 
                     << " (1-3, 0 to cancel): ";
                cin >> selection;
            } 
            while(selection > itemCount || selection < 0);

            // Item selected (not cancel)
            if(selection != cancel) {
                // Get the quantity
                do {
                    cout << "Please enter quantity (0 to skip): ";
                    cin >> qtyItem;
                }
                while(qtyItem < 0);

                // let's do some work if we have selection and quantity
                if(qtyItem > 0) {
                    // Calculate item total
                    amtPurchase = menuItemPrice[itemMap[selection - 1]] * qtyItem;

                    // check if there is budget
                    if(amtPurchase > budget) {
                        cout << "Order amount exceeds budget -- cannot proceed.";
                    }
                    // process item - good purchase!
                    else {
                        // Add to shooping cart
                        shoppingCart[shoppingCartPointer][0] = itemMap[selection - 1]; 
                        shoppingCart[shoppingCartPointer][1] = qtyItem; // item qty selected
                        shoppingCartPointer++;

                        // output to user
                        cout << "Added to shopping cart: " 
                             << menuItemLabel[ itemMap[selection - 1] ] 
                             << " [" << qtyItem << "] (";
                        printf("$%'.2f)", amtPurchase);
                        budget -= amtPurchase;
                        total += amtPurchase;
                    }
                }
                cout << endl;
            }

            printf("Balance: $%'.2f\n\n", budget);
            
            do { // keep them in here until they enter Y or N
                cout << "Continue shopping in this category? (Y/N): ";
                cin >> continueShopping;
                
                // Is it Y or N?
                if(toupper(continueShopping) != 'Y' && toupper(continueShopping) != 'N') {
                    // It's N - output error message
                    cout << "Invalid choice. Please enter Y/N: " << endl;
                }

            }// No leaving until y or n
            while(toupper(continueShopping) != 'Y' && toupper(continueShopping) != 'N');
            
            cout << endl;

        } 
        while(toupper(continueShopping) == 'Y');
    }

    // ###### Receipt & Shipping Section ######

    // Were purchases made?
    if(total > 0) {
        // Calculate Shipping Costs
        // For each menu type - fruit, veg, bev...
        for(int iMenuType = 0; iMenuType < cMenuTypeCount; iMenuType++) {
            // For each item in the shopping cart
            for(int i = 0; i < shoppingCartPointer; i++) {
                // If the item is the type from the outerloop
                if(menuItemType[shoppingCart[i][0]] == iMenuType) {
                    // Add it to the shipping cost and move to the next menu type
                    shippingCost += menuTypeShippingCost[iMenuType];
                    break;
                }
            }
        }

        // Print the receipt
        cout << endl 
            << "================== Invoice - Panther Home ==================" << endl;
        printf("%-30s%10s%10s%10s\n","Item", "Price", "Qty", "Amount");
        cout << "------------------------------------------------------------" << endl;
        // go through each item in the shopping cart
        for(int i = 0; i < shoppingCartPointer; i++) {
            printf("%-30s%10'.2f%10d%10'.2f\n", menuItemLabel[shoppingCart[i][0]].c_str(), 
                    menuItemPrice[ shoppingCart[i][0] ], shoppingCart[i][1], 
                    shoppingCart[i][1] * menuItemPrice[ shoppingCart[i][0] ]);
        }
        total += shippingCost;
        printf("Shipping:%51'.2f\n", shippingCost);
        cout << "------------------------------------------------------------" << endl;
        printf("Total Amount:%47'.2f\n", total);
        cout << "------------------------------------------------------------" << endl;
    }
    else { 
        // no purchases!
        cout << "No purchases were made." << endl;
    }
    
    return 0;

}
