#include <cstdio>
#include <algorithm>
using namespace std;
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) Fr(i,0,n)



int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		int n;
		scanf("%d", &n);
		
		double e = 0;
		
		Fr(x, 1, n+1){
			e = (x * e + n) / double(x);
		}
		
		printf( "%.2lf\n", e);
		
	}
}






