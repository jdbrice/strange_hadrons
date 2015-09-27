#include "plot_double_ratio.C"

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


void plot_double_ratio_vs_energy( string iNum="0", string iDen="6", string plc = "la" ){

	Reporter rp( "img/rp_double_ratio.pdf", 500, 750 );

	RooPlotLib rpl;

	gPad->SetTopMargin( 0.01);
	TLegend * leg = new TLegend( 0.6, 0.1, 0.9, 0.4 );
	leg-> SetNColumns(1);
	leg->SetTextFont( 52 );
	leg->SetTextSize( 0.05 );

	gPad->SetLeftMargin( 0.15 );

	TH1 * master = new TH1F( "frame",  " ;   ", 100, 0, 10 );
	rpl.style( master ).set( "yto", 1.2 ).draw();

	float scaler = 32.0;
	int iColor = 0;
	for ( string energy : renergies ){

		TGraph * g = plot_double_ratio( energy, iNum, iDen, plc, colors[iColor], scaler );


		rpl.style( g )
			.set( "markerstyle", markers[ iColor ] )
			.set( "markersize", 2 )
			.set( "color", colors[ iColor ] );

		string ll = (energy_label_short( energy ) + " x " + ts( (int)scaler )).c_str();
		leg->AddEntry( g, ll.c_str() );

		scaler /= 2;
		iColor++;
	} 


	rpl.style( master )
		.set( "xr", 0, 5.2 )
		.set( "yr", .3, 140 )
		.set( "logy", 1 );

	string yt = centrality_labels[ stoi( iNum ) ] + " central / " + centrality_labels[ stoi( iDen ) ] + " central " + plc_label( plc ) + "/ K_{s}^{0} Ratio";

	rpl.style( master )
		.set( "yr", 0.3, 140 )
		.set( "yts", 0.06 )
		.set( "yls", 0.05 )
		.set( "yto", 1.2 )
		.set( "xr", 0, 5 )
		.set( "title", " ; p_{T} [GeV/c]; " + yt )
		.set( "xts", 0.06 )
		.set( "xto", 0.7 );

	leg->Draw();
	gPad->SetGrid(1, 0);

	rp.saveImage( "img/double_ratio_" + iNum+"_over_" + iDen + "_" + plc + "_over_ks0_.pdf" );


}