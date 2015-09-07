#include "draw_single_spectra.C"
#include "RooPlotLib.h"
#include "Reporter.h"


void draw_spectra_vs_centrality( string en, string plc ){
	Logger::setGlobalLogLevel( Logger::llAll );

	Reporter rp( "tmp.pdf", 900, 700 );
	RooPlotLib rpl;

	TH1 * master;
	int iColor = 0;
	for ( string iCen : centralities ){
		INFO( "Drawing " << en << " " << plc << " " << iCen );
		
		if ( 0 == iColor )
			master = draw_single_spectra( en, plc, iCen, colors[ iColor ], "", pow( 10, -iColor ) );
		else 
			draw_single_spectra( en, plc, iCen, colors[ iColor ], "same", pow( 10, -iColor ) );

		iColor ++;
	}

	master->GetYaxis()->SetRangeUser( 10e-15, 1e2 );
	rpl.style( master ).set( "yto", 1.1 ).set( "markerstyle", 8 );


	rp.saveImage( "img/spectra_" + en + "_" + plc + ".pdf" );
	

}