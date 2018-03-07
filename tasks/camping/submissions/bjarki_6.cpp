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

#define MAXN 2010
#define LGN 12

// char arr[MAXN][MAXN];
// int sm[MAXN][MAXN];
vector<vi> sm, mx;

int querysm(int x0, int x1, int y0, int y1) {
    int res = sm[x1+1][y1+1];
    res -= sm[x0][y1+1];
    res -= sm[x1+1][y0];
    res += sm[x0][y0];
    return res;
}

// int mx[MAXN][MAXN];
short ****st;

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
    m = max(m, (int)st[k1][x1-(1<<k1)+1][k2][y0]);
    m = max(m, (int)st[k1][x0][k2][y1-(1<<k2)+1]);
    m = max(m, (int)st[k1][x1-(1<<k1)+1][k2][y1-(1<<k2)+1]);

    return m;
}

int main() {

    cin.sync_with_stdio(false);
    cin >> n >> m;

    st = new short***[LGN];
    rep(i,0,LGN) {
        st[i] = new short**[n];
        rep(j,0,n) {
            st[i][j] = new short*[LGN];
            rep(k,0,LGN) {
                st[i][j][k] = new short[m];
            }
        }
    }

    vector<vector<char> > arr(n, vector<char>(m, '.'));
    sm = vector<vi>(n, vi(m, 0));
    mx = vector<vi>(n, vi(m, 0));
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
            int lo = 0,
                hi = n,
                res = -1;

            while (lo <= hi) {
                int sz = (lo+hi)/2;
                if (i+sz-1 < n && j + sz-1 < n && querysm(i,i+sz-1, j,j+sz-1) == 0) {
                    lo = sz+1;
                    res = sz;
                } else {
                    hi = sz-1;
                }
            }

            assert(res != -1);
            mx[i][j] = res;
        }
    }

    rep(k1,0,LGN) {
        rep(i,0,n) {
            rep(k2,0,LGN) {
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

        int lo = 0,
            hi = n,
            res = -1;
        while (lo <= hi) {
            int best = (lo+hi)/2;
            if (querymx(x-best+1, x, y-best+1, y) >= best) {
                lo = best + 1;
                res = best;
            } else  {
                hi = best - 1;
            }
        }
        assert(res != -1);
        cout << res*res << endl;
    }

    return 0;
}

