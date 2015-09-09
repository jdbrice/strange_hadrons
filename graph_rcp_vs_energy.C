#include "graph_single_rcp.C"


void graph_rcp_vs_energy( string plc ="ks", string iCen = "0", string iPer = "6", Reporter * rp = nullptr ){

	Logger::setGlobalLogLevel( Logger::llAll );

	
	RooPlotLib rpl;

	gStyle->SetTitleSize( 0.11, "t" );
	gStyle->SetTitleX( 0.72 );
	gStyle->SetTitleY( 0.9);

	TLegend * leg = new TLegend( 0.05, 0.1, 0.95, 0.95 );
	leg->SetTextFont( 52 );
	leg->SetTextSize( 0.07 );


	TH1 * master = new TH1F( "frame", (plc_label( plc) + " ; R_{CP} ( " + centrality_labels[ stoi(iCen) ] + " ) / ( " + centrality_labels[ stoi(iCen) ] + " )" ).c_str(), 100, 0, 5 );
	rpl.style( master ).set( "yto", 1.3 ).draw();
	
	int iColor = 0;
	for ( string en : energies ){

		TGraph * g = graph_single_rcp( en, plc, iCen, iPer, 
			n_coll[en][ stoi(iCen) ], n_coll[en][ stoi(iPer) ],
			colors[ iColor ], "same pe" );
		g->SetFillColorAlpha( colors[iColor], 0.33  ) ;

		string sc = en ;
		
		leg->AddEntry( g, sc.c_str() );
		iColor ++;
	}

	master->GetXaxis()->SetRangeUser( 0.1, 4.8 );
	master->GetYaxis()->SetRangeUser( .2, 5 );

	if ( nullptr != rp ){ 	
		rp->saveImage( "img/spectra_" + iCen + "_over_" + iPer + "_" + plc + ".pdf" );

		if ( "axi" == plc ){
			rp->next();
			leg->Draw();
		}
	}	
	
}