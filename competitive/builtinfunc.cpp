#include <bits/stdc++.h>

using namespace std;

int main()
{
	int x = 5328;
	cout << __builtin_clz(x) << endl; // number of zero from left
	cout << __builtin_ctz(x) << endl; // number of zero from right
	cout << __builtin_popcount(x) << endl; // number of ones in the bits.
	cout << __builtin_parity(x) << endl;
}



