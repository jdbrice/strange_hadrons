#include "SpectraLoader.h"

#include "RooPlotLib.h"
#include "Logger.h"

string file_name( string energy, string plc, string iCen ){
	return "ratio_data/ratio_" + energy + "_" + plc + "_ks0_" + iCen + ".dat";
}

TGraphErrors * plot_single_ratio( string energy ="15", string plc="la", string iCen ="0" ){
	Logger::setGlobalLogLevel( Logger::llAll );
	string tag = "single_ratio";

	string fn = file_name( energy, plc, iCen );

	INFO( tag, "Loading " << fn );
	SpectraLoader ratio( file_name( energy, plc, iCen ) );
	

	// truncate since some was not shown at sQM
	if ( "15" == energy )
		ratio.trunc( 2 );


	TGraphErrors * g_ratio = ratio.statGraph();

	RooPlotLib rpl;


	rpl.style( g_ratio )
		.set( "color", kRed )
		.set( "draw", "same pe" )
		.set( "optstat", 0 )
		.draw();

	return g_ratio;
}