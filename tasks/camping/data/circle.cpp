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

#define SQ(x) ((ll)(x)*(x))

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]),
        m = atoi(argv[2]),
        k = atoi(argv[3]),
        r = atoi(argv[4]),
        q = atoi(argv[5]);
    srand(atoi(argv[6]));

    vii idx;
    rep(i,0,n) rep(j,0,m) idx.push_back(ii(i,j));

    vii out;
    iter(it,idx) {
        if (SQ(it->first - n/2) + SQ(it->second - m/2) > SQ(r)) {
            out.push_back(*it);
        }
    }

    random_shuffle(idx.begin(), idx.end());
    random_shuffle(out.begin(), out.end());

    assert(k < size(out));
    assert(q < size(idx));

    cout << n << " " << m << endl;
    vector<vector<char> > arr(n, vector<char>(m, '.'));
    rep(i,0,k) {
        arr[out[i].first][out[i].second] = '#';
    }
    rep(i,0,n) {
        rep(j,0,m) {
            cout << arr[i][j];
        }
        cout << endl;
    }

    cout << q << endl;
    rep(i,0,q) {
        cout << idx[i].first+1 << " " << idx[i].second+1 << endl;
    }

    return 0;
}

