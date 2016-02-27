#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int qtdM, mesas;
vector<ll> moedas;
int comb[ 5 ];
vector<ll> result;
ll mini, maxi;

ll euclides( ll a, ll b ){
	ll temp;
	
	while( b ){
		temp = a % b;
		a = b;
		b = temp;
	}
	
	return a;
}

ll mmc( ll a, ll b ){
	return ( a * ( b / euclides( a, b ) ) );
}

void preencher(){
	const int c = qtdM - 4;
	for( int i = 1; i <= 4; ++i )
		comb[i] = i;
	int i;
	ll combinacao;
	
	while( true ){
		combinacao = 1;
		for( int j = 1; j <= 4; ++j ){
		//	cout << moedas[comb[j] - 1] << endl;;
			combinacao = mmc( combinacao, moedas[ comb[ j ] - 1 ] );
		}
		
		result.push_back( combinacao );

		i = 4;
		while( i != 0 && comb[i] == c + i )
			--i;
		if( i == 0 )
			break;
			
		++comb[ i ];
		for( i = i + 1; i <= 4; ++i )
			comb[ i ] = comb[ i - 1 ] + 1;
	}

}

int main(){
	int buff;
	while( (cin >> qtdM >> mesas) && qtdM && mesas ){
		moedas.clear();
		result.clear();
		for( int i = 0; i < qtdM; ++i ){
			cin >> buff;
			moedas.push_back( buff );
		}

		preencher();
		
		for( int i = 0; i < mesas; ++i ){
			ll altura;
			mini = 0;
			maxi = 0x7fffffff;
			cin >> altura;
			//cout << "Alt: " << altura << endl;
			ll div;
			for( vector<ll>::iterator it = result.begin(); it != result.end(); ++it ){
				if( altura % ( *it ) == 0 )
					mini = maxi = altura;
				else{
					div = altura / ( *it );
					if( ( *it ) * div > mini )
						mini = ( *it ) * div;
					++div;
					if( ( *it ) * div < maxi )
						maxi = ( *it ) * div;
				}
			}
			
			cout << mini << " " << maxi << endl;
		}
	}
}
