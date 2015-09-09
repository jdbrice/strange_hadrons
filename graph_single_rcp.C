#include "draw_single_spectra.C"


TGraph * graph_single_rcp( 	string energy = "15", 
							string plc = "ks", 
							string iCen = "0", string iPer = "5",
							double cen_nColl = 787.915, double per_nColl = 71.739, 
							int color = kRed, 
							string draw_opt = ""){

	if ( "" == draw_opt ){
		TH1 * master = new TH1F( "frame", (plc_label( plc) + " ; pT [GeV/c] ; dN^{2} / ( N_{evt} 2 #pi pT dpT dy )  ").c_str(), 100, 0, 5 );
		master->Draw();
		master->GetYaxis()->SetRangeUser(0.2, 5);
	}

	gStyle->SetOptStat( 0 );
	INFO( "Filenames" );

	string cen_fn = file_name( energy, plc, iCen );
	string per_fn = file_name( energy, plc, iPer );

	SpectraLoader cen_sl( cen_fn );
	SpectraLoader per_sl( per_fn );

	TH1 * num = cen_sl.statHisto( "cen_num" );
	TH1 * den = per_sl.statHisto( "per_den" );

	num->Divide( den );
	num->Scale( per_nColl / cen_nColl );

	SpectraLoader sl( cen_sl.pT, num );

	TGraphErrors * g = sl.statGraph();
	g->SetLineColor( color );
	g->SetMarkerStyle( 8 );
	g->SetMarkerColor( color );


	g->Draw( "pe" );

	return g;

}