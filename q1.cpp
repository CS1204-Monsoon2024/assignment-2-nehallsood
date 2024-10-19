#include <iostream>
#include <vector>
using namespace std;

// Node class representing each element in the linked list
class Node {
public:
    int data;        // Data stored in the node
    Node* next;      // Pointer to the next node

    Node(int val) : data(val), next(nullptr) {} // Constructor for Node
};

// LinkedList class with modular hashing and basic operations
class LinkedList {
private:
    Node* head;            // Pointer to the head of the list
    int size;              // Number of elements in the list
    int hashValue;         // Hash value for the list
    const int base = 31;   // Base for the hash function
    const int mod = 1e9 + 7;  // Large prime modulus for the hash function

    vector<int> precomputedPowers;  // Precomputed powers of base mod

    // Precompute powers of base (mod) to avoid recalculating them
    void calcpower(int newSize) {
        if (precomputedPowers.size() < newSize + 1) {
            int currentSize = precomputedPowers.size();
            precomputedPowers.resize(newSize + 1);
            for (int i = currentSize; i <= newSize; i++) {
                precomputedPowers[i] = (precomputedPowers[i - 1] * base) % mod;
            }
        }
    }

public:
    // Constructor to initialize the linked list
    LinkedList() {
        head = nullptr;
        size = 0;
        hashValue = 0;
        precomputedPowers.push_back(1); // base^0 = 1
    }

    // Destructor to free all allocated memory
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Insert a new node with given data at the end of the list
    void insert(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;  // If the list is empty, set the head to the new node
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;  // Add the new node to the end of the list
        }

        // Precompute powers of base up to the new size
        calcpower(size);

        // Update the rolling hash value
        hashValue = (hashValue + value * precomputedPowers[size]) % mod;
        size++;  // Increase the size of the list
    }

    // Delete a node at the specified index
    void deleteElement(int index) {
        if (index < 0 || index >= size) {
            return;  // Index out of bounds, do nothing
        }

        Node* temp = head;
        Node* prev = nullptr;
        int i = 0;
        int value;

        // Special case: Deleting the head node
        if (index == 0) {
            value = head->data;
            head = head->next;
            delete temp;
        } else {
            // Traverse to the node at the specified index
            while (i < index) {
                prev = temp;
                temp = temp->next;
                i++;
            }

            // Delete the node
            value = temp->data;
            prev->next = temp->next;
            delete temp;
        }

        // Precompute powers of base up to the current size if necessary
        calcpower(size);

        // Update the rolling hash value by subtracting the deleted node's contribution
        hashValue = (hashValue - value * precomputedPowers[index]) % mod;
        if (hashValue < 0) {
            hashValue += mod;  // Ensure the hash value is positive
        }

        size--;  // Decrease the size of the list
    }

    // Check if two linked lists are equivalent by comparing hash values and elements
    bool equalityCheck(LinkedList& other) {
        // First check if the hash values are different
        if (this->hashValue != other.hashValue) {
            return false;
        }

        // If hash values are the same, compare the nodes element by element
        Node* current1 = this->head;
        Node* current2 = other.head;

        while (current1 != nullptr && current2 != nullptr) {
            if (current1->data != current2->data) {
                return false;  // If any element is different, return false
            }
            current1 = current1->next;
            current2 = current2->next;
        }

        return current1 == nullptr && current2 == nullptr;  // Both lists should end at the same time
    }

    // Print the linked list (for testing purposes)
    void print() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // Get the size of the list
    int getSize() {
        return size;
    }

    // Get the hash value of the list
    int getHash() {
        return hashValue;
    }
};

int main() {
    LinkedList list1;
    LinkedList list2;

    // Insert elements into the first list
    list1.insert(10);
    list1.insert(20);
    list1.insert(30);

    // Insert elements into the second list
    list2.insert(10);
    list2.insert(20);
    list2.insert(30);

    // Print the lists and their hash values
    cout << "List 1: ";
    list1.print();
    cout << "Hash value of List 1: " << list1.getHash() << endl;

    cout << "List 2: ";
    list2.print();
    cout << "Hash value of List 2: " << list2.getHash() << endl;

    // Check if the lists are equivalent
    if (list1.equalityCheck(list2)) {
        cout << "Lists are equivalent!" << endl;
    } else {
        cout << "Lists are not equivalent!" << endl;
    }

    // Delete a node from the first list
    list1.deleteElement(1);

    // Print the updated list and its hash value
    cout << "Updated List 1: ";
    list1.print();
    cout << "Updated Hash value of List 1: " << list1.getHash() << endl;

    return 0;
}