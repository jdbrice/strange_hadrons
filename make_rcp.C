
#include "SpectraLoader.h"

void make_rcp( string fname, int iCen = 0, int iPer = 6 ){
	
	Logger::setGlobalLogLevel( Logger::llAll );

	SpectraLoader sCen( fname + ts(iCen) + ".dat" );
	sCen.trim( 1 );
	SpectraLoader sPer( fname + ts(iPer) + ".dat" );
	sPer.trim( 1 );

	TH1D * hCen = sCen.statHisto( "cen");
	TH1D * hPer = sPer.statHisto( "per");

	TH1D * rcp = (TH1D*)hCen->Clone( "rcp" );

	rcp->Divide( hPer );
	rcp->Scale( 18.3 / 790.0 );

	rcp->Draw();
	

}