
#include "SpectraLoader.h"

void make_spectra( string fname ){
	
	Logger::setGlobalLogLevel( Logger::llAll );

	SpectraLoader sl( fname );

	TH1D * hStat = sl.statHisto( "test" );
	
	
	hStat->Draw("");
	

}