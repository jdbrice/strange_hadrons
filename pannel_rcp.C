#include "plot_rcp_for_energy.C"


void pannel_rcp(){


	Reporter rp( "img/pannel_rcp.pdf", 1800, 900 );

	rp.newPage( 3, 2, 0.0, 0.0 );

	TCanvas * c = rp.getCanvas();
	c->SetTopMargin( 0.01 ); 
	c->cd(0);
	gPad->SetTopMargin( 0.01 ); 

	rp.cd(1, 1);


	for ( string en: renergies ){

		if ( on_left( en ) )
			gPad->SetLeftMargin( 0.15 );
		if ( on_bottom( en ) )
			gPad->SetBottomMargin( 0.18 );
		if ( on_top( en ) )
			gPad->SetTopMargin( 0.01 );


		plot_rcp_for_energy( en, true );
		rp.saveImage( "img/pannel_rcp.png" );
		rp.next();
	}

}