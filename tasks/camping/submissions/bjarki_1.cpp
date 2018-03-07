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

int main() {
    cin.sync_with_stdio(false);
    int n,m;
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
            rep(sz,0,n+1) {
                if (i+sz-1 < n && j + sz-1 < n) {
                    if (querysm(i,i+sz-1, j,j+sz-1) == 0) {
                        rep(x,0,sz) {
                            rep(y,0,sz) {
                                mx[i+x][j+y] = max(mx[i+x][j+y], sz);
                            }
                        }
                    }
                }
            }
        }
    }

    int qs;
    cin >> qs;
    rep(q,0,qs) {
        int x,y;
        cin >> x >> y;
        x--, y--;
        cout << mx[x][y]*mx[x][y] << endl;
    }

    return 0;
}

