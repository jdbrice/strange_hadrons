
#include "SpectraLoader.h"

void make_spectra( string fname ){
	
	Logger::setGlobalLogLevel( Logger::llAll );

	SpectraLoader sl( fname );

	TGraphErrors * graph = sl.statGraph();

	//graph->Draw();

	TH1D * hStat = sl.relStatHisto( "test" );
	TH1D * hSys = sl.relSysHisto( "test2" );
	hSys->SetLineColor( kRed );
	hStat->Draw("same");
	hSys->Draw("same");

}