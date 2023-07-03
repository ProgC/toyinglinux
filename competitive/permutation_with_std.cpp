#include <bits/stdc++.h>

using namespace std;

constexpr int n = 3;
vector<int> permutation;
bool chosen[n+1];

#define REP(i,a,b) for ( int i = a; i < b; i++ )

int main()
{
	for ( int i = 1; i <= n; ++i )
	{
		permutation.push_back(i);
	}

	do {
		REP(i,0,n) {
			cout << permutation[i] << " ";
		}
		cout << endl;
	} while(next_permutation(permutation.begin(), permutation.end()));

}

