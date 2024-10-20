#include <iostream>
#include <vector>
using namespace std;

// helper function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// helper function to find the next prime number greater than or equal to `n`
int nextPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

class HashTable {
private:
    vector<int> table;   // The hash table itself
    int size;            // The current capacity of the table
    int count;           // Number of elements currently in the table
    const int EMPTY = -1;   // Empty slot
    const int DELETED = -2; // Deleted slot
    const double LOAD_FACTOR = 0.8; // Load factor threshold for resizing

    // Hash function
    int hash(int key) {
        return key % size;
    }

    // Resize the hash table when load factor exceeds threshold
    void resize() {
        int newSize = nextPrime(size * 2); // Resize to at least twice the size
        vector<int> newTable(newSize, EMPTY);

        // Rehash existing elements into new table
        for (int i = 0; i < size; i++) {
            if (table[i] != EMPTY && table[i] != DELETED) {
                int key = table[i];
                int idx = key % newSize;
                int step = 1;
                while (newTable[idx] != EMPTY) {
                    idx = (idx + step * step) % newSize;
                    step++;
                }
                newTable[idx] = key;
            }
        }
        table = newTable;
        size = newSize;
    }

public:
    // Constructor
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table.resize(size, EMPTY);
        count = 0;
    }

    // Insert function
    void insert(int key) {
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        if (count >= size * LOAD_FACTOR) {
            resize();
        }

        int idx = hash(key);
        int step = 1;
        int startIdx = idx;

        while (table[idx] != EMPTY && table[idx] != DELETED) {
            idx = (startIdx + step * step) % size;
            step++;

            if (step >= size) {
                cout << "Max probing limit reached!" << endl;
                return;
            }
        }

        table[idx] = key;
        count++;
    }

    // Remove function
    void remove(int key) {
        int idx = search(key);
        if (idx == -1) {
            cout << "Element not found" << endl;
            return;
        }
        table[idx] = DELETED;
        count--;
    }

    // Search function
    int search(int key) {
        int idx = hash(key);
        int step = 1;
        int startIdx = idx;

        while (table[idx] != EMPTY) {
            if (table[idx] == key) {
                return idx;
            }
            idx = (startIdx + step * step) % size;
            step++;

            if (step >= size) {
                break;
            }
        }
        return -1; // Key not found
    }

    // Print function
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == EMPTY || table[i] == DELETED) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};


