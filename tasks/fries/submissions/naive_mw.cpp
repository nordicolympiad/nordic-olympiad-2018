#include <bits/stdc++.h>

using namespace std;

int main() {
    int P, T;
    double L;
    cin >> P >> T >> L;
    vector<vector<double>> fries(T+1, vector<double>(301));
    for (int i = 0; i < P; i++) {
        int p;
        cin >> p;
        p += 100;
        fries[0][p] = 1;
    }
    for (int i = 0; i < T; i++) {
        for (int j = 1; j < 300; j++) {
            fries[i+1][j-1] += fries[i][j] / 2;
            fries[i+1][j+1] += fries[i][j] / 2;
        }
    }
    int ans = 0;
    for (int j = 0; j <= 300; j++) {
        if (fries[T][j] >= L)
            ++ans;
    }
    cout << ans << endl;
}
