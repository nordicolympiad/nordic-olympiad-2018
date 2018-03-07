#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for(int i = (a); i < (b); i++)
#define iter(it,c) for(auto it = (c).begin(); it != (c).end();++it)
#define pb push_back
#define fs first
#define sc second
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int INF = ~(1<<31);
const double pi = acos(-1);
const double EPS = 1e-9;

int A[2520][2520];
int P[2520][2520];
int K[2520][2520];
int MX[2520][2520];

#define MAX_N 2520
#define LOG_TWO_N  12
struct RMQ {
	int _A[MAX_N], SpT[MAX_N][LOG_TWO_N];
	RMQ(int n, vi A) {
		rep(i,0,n) _A[i] = A[i], SpT[i][0] = i;
		for(int j = 1; (1<<j) <= n; j++) {
			for(int i = 0; i + (1<<j) - 1 < n; i++) {
				if(_A[SpT[i][j-1]] < _A[SpT[i+(1<<(j-1))][j-1]]) SpT[i][j] = SpT[i][j-1];
				else SpT[i][j] = SpT[i+(1<<(j-1))][j-1];
			}
		}
	}
	int query(int i, int j) {
		int k = (int)floor(log((double)j-i+1) / log(2.0));
		if(_A[SpT[i][k]] <= _A[SpT[j-(1<<k)+1][k]]) return _A[SpT[i][k]];
		else return _A[SpT[j-(1<<k)+1][k]];
	}
};

// Time complexity O(n^2 log(n))
int main() {
	cin.sync_with_stdio(false);
	cin.tie(0);
    int n,m;
    memset(P,0,sizeof(P));
    memset(MX,0,sizeof(MX));
    cin >> n >> m;
    rep(i,0,n) rep(j,0,m) {
        char c;
        cin >> c;
		A[i][j] = c == '.' ? 1 : 0;
	}

    rep(i,0,n) rep(j,0,m) P[i][j+1] = P[i][j]+A[i][j];

    rep(c_1,0,m) {
        vi H(n);
        rep(r, 0, n) {
            if(A[r][c_1] == 0) {
                H[r] = 0;
                continue;
            }
            ll lo = c_1, hi = m-1;
            ll ans = 1;
            while(lo <= hi) {
                ll mid = (lo+hi)/2;
                ll sum = P[r][mid+1]-P[r][c_1];
                if(sum == mid-c_1+1) {
                    ans = mid-c_1+1;
                    lo = mid+1;
                } else {
                    hi = mid-1;
                }
            }
            H[r] = ans;
        }
        RMQ rmq(n, H);
        vi ANS(n);
        rep(i,0,n) {
            ll lo = 0, hi = H[i]-1;
            int ans = 0;
            while(lo <= hi) {
                ll mid = (lo+hi)/2;
                ll _end = i+mid;
                if(_end >= n) {
                    hi = mid-1;
                } else {
                    ll mn = rmq.query(i,_end);
                    if(mn <= mid) {
                        hi = mid-1;
                    } else {
                        ans = mid+1;
                        lo = mid+1;
                    }
                }
            }
            ANS[i] = ans;
        }
        rep(i,0,n) {
            K[i][c_1] = ANS[i];
        }
        priority_queue<ii> pq;
        rep(i,0,n) {
            pq.push(ii(ANS[i], i));
            while(!pq.empty()) {
                ii _at = pq.top();
                if(i+1 > _at.sc+_at.fs) {
                    pq.pop();
                    continue;
                } else break;
            }
            if(!pq.empty()) {
                ii _at = pq.top();
                MX[i][c_1] = _at.fs;
            }
        }
    }
    // Fixing the values
    rep(i,0,n) {
        priority_queue<ii> pq;
        rep(j,0,m) {
            pq.push(ii(MX[i][j], j));
            while(!pq.empty()) {
                ii _at = pq.top();
                if(j+1 > _at.sc+_at.fs) {
                    pq.pop();
                    continue;
                } else break;
            }
            if(!pq.empty()) {
                ii _at = pq.top();
                MX[i][j] = _at.fs;
            }
        }
    }
    int q;
    cin >> q;
    rep(i,0,q) {
        // row, column input, expected one based index
        int y,x;
        cin >> y >> x;
        y--;x--;
        cout << MX[y][x]*MX[y][x] << '\n';
    }
    return 0;
}
