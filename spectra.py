#!/usr/bin/env python2.7

import argparse
import os
import glob

parser = argparse.ArgumentParser( description="converts spectra to a gooder format" )
parser.add_argument( "needle", help="string matching all files to convert eg path/*" )
parser.add_argument( "output_path", help="path to save output files to" )

args = parser.parse_args()

input_files = glob.glob( args.needle );

t_filename = "spectra_{energy}_{plc}_{iCen}.{ext}"



def convert_file( file_name, energy, plc, output_path ) :
	
	with open( file_name ) as f:
		content = f.readlines()

		iCen = 6
		for x in content :
			
			if x.startswith( "-" ) or x.startswith( "#-" ) :
				if 6 != iCen :
					nf.close()
				nf = open( os.path.join( output_path, t_filename.format( energy=energy, plc=plc, iCen=iCen, ext='dat' ) ), 'w' )
				nf.write( "%15s %15s %15s %15s \n" % ( "pT", "value", "stat_uncertainty", "sys_uncertainty" ) )
				iCen = iCen - 1
				
			else :
				print "parsing", x
				parts = x.split()
				pT =  parts[0]
				value =  parts[ 1 ]
				stat =  parts[ 2 ]

				nf.write( "%15s %15s %15s %15s \n" % (pT, value, stat, repr(0.0) ) )
		nf.close()


for a_file in input_files :
	f_name = os.path.basename( a_file )
	print f_name

	energy = f_name[ 4:6 ]
	if energy[-1] == "_" :
		energy = energy[ 0:-1 ]

	plc = f_name[ f_name.find( "_" ) + 1 : f_name.find( "_", f_name.find( "_" ) + 1 ) ]

	print "Energy =", energy
	print "Plc =", plc

	convert_file( a_file, energy, plc, args.output_path )



