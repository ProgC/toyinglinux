#include <bits/stdc++.h>

using namespace std;

constexpr int n = 3;
vector<int> permutation;
bool chosen[n+1];

#define REP(i,a,b) for ( int i = a; i < b; i++ )

void search() {

	if (permutation.size() == n) {
		// process permutation
		REP(i,0,n) {
			cout << permutation[i] << " ";
		}		
		cout << endl;
	}
	else
	{
		for ( int i = 1; i <= n; i++ ) {
			if ( chosen[i] )
				continue;
			chosen[i] = true;
			permutation.push_back(i);
			search();
			chosen[i] = false;
			permutation.pop_back();
		}
	}
}

int main()
{
	search();

}

