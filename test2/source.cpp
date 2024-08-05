#include <iostream>
#include <vector>
#include <set>

using namespace std;

template <typename Element>
ostream& operator<<(ostream& out, const vector<Element>& container);
template <typename Element>
ostream& operator<<(ostream& out, const set<Element>& container);

template <typename Container>
void Print(ostream& out, const Container& container) {
    bool is_first = true;
    for (const auto& element : container) {
        if (is_first) {
            out << element;
            is_first = false;
            continue;
        }
        out << ", "s << element;
    }
}

template <typename Type>
ostream& operator<<(ostream& out, const vector<Type>& container) {
    Print(out, container);
    return out;
}

template <typename Type>
ostream& operator<<(ostream& out, const set<Type>& container) {
    Print(out, container);
    return out;
}

int main() {
    const set<string> cats = {"Мурка"s, "Белка"s, "Георгий"s, "Рюрик"s};
    cout << cats << endl; 
    return 0;
}