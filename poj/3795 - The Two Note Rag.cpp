#include <iostream>
#include <cstdio>
using namespace std;
#define rep(i, n) for(int i = 0; i < n; ++i)	
long long pd[] = {-1, 1, 9, 89, 89, 589, 3089, 3089, 3089, 315589, 315589, 8128089, 164378089, 945628089, 1922190589, 11687815589, 109344065589, 231414378089, 1452117503089, 4503875315589, 65539031565589};

int main(){
	int t;
	scanf("%d", &t);
	rep(cas, t){
		int r;
		scanf("%d", &r);
		cout << (cas+1) << " " << r << " " << pd[r] << endl;
	}
}

