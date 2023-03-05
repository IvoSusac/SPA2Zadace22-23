#include <iostream>
#include <vector>

using namespace std;

template<typename V>
class Dictionary {
private:
    vector<pair<int, V>> container;
    int size = 0;
public:
    Dictionary();
    Dictionary(int s);

    ~Dictionary();

    int hash(int k, int i);
    typename vector<pair<int, V>>::iterator search(int key) const;
    bool insert(int key, V value);
    bool remove(int key);
    void print() const;

    typename vector<pair<int, V>>::iterator begin() const;
    typename vector<pair<int, V>>::iterator end() const;

};

template<typename V>
Dictionary<V>::Dictionary() {}

template<typename V>
Dictionary<V>::Dictionary(int s) {
    for (int i = 0; i < s; ++i) {
        container.push_back({-1, V()});
    }
}

template<typename V>
Dictionary<V>::~Dictionary() {}

template<typename V>
int Dictionary<V>::hash(int k, int i) {
    int m = container.size();
    int h1 = k % m;
    int h2 = i * (1 + (k % (m - 1)));
    return (h1 + h2) % m;
}

template<typename V>
typename vector<pair<int, V>>::iterator Dictionary<V>::search(int key) const {
    int i = 0;
    while (true) {
        int h = hash(key, i);
        if (container[h].first == -1)
            return container.end();
        else if (container[h].first == key)
            return container.begin() + h;
        ++i;
    }
}

template<typename V>
bool Dictionary<V>::insert(int key, V value) {
    if (size < container.size()) {
        int i = 0;
        while (true) {
            int h = hash(key, i);
            if (container[h].first == -1) {
                container[h].first = key;
                container[h].second = value;
                ++size;
                return true;
            }
            else if (container[h].first == key) {
                container[h].second = value;
                return true;
            }
            ++i;
        }
    }
    else return false;
}

template<typename V>
bool Dictionary<V>::remove(int key) {
    int i = 0;
    while(true) {
        int h = hash(key, i);
        if (container[h].first == -1)
            return false;
        else if (container[h].first == key) {
            container[h].first = -1;
            container[h].second = V();
            return true;
        }
        i++;
    }
}

template<typename V>
void Dictionary<V>::print() const {
    for (pair<int, V> p : container) {
        if (p.first == -1)
            cout << "nil ";
        else
            cout << "K:" << p.first << " V:" << p.second << " ";
    }
    cout << endl;
}

template<typename V>
typename vector<pair<int, V>>::iterator Dictionary<V>::begin() const {
    return container.begin();
}

template<typename V>
typename vector<pair<int, V>>::iterator Dictionary<V>::end() const {
    return container.end();
}

int main()
{
    vector<int> keys(10);
    vector<float> values {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f};

    Dictionary<float> dict(19);

    for (int i = 0; i < 10; ++i)
        cin >> keys[i];

    for (int i = 0; i < 10; ++i)
        dict.insert(keys[i], values[i]);

    dict.remove(keys[6]);
    dict.insert(keys[2], 1.1);
    dict.print();

    return 0;
}






