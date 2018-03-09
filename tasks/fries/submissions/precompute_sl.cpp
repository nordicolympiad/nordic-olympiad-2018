#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	cin.sync_with_stdio(false);
	int P, T;
	double L;
	cin >> P >> T >> L;

	vector<double> coef(T+1);
	rep(k,0,T+1) {
		coef[k] = exp(lgamma(T+1) - T*log(2) - lgamma(k+1) - lgamma(T-k+1));
	}

	vector<double> vec(10000000 + 2*T + 10);
	rep(i,0,P) {
		int x;
		cin >> x;
		rep(k,0,T+1)
			vec[x + 2*k] += coef[k];
	}

	int res = 0;
	rep(i,0,sz(vec)) {
		if (vec[i] >= L) res++;
	}

	cout << res << endl;
}
