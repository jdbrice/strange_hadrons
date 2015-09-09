#include <fstream>
#include <algorithm>

#include "Logger.h"

#include "TGraphErrors.h"

class SpectraLoader{

public:

	static constexpr auto tag = "SpectraLoader";
	vector<double> pT;
	vector<double> value;
	vector<double> stat;
	vector<double> sys;

	// computed
	vector<double> width;
	vector<double> bins;

	SpectraLoader( vector<double> _pT,  vector<double> _value,  vector<double> _stat,  vector<double> _sys ){
		pT = _pT;
		value = _value;
		stat = _stat;
		sys = _sys;
	}

	SpectraLoader( vector<double>_pT, TH1 * h ){
		pT = _pT;
		value.clear();
		stat.clear();
		for ( int i = 1; i <= h->GetNbinsX(); i++ ){
			value.push_back( h->GetBinContent( i ) );
			stat.push_back( h->GetBinError( i ) );
		}
	}

	SpectraLoader( string fname, vector<double> _bins = {} ){

		ifstream inf( fname.c_str() );

		string tmp;
		double a, b, c, d;

		getline( inf, tmp );

		while( inf >> a >> b >> c >> d ){

			pT.push_back( a );
			value.push_back( b );
			stat.push_back( c );
			sys.push_back( d );

			INFO( tag,  "[" << a << "] = " << b << " +/- " << c << " +/- " << d );

		}	

		if ( pT[ 0 ] > pT[ pT.size() - 1 ] ){
			reverse( pT.begin(), pT.end() );
			reverse( value.begin(), value.end() );
			reverse( stat.begin(), stat.end() );
			reverse( sys.begin(), sys.end() );
		}

		bins = _bins;

	
		inf.close();
	}

	void trim( int N = 1 ){

		for ( int i = 0; i < N; i++ ){
			pT.erase( pT.begin() );
			width.erase( width.begin() );
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
			width.pop_back();
			value.pop_back();
			stat.pop_back();
			sys.pop_back();
		}
	}

	TGraphErrors * statGraph(){
		INFO( "SpectraLoader", "N = " << pT.size() );
		for ( double v : pT ){
			INFO( "pT = " << v );

		}
		for ( double v : value ){
			INFO( "val = " << v );
		}
		TGraphErrors * graph = new TGraphErrors( pT.size(), pT.data(), value.data(), width.data(), stat.data() );
		return graph;
	}

	vector<double> getBins() {
		if ( bins.size() > 1 ){
			INFO( "bins already defined" );
			return bins;
		}
		
		INFO("computing bins")
		// make the bin edges
		bins.push_back( 0 );
		for ( int i = 1; i <= 50; i++ ){
			bins.push_back( i );
		}

		return bins;
	}

	TH1D * statHisto( string name ){
		if ( bins.size() <= 1 )
			getBins();
		TH1D * h = new TH1D( name.c_str(), "", bins.size() - 1, bins.data() );
		for ( int i = 0; i < bins.size() + 1; i++ ){
			h->SetBinContent( i + 1, value[ i ] );
			h->SetBinError( i + 1, stat[ i ] );
		}
		return h;
	}

	

	TH1D * sysHisto( string name ){
		TH1D * h = new TH1D( name.c_str(), "", bins.size() - 1, bins.data() );
		for ( int i = 0; i < bins.size() + 1; i++ ){
			h->SetBinContent( i + 1, value[ i ] );
			h->SetBinError( i + 1, sys[ i ] );
		}
		return h;
	}

	TH1D * relSysHisto( string name ){
		vector<double> bins = getBins();
		TH1D * h = new TH1D( name.c_str(), "", bins.size() - 1, bins.data() );
		for ( int i = 0; i < bins.size() + 1; i++ ){
			h->SetBinContent( i + 1, sys[i] / value[ i ] );
			h->SetBinError( i + 1, 0 );
		}
		return h;
	}

	TH1D * relStatHisto( string name ){
		vector<double> bins = getBins();
		TH1D * h = new TH1D( name.c_str(), "", bins.size() - 1, bins.data() );
		for ( int i = 0; i < bins.size() + 1; i++ ){
			h->SetBinContent( i + 1, stat[i] / value[ i ] );
			h->SetBinError( i + 1, 0 );
		}
		return h;
	}




	SpectraLoader operator/ ( SpectraLoader &b  ){
		return divide( b );
	}

	SpectraLoader operator/ ( double v  ){
		return divide( v );
	}

	SpectraLoader divide( double v ){
		INFO( "SpectraLoader", "Divide" );

		vector<double> _pT;
		vector<double> _value;
		vector<double> _stat;
		vector<double> _sys;

		for ( int i = 0; i < value.size(); i++ ){
			_value.push_back( value[i] / v );
			_pT.push_back( pT[i] );
			_stat.push_back( stat[i] / v );
			_sys.push_back( sys[i] / v );
		}

		SpectraLoader sl( _pT, _value, _stat, _sys );
		INFO( "SpectraLoader", "Done" );
		return sl;
	}


	SpectraLoader divide( SpectraLoader &b ){
		INFO( "SpectraLoader", "Divide" );

		vector<double> _pT;
		vector<double> _value;
		vector<double> _stat;
		vector<double> _sys;

		for ( int i = 0; i < std::min( value.size(), b.value.size() ); i++ ){
			_value.push_back( value[i] / b.value[i] );

			_pT.push_back( pT[i] );
			_stat.push_back( ((stat[i] / value[i]) + ( b.stat[i] / b.value[i] )) * (value[i] / b.value[i]) );
			_sys.push_back( ((sys[i] / value[i]) + ( b.sys[i] / b.value[i] )) * (value[i] / b.value[i]) );
		}

		SpectraLoader sl( _pT, _value, _stat, _sys );
		INFO( "SpectraLoader", "Done" );
		return sl;
	}



	SpectraLoader operator* ( double v  ){
		return multiply( v );
	}

	SpectraLoader multiply( double v ){
		INFO( "SpectraLoader", "Divide" );

		vector<double> _pT;
		vector<double> _value;
		vector<double> _stat;
		vector<double> _sys;

		for ( int i = 0; i < value.size(); i++ ){
			_value.push_back( value[i] * v );
			_pT.push_back( pT[i] );
			_stat.push_back( stat[i] * v );
			_sys.push_back( sys[i] * v );
		}

		SpectraLoader sl( _pT, _value, _stat, _sys );
		INFO( "SpectraLoader", "Done" );
		return sl;
	}

};