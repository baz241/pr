/*
#include <iostream>
#include <vector>

using namespace std;

int main() {
    const vector<int> v = {6, 18, 2093};
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << endl;
    }
}
*/

/*
#include <iostream>
#include <vector>

using namespace std;

int main() {
    const vector<int> v = {6, 18, 2093};
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << endl;
    }
}
*/

/*
#include <iostream>
#include <map>

using namespace std;

int main() {
    const map<string, int> cities_birth = {
        {"Moscow"s, 1147},
        {"Saint Petersburg"s, 1703},
        {"Petropavlovsk-Kamchatshiy"s, 1740},
    };
    for (const auto& [name, birth] : cities_birth) {
        cout << name << " is "s << 2020 - birth << " years old"s << endl;
    }
}
*/

/*
#include <iostream>
#include <string>
#include <vector>
    
using namespace std;

vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == ' ') {
            continue;
        }
        const size_t space_pos = text.find(' ', i);
        if (space_pos == text.npos) {
            words.push_back(text.substr(i));
            break;
        } else {
            words.push_back(text.substr(i, space_pos - i));
            i = space_pos;
        }
    }
    return words;
}

int main() {
    const string query = "hello kitty"s;
    for (const auto& word : SplitIntoWords(query)) {
        cout << '[' << word << ']' << endl;
    }
}
*/

/*
using namespace std;

class Rational {
public:
    Rational() {
        numerator_ = 0;
        denominator_ = 1;
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }
    
    void SetNumerator(int numerator) {
        numerator_ = numerator;
    }

    void SetDenominator(int denominator) {
        if (denominator != 0) {
            denominator_ = denominator;
        }
    }

private:
    int numerator_;
    int denominator_;
};
*/


#include <string>

using namespace std;

enum class AnimalType {
    Cat,
    Dog,
    Mouse,
};

class Animal {
public:
    Animal() = default;

    Animal(AnimalType type, const string& name, const string& owner_name) {
        type_ = type;
        name_ = name;
        owner_name_ = owner_name;
    }

    AnimalType GetType() const {
        return type_;
    }

    const string& GetName() const {
        return name_;
    }

    const string& GetOwnerName() const {
        return owner_name_;
    }

private:
    AnimalType type_ = AnimalType::Cat;
    string name_ = "Boris"s;
    string owner_name_ = "Ivan"s;
};