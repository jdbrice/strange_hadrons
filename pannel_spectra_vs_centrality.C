#include "draw_spectra_vs_centrality.C"



void pannel_spectra_vs_centrality( string en = "15" ){

	Reporter rp( "_tmp.pdf", 1200, 700 );

	rp.newPage( 3, 2, 0, 0 );

	for ( string plc : { "la", "xi", "ks", "ala", "axi" } ){
		draw_spectra_vs_centrality(en, plc, &rp);

		rp.savePage();
		if ( "axi" != plc )
			rp.next();
	}

	rp.saveImage( "img/pannel_spectra_vs_centrality_" + en + ".pdf" );

}