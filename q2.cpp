#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>

// Function to generate a dataset of 1000 random integers
std::vector<int> generateDataSet(int size = 1000, int min_value = 1000, int max_value = 9999) {
    std::vector<int> dataset;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min_value, max_value);
    
    for (int i = 0; i < size; ++i) {
        dataset.push_back(dist(gen));
    }
    
    return dataset;
}

// Hash function 1: h(x) = x % 50
int hashModulo(int x) {
    return x % 50;
}

// Hash function 2: h(x) = ((a * x + b) % p) % 50
int hashLinear(int x, int a, int b, int prime_modulus) {
    return ((a * x + b) % prime_modulus) % 50;
}

// Function to evaluate the hash function and count the frequency of hash values
std::unordered_map<int, int> evaluateHashFunction(const std::vector<int>& dataset, int (*hashFunction)(int, int, int, int), int a = 0, int b = 0, int prime_modulus = 50) {
    std::unordered_map<int, int> hash_distribution;
    
    for (int x : dataset) {
        int hash_value = hashFunction(x, a, b, prime_modulus);
        hash_distribution[hash_value]++;
    }
    
    return hash_distribution;
}

// Helper function to print hash distributions
void printHashDistribution(const std::unordered_map<int, int>& distribution) {
    for (const auto& pair : distribution) {
        std::cout << "Hash Value: " << pair.first << " -> Count: " << pair.second << std::endl;
    }
}

// Simple wrapper to make hashModulo compatible with evaluateHashFunction
int hashModuloWrapper(int x, int, int, int) {
    return hashModulo(x);
}

int main() {
    // Step 1: Generate a dataset of 1000 random integers
    std::vector<int> dataset = generateDataSet();

    // Constants for hashLinear function (hash function 2)
    int prime_modulus = 100003;  // A large prime number
    int coefficient_a = rand() % (prime_modulus - 1) + 1;  // Random 'a' from [1, prime_modulus-1]
    int constant_b = rand() % prime_modulus;  // Random 'b' from [0, prime_modulus-1]

    // Evaluate hash function 1 (h(x) = x % 50)
    std::cout << "Evaluating hash function 1: h(x) = x % 50..." << std::endl;
    auto hash_modulo_distribution = evaluateHashFunction(dataset, hashModuloWrapper);
    printHashDistribution(hash_modulo_distribution);

    // Evaluate hash function 2 (h(x) = ((a * x + b) % p) % 50)
    std::cout << "\nEvaluating hash function 2: h(x) = ((a * x + b) % p) % 50..." << std::endl;
    auto hash_linear_distribution = evaluateHashFunction(dataset, hashLinear, coefficient_a, constant_b, prime_modulus);
    printHashDistribution(hash_linear_distribution);

    return 0;
}