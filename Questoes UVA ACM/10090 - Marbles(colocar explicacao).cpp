#include <cstdio>
using namespace std;

typedef long long ll;

ll h1, h2;

ll n, n1, n2, c1, c2, g;

ll gcd( ll a, ll b ){
	ll x2, x1, y2, y1, mod, quo, atx, aty;
	x2 = 1;	y2 = 0;	x1 = 0;	y1 = 1;
	
	while( b ){
		quo = a / b;
		mod = a % b;
		atx = x2 - quo * x1;
		aty = y2 - quo * y1;
		a = b;
		b = mod;
		x2 = x1;
		y2 = y1;
		x1 = atx;
		y1 = aty;
	}
	
	h1 = x2;
	h2 = y2;
	
	return a;
}

ll custo( ll t ){
	ll k1 = ( h1 * n ) / g + ( n2 * t ) / g;
	ll k2 = ( h2 * n ) / g - ( n1 * t ) / g;
	
	return k1 * c1 + k2 * c2;
}

ll teto( ll a, ll b ){
	if( a < 0 )
		return a / b;
	return ( a + b - 1 ) / b;
}

ll chao( ll a, ll b ){
	if( a > 0 )
		return a / b;
	return ( a - b + 1 ) / b;
}

int main(){
	while( scanf( "%lld", &n ) && n ){
		//cin >> c1 >> n1 >> c2 >> n2;
		scanf( "%lld %lld %lld %lld", &c1, &n1, &c2, &n2 );
		
		g = gcd( n1, n2 );
		
		if( n % g != 0 )
			printf( "failed\n" );
			//cout << "failed" << endl;
		else{
			ll k1, k2, t;
			
			if( teto( -h1 * n, n2 ) >  chao( h2 * n, n1 ) )
				printf( "failed\n" );
				//cout << "failed" << endl;
			else{
				if( custo( teto( -h1 * n, n2 ) ) <= custo( chao( h2 * n, n1 ) ) )
					t = teto( -h1 * n, n2 );
				else
					t = chao( h2 * n, n1 );
					
				k1 = ( h1 * n ) / g + ( n2 * t ) / g;
				k2 = ( h2 * n ) / g - ( n1 * t ) / g;
				
				printf( "%lld %lld\n", k1, k2 );
				//cout << k1 << " " << k2 << endl;
			}
		}
	}
}

