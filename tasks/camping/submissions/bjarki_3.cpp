#include <bits/stdc++.h>
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = 2147483647;

char arr[1010][1010];
int sm[1010][1010];

int querysm(int x0, int x1, int y0, int y1) {
    int res = sm[x1+1][y1+1];
    res -= sm[x0][y1+1];
    res -= sm[x1+1][y0];
    res += sm[x0][y0];
    return res;
}

int mx[1010][1010];

int n,m;
int querymx(int x0, int x1, int y0, int y1) {
    x0 = max(0, x0);
    x1 = min(x1, n-1);

    y0 = max(0, y0);
    y1 = min(y1, m-1);

    if (x0 > x1 || y0 > y1)
        return 0;

    int m = 0;
    rep(x,x0,x1+1) {
        rep(y,y0,y1+1) {
            m = max(m, mx[x][y]);
        }
    }

    return m;
}

int main() {
    cin.sync_with_stdio(false);
    cin >> n >> m;
    rep(i,0,n) {
        rep(j,0,m) {
            cin >> arr[i][j];
        }
    }

    rep(i,0,n) {
        rep(j,0,m) {
            sm[i+1][j+1] = arr[i][j] == '#';
            sm[i+1][j+1] += sm[i+1][j];
            sm[i+1][j+1] += sm[i][j+1];
            sm[i+1][j+1] -= sm[i][j];
        }
    }

    rep(i,0,n) {
        rep(j,0,n) {
            int sz = n;
            while (sz > 0) {
                if (i+sz-1 < n && j + sz-1 < n) {
                    if (querysm(i,i+sz-1, j,j+sz-1) == 0) {
                        break;
                    }
                }
                sz--;
            }
            mx[i][j] = sz;
        }
    }

    int qs;
    cin >> qs;
    rep(q,0,qs) {
        int x,y;
        cin >> x >> y;
        x--, y--;

        int best = n;
        while (best > 0) {
            // int m = 0;
            // rep(i,0,best) {
            //     rep(j,0,best) {
            //         if (x-i >= 0 && y-j >= 0) {
            //             m = max(m, mx[x-i][y-j]);
            //         }
            //     }
            // }
            if (querymx(x-best+1, x, y-best+1, y) >= best) {
                break;
            }
            best--;
        }

        cout << best*best << endl;
    }

    return 0;
}

