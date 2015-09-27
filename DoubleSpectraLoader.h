#ifndef DOUBLE_SPECTRA_LOADER_H
#define DOUBLE_SPECTRA_LOADER_H


#include "Logger.h"

class DoubleSpectraLoader 
{
public:
	static constexpr auto tag = "DoubleSpectraLoader";
	vector<double> pT;
	vector<double> value;
	vector<double> stat;
	vector<double> sys;
	vector<double> bins;
	int first_bin;

	DoubleSpectraLoader( string _fn1, string _fn2, vector<double> _bins, int _first_bin = 0 ){
		INFO(tag, "("+ _fn1 +", " + _fn2 +")");

		first_bin = _first_bin;
		ifstream inf1( _fn1.c_str() );
		ifstream inf2( _fn2.c_str() );

		string tmp;
		double a1, b1, c1, d1;
		double a2, b2, c2, d2;

		getline( inf1, tmp );
		getline( inf2, tmp );

		while( inf1 >> a1 >> b1 >> c1 >> d1 && inf2 >> a2 >> b2 >> c2 >> d2  ){

			INFO( tag,  "[" << a1 << "] = " << b1 << " +/- " << c1 << " +/- " << d1 );
			INFO( tag,  "[" << a2 << "] = " << b2 << " +/- " << c2 << " +/- " << d2 );
			
			pT.push_back( (a1 + a2)/2.0 );
			value.push_back( b1+b2 );
			stat.push_back( c1+c2 );
			sys.push_back( d1+d2 );
		}	

		bins = _bins;

		inf1.close();
		inf2.close();

	}
	~DoubleSpectraLoader(){

	}

	void trim( int N = 1 ){

		for ( int i = 0; i < N; i++ ){
			pT.erase( pT.begin() );
			value.erase( value.begin() );
			stat.erase( stat.begin() );
			sys.erase( sys.begin() );
		}
	}

	void trunc( int N = 1 ){
		INFO( "N  = " <<N );
		for ( int i = 0; i < N; i++ ){
			INFO( "truncateing")
			pT.pop_back();
			value.pop_back();
			stat.pop_back();
			sys.pop_back();
		}
	}

	TH1D * statHisto( string name ){
		TH1D * h = new TH1D( name.c_str(), "", bins.size() - 1, bins.data() );
		for ( int i = 0; i < bins.size() + 1; i++ ){
			h->SetBinContent( i + 1 + first_bin, value[ i ] );
			h->SetBinError( i + 1 + first_bin, stat[ i ] );
		}
		return h;
	}

	

	TH1D * sysHisto( string name ){
		TH1D * h = new TH1D( name.c_str(), "", bins.size() - 1, bins.data() );
		for ( int i = 0; i < bins.size() + 1; i++ ){
			h->SetBinContent( i + 1 + first_bin, value[ i ] );
			h->SetBinError( i + 1 + first_bin, sys[ i ] );
		}
		return h;
	}
	
};

#endif