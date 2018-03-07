#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int P, T;
vi pos;
template<bool BOTH>
pii solve(double L, double L2) {
	vector<double> coeffs;
	int i = 0;
	double ba = lgamma(T+1) - T * log(2);
	for (;; i++) {
		int k = (T+1)/2 + i;
		if (k > T) break;
		// (T choose k) * 2^-T
		double c = exp(ba - lgamma(k+1) - lgamma(T-k+1));
		if (c < 1e-15) break;
		coeffs.push_back(c);
	}

	int C = sz(coeffs);
	// cerr << "#relevant coefficients = " << 2*C << endl;
	assert(2 * C < (1 << 20));

	int res = 0, res2 = 0;
	double* vec = new double[1 << 21]{};
	rep(it,0,(1 << 11)) {
		unsigned lo = (unsigned)it << 21;
		if ((int)lo > 100000000 || (int)(lo - (1 << 21)) < -100000000) continue;
		auto addf = [&](int idx, double amt) {
			vec[(unsigned)idx & ((1 << 21) - 1)] += amt;
		};
		auto add = [&](int idx, double amt) {
			unsigned ix = idx - lo;
			if (ix >= (1 << 21)) return;
			vec[(unsigned)idx & ((1 << 21) - 1)] += amt;
		};

		bool any = false;
		trav(x, pos) {
			unsigned mi = (unsigned)(x - 2 * C - 5) - lo, ma = (unsigned)(x + 2 * C + 5) - lo;
			bool ok = 0;
			if (mi > (1 << 30) && ma < (1 << 30)) ok = 1; // overflow
			else if (mi < (1 << 21)) ok = 1; // no overflow, but overlap
			if (!ok) continue;
			any = true;
			bool full = (mi < (1 << 21) && ma < (1 << 21));
			if (full) {
			if (T & 1) {
				rep(i,0,C) addf(x + 1 + 2*i, coeffs[i]);
				rep(i,0,C) addf(x - 1 - 2*i, coeffs[i]);
			} else {
				rep(i,0,C) addf(x + 2*i, coeffs[i]);
				rep(i,1,C) addf(x - 2*i, coeffs[i]);
			}
			} else {
			if (T & 1) {
				rep(i,0,C) add(x + 1 + 2*i, coeffs[i]);
				rep(i,0,C) add(x - 1 - 2*i, coeffs[i]);
			} else {
				rep(i,0,C) add(x + 2*i, coeffs[i]);
				rep(i,1,C) add(x - 2*i, coeffs[i]);
			}
			}
		}

		if (!any) continue;
		rep(i,0,(1 << 21)) {
			double x = vec[i];
			vec[i] = 0;
			if (x >= L) res++;
			if (BOTH && x >= L2) res2++;
		}
	}
	return {res, res2};
}

int main() {
	cin.sync_with_stdio(false);
	cin.exceptions(cin.failbit);
	double L;
	cin >> P >> T >> L;
	pos.resize(P);
	rep(i,0,P) cin >> pos[i];
	sort(all(pos));
#ifdef WANT_BOUNDS
	auto pa = solve<true>(L * 1.2, L * 0.8);
	cout << "bounds " << pa.first << ' ' << pa.second << endl;
#else
	assert(P <= 500 || T <= 100000);
	cout << solve<false>(L, L).first << endl;
#endif
	_Exit(0);
}
