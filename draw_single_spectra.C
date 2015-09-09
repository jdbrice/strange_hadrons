#ifndef DRAW_SINGLE_SPECTRA_C
#define DRAW_SINGLE_SPECTRA_C


#include "SpectraLoader.h"
#include "Utils.h"
#include "Logger.h"
#include "common.C"

#include <sys/stat.h>

 bool file_exists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

string file_name( string energy, string plc, string iCen ){
	string base = "/Users/danielbrandenburg/bnl/local/work/strangeHadronPresentation/converted_spectra/";
	return base + "spectra_" + energy + "_" + plc + "_" + iCen + ".dat";

}

string plc_label( string plc ){
	if ("la" == plc )
		return "#Lambda";
	if ("ala" == plc )
		return "#bar{#Lambda}";

	if ("xi" == plc )
		return "#Xi^{-}";
	if ("axi" == plc )
		return "#bar{#Xi}^{+}";

	if ( "ks" == plc )
		return "K^{0}_{S}";

	return "";
}

TGraphErrors* draw_single_spectra( 	string energy, string plc, string iCen,
							int color = kRed, string draw_opt = "", double scaler = 1.0 ){

	Logger::setGlobalLogLevel( Logger::llAll );
	gStyle->SetOptStat( 0 );


	string fn = file_name( energy, plc, iCen );
	if ( !file_exists( fn ) )
		return new TGraphErrors();



	INFO( "Loading " << fn )
	SpectraLoader sl( fn );

	sl = sl * scaler;

	TGraphErrors* stat = sl.statGraph( );

	//stat->Scale( scaler );

	// if ( "la" == plc || "ala" == plc){
	// 	stat->SetBinContent( 1, 0 );
	// 	stat->SetBinError( 1, 0 );
	// }

	
	stat->SetTitle( " ; pT [GeV/c]; dN^{2} / ( N_{evt} 2 #pi pT dpT dy )" );
	stat->SetLineColor( color );
	stat->SetMarkerStyle( 8 );
	stat->SetMarkerColor( color );
	
	stat->Draw( draw_opt.c_str() );

	gPad->SetLogy(1);

	return stat;

}

#endif