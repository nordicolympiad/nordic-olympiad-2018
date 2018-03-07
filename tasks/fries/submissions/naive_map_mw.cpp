#include <bits/stdc++.h>

using namespace std;

int main() {
    int P, T;
    double L;
    cin >> P >> T >> L;
    vector<map<int, double>> fries(T+1);
    for (int i = 0; i < P; i++) {
        int p;
        cin >> p;
        fries[0][p] = 1;
    }
    for (int i = 0; i < T; i++) {
        for (const auto& it : fries[i]) {
            fries[i+1][it.first-1] += it.second / 2;
            fries[i+1][it.first+1] += it.second / 2;
        }
    }
    int ans = 0;
    for (const auto& it : fries[T]) {
        if (it.second >= L)
            ++ans;
    }
    cout << ans << endl;
}
