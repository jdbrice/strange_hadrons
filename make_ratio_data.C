#include "draw_single_spectra.C"


void make_ratio_data( string plc = "la", string energy = "15" ){
	string tag = "ratio_data";
	Logger::setGlobalLogLevel( Logger::llAll );

	RooPlotLib rpl;

	TH1D * frame = new TH1D( "frame", "frame", 100, 0, 10 );
	rpl.style( frame )
		.set( "yr", 0, 5 )
		.set( "xr", 0, 5 )
		.draw();

	for ( int iCen = 0; iCen < 7; iCen ++ ){
		string fn1 = file_name( energy, plc, ts(iCen) );
		string fn2 = file_name( energy, "ksrb", ts(iCen) );
		if ( !file_exists( fn1 ) || !file_exists( fn2 ) ){
			INFO( tag, fn1 << " or " << fn2 << " DNE" );
			continue;
		}

		SpectraLoader sl1( fn1 );
		SpectraLoader sl2( fn2 );
		sl2.trim(1);
		sl2.trunc( 2 );

		INFO( "first pT = " << sl1.value[ 0 ] );

		SpectraLoader slRatio = sl1 / sl2;

		TGraph * g = slRatio.statGraph();

		rpl.style( g )
			.set( "color", iCen )
			.set( "draw", "same" )
			.draw();

		slRatio.export_data( "ratio_data/ratio_" + energy + "_" + plc +"_ks0_" + ts(iCen) +".dat" );


	}



	
}