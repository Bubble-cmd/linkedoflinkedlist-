#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include <time.h>

void printMenu() {
    printf("\nMenu:\n");
    printf("1. Add warehouse\n");
    printf("2. Add item to warehouse\n");
    printf("3. Print warehouse inventory\n");
    printf("4. Search for item in warehouse\n");
    printf("5. Remove item from warehouse\n");
    printf("6. Exit\n");
}

void addWarehouseMenu(Warehouse** warehouses) {
    char warehouseName[50];
    clock_t start = clock(); // Start timer
    printf("Enter warehouse name: ");
    scanf_s("%s", warehouseName, sizeof(warehouseName));
    addWarehouse(warehouses, createWarehouse(warehouseName));
    clock_t end = clock(); // Stop timer
    printf("Warehouse '%s' added successfully.\n", warehouseName);
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds.\n", cpu_time_used);
}

void addItemMenu(Warehouse* warehouses) {
    char warehouseName[50];
    char itemName[50];
    int quantity;
    clock_t start = clock(); // Start timer
    printf("Enter warehouse name: ");
    scanf_s("%s", warehouseName, sizeof(warehouseName));
    printf("Enter item name: ");
    scanf_s("%s", itemName, sizeof(itemName));
    printf("Enter quantity: ");
    scanf_s("%d", &quantity);
    clock_t start = clock(); // Start timer
    Warehouse* warehouse = findWarehouse(warehouses, warehouseName);
    if (warehouse != NULL) {
        addItemToWarehouse(warehouse, createItem(itemName, quantity));
        printf("Item '%s' added to warehouse '%s' successfully.\n", itemName, warehouseName);
    }
    else {
        printf("Warehouse '%s' not found.\n", warehouseName);
    }
    clock_t end = clock(); // Stop timer
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds.\n", cpu_time_used);
}

void printInventoryMenu(Warehouse* warehouses) {
    char warehouseName[50];
    clock_t start = clock(); // Start timer
    printf("Enter warehouse name to print inventory: ");
    scanf_s("%s", warehouseName, sizeof(warehouseName));
    clock_t start = clock(); // Start timer
    Warehouse* warehouse = findWarehouse(warehouses, warehouseName);
    if (warehouse != NULL) {
        printWarehouseInventory(warehouse);
    }
    else {
        printf("Warehouse '%s' not found.\n", warehouseName);
    }
    clock_t end = clock(); // Stop timer
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds.\n", cpu_time_used);
}

void searchItemMenu(Warehouse* warehouses) {
    char warehouseName[50];
    char itemName[50];
    clock_t start = clock(); // Start timer
    printf("Enter warehouse name: ");
    scanf_s("%s", warehouseName, sizeof(warehouseName));
    printf("Enter item name to search: ");
    scanf_s("%s", itemName, sizeof(itemName));
    clock_t start = clock(); // Start timer
    Warehouse* warehouse = findWarehouse(warehouses, warehouseName);
    if (warehouse != NULL) {
        Item* item = searchItemInWarehouse(warehouse, itemName);
        if (item != NULL) {
            printf("Item '%s' found in warehouse '%s'. Quantity: %d\n", itemName, warehouseName, item->quantity);
        }
        else {
            printf("Item '%s' not found in warehouse '%s'.\n", itemName, warehouseName);
        }
    }
    else {
        printf("Warehouse '%s' not found.\n", warehouseName);
    }
    clock_t end = clock(); // Stop timer
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds.\n", cpu_time_used);
}

void removeItemMenu(Warehouse* warehouses) {
    char warehouseName[50];
    char itemName[50];
    clock_t start = clock(); // Start timer
    printf("Enter warehouse name: ");
    scanf_s("%s", warehouseName, sizeof(warehouseName));
    printf("Enter item name to remove: ");
    scanf_s("%s", itemName, sizeof(itemName));
    clock_t start = clock(); // Start timer
    Warehouse* warehouse = findWarehouse(warehouses, warehouseName);
    if (warehouse != NULL) {
        removeItemFromWarehouse(warehouse, itemName);
        printf("Item '%s' removed from warehouse '%s'.\n", itemName, warehouseName);
    }
    else {
        printf("Warehouse '%s' not found.\n", warehouseName);
    }
    clock_t end = clock(); // Stop timer
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds.\n", cpu_time_used);
}

int main() {
    Warehouse* warehouses = NULL;
    int choice;
    do {
        printMenu();
        printf("Enter your choice: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            addWarehouseMenu(&warehouses);
            break;
        case 2:
            addItemMenu(warehouses);
            break;
        case 3:
            printInventoryMenu(warehouses);
            break;
        case 4:
            searchItemMenu(warehouses);
            break;
        case 5:
            removeItemMenu(warehouses);
            break;
        case 6:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
            break;
        }
    } while (choice != 6);

    // Free memory for warehouses
    deleteAllWarehouses(&warehouses);

    return 0;
}
