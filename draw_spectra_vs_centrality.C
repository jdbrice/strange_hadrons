#include "draw_single_spectra.C"
#include "RooPlotLib.h"
#include "Reporter.h"


void draw_spectra_vs_centrality( string en, string plc, Reporter *rp = nullptr ){
	Logger::setGlobalLogLevel( Logger::llAll );

	
	RooPlotLib rpl;

	gStyle->SetTitleSize( 0.11, "t" );
	gStyle->SetTitleX( 0.72 );
	gStyle->SetTitleY( 0.9);

	TLegend * leg = new TLegend( 0.05, 0.1, 0.95, 0.95 );
	leg->SetTextFont( 52 );
	leg->SetTextSize( 0.07 );


	TH1 * master = new TH1F( "frame", (plc_label( plc) + " ; pT [GeV/c] ; dN^{2} / ( N_{evt} 2 #pi pT dpT dy )  ").c_str(), 100, 0, 5 );
	rpl.style( master ).set( "yto", 1.3 ).draw();
	
	int iColor = 0;
	for ( string iCen : centralities ){
		INFO( "Drawing " << en << " " << plc << " " << iCen );
		
		TGraph * g = draw_single_spectra( en, plc, iCen, colors[ iColor ], "same pe", pow( 10, -iColor ) );

		g->SetFillColorAlpha( colors[iColor], 0.33  ) ;

		string sc = centrality_labels[iColor] + " x 1";
		if ( iColor > 0 ){
			sc = centrality_labels[iColor] + " x 10^{-" + ts(iColor) + "}";
		}

		leg->AddEntry( g, sc.c_str() );

		iColor ++;
	}

	master->GetXaxis()->SetRangeUser( 0.1, 4.8 );
	master->GetYaxis()->SetRangeUser( 5e-16, 5e2 );

	if ( nullptr != rp ){ 	
		rp->saveImage( "img/spectra_" + en + "_" + plc + ".pdf" );

		if ( "axi" == plc ){
			rp->next();
			leg->Draw();
		}
	}
	

}