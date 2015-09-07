
#include "draw_single_rcp.C"
#include "draw_double_rcp.C"
#include "draw_ncoll_uncertainty.C"
#include "Reporter.h"
#include "RooPlotLib.h"
#include "common.C"

void draw_rcp_for_energy( string en, string iCen = "0", string iPer = "5" ){

	Reporter rp( "tmp.pdf", 400, 600 );
	RooPlotLib rpl;

	double cen_n_coll = n_coll[ en ][ stoi( iCen ) ];
	double per_n_coll = n_coll[ en ][ stoi( iPer ) ];

	TH1 * master;

	int iColor = 0;
	

			
			master = draw_single_rcp( en, "ks", iCen, iPer, cen_n_coll, per_n_coll, colors[ 0 ], "" );

			draw_double_rcp( en, "la", "ala", iCen, iPer, cen_n_coll, per_n_coll, colors[ 1 ], "same" );
			draw_double_rcp( en, "xi", "axi", iCen, iPer, cen_n_coll, per_n_coll, colors[ 2 ], "same" );
		
	

	draw_ncoll_uncertainty( 0, cen_n_coll, 29, per_n_coll, 7, true );

	
	rp.saveImage( "img/rcp_" + en + "_" + iCen + "_" + iPer + ".pdf" );

}