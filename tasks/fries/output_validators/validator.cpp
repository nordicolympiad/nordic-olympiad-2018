// usage: ./a.out input_file correct_output feedback_dir < contestants_output

#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define trav(a, x) for (auto& a : x)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;

string input_file, answer_file;

void die(const string& msg) {
	cout << msg << endl;
	exit(43);
}

void accept() {
	exit(42);
}

void assert_done(istream& is) {
	try {
		string dummy;
		is >> dummy;
		if (is) die("extraneous data: " + dummy);
	} catch(...) {}
}

pii getSampleBounds(string ans) {
	if (ans == "1") return {1, 1};
	if (ans == "13") return {12, 15};
	assert(0);
}

int main(int argc, char** argv) {
	if (argc < 4) exit(1);
	cin.sync_with_stdio(0);
	cin.tie(0);

	input_file = argv[1];
	answer_file = argv[2];

	ifstream fin(answer_file);
	string word;
	fin >> word;
	assert(fin);
	int lo, hi;
	if (word == "bounds") {
		fin >> lo;
		fin >> hi;
		assert(fin);
	} else {
		// special case: sample file, use hard-coded answers instead... sigh.
		tie(lo, hi) = getSampleBounds(word);
	}
	assert_done(fin);
	fin.close();

	assert(lo <= hi);

	try {
		int ans;
		cin >> ans;
		if (!cin) {
			// special case: also accept the exact answer file to avoid kattis warnings...
			cin.clear();
			cin >> word;
			if (cin && word == "bounds") {
				int x, y;
				cin >> x >> y;
				if (cin && x == lo && y == hi) accept();
			}
			die("eof");
		}
		assert_done(cin);

		if (ans < lo) die("too low");
		if (ans > hi) die("too high");
		accept();
	} catch(...) {
		die("IO failure");
	}
}
