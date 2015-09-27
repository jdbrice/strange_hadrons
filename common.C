#ifndef DANNY
#define DANNY

vector<string> centralities 		= { "0", "1", "2", "3", "4", "5", "6" };
vector<string> centrality_labels 	= { "0-5%", "5-10%", "10-20%", "20-30%", "30-40%", "40-60%", "60-80%" };

vector<string> energies = { "7", "11", "15", "19", "27", "39" };
vector<string> renergies = { "39", "27", "19", "15", "11", "7" };


vector<int> colors 		= { kRed + 1, 	kAzure - 3, 	kGreen + 1,		 kMagenta + 3, 		kOrange + 7, 	kBlue + 3, kCyan	};

vector<int> markers = { 20, 21, 34, 22, 33, 29, 23 };

map<string, vector<double> > n_coll = 
{
	{"7", 	{ 773.78160, 628.57471, 450.06667, 283.09279, 170.62760, 74.26815, 19.19978} },
    {"11", 	{  784.45235, 635.10335, 453.30864, 283.86052, 171.77151, 74.74965, 19.08872} },
    {"15", 	{  787.915, 639, 455, 284, 171, 71.739, 18.305 } },
    {"19", 	{  799.84, 642.84, 458.4, 284.54252, 169.88653, 74.01196, 18.91901 } },
    {"27", 	{  841.47851, 693.95012, 496.90694, 311.59162, 187.65520, 81.95383, 19.97044} },
	{"39", 	{  852.69718, 687.23303, 491.68086, 305.79089, 182.57132, 78.54930, 19.39689 } }
};


bool on_left( string en ){
	if ( "39" == en || "15" == en)
		return true;
	return false;
}

bool on_bottom( string en ){
	if ( "15" == en || "11" == en || "7" == en )
		return true;
	return false;
}

bool on_top( string en ){
	return !on_bottom( en);
}

string energy_label( string en ){
	if ( "27" == en )
		return "Au+Au 27";
	if ( "39" == en )
		return "Au+Au 39";
	if ( "19" == en )
		return "Au+Au 19.6";
	if ( "15" == en )
		return "Au+Au 14.5";
	if ( "11" == en )
		return "Au+Au 11.5";
	if ( "7" == en )
		return "Au+Au 7.7";
}

string energy_label_short( string en ){
	if ( "27" == en )
		return "27";
	if ( "39" == en )
		return "39";
	if ( "19" == en )
		return "19.6";
	if ( "15" == en )
		return "14.5";
	if ( "11" == en )
		return "11.5";
	if ( "7" == en )
		return "7.7";
}




#endif