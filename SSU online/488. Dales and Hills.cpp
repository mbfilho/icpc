#include <cstdio>
#include <list>
#include <iostream>
using namespace std;

int menor( int a, int b ){
	if( a < b )
		return a;
	return b;
}

int maior( int a, int b ){
	if( a > b )
		return a;
	return b;
}

class Coisa{
public:
	int i, j, k;
};


int main(){
	Coisa thill, tdale;
	int cont, n;
	int ah, ad;
	int casos;
	freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	scanf( "%d", &casos );
	while( casos-- ){
		thill.i = thill.j = thill.k = 0;
		tdale.i = tdale.j = tdale.k = 0;
		ah = ad = 0;
		
		scanf( "%d", &n );
		bool dec = false, cre = false;
		
		int ant, pos;
		scanf( "%d", &ant );
		for( int i = 1; i < n; ++i ){
			scanf( "%d", &pos );
			
			if( pos > ant ){
				if( cre ){
					thill.j = i;
					thill.k = i;
					tdale.k = i;
				}
				if( dec ){
					tdale.j = i - 1;
					tdale.k = i;
					thill.i = i - 1;
					thill.j = thill.k = i;
				}
				
				cre = true;
				dec = false;
			}else if( pos < ant ){
				if( cre ){
					thill.j = i - 1;
					thill.k = i;	
					tdale.i = i - 1;
					tdale.j = tdale.k = i;
				}
				
				if( dec ){
					thill.k = i;
					tdale.j = i;
					tdale.k = i;
				}
				
				cre = false;
				dec = true;
				
			}else{
				cre = dec = false;
				thill.i = thill.j = thill.k = i;
				tdale.i = tdale.j = tdale.k = i;
			}
			
			
			ant = pos;
			
			ah = maior( ah, menor( thill.j - thill.i, thill.k - thill.j ) );
			ad = maior( ad, menor( tdale.j - tdale.i, tdale.k - tdale.j ) );			
		}
		printf( "%d %d\n", ah, ad ); 
	}
	
}
