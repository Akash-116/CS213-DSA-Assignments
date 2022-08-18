#include <bits/stdc++.h>
#include "./Assignment_1.h"
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	srand(time(NULL));
	int n = 50;
	int s[100];
	for (int i = 0; i < 100; i++)
		s[i] = i;
	int corr = 0;
	for (int i = 0; i < 100; i++) { //was i<1000
		random_shuffle(s,s+100);
		permutation p(100,s);
		int last = -1;
		bool b = true;
		for (int j = 0; j < 100; j++) { // was j<100
			permutation q = p^j;
			int t = q.log(p);
			if (t != last+1 && t != 0)
				b  = false;
			last = t;
		}
			if (b) corr++;
	}
	cout << "CORRECT: " << corr << '\n';
	cout << "WRONG: " << 100-corr << '\n';
	return 0;
}
