#include "draw_single_spectra.C"

TGraph *  graph_ratio( 
					string energy ="15", 
					string plc1 = "ala", string plc2 = "ks", 
					string iCen = "0",
					int color = kRed,
					string draw_opt = "" ){
	

	if ( "" == draw_opt ){
		TH1 * master = new TH1F( "frame", (" ; pT [GeV/c] ; " + plc_label( plc1) +"/" + plc_label( plc2) ).c_str(), 100, 0, 5 );
		master->Draw();
		master->GetYaxis()->SetRangeUser(0.2, 5);
	}

	gStyle->SetOptStat( 0 );
	INFO( "Filenames" );

	string fn1 = file_name( energy, plc1, iCen );
	string fn2 = file_name( energy, plc2, iCen );

	SpectraLoader num_sl( fn1 );
	SpectraLoader den_sl( fn2 );

	TH1 * num = num_sl.statHisto( "num" );
	TH1 * den = den_sl.statHisto( "den" );

	num->Divide( den );
	SpectraLoader sl( num_sl.pT, num );

	TGraphErrors * g = sl.statGraph();
	g->SetLineColor( color );
	g->SetMarkerStyle( 8 );
	g->SetMarkerColor( color );


	g->Draw( "pe" );

	return g;

}