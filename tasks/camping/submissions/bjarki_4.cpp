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
int st[11][1010][11][1010];

int n,m;
int querymx(int x0, int x1, int y0, int y1) {
    x0 = max(0, x0);
    x1 = min(x1, n-1);

    y0 = max(0, y0);
    y1 = min(y1, m-1);

    if (x0 > x1 || y0 > y1)
        return 0;

    int k1 = 0,
        k2 = 0;
    while (x0 + (1<<(k1+1)) - 1 <= x1)
        k1++;
    while (y0 + (1<<(k2+1)) - 1 <= y1)
        k2++;

    int m = st[k1][x0][k2][y0];
    m = max(m, st[k1][x1-(1<<k1)+1][k2][y0]);
    m = max(m, st[k1][x0][k2][y1-(1<<k2)+1]);
    m = max(m, st[k1][x1-(1<<k1)+1][k2][y1-(1<<k2)+1]);

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

    rep(k1,0,11) {
        rep(i,0,n) {
            rep(k2,0,11) {
                rep(j,0,m) {
                    if (k1 == 0 && k2 == 0) {
                        st[k1][i][k2][j] = mx[i][j];
                    } else if (k1 == 0) {
                        st[k1][i][k2][j] = st[k1][i][k2-1][j];
                        if (j+(1<<(k2-1)) < m) {
                            st[k1][i][k2][j] = max(st[k1][i][k2][j], st[k1][i][k2-1][j+(1<<(k2-1))]);
                        }
                    } else if (k2 == 0) {
                        st[k1][i][k2][j] = st[k1-1][i][k2][j];
                        if (i+(1<<(k1-1)) < n) {
                            st[k1][i][k2][j] = max(st[k1][i][k2][j], st[k1-1][i+(1<<(k1-1))][k2][j]);
                        }
                    } else {
                        st[k1][i][k2][j] = st[k1-1][i][k2-1][j];
                        if (j+(1<<(k2-1)) < m) {
                            st[k1][i][k2][j] = max(st[k1][i][k2][j], st[k1-1][i][k2-1][j+(1<<(k2-1))]);
                        }
                        if (i+(1<<(k1-1)) < n) {
                            st[k1][i][k2][j] = max(st[k1][i][k2][j], st[k1-1][i+(1<<(k1-1))][k2-1][j]);
                        }
                        if (j+(1<<(k2-1)) < m && i+(1<<(k1-1)) < n) {
                            st[k1][i][k2][j] = max(st[k1][i][k2][j], st[k1-1][i+(1<<(k1-1))][k2-1][j+(1<<(k2-1))]);
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

        int best = n;
        while (best > 0) {
            if (querymx(x-best+1, x, y-best+1, y) >= best) {
                break;
            }
            best--;
        }

        cout << best*best << endl;
    }

    return 0;
}

