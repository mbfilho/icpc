#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int,int> Frac;
#define mp make_pair
#define X first
#define Y second

int n, m;
int an, bm;

int gcd(int a, int b){
	while(b){
		int tmp = a % b;
		a = b;
		b = tmp;
	}
	
	return a;
}

int main(){
	scanf("%d%d", &n, &m);
	
	scanf("%d", &an);
	for(int i = 0; i < n; ++i) scanf("%*d");
	
	scanf("%d", &bm);
	for(int i = 0; i < m; ++i) scanf("%*d");
	
	Frac f = mp(an, bm);
	if(n == m){
		int mdc = gcd(abs(f.X), abs(f.Y));
		f = mp(f.X/mdc, f.Y/mdc);
		
		if(f.Y < 0){
			f.Y *= -1;
			f.X *= -1;
		}
		
		printf( "%d/%d\n", f.X, f.Y);
	}else if(n > m){
		if(f.X * f.Y > 0)
			printf("Infinity\n");
		else
			printf("-Infinity\n");
	}else if(n < m){
		printf("0/1\n");
	}
}



