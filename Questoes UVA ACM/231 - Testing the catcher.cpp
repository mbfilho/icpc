#include <iostream>
#include <vector>
using namespace std;

unsigned short val;
vector<unsigned short> seq;
vector<unsigned short> m;

int busca( int ini, int fim ){

	if( ini == fim ){
		if( seq[ m[ ini ] ] >= val )
			return ini;
		return 0;
	}

	int meio = (ini + fim) / 2;

	if( seq[ m[ meio ] ] >= val ){
		int j = busca( meio + 1, fim );
		if( j == 0 )
			return meio;

		return j;
	}

	return busca( ini, meio );
}

int main(){
	int l;
	int temp;
	int test = 1;

	freopen( "in.txt", "r", stdin );
	cin >> temp;
	while( temp != -1 ){
		seq.clear();

		while( temp != -1 ){
			seq.push_back( temp );
			cin >> temp;
		}

		if( m.capacity() < seq.size() )
			m.resize( seq.size() );

		l = 1;
		m[ 1 ] = 0;
		for( int i = 1; i < seq.size(); ++i ){
			val = seq[ i ];
			int j = busca( 1, l );

			if( j == l || seq[ m[ j + 1 ] ] < seq[ i ] ){
				m[ j + 1 ] = i;

				if( j == l )
					++l;
			}
		}

		cout << "Test #" << test++ << ":" << endl;
		cout << "  maximum possible interceptions: " << l << endl;
		cin >> temp;
		if( temp != -1 )
			cout << endl;
	}


}
