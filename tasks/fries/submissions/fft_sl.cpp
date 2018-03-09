#include <bits/stdc++.h>
using namespace std;

// FFT-based solution. Slightly too slow, alas -- it runs in
// O(P + C log C) where C is the maximum coordinate size, and in
// practice around 4x of the time limit. See fft_opt_sl.cpp
// for an optimized version which passes on kattis.

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// From https://github.com/jaehyunp/stanfordacm/blob/master/code/FFT.cc
typedef complex<double> cd;
typedef vector<cd> carray;
struct FFT {
	vector<cd> A;
	int n, L;

	int ReverseBits(unsigned x) {
		x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
		x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
		x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
		x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
		x = ((x >> 16) | (x << 16));
		return x >> (32 - L);
	}

	void BitReverseCopy(const vector<cd>& a) {
		for (n = 1, L = 0; n < sz(a); n <<= 1, L++) ;
		A.resize(n);
		for (int k = 0; k < n; k++) 
			A[ReverseBits(k)] = a[k];
	}

	vector<cd> DFT(const vector<cd>& a, bool inverse) {
		BitReverseCopy(a);
		for (int s = 1; s <= L; s++) {
			int m = 1 << s;
			cd wm = polar(1.0, 2.0 * M_PI / m);
			if (inverse) wm = cd(1, 0) / wm;
			for (int k = 0; k < n; k += m) {
				cd w = 1;
				for (int j = 0; j < m/2; j++) {
					cd t = w * A[k + j + m/2];
					cd u = A[k + j];
					A[k + j] = u + t;
					A[k + j + m/2] = u - t;
					w = w * wm;
				}
			}
		}
		return move(A);
	}
};

void fft(vector<cd>& ar, bool inv) {
	FFT fft;
	ar = fft.DFT(ar, inv);
	if (inv) {
		double iv = 1.0 / sz(ar);
		for (cd& x : ar)
			x *= iv;
	}
}

int main() {
	cin.sync_with_stdio(false);
	cin.exceptions(cin.failbit);
	int P, T;
	double L;
	cin >> P >> T >> L;
	int n = 1 << 24; // > 10^7 + slack
	carray v(n), w(n);
	rep(i,0,P) {
		int pos;
		cin >> pos;
		v[pos] = 1;
	}

	// Forward FFT
	fft(v, false);

	// Closed form for Fourier transform of w with w[-1] = w[1] = 1, rest 0
	rep(i,0,n) {
		cd x = polar(1.0, -2 * M_PI * i / n);
		w[i] = 0.5 * x + 0.5 / x;
	}

	// In the Fourier world, convolving v with w T times is the same as pointwise multiplication by w[i]^T
	rep(i,0,n) {
		v[i] *= pow(w[i], T);
	}

	// Backward FFT
	fft(v, true);

	int res = 0;
	rep(i,0,n) {
		if (v[i].real() > L)
			res++;
	}

	cout << res << endl;
	exit(0);
}
