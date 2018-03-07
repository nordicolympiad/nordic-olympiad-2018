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


vector<vector<int> > sm;

int querysm(int x0, int x1, int y0, int y1) {
    int res = sm[x1+1][y1+1];
    res -= sm[x0][y1+1];
    res -= sm[x1+1][y0];
    res += sm[x0][y0];
    return res;
}


int n,m;

int main() {
    cin.sync_with_stdio(false);
    cin >> n >> m;

    sm = vector<vector<int> >(n, vector<int>(m, 0));
    vector<vector<char> > arr(n, vector<char>(m, '.'));
    vector<vector<int> > mx(n, vector<int>(m, 0));
    vector<vector<int> > res(n, vector<int>(m, 0));

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

#define BEGIN 0
#define QUERY 1
#define END 2

    rep(i,0,n) {
        multiset<int> cur;
        vector<pair<int, ii> > ev;
        rep(j,0,m) {
            ev.push_back(make_pair(j, ii(QUERY, j)));
            if (mx[i][j] > 0) {
                ev.push_back(make_pair(j, ii(BEGIN, mx[i][j])));
                ev.push_back(make_pair(j+mx[i][j]-1, ii(END, mx[i][j])));
            }
        }
        sort(ev.begin(), ev.end());
        iter(it,ev) {
            if (it->second.first == BEGIN) {
                cur.insert(it->second.second);
            } else if (it->second.first == END) {
                cur.erase(cur.find(it->second.second));
            } else {
                assert(it->second.first == QUERY);
                mx[i][it->second.second] = cur.empty() ? 0 : *cur.rbegin();
            }
        }
    }

    rep(j,0,m) {
        multiset<int> cur;
        vector<pair<int, ii> > ev;
        rep(i,0,n) {
            ev.push_back(make_pair(i, ii(QUERY, i)));
            if (mx[i][j] > 0) {
                ev.push_back(make_pair(i, ii(BEGIN, mx[i][j])));
                ev.push_back(make_pair(i+mx[i][j]-1, ii(END, mx[i][j])));
            }
        }
        sort(ev.begin(), ev.end());
        iter(it,ev) {
            if (it->second.first == BEGIN) {
                cur.insert(it->second.second);
            } else if (it->second.first == END) {
                cur.erase(cur.find(it->second.second));
            } else {
                assert(it->second.first == QUERY);
                mx[it->second.second][j] = cur.empty() ? 0 : *cur.rbegin();
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

