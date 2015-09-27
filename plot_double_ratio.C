#include "plot_single_ratio.C"
#include "common.C"


TGraph * plot_double_ratio( string energy ="15", string iNum="0", string iDen="6", string plc ="la", int color = kRed, double scaler = 1.0 ){

	Logger::setGlobalLogLevel( Logger::llAll );
	string tag = "double_ratio";

	string fn1 = file_name( energy, plc, iNum );
	string fn2 = file_name( energy, plc, iDen );

	INFO( tag, "Loading " << fn1 );
	INFO( tag, "Loading " << fn2 );
	SpectraLoader num( fn1 );
	SpectraLoader den( fn2 );

	SpectraLoader ratio = num / den;

	ratio = ratio * scaler;
	
	TGraphErrors * g_ratio = ratio.statGraph();

	RooPlotLib rpl;


	rpl.style( g_ratio )
		.set( "color", kRed )
		.set( "draw", "same pe" )
		.set( "optstat", 0 )
		.draw();

	TLine * lUnity = new TLine( 0, scaler, 5.0, scaler );

	rpl.style( lUnity ).set( "color", color ).set( "lw", 2 );
	lUnity->SetLineColor( color );
	lUnity->SetLineWidth( 6 );
	lUnity->Draw();
	lUnity->SetLineStyle( kDashed );

	return g_ratio;


}