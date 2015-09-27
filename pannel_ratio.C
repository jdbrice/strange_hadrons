#include "plot_ratio_vs_centrality.C"


void pannel_ratio( string plc = "la" ){


	Reporter rp( "img/pannel_ratio.pdf", 1150, 900 );

	rp.newPage( 3, 2, 0.0, 0.005 );

	gStyle->SetTitleSize( 0.25, "t" );
	gStyle->SetTitleX( 0.2 );

	TCanvas * c = rp.getCanvas();
	c->SetTopMargin( 0.01 ); 
	
	c->SetTopMargin( 0.001 ); 

	rp.cd(1, 1);


	for ( string en: renergies ){

		// all need y axis shown
		if ( "la" == plc ){
			gPad->SetLeftMargin( 0.13 );
			if ( on_left( en ) )
				gPad->SetLeftMargin( 0.18 );
			if ( on_bottom( en ) )
				gPad->SetBottomMargin( 0.18 );
			if ( on_top( en ) )
				gPad->SetTopMargin( 0.01 );
		} else {
			gPad->SetLeftMargin( 0.15 );
			if ( on_bottom( en ) )
				gPad->SetBottomMargin( 0.18 );
		}


		plot_ratio_vs_centrality( en, plc );
		rp.saveImage( "img/pannel_ratio_" + plc + "_over_ks0.png" );
		rp.next();
	}

}