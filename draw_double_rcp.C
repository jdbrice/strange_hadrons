#include "draw_single_spectra.C"
#include "draw_single_rcp.C"
#include "RooPlotLib.h"

TH1* draw_double_rcp(string energy, string plc1, string plc2, string iCen = "0", string iPer = "5",
							double cen_nColl = 800.0, double per_nColl = 20.0, 
							int color = kRed, string draw_opt = ""){

	gROOT->SetBatch( true );
	RooPlotLib rpl;

	gStyle->SetOptStat( 0 );

	string cen_fn1 = file_name( energy, plc1, iCen );
	string cen_fn2 = file_name( energy, plc2, iCen );

	string per_fn1 = file_name( energy, plc1, iPer );
	string per_fn2 = file_name( energy, plc2, iPer );

	SpectraLoader cen_sl1( cen_fn1 );
	SpectraLoader per_sl1( per_fn1 );

	SpectraLoader cen_sl2( cen_fn2 );
	SpectraLoader per_sl2( per_fn2 );
	

	// if ( "15" == energy && ("la" == plc1 || "la" == plc2) ){

	// 	cen_sl1.trim(1);
	// 	per_sl1.trim(1);
	// 	cen_sl2.trim(1);
	// 	per_sl2.trim(1);

	// 	cen_sl1.trunc(1);
	// 	per_sl1.trunc(1);
	// 	cen_sl2.trunc(1);
	// 	per_sl2.trunc(1);
	// }

	// if ( "15" == energy && "xi" == plc1 || "xi" == plc2 ){

	// 	cen_sl1.trunc(1);
	// 	per_sl1.trunc(1);
	// 	cen_sl2.trunc(1);
	// 	per_sl2.trunc(1);
	// }

	TH1* cen_stat =  cen_sl1.statHisto( cen_fn1 + "_cen_stat" );
	TH1* per_stat =  per_sl1.statHisto( per_fn1 + "_per_stat" );

	TH1* cen_stat2 =  cen_sl2.statHisto( cen_fn2 + "_cen_stat" );
	TH1* per_stat2 =  per_sl2.statHisto( per_fn2 + "_per_stat" );

	if ( "la" == plc1 || "la" == plc2 ){

		cen_stat = normalize_la( cen_stat );
		per_stat = normalize_la( per_stat );
		cen_stat2 = normalize_la( cen_stat2 );
		per_stat2 = normalize_la( per_stat2 );
	}

	if ( "xi" == plc1 || "xi" == plc2 ){

		cen_stat = normalize_xi( cen_stat );
		per_stat = normalize_xi( per_stat );
		cen_stat2 = normalize_xi( cen_stat2 );
		per_stat2 = normalize_xi( per_stat2 );
	}

	cen_stat->Add( cen_stat2 );
	per_stat->Add( per_stat2 );

	

	TH1* cen_stat_rcp = (TH1*)cen_stat->Clone( (cen_fn1 + "_cen_stat_rcp").c_str() );

	if ( "la" == plc1 || "ala" == plc1){
		cen_stat_rcp->SetBinContent( 1, 0 );
		cen_stat_rcp->SetBinError( 1, 0 );
	}

	rpl.style( cen_stat_rcp ).set( "title", " ;pT [GeV/c]" );

	cen_stat_rcp->Divide( per_stat );
	cen_stat_rcp->Scale( per_nColl / cen_nColl );

	cen_stat_rcp->SetMarkerStyle( 8 );
	cen_stat_rcp->SetLineColor( color );
	cen_stat_rcp->SetMarkerColor( color );

	cen_stat_rcp->Draw( (draw_opt + " e1").c_str() );

	cen_stat_rcp->GetYaxis()->SetRangeUser( 0.25, 10 );

	// gPad->SetLogy(1);
	gPad->SetGrid( 1, 1 );


	return cen_stat_rcp;

}