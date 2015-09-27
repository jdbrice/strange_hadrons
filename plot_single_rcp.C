#include "RcpLoader.h"

#include "RooPlotLib.h"
#include "Logger.h"

string file_name( string energy, string plc ){
	return "rcp_data/Rcp_" + plc + "_" + energy + "GeV.txt";
}

TGraphErrors * plot_single_rcp( string energy ="15", string plc="Ks0" ){
	Logger::setGlobalLogLevel( Logger::llAll );


	RcpLoader rcp( file_name( energy, plc ) );
	

	TGraphErrors * g_rcp = rcp.statGraph();

	RooPlotLib rpl;


	rpl.style( g_rcp )
		.set( "color", kRed )
		.set( "draw", "same pe" )
		.draw();

	return g_rcp;
}