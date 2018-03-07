// small optimization
#include <iostream>

using namespace std;

#define M 1000000007

typedef long long ll;

int n, q;
int a[101010];
int b[101010];
int x[101010];

bool seen[101010];
int minx[101010];
int maxx[101010];
int ming[101010];
int inc[101010];

ll result = 1;

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) ming[i] = 1;
    for (int i = 1; i <= q; i++) {
        cin >> a[i] >> b[i] >> x[i];
        if (!seen[x[i]]) {
            seen[x[i]] = true;
            minx[x[i]] = a[i];
            maxx[x[i]] = b[i];
        }
        minx[x[i]] = max(minx[x[i]],a[i]);
        maxx[x[i]] = min(maxx[x[i]],b[i]);
        for (int j = a[i]; j <= b[i]; j++) {
            ming[j] = max(ming[j],x[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        inc[ming[i]]++;
    }
    int amount = 0;
    for (int i = 1; i <= n; i++) {
        amount += inc[i];
        if (seen[i]) {
            int choices = 0;
            for (int j = minx[i]; j <= maxx[i]; j++) {
                if (ming[j] <= i) choices++;
            }
            result *= choices;
        } else {
            result *= amount;
        }
        amount--;
        result %= M;
    }
    cout << result << "\n";
}
