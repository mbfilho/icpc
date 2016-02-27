#include <map>
#include <iostream>
using namespace std;
typedef long long ll;
const ll MAX = 1200000000000000000LL;
 
/*
Accepted!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/
map<ll,ll> mapa;
map<ll,ll>::iterator it;

ll pot[ 25 ];

ll g( ll, int );
ll f( ll );


ll g( ll k, int i ){	
	ll a, b, c;
	
	c = k % pot[ i ];
	b = ( k / pot[ i ] ) % 100;
	a = k / pot[ i + 2 ];

	
	if( b == 13 )
		return  ( a * f( pot[ i ] ) + f( c ) + 1 );
	else if( b < 13 )
		return ( a * f( pot[ i ] ) );
	else
		return ( ( a + 1 ) * f( pot[ i ] ) );
}


ll f( ll arg ){
	if( ( it = mapa.find( arg ) ) != mapa.end() )
		return it -> second;
	
	ll retorno = arg;
	
	int i = 0;
	while( 13 * pot[ i ] <= arg ){
		retorno -= g( arg, i );
		++i;
	}
	
	return mapa[ arg ] = retorno;
}

ll seguro( ll n ){
	int i = 0;
	ll temp = n;
	
	while( n ){
		if( n % 100 == 13 ){
			--n;
			for( int j = 0; j < i; ++j ){
				n *= 10;
				n += 9;
			}
			
			return seguro( n );
		}
		++i;
		n = n / 10; 
	}
	
	if( n )
		return n;
	else
		return temp;
}

ll busca( ll n ){
	ll resposta, ini = n, fim;
	if( n >= MAX / 2 )
		fim = MAX;
	else
		fim = 2 * n;

	ll meio;
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		if( ( resposta = f( meio ) ) > n )
			fim = meio - 1;
		else if( resposta < n )
			ini = meio + 1;
		else
			return meio;
	}
	
	return 1;
}

int main(){
	pot[ 0 ] = 1;
	for( int i = 1; i <= 24; ++i )
		pot[ i ] = pot[ i - 1 ] * 10;

	mapa[ pot[ 0 ] ] = 1LL;
	mapa[ pot[ 1 ] ] = 10LL;
	mapa[ pot[ 2 ] ] = 99LL;

	ll num;
	
	int casos;	
	cin >> casos;
	
	//int i = 0;
	while( casos-- ){
		cin >> num;

	//	++i;
		num = busca( num );
		//cout << num << endl;
		cout << seguro( num ) << endl;
	}
	
}
