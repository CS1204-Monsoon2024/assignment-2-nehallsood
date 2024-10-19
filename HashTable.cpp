#include <iostream>
#include <vector>
using namespace std;

// Helper function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false; // Numbers less than or equal to 1 are not prime
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false; // If divisible by any number, it's not prime
    }
    return true; // Otherwise, it's prime
}

// Helper function to find the next prime number greater than or equal to `n`
int nextPrime(int n) {
    while (!isPrime(n)) {
        n++; // Keep increasing n until a prime number is found
    }
    return n;
}

class HashTable {
private:
    vector<int> table;   // The hash table itself, represented as a vector of integers
    int size;            // The current capacity of the table (how many slots it has)
    int count;           // Number of elements currently in the table
    const int EMPTY = -1;  // Value representing an empty slot in the table
    const int DELETED = -2;// Value representing a deleted slot in the table
    const double LOAD_FACTOR = 0.8; // Maximum load factor before resizing (80% full)

    // Simple hash function: returns the key modulo the size of the table
    int hash(int key) {
        return key % size;
    }

    // Resize the hash table when it becomes too full. The new size will be a prime number
    // at least twice as big as the current one.
    void resize() {
        int newSize = nextPrime(size * 2); // Find the next prime number that's twice the size
        vector<int> newTable(newSize, EMPTY); // Create a new table with all slots empty

        // Move all existing elements to the new table using the new size
        for (int i = 0; i < size; i++) {
            if (table[i] != EMPTY && table[i] != DELETED) {
                int key = table[i]; // Get the existing key
                int idx = key % newSize; // Compute the hash for the new table size
                int step = 1;
                while (newTable[idx] != EMPTY) {
                    // Use quadratic probing to find the next available slot
                    idx = (idx + step * step) % newSize;
                    step++;
                }
                newTable[idx] = key; // Insert the key into the new table
            }
        }
        table = newTable; // Replace the old table with the new, larger one
        size = newSize;   // Update the table size
    }

public:
    // Constructor: Initialize the hash table with a given initial size
    HashTable(int initialSize) {
        size = nextPrime(initialSize);    // Make sure the size is a prime number
        table.resize(size, EMPTY);        // Create the table with all slots empty
        count = 0;                        // Start with no elements in the table
    }

    // Insert a new element into the table
    void insert(int key) {
        // First, check if the key is already in the table
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        // If the table is too full (load factor exceeds 80%), resize it
        if (count >= size * LOAD_FACTOR) {
            resize();
        }

        int idx = hash(key); // Compute the hash index for the new key
        int step = 1;
        int startIdx = idx;

        // Quadratic probing: find the next available slot if the current one is taken
        while (table[idx] != EMPTY && table[idx] != DELETED) {
            idx = (startIdx + step * step) % size;
            step++;

            if (step >= size) {  // If we've probed all possible slots, stop
                cout << "Max probing limit reached!" << endl;
                return;
            }
        }

        // Insert the new key into the available slot
        table[idx] = key;
        count++; // Increment the element count
    }

    // Remove a key from the table
    void remove(int key) {
        int idx = search(key); // Find the index of the key
        if (idx == -1) {
            // If the key wasn't found, print a message and stop
            cout << "Element not found" << endl;
            return;
        }

        // Mark the slot as deleted, so it can be reused later
        table[idx] = DELETED;
        count--; // Decrease the element count
    }

    // Search for a key in the table and return its index, or -1 if not found
    int search(int key) {
        int idx = hash(key); // Compute the hash index for the key
        int step = 1;
        int startIdx = idx;

        // Quadratic probing: keep searching if the key isn't at the current index
        while (table[idx] != EMPTY) {
            if (table[idx] == key) {
                return idx; // Key found, return the index
            }
            idx = (startIdx + step * step) % size;
            step++;

            if (step >= size) {  // If we've searched the entire table, stop
                break;
            }
        }

        return -1;  // Key not found, return -1
    }

    // Print the current state of the hash table
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == EMPTY || table[i] == DELETED) {
                // Print a dash for empty or deleted slots
                cout << "- ";
            } else {
                // Print the actual value for filled slots
                cout << table[i] << " ";
            }
        }
        cout << endl; // End the line after printing the table
    }
};
int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}