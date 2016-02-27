#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <list>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
int H = 17;

string st[ 6 ];

string concatenar( string& a, string& b ){
	ull ha = 0, hb = 0;
	int tama = a.size(), tamb = b.size();
	int tam = min( tama, tamb );
	
	int maior = -1;
	ull base = 1;
	for( int i = 0; i < tam; ++i ){
		hb = hb * H + ( b[ i ] - 'A' );
		ha = ha + ( a[ tama - i - 1 ] - 'A' ) * base;
		base = base * H;
		
		if( hb == ha )
			maior = i;
	}
	
	string res = a;
	for( maior += 1; maior < tamb; ++maior )
		res += b[ maior ];
	return res;
}

int main(){
	int casos;
	cin >> casos;
	
	for( int c = 1; c <= casos; ++c ){
		cin >> n;
		int menor = 0x7fffffff;
		for( int i = 0; i < n; ++i )
			cin >> st[ i ];
		sort( st, st + n );
		string temp;
		
		cout << "Case " << c << ": ";
		if( n == 1 )
			cout << st[ 0 ].size() << endl;
		else{
			do{
				temp = concatenar( st[ 0 ], st[ 1 ] );
				for( int i = 2; i < n; ++i )
					temp = concatenar( temp, st[ i ] );
				if( temp.size() < menor )
					menor = temp.size();
			}while( next_permutation( st, st + n ) );
			
			cout << menor << endl;
		}
	}
}
