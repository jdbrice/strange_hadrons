#ifndef SINGLE_RCP
#define SINGLE_RCP


#include "draw_single_spectra.C"
#include "RooPlotLib.h"

int n_la_bins = 14;
double la_bins[] = {
	 0.20586,
0.402734,
0.600391,
0.799072,
0.998142,
 1.19746,
 1.39697,
 1.59659,
 1.79627,
 2.06013,
 2.47311,
 2.97147,
 3.47037,
 4.05112,
 4.71352
};


int n_ks_bins = 15;
double ks_bins[] = {
0.2,
0.4,
0.6,
0.8,
1.0,
1.2,
1.4,
1.6,
1.8,
2.0,
2.2,
2.6,
3.0,
3.4,
3.8,
4.2
};


TH1 * normalize_la( TH1 * in ){
	string name = string(in->GetName()) + "_normed";
	TH1 * out = new TH1D( name.c_str(), "", n_la_bins, la_bins );

	for ( int i = 1; i <= in->GetNbinsX(); i++ ){
		out->SetBinContent( i + 1, in->GetBinContent( i ) );
		out->SetBinError( i + 1, in->GetBinError( i ) );
	}
	return out;
}

TH1 * normalize_ks( TH1 * in ){
	string name = string(in->GetName()) + "_normed";
	TH1 * out = new TH1D( name.c_str(), "", n_ks_bins, ks_bins );

	for ( int i = 1; i <= in->GetNbinsX(); i++ ){
		out->SetBinContent( i + 1, in->GetBinContent( i ) );
		out->SetBinError( i + 1, in->GetBinError( i ) );
	}
	return out;
}



TH1* draw_single_rcp(string energy, string plc, string iCen = "0", string iPer = "5",
							double cen_nColl = 800.0, double per_nColl = 20.0, 
							int color = kRed, string draw_opt = ""){

	RooPlotLib rpl;

	gStyle->SetOptStat( 0 );
	INFO( "Filenames" );

	string cen_fn = file_name( energy, plc, iCen );
	string per_fn = file_name( energy, plc, iPer );

	SpectraLoader cen_sl( cen_fn );
	SpectraLoader per_sl( per_fn );

	if ( "la" == plc || "ala" == plc){
		cen_sl.trim(1);
		per_sl.trim(1);
	}
	
	TH1* cen_stat =  cen_sl.statHisto( cen_fn + "_cen_stat" ) ;
	TH1* per_stat =  per_sl.statHisto( per_fn + "_per_stat" ) ;

	

	if ( "ks" == plc ){
		INFO( "Normalizing ks" );
		cen_stat = normalize_ks( cen_stat );
		per_stat = normalize_ks( per_stat );
	}

	

	if ( "la" == plc || "ala" == plc){
		cen_stat = normalize_la( cen_stat );
		per_stat = normalize_la( per_stat );
	}

	TH1* cen_stat_rcp = (TH1*)cen_stat->Clone( (cen_fn + "_cen_stat_rcp").c_str() );
	rpl.style( cen_stat_rcp ).set( "title", " ;pT [GeV/c]; R_{CP} (" + centrality_labels[ stoi( iCen ) ] + " / " + centrality_labels[ stoi( iPer ) ] + " )" );


	cen_stat_rcp->Divide( per_stat );
	cen_stat_rcp->Scale( per_nColl / cen_nColl );

	cen_stat_rcp->SetMarkerStyle( 8 );
	cen_stat_rcp->SetLineColor( color );
	cen_stat_rcp->SetMarkerColor( color );

	cen_stat_rcp->Draw( (draw_opt + " e1").c_str() );

	cen_stat_rcp->GetYaxis()->SetRangeUser( 0.25, 5 );

	gPad->SetLogy(1);
	gPad->SetGrid( 1, 1 );


	return cen_stat_rcp;

}

#endif