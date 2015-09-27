#include "plot_single_rcp.C"
#include "common.C"


string legend_label( string plc ){
	if ( "Lambda" == plc )
		return "#Lambda + #bar{#Lambda}";
	if ( "Omega" == plc )
		return "#Omega^{-} + #Omega^{+}";
	if ( "Xi" == plc )
		return "#Xi^{-} + #Xi^{+}";
	if ( "Ks0" == plc )
		return "K_{s}^{0}";
}


void plot_rcp_for_energy( string energy = "15", bool pannel = false ){

	RooPlotLib rpl;

	TH1 * master = new TH1D( "frame", "frame", 100, 0, 10 );
	master->Draw();

	if ( !pannel  ){
		gPad->SetLeftMargin( 0.15 );
		gPad->SetBottomMargin( 0.15 );
		gPad->SetRightMargin( 0.01 );
		gPad->SetTopMargin( 0.01 );
	}

	gStyle->SetTitleFontSize(0.1);

	vector<string> plcs = { "Ks0", "Lambda", "Xi" };

	if ( "19" == energy || "27" == energy || "39" == energy )
		plcs.push_back( "Omega" ); 


	TLegend * leg = new TLegend( 0.2, 0.5, 0.65, 0.85 );
	leg-> SetNColumns(2);
	leg->SetTextFont( 52 );
	leg->SetTextSize( 0.07 ); 

	int index = 0;
	for ( string plc : plcs){
		TGraphErrors * g = plot_single_rcp( energy, plc );

		rpl.style( g )
			.set( "color", colors[ index ] )
			.set( "markerstyle", markers[ index ] )
			.set( "markersize", 2 );

		rpl.style( g->GetHistogram() )
			.set( "titlesize", 0.25 );

		leg->AddEntry( g, legend_label(plc).c_str(), "pe" );


		index ++;
	}

	rpl.style( master )
		//.set( "title", energy + " GeV; p_{T} [GeV/c]; R_{CP} (0-5%) / (40-60%)" )
		.set( "title", energy_label( energy ) + " GeV; p_{T} [GeV/c]" )
		.set( "optstat", 0 )
		.set( "yr", 0.2, 4.2 )
		.set( "xr", 0.2, 5.2 )
		.set( "xls", 0.08 )
		.set( "yls", 0.08 )
		.set( "yts", 0.08 )
		.set( "xts", 0.08 );

	TLine * lUnity = new TLine( 0.2, 1, 5.2, 1 );
	rpl.style( lUnity )
		.set( "color", kBlack )
		.set( "linewidth", 4 )
		.set( "linestyle", kDashed )
		.set( "draw", "same" )
		.draw();

	if ( "39" == energy )
		leg->Draw("same");
	



}