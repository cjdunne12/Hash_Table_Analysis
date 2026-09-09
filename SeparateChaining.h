#ifndef HASHING_SEPARATECHAINING_H
#define HASHING_SEPARATECHAINING_H

#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <vector>
using std::cout, std::endl, std::list, std::nullopt, std::optional, std::string, std::vector;

template<typename Keyable>
class SeparateChaining {
private:
    struct pair {
        string key;
        Keyable value;

        // Overload == operator
        friend bool operator == (const pair& left, const pair& right) {
            return left.key == right.key;
        }
    };
    unsigned long collisions = 0;
    vector<list<pair>> table;

    unsigned long hornerHash(string key) const {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % table.size();
    }

    // Find the next prime number
    int nextPrime(int n) {
        if (n % 2 == 0) {
            ++n;
        }
        bool prime = false;
        while (!prime) {
            prime = true;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    prime = false;
                }
            }
            n += 2;
        }
        return (n-2);
    }

public:
    // Constructor
    SeparateChaining(unsigned long tableSize) {
        // This will fill the table with empty lists
        table.resize(nextPrime(tableSize));
    }

    // Insert
    bool insert(string key, Keyable item) {
        if (!find(key)) {
            unsigned long index = hornerHash(key);

            collisions+= table[index].size();

            table[index].push_back({key, item});
            return true;
        }
        return false;
    }

    // Find
    optional<Keyable> find(string key) const {
        unsigned long index = hornerHash(key);
        for (const pair& p : table[index]) {
            if (p.key == key) {
                return p.value;
            }
        }
        return nullopt;
    }

    // Remove
    bool remove(string key) {
        unsigned long index = hornerHash(key);
        for (pair& p : table[index]) {
            if (p.key == key) {
                table[index].remove(p);
                return true;
            }
        }
        return false;
    }

    // Prints the table
    void printTable() const {
        cout << "Beginning of table" << endl;
        for (unsigned long i = 0; i < table.size(); ++i) {
            cout << i << ": ";
            for (const pair& p : table[i]) {
                if (p == *table[i].begin()) {
                    cout << p.value;
                } else {
                    cout << ", " << p.value;
                }
            }
            cout << endl;
        }
        cout << "End of table" << endl;
    }

    unsigned long getCollisions() const {
        return collisions;
    }
};

#endif
