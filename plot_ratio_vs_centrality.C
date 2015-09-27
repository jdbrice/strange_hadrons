
#include "plot_single_ratio.C"
#include "common.C"

void plot_ratio_vs_centrality( string energy="15", string plc="la", bool pannel = true ){

	RooPlotLib rpl;

	if ( !pannel  ){
		gPad->SetLeftMargin( 0.15 );
		gPad->SetBottomMargin( 0.15 );
		gPad->SetRightMargin( 0.01 );
		gPad->SetTopMargin( 0.01 );
	}

	gPad->SetTopMargin( 0.001 );
	gStyle->SetTitleFontSize(0.1);


	TH1 * master = new TH1F( "frame",  " ;   ", 100, 0, 10 );
	rpl.style( master ).set( "yto", 1.3 ).draw();
	

	TLegend * leg;
	if ( "la" == plc  )
		leg = new TLegend( 0.55, 0.3, 0.99, 0.9, "Centrality:" );
	else 
		leg = new TLegend( 0.6, 0.25, 0.99, 0.85, "Centrality:" );
	leg-> SetNColumns(1);
	leg->SetTextFont( 52 );
	leg->SetTextSize( 0.07 ); 

	int iColor = 0;
	for ( string iCen : centralities ){

		TGraph * g = plot_single_ratio( energy, plc, iCen );

		rpl.style( g )
			.set( "mst", markers[ iColor ] )
			.set( "ms", 2 )
			.set( "color", colors[iColor] );

		leg->AddEntry( g, centrality_labels[ iColor ].c_str(), "pe" );  

		iColor++;
	}


	rpl.style( master )
		.set( "title", energy_label( energy ) + " ; p_{T} [GeV/c]; #Lambda / K_{s}^{0}" )
		.set( "yr", 0, 5.2 )
		.set( "xr", 0, 4.5 )
		.set( "xls", 0.08 )
		.set( "yls", 0.08 )
		.set( "yts", 0.08 )
		.set( "xts", 0.08 )
		.set( "xticks", 6, 5, 0, 1 );

	if ( pannel )
		rpl.style( master )
		.set( "title", energy_label( energy ) + "; p_{T} [GeV/c];" );

	if ( on_left( energy ) )
		rpl.set( "yto", 0.85 );
	else
		rpl.set( "yto", 1.75 );

	
	if ( "la" == plc ){
		if ( "7" == energy ){
			rpl.set( "yr", 0.15, 9.5 );
			leg->Draw("same");
		}
		if ( "11" == energy )
			rpl.set( "yr", 0.15, 7.7 );
		if ( "15" == energy )
			rpl.set( "yr", 0.15, 6.2 );
		if ( "19" == energy )
			rpl.set( "yr", 0.15, 5.7 );
		if ( "27" == energy )
			rpl.set( "yr", 0.15, 4.7 );
		if ( "39" == energy )
			rpl.set( "yr", 0.15, 3.2 );
	} else if ( "ala" == plc ){
		if ( on_top( energy ) )
			rpl.set( "yr", 0.001, 1.1 );
		if ( on_bottom(energy) )
			rpl.set( "yr", 0.001, 0.59 );
		if ( "7" == energy ){
			rpl.set( "yr", 0.001, 0.15 );
			leg->Draw("same");
		}
		// if ( "11" == energy )
		// 	rpl.set( "yr", 0.001, 0.49 );
		// if ( "15" == energy )
		// 	rpl.set( "yr", 0.05, 0.49 );
		// if ( "19" == energy )
		// 	rpl.set( "yr", 0.05, 1.1 );
		if ( "27" == energy )
			rpl.set( "yr", 0.001, 1.3 );
		// if ( "39" == energy )
		// 	rpl.set( "yr", 0.05, 1.1 );
	}



}