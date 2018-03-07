#include <vector>
#include <map>
#include <iostream>

#define MAXWIDTH 100000
#define PRECISION 0.8

using namespace std;

struct Event {
    int index;
    double value;

    Event(int _index, double _value) : index(_index), value(_value) {
    }

    bool operator<(const Event& other) const {
        return index < other.index;
    }
};

struct Input {
    vector<int> origins;
    double L;
    int T;
};

Input readInput() {
    Input input;
    int P;
    cin >> P >> input.T >> input.L;
    input.L *= 0.9;
    input.origins.resize(P);
    for (int i = 0; i < P; i++) {
        cin >> input.origins[i];
    }
    return input;
}

vector<double> precomputeDistribution(int T) {
    vector<double> p(MAXWIDTH);
    p[0] = 1.0;
    int k = (T + 1)/2;
    double sum;
    if (T%2 == 1)
        sum = 2*p[0];
    else
        sum = p[0];
    for (int i = 1; i < MAXWIDTH; i++) {
        p[i] = (p[i-1] * (T - k)) / (k + 1);
        k++;
        sum += 2*p[i];
        if (p[i] < 1e-12)
            p[i] = 0;
    }
    for (int i = 0; i < MAXWIDTH; i++) {
        p[i] /= sum;
    }
    return p;
}

vector<Event> generateEvents(int T, const vector<double>& distribution) {
    vector<Event> events;
    double currentVal = distribution[0];
    for (size_t i = 0; i < distribution.size(); i++) {
        if (distribution[i] < currentVal * PRECISION) {
            events.emplace_back(2*(i-1) + (T%2), currentVal);
            currentVal = distribution[i] * PRECISION;
        }
    }
    vector<Event> allEvents;
    for (size_t i = events.size(); i--; ) {
        allEvents.emplace_back(-events[i].index, events[i].value);
    }
    for (size_t i = 1; i < events.size(); i++) {
        allEvents.emplace_back(events[i-1].index+2, events[i].value);
    }
    allEvents.emplace_back(events.back().index+2, 0);
    return allEvents;
}

int main() {
    ios_base::sync_with_stdio(false);
    auto input = readInput();
    auto distribution = precomputeDistribution(input.T);
    auto events = generateEvents(input.T, distribution);
    int ans = 0;
    for (int parity = 0; parity < 2; ++parity) {
        const int MAX_SIZE = 10000000, PAD = 200000;
        vector<double> difference((MAX_SIZE + 2*PAD) / 2);

        for (int origin : input.origins) {
            if (((origin + input.T)&1) != parity)
                continue;
            double currentValue = 0;
            for (const auto& event : events) {
                difference[(origin + event.index + PAD) >> 1] += event.value - currentValue;
                currentValue = event.value;
            }
        }
        double currentValue = 0;
        for (double dif : difference) {
            if (currentValue > input.L) {
                ans++;
            }
            currentValue += dif;
        }
    }
    cout << ans << endl;
}
