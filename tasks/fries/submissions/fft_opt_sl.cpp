#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx")
#include <bits/stdc++.h>
#include <immintrin.h>
using namespace std;

// Optimized FFT-based solution.

const int logn = 24;
const int n = 1 << logn; // > 10^7 + slack

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#if 0
void CL(const char* str) {
	static int prev = 0;
	int now = (int)clock(), ret = now - prev;
	prev = now;
	cerr << str << ' ' << (ret / 1000) << endl;
}
#else
#define CL(x)
#endif

// Re-implement complex<double>, because its operator* is rather slow...
struct cd {
	double r, i;
	cd(double a, double b) : r(a), i(b) {}
	cd(double r) : r(r), i(0) {}
	cd() : r(0), i(0) {}
	cd(complex<double> x) : r(x.real()), i(x.imag()) {}
	cd operator+(cd o) { return cd(r + o.r, i + o.i); }
	cd operator-(cd o) { return cd(r - o.r, i - o.i); }
	cd operator*(cd o) { return cd(r * o.r - i*o.i, r * o.i + i * o.r); }
	void operator*=(cd o) { *this = *this * o; }
	double real() const { return r; }
};
cd operator*(cd a, double b) { return cd(a.r * b, a.i * b); }
cd operator*(double b, cd a) { return cd(b * a.r, b * a.i); }
cd conj(cd x) { return cd(x.r, -x.i); }
cd pow(cd x, int e) {
	if (e == 1) return x;
	cd y = pow(x, e >> 1);
	y = y * y;
	if (e & 1) y = y * x;
	return y;
}

int ReverseBits(unsigned x, int L) {
	x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
	x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
	x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
	x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
	x = ((x >> 16) | (x << 16));
	return x >> (32 - L);
}


// Fast bit reversal permutation code from https://bitbucket.org/orserang/bit-reversal-methods/
// MIT licensed, (c) 2017 Oliver Serang

template <unsigned char LOG_N>
class BitReversal {
protected:
  static const unsigned char reversed_byte_table[256];

public:
  inline static unsigned int reverse_int_byte_table(unsigned int x){
    unsigned char inByte0 = (unsigned char)((x & 0xFF));
    unsigned char inByte1 = (unsigned char)((x & 0xFF00) >> 8);
    unsigned char inByte2 = (unsigned char)((x & 0xFF0000) >> 16);
    unsigned char inByte3 = (unsigned char)((x & 0xFF000000) >> 24);
    return (unsigned int)((reversed_byte_table[inByte0] << 24) | (reversed_byte_table[inByte1] << 16) | (reversed_byte_table[inByte2] << 8) | reversed_byte_table[inByte3]);
  }

  inline static unsigned long reverse_bytewise(unsigned long x) {
    return reverse_int_byte_table((unsigned int)x) >> (sizeof(unsigned int)*8 - LOG_N);
  }

  inline static unsigned int reverse_bytewise(unsigned int x) {
    // To prevent unnecessary warnings about (desired) behavior when LOG_N == 0:
    return reverse_int_byte_table(x) >> (sizeof(unsigned int)*8 - LOG_N);
  }
};

// From StackOverflow:
// http://stackoverflow.com/questions/746171/best-algorithm-for-bit-reversal-from-msb-lsb-to-lsb-msb-in-c#24058332
template<unsigned char LOG_N>
const unsigned char BitReversal<LOG_N>::reversed_byte_table[256] = {0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, 0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, 0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA, 0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE, 0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1, 0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5, 0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD, 0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB, 0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF};


// From Carter and Gatlin 1998
template<typename T, unsigned char LOG_N, unsigned char LOG_BLOCK_WIDTH>
class OutOfPlaceCOBRAShuffle {
public:
	inline static void apply(T*__restrict &V1, T*__restrict &V2) {
		T*__restrict const v1 = V1;
		T*__restrict const v2 = V2;
		T*__restrict const result1 = (T*)_mm_malloc(sizeof(T)*1ul<<LOG_N, 32);
		T*__restrict const result2 = (T*)_mm_malloc(sizeof(T)*1ul<<LOG_N, 32);

		constexpr unsigned char NUM_B_BITS = LOG_N - 2*LOG_BLOCK_WIDTH;
		constexpr unsigned long B_SIZE = 1ul << NUM_B_BITS;
		constexpr unsigned long BLOCK_WIDTH = 1ul << LOG_BLOCK_WIDTH;

		T*__restrict buffer1 = (T*)malloc(sizeof(T)*BLOCK_WIDTH*BLOCK_WIDTH);
		T*__restrict buffer2 = (T*)malloc(sizeof(T)*BLOCK_WIDTH*BLOCK_WIDTH);

		for (unsigned long b=0; b<B_SIZE; ++b) {
			unsigned long b_rev = BitReversal<NUM_B_BITS>::reverse_bytewise(b);

			// Copy block to buffer:
			for (unsigned long a=0; a<BLOCK_WIDTH; ++a) {
				unsigned long a_rev = BitReversal<LOG_BLOCK_WIDTH>::reverse_bytewise(a);

				for (unsigned long c=0; c<BLOCK_WIDTH; ++c) {
					unsigned long A = (a_rev << LOG_BLOCK_WIDTH) | c;
					unsigned long B = (a << NUM_B_BITS << LOG_BLOCK_WIDTH) | (b << LOG_BLOCK_WIDTH) | c;
					buffer1[A] = v1[B];
					buffer2[A] = v2[B];
				}
			}

			// Swap from buffer:
			for (unsigned long c=0; c<BLOCK_WIDTH; ++c) {
				// Note: Typo in original pseudocode by Carter and Gatlin at
				// the following line:
				unsigned long c_rev = BitReversal<LOG_BLOCK_WIDTH>::reverse_bytewise(c);

				for (unsigned long a_rev=0; a_rev<BLOCK_WIDTH; ++a_rev) {
					unsigned long A = (c_rev << NUM_B_BITS << LOG_BLOCK_WIDTH) | (b_rev<<LOG_BLOCK_WIDTH) | a_rev;
					unsigned long B = (a_rev<<LOG_BLOCK_WIDTH) | c;
					result1[A] = buffer1[B];
					result2[A] = buffer2[B];
				}
			}
		}
		free(buffer1);
		free(buffer2);

		V1 = result1;
		V2 = result2;
	}
};

// END fast bitrev

void BitReverse(int n, int L, double*& areal, double*& aimag) {
	OutOfPlaceCOBRAShuffle<double, logn, 5>().apply(areal, aimag);
}

// Modified from https://github.com/jaehyunp/stanfordacm/blob/master/code/FFT.cc
void fft(int n, double*& Areal, double*& Aimag, bool inverse) {
	int L = 0;
	for (int i = 1; i < n; i <<= 1) L++;
	if (inverse) {
		BitReverse(n, L, Areal, Aimag);
		CL("bitrev");
	}
	double* areal = Areal;
	double* aimag = Aimag;
	for (int s = 1; s <= L; s++) {
		int m = 1 << s;
		cd wm = polar(1.0, 2.0 * M_PI / m);
		if (inverse) wm = conj(wm);
		cd w0 = 1, w1 = wm, w2 = wm * wm, w3 = w2 * wm, w4 = w2 * w2;

		typedef __m256d md;

		md R4 = _mm256_set1_pd(w4.r);
		md I4 = _mm256_set1_pd(w4.i);

		for (int k = 0; k < n; k += m) {
			if (m >= 8) {
				md* __restrict__ ra = (md*)&areal[k + m/2];
				md* __restrict__ rb = (md*)&areal[k];
				md* __restrict__ ia = (md*)&aimag[k + m/2];
				md* __restrict__ ib = (md*)&aimag[k];

				md RW = _mm256_setr_pd(w0.r, w1.r, w2.r, w3.r);
				md IW = _mm256_setr_pd(w0.i, w1.i, w2.i, w3.i);

				for (int j = 0; j < m/8; j++) {
					md RA = ra[j];
					md IA = ia[j];
					md RB = rb[j];
					md IB = ib[j];

					md RT = RW * RA - IW * IA;
					md IT = RW * IA + IW * RA;

					md RS = RB + RT;
					md IS = IB + IT;
					md RD = RB - RT;
					md ID = IB - IT;

					rb[j] = RS;
					ib[j] = IS;
					ra[j] = RD;
					ia[j] = ID;

					md RN = RW * R4 - IW * I4;
					md IN = RW * I4 + IW * R4;
					RW = RN;
					IW = IN;
				}
			} else {
				cd w = 1;
				for (int j = 0; j < m/2; j++) {
					cd t = w * cd(areal[k + j + m/2], aimag[k + j + m/2]);
					cd u = cd(areal[k + j], aimag[k + j]);
					cd sum = u + t, dif = u - t;
					areal[k + j] = sum.r;
					areal[k + j + m/2] = dif.r;
					aimag[k + j] = sum.i;
					aimag[k + j + m/2] = dif.i;
					w = w * wm;
				}
			}
		}
	}
	CL("fft");
}

int main() {
	cin.sync_with_stdio(false);
	cin.exceptions(cin.failbit);
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
	int P, T;
	double L;
	cin >> P >> T >> L;
	double *vreal = (double*)_mm_malloc(n * sizeof(double), 32);
	double *vimag = (double*)_mm_malloc(n * sizeof(double), 32);
	double *wreal = (double*)_mm_malloc(n * sizeof(double) + 32, 32);
	double *wimag = (double*)_mm_malloc(n * sizeof(double) + 32, 32);
	memset(vreal, 0, n * sizeof(double));
	memset(vimag, 0, n * sizeof(double));
	rep(i,0,P) {
		int pos;
		cin >> pos;
		vreal[ReverseBits(pos, logn)] = 1;
	}

	CL("read input");
	fft(n, vreal, vimag, false);

	// Closed form for Fourier transform of w with w[-1] = w[1] = 1, rest 0
	cd root = polar(1.0, -2 * M_PI / n), wa = 1.0;
	const int chunk = 32;
	for (int i = 0; i <= n/2; i += chunk) {
		// for precision, occasionally reset 'wa' to its mathematically
		// correct, but slow to compute, value
		wa = polar(1.0, -2 * M_PI * i / n);
		for (int j = i; j < i + chunk; j++) {
			cd w = 0.5 * wa + 0.5 * conj(wa);
			wreal[n - j] = wreal[j] = w.r;
			wimag[n - j] = wimag[j] = w.i;
			wa *= root;
		}
	}
	CL("computed w");

	// In the Fourier world, convolving v with w T times is the same as pointwise multiplication by w[i]^T
	double lim = pow(1e-8, 2.0 / T);
	rep(i,0,n) {
		if (wreal[i] * wreal[i] + wimag[i] * wimag[i] < lim) {
			vreal[i] = vimag[i] = 0;
			continue;
		}
		cd x = cd(vreal[i], vimag[i]) * pow(cd(wreal[i], wimag[i]), T);
		vreal[i] = x.r;
		vimag[i] = x.i;
	}

	CL("exponentiated");

	fft(n, vreal, vimag, true);

	int res = 0;
	rep(i,0,n) {
		double c = vreal[i] / n;
		if (c > L)
			res++;
	}

	cout << res << endl;
	CL("done");
	_Exit(0);
}
