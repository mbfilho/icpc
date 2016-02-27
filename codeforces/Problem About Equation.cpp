#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
using namespace std;
typedef unsigned long long hash;
typedef long long ll;
typedef pair<int,int> Ponto;
#define mp make_pair
#define X first
#define Y second
#define pb push_back

int n, b;
int a[300];


int main(){
	scanf( "%d%d", &n, &b );
	int maior = 0;
	for( int i = 0; i < n; ++i ){
		scanf( "%d", a + i );
		maior = max( maior, a[i] );
	}
	
	for( int i = 0; i < n; ++i ){
		b -= (maior - a[i]);
	}
	
	if(b < 0) printf( "-1\n" );
	else{
		for( int i = 0; i < n; ++i ){
			printf( "%.6lf\n", (maior - a[i]) + double(b) / double(n)); 
		}
	}
}

