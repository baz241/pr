#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    string typeStr;
    is >> typeStr;
    if (typeStr == "NEW_BUS"s) {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count = 0;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (auto& stop : q.stops) {
            is >> stop;
        }
    } else if (typeStr == "BUSES_FOR_STOP"s) {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (typeStr == "STOPS_FOR_BUS"s) {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop"s;
        return os;
    }
    bool is_first = true;
    for (const auto& bus : r.buses) {
        if (!is_first) {
            os << " "s;
        }
        is_first = false;
        os << bus;
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<pair<string, vector<string>>> stops_for_buses;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    if (r.stops_for_buses.empty()) {
        os << "No bus"s;
    } else {
        bool first = true;
        for (const auto& stop_and_buses : r.stops_for_buses) {
            if (!first) {
                os << endl;
            }
            first = false;
            os << "Stop "s << stop_and_buses.first << ":"s;
            if (stop_and_buses.second.size() == 1) {
                os << " no interchange"s;
            } else {
                for (const auto& bus : stop_and_buses.second) {
                    if (bus != r.bus) {
                        os << " "s << bus;
                    }
                }
            }
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    if (r.buses_to_stops.empty()) {
        return os;
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод

    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
    }
private:

};

void TestQueryInput() {
    istringstream input;
    Query q;

    input.str("NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"s);
    input >> q;
    assert(q.type == QueryType::NewBus);
    assert(q.bus == "32"s);
    vector<string> test = {"Tolstopaltsevo"s, "Marushkino"s, "Vnukovo"s};
    assert(q.stops == test);

    input.clear();
    input.str("BUSES_FOR_STOP Marushkino"s);
    input >> q;
    assert(q.type == QueryType::BusesForStop);
    assert(q.stop == "Marushkino"s);

    input.clear();
    input.str("STOPS_FOR_BUS 32K"s);
    input >> q;
    assert(q.type == QueryType::StopsForBus);
    assert(q.bus == "32K"s);

    input.clear();
    input.str("ALL_BUSES"s);
    input >> q;
    assert(q.type == QueryType::AllBuses);
}

void TestBusesForStopResponseOutput() {
    ostringstream output;

    BusesForStopResponse p = {{"a1"s, "b123"s, "z12312"s}};
    output << p;
    assert(output.str() == "a1 b123 z12312"s);
}

void TestAll() {
    TestQueryInput();
    TestBusesForStopResponseOutput();
}

// Реализуйте функции и классы, объявленные выше, чтобы эта функция main
// решала задачу "Автобусные остановки"

int main() {
    TestAll();
    return 0;
    // int query_count;
    // Query q;

    // cin >> query_count;

    // BusManager bm;
    // for (int i = 0; i < query_count; ++i) {
    //     cin >> q;
    //     switch (q.type) {
    //         case QueryType::NewBus:
    //             bm.AddBus(q.bus, q.stops);
    //             break;
    //         case QueryType::BusesForStop:
    //             cout << bm.GetBusesForStop(q.stop) << endl;
    //             break;
    //         case QueryType::StopsForBus:
    //             cout << bm.GetStopsForBus(q.bus) << endl;
    //             break;
    //         case QueryType::AllBuses:
    //             cout << bm.GetAllBuses() << endl;
    //             break;
    //     }
    // }
}