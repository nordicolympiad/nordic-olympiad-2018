#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;

#define M 1000000007

int n, q;
int seen[201010];
int maxa[201010];
int minb[201010];
vector<pair<int,int>> events[201010];
multiset<int> active;
int count1[201010];
int count2[201010];

void add_range(int a, int b, int x) {
    if (!seen[x]) {
        seen[x] = 1;
        maxa[x] = a;
        minb[x] = b;
    }
    maxa[x] = max(maxa[x],a);
    minb[x] = min(minb[x],b);
    events[a].push_back({1,x});
    events[b+1].push_back({-1,x});
}

int main() {
    cin >> n >> q;
    add_range(1,n,1);
    for (int i = 1; i <= q; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        add_range(a,b,x);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < events[i].size(); j++) {
            int t = events[i][j].first;
            int x = events[i][j].second;
            if (t == 1) active.insert(x);
            else active.erase(active.find(x));
        }
        int x = *active.rbegin();
        if (i >= maxa[x] && i <= minb[x]) count1[x]++;
        else count2[x]++;
    }
    ll result = 1;
    int choices = 0;
    for (int i = 1; i <= n; i++) {
        choices += count1[i];
        choices += count2[i];
        if (seen[i]) {
            result *= count1[i];
        } else {
            result *= choices;
        }
        result %= M;
        choices--;
    }
    cout << result << "\n";
}
