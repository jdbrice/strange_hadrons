#include "draw_single_spectra.C"
#include "DoubleSpectraLoader.h"
#include "RooPlotLib.h"
#include "common.C"


vector<double> ks_bins = { 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.6, 3.0, 3.4, 3.8, 4.2 };


int first_bin_for( string plc ){
	if ("la" == plc || "ala" == plc)
		return 1;
	return 0;
}

vector<double> bins_for( string plc ){

	if ( "la" == plc || "ala" == plc )
		return ks_bins; // TODO: correct binning

	return ks_bins;
}


TH1* draw_double_rcp(	string energy = "15", 
						string plc1 = "la",
						string plc2 = "ala",
						string iCen = "0", string iPer = "5",
						double cen_nColl = 800.0, double per_nColl = 20.0, 
						int color = kRed, 
						string draw_opt = ""){

	Logger::setGlobalLogLevel( Logger::llAll );
	// gROOT->SetBatch( true );
	RooPlotLib rpl;

	gStyle->SetOptStat( 0 );

	string cen_fn1 = file_name( energy, plc1, iCen );
	string cen_fn2 = file_name( energy, plc2, iCen );

	string per_fn1 = file_name( energy, plc1, iPer );
	string per_fn2 = file_name( energy, plc2, iPer );


	DoubleSpectraLoader dsl_cen = DoubleSpectraLoader( cen_fn1, cen_fn2, bins_for( plc1 ), first_bin_for( plc1 ) ); 
	DoubleSpectraLoader dsl_per = DoubleSpectraLoader( per_fn1, per_fn2, bins_for( plc2 ), first_bin_for( plc2 ) ); 


	TH1D * h_cen = dsl_cen.statHisto( "cen" );
	TH1D * h_per = dsl_per.statHisto( "per" );

	TH1D * h_rcp = (TH1D*)h_cen->Clone( "rcp" );
	h_rcp->Divide( h_per );

	rpl.style( h_rcp )
		.set( "title", " ; p_{T} [GeV/c]; R_{CP} (" + centrality_labels[ stoi(iCen) ] + ") / (" + centrality_labels[ stoi(iPer) ] + ")  " )
		.set( "color", color )
		.set( "markersize", 2 )
		.set( "markerstyle", 8 )
		.set( "draw", draw_opt +" pex0" )
		.draw();

	gPad->SetRightMargin( 0.01 );
	gPad->SetTopMargin( 0.01 );


	return h_rcp;
}