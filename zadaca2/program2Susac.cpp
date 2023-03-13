#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Database {
    Database(int m);

    vector<bool> container;

    int h1(const string& s);
    int h2(const string& s);
    int h3(const string& s);
    int h4(const string& s);

    void insert(const string& username);
    string search(const string &username);
};

Database::Database(int m) {
    container.resize(m, false);
}

int Database::h1(const string &s) {
    unsigned long long sum = 0;
    int m = container.size();
    for (int i = 0; i < s.size(); ++i)
        sum += s[i] % m;

    return sum % m;
}

int Database::h2(const string &s) {
    unsigned long long sum = 0;
    int m = container.size();
    for (int i = 0; i < s.size(); ++i)
        sum += (s[i] * int(pow(19, i))) % m;

    return (1 + sum) % m;
}

int Database::h3(const string &s) {
    unsigned long long sum = 0;
    int m = container.size();
    for (int i = 0; i < s.size(); ++i)
        sum += (s[i] * int(pow(30, i))) % m;

    return (7 + sum) % m;
}

int Database::h4(const string &s) {
    unsigned long long sum = 0;
    int m = container.size();
    for (int i = 0; i < s.size(); ++i)
        sum += (s[i] * int(pow(3, i)) * int(pow(7, i))) % m;

    return (3 + sum) % m;
}

void Database::insert(const string &username) {
    container[h1(username)] = true;
    container[h2(username)] = true;
    container[h3(username)] = true;
    container[h4(username)] = true;
}

string Database::search(const string &username) {
    string fail = "Element nije u tablici.";
    string succ = "Element je vjerojatno u tablici.";

    if (!container[h1(username)])
        return fail;
    if (!container[h2(username)])
        return fail;
    if (!container[h3(username)])
        return fail;
    if (!container[h4(username)])
        return fail;

    return succ;
}

int main() {
    Database db(100);

    vector<string> names = {
            "jopis107", "hstranput", "Matej293", "MateaCucman", "JosipCestar",
            "lanamak", "DanijelaValjak", "filipuranjek", "domagojziros", "lsanic",
            "TomislavVinkovic", "IvoSusac", "matej2810", "KresimirSecan",
            "inespejic", "InesSimunovic", "IvanFrantal", "Frle001", "inesstrapac",
            "mkolak", "Dpritisa", "istvavk", "mtoldi", "lbrodar5", "mkristic",
            "andreamatasovic", "balentovicanja", "IvanaVinkovic", "prakidzija",
            "DMV1204", "JMesaric", "KarloKampic", "jurick1910", "LarisaDarojkovic"
    };

    for (auto name : names)
        db.insert(name);


    cout << db.search("IvoSusac") << endl;
    cout << db.search("IvoSule") << endl;
    cout << db.search("JosipCestar") << endl;
    cout << db.search("JosipCes") << endl;
    cout << db.search("alomali") << endl;
    cout << db.search("alomali1") << endl;
    cout << db.search("cantomax") << endl;



    return 0;
}