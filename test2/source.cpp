#include <iostream>
#include <string>

using namespace std;

// Определяет, будет ли слово палиндромом
// text может быть строкой, содержащей строчные буквы английского алфавита и пробелы
// Пустые строки и строки, состоящие только из пробелов, - это не палиндромы
bool IsPalindrome(const string& text) {
    // Напишите недостающий код
    size_t start = 0;
    size_t end = 0;
    while (start != text.size() && end )
}

int main() {
    string text;
    getline(cin, text);

    cout << 1 / 2 << endl;

    // cout << text.size() / 2;

    // return 0;

    if (IsPalindrome(text)) {
        cout << "palindrome"s << endl;
    } else {
        cout << "not a palindrome"s << endl;
    }
}