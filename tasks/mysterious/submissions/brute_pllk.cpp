#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, q;
int a[101010];
int b[101010];
int x[101010];
int cc;

int main() {
    cin >> n >> q;
    for (int i = 1; i <= q; i++) {
        cin >> a[i] >> b[i] >> x[i];
    }
    vector<int> v;
    for (int i = 1; i <= n; i++) v.push_back(i);
    do {
        bool ok = true;
        for (int i = 1; i <= q; i++) {
            int u = v[a[i]-1];
            for (int j = a[i]; j <= b[i]; j++) {
                u = min(u,v[j-1]);
            }
            if (u != x[i]) ok = false;
        }
        if (ok) cc++;
    } while (next_permutation(v.begin(),v.end()));
    cout << cc << "\n";
}
