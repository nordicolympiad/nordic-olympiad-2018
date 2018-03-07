#include "validator.h"

void run() {
	int p = Int(1, Arg("p"));
	Space();
	Int(1, Arg("t"));
	Space();
	Float(1e-4, 10);
	Endl();

	auto vals = SpacedInts(p, 0, Arg("lim", 10000000));
	AssertUnique(vals);
}
