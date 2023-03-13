#include <iostream>
#include <list>
#include <random>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

vector<int> extractDigits(int number) {
    vector<int> digits;

    if (number == 0)
        return {0};

    while (number > 0) {
        digits.push_back(number % 10);
        number /= 10;
    }

    return digits;
};

template<typename V>
struct HashTable {
    HashTable();

    vector<list<pair<int, V>>> container;
    vector<int> randomVars;

    void insert(int key, V value);
    pair<int, V> search(int key);

    int hash(int key);

};

template<typename V>
HashTable<V>::HashTable() {
    default_random_engine generator(time(0));
    uniform_int_distribution<int> distribute(0, 6);

    for (int i = 0; i < 7; ++i)
        randomVars.push_back(distribute(generator));

    container.resize(7);
}

template<typename V>
int HashTable<V>::hash(int key) {
    vector<int> digits = extractDigits(key);
    int sum = 0;

    for (int i = 0; i < digits.size(); ++i)
        sum += randomVars[i] * digits[i];

    return sum % 7;
}

template<typename V>
void HashTable<V>::insert(int key, V value) {
    int h = hash(key);

    auto it = find_if(container[h].begin(), container[h].end(), [&key](const auto &p){ return p.first == key; });
    if (it != container[h].end())
        it->second = value;
    else
        container[h].push_front({key, value});
}

template<typename V>
pair<int, V> HashTable<V>::search(int key) {
    int h = hash(key);

    auto it = find_if(container[h].begin(), container[h].end(), [&key](const auto &p){ return p.first == key; });
    if (it == container[h].end()) {
        cout << "No element with key " << key << " was found.";
        return {};
    }
    else
        return *it;
}

int main() {
    HashTable<float> hashTable;

    vector<int> keys = {152, 250, 300, 5, 2, 123, 20, 85, 63, 100, 200, 0};

    float value = 0.0f;
    for (auto key : keys) {
        hashTable.insert(key, value);
        value += 0.1f;
    }

    pair<int, float> p = hashTable.search(5);

    cout << p.first << ", " << p.second << endl;


    return 0;
}