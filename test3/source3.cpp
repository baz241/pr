#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

struct Point {
    int x = 0;
    int y = 0;
};

ostream& operator<<(ostream& output, Point p) {
    output << p.x << ' ' << p.y;
    return output;
}

istream& operator>>(istream& input, Point& p) {
    input >> p.x >> p.y;
    return input;
}

void TestPointOutput() {
    Point p = {15, -8};
    ostringstream output;
    output << p;
    cout << p << endl;
    // Метод str() возвращает строку с содержимым, выведенным в ostringstream
    // assert(output.str() == "15 -8"s);
}

void TestPointInput() {
    istringstream input;
    // Метод str(строка) у istringstream позволяет задать содержимое, которое будет считываться из istringstream
    input.str("-9 33"s);
    Point p;
    input >> p;
    cout << p.x << endl << p.y << endl;
    // assert(p.x == -9);
    // assert(p.y == 33);
}

int main() {
    TestPointOutput();
    TestPointInput();
}