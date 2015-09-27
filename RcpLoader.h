#include <fstream>
#include <algorithm>

#include "Logger.h"

#include "TGraphErrors.h"
#include "TH1.h"
#include "TH1D.h"

class RcpLoader{

	// TODO: fix the R_CP and baryon/meson plots

public:

	static constexpr auto tag = "RcpLoader";
	vector<double> pT;
	vector<double> value;
	vector<double> stat;

	RcpLoader( string fname ){

		ifstream inf( fname.c_str() );

		string tmp;
		double a, b, c;

		getline( inf, tmp );

		while( inf >> a >> b >> c ){

			pT.push_back( a );
			value.push_back( b );
			stat.push_back( c );

			INFO( tag,  "[" << a << "] = " << b << " +/- " << c );

		}	

		if ( pT[ 0 ] > pT[ pT.size() - 1 ] ){
			reverse( pT.begin(), pT.end() );
			reverse( value.begin(), value.end() );
			reverse( stat.begin(), stat.end() );
		}
	
		inf.close();
	}

	void trim( int N = 1 ){

		for ( int i = 0; i < N; i++ ){
			pT.erase( pT.begin() );
			value.erase( value.begin() );
			stat.erase( stat.begin() );
		}
	}

	void trunc( int N = 1 ){
		INFO( "N  = " <<N );
		for ( int i = 0; i < N; i++ ){
			INFO( "truncating")
			pT.pop_back();
			value.pop_back();
			stat.pop_back();
		}
	}

	TGraphErrors * statGraph(){
		INFO( tag, "N = " << pT.size() );
		for ( double v : pT ){
			INFO( "pT = " << v );

		}
		for ( double v : value ){
			INFO( "val = " << v );
		}
		TGraphErrors * graph = new TGraphErrors( pT.size(), pT.data(), value.data(), 0, stat.data() );
		return graph;
	}
};