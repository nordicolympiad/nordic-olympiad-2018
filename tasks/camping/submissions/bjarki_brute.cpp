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

int main() {
    cin.sync_with_stdio(false);
    int n,m;
    cin >> n >> m;

    vector<vector<char> > arr(n, vector<char>(m, '.'));
    vector<vector<int> > mx(n, vector<int>(m, 0));
    rep(i,0,n) {
        rep(j,0,m) {
            cin >> arr[i][j];
        }
    }

    rep(i,0,n) {
        rep(j,0,n) {
            rep(sz,1,n+1) {
                if (i+sz-1 < n && j + sz-1 < n) {
                    bool ok = true;
                    rep(x,0,sz) {
                        rep(y,0,sz) {
                            ok = ok && arr[i+x][j+y] == '.';
                        }
                    }
                    if (ok) {
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

