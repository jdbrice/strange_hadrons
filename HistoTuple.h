#ifndef HISTO_TUPLE_H
#define HISTO_TUPLE_H


class HistoTuple {

	TH1* h1, h2;

public:
	HistoTuple( TH1* _h1, TH1* _h2 ){
		h1 = _h1;
		h2 = _h2;
	}
	~HistoTuple(){

	}


	HistoTuple divide( HistoTuple & other ){

		TH1 * h1r = h1->Clone( (h1->GetName() + "_ratio").c_str() );
		TH1 * h2r = h2->Clone( (h2->GetName() + "_ratio").c_str() );

		h1r->Divide( other.h1 );
		h2r->Divide( other.h2 );

		HistoTuple result( h1r, h2r );
		return result;
	}
	HistoTuple operator / ( HistoTuple & other ){
		return divide( other );
	}



};

#endif