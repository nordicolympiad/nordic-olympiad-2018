#include <bits/stdc++.h>
#define MAXWIDTH 10000
using namespace std;

int main() {
    int P, T;
    double L;
    cin >> P >> T >> L;
    unordered_map<int, double> fries;
    auto logFactorial = [](int n) {
        if (!n)
            return 0.0;
        return log(sqrt(2*M_PI*n)) + n * (log(n) - 1);
    };
    auto distribution = [=](int diff) {
        int k = (T-diff)/2;
        double ans = logFactorial(T);
        ans -= logFactorial(k);
        ans -= logFactorial(T-k);
        return exp(ans-T*log(2));
    };
    while (P--) {
        int ind;
        cin >> ind;
        for (int i = -MAXWIDTH - (T%2); i <= MAXWIDTH; i += 2) {
            fries[ind+i] += distribution(i);
        }
    }
    int ans = 0;
    for (const auto& it : fries) {
        if (it.second >= L) {
            ans++;
        }
    }
    cout << ans << endl;
}
