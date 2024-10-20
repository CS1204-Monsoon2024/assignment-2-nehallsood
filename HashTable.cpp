#include <vector>
#include <iostream>

using namespace std;

class HashTable {
private:
    vector<int> table;
    int currentSize;
    int numElements;

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    void resizeTable() {
        int newSize = nextPrime(2 * currentSize);
        vector<int> oldTable = table;
        table.clear();
        table.resize(newSize, -1);
        currentSize = newSize;
        numElements = 0;

        int oldSize = oldTable.size();
        for (int i = 0; i < oldSize; ++i) {
            int key = oldTable[i];
            if (key != -1) {
                insert(key);
            }
        }
    }


public:
    HashTable(int size) {
        currentSize = size;
        table.resize(size, -1);
        numElements = 0;
    }

    void insert(int key) {
        if ((float)numElements / currentSize > 0.8) {
            resizeTable();
        }

        int hashIndex = key % currentSize;
        int i = 0;
        int probingLimit = (currentSize + 1) / 2;

        while (table[(hashIndex + i * i) % currentSize] != -1 &&
               table[(hashIndex + i * i) % currentSize] != key) {
            i++;
            if (i > probingLimit) {
                cout << "Max probing limit reached!" << endl;
                return;
            }
        }

        if (table[(hashIndex + i * i) % currentSize] == key) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        table[(hashIndex + i * i) % currentSize] = key;
        numElements++;
    }

    void remove(int key) {
        int hashIndex = key % currentSize;
        int i = 0;
        int probingLimit = (currentSize + 1) / 2;

        while (table[(hashIndex + i * i) % currentSize] != key) {
            i++;
            if (i > probingLimit || table[(hashIndex + i * i) % currentSize] == -1) {
                cout << "Element not found" << endl;
                return;
            }
        }

        table[(hashIndex + i * i) % currentSize] = -1;
        numElements--;
    }

    int search(int key) {
        int hashIndex = key % currentSize;
        int i = 0;
        int probingLimit = (currentSize + 1) / 2;

        while (table[(hashIndex + i * i) % currentSize] != key) {
            i++;
            if (i > probingLimit || table[(hashIndex + i * i) % currentSize] == -1) {
                return -1;
            }
        }

        return (hashIndex + i * i) % currentSize;
    }

    void printTable() {
        for (int i = 0; i < currentSize; i++) {
            if (table[i] == -1)
                cout << "- ";
            else
                cout << table[i] << " ";
        }
        cout << endl;
    }
};