#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;


void rec( int s, int maior, vector<int>& temp ){
	if( !s ){
		printf( "%d", temp[0] );
		for( int i = 1; i < temp.size(); ++i ) printf( "+%d", temp[i] );
		printf( "\n" );
		return;
	}
	
	for( int i = maior; i > 0; --i ){
		temp.push_back( i );
		rec( s - i, min( i, s - i ), temp );
		temp.pop_back();
	}
}

int main(){
	freopen( "part.in", "r", stdin );
	freopen( "part.out", "w", stdout );
	
	int n;
	scanf( "%d", &n );
	vector<int> tmp;
	rec( n, n, tmp );
}


