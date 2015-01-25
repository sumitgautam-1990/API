/**
 * File: TestAppIfenConvert.cpp
 * Author: T. Pany
 *  
 * Copyright(c) 2014 Institute of Navigation
 * http://www.ion.org
 *
 * The program demonstrates the converion of IFEN internal meta data 
 * structures to/from the ION standard.
 *  
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

// include files for ION GNSS metadata standard
#include<GnssMetadata/Metadata.h>
#include<GnssMetadata/Xml/XmlProcessor.h>
using namespace GnssMetadata;

// some IFEN specific typedefs
typedef int nsr_int32;
typedef long long nsr_int64;

//! Modified class from IFEN rx to create and manage high precision time and to convert it to/from different time systems 
class PreciseTime
{
	public:
		//! Number of seconds (integer part of the precise time).
		nsr_int64	nTime;
		//! Sub-second (fractional part of the precise time). 0.0<= dValue <1.0. In fact, the real time value = nTime.0 + dTime.
		double	dTime;			

}; // end of class PreciseTime

//! Modified data structure of IFEN software receiver to represent metadata
class DSamplePacketInfo
{
	public:
		// max. number of processed RF bands
		const static int nMaxSimultaneousStreams=8;

		//! type of sample input
		enum SampleInputSource
		{
			File,	// read data from a file, whose configuration is stored previously as an XML format. Now a ClassicDataFile format is used.
			NavPortUSB,	// NavPort frontend conntected via USB
			NavPort2USB,// NavPort2 frontend conntected via USB
			NavPort4USB,// NavPort4 frontend conntected via USB
			NavPort5USB,// NavPort5 frontend conntected via USB
			FausstUSB,  // FAUSST frontend conntected via USB
			NI,			// NI card
			Audio,		// Uses sound card input
			NI2,		// Dual NI
			SourceUnknown		// No real source, used for initialization or test purposes
		};
		//! Number of streams.
		nsr_int32	nStreams;	
		//! Time of first sample of stream (GPS time scale).
		PreciseTime	ptCoarseStartTime;	
		//! Frontend Number.
		nsr_int32	vnFrontendNo[nMaxSimultaneousStreams];
		//! Antenna ID.
		nsr_int32	vnAntennaId[nMaxSimultaneousStreams];
		//! RF Band (Channel) Number of the virtual bands per Frontend. For each virtual band i in vnBandNo[i] the corresponding RF band number is given by vnRfBandNo[i]
		nsr_int32	vnRfBandNo[nMaxSimultaneousStreams];
		//! Virtual Band (Channel) Number per Frontend, see vector vnRfBandNo for RF band number for virtual stream 
		nsr_int32	vnBandNo[nMaxSimultaneousStreams];
		//! Number of bits per IF sample.
		nsr_int32	vnNoBits[nMaxSimultaneousStreams];
		//! Sample rate = fz/fn
		double vdSampleRate[nMaxSimultaneousStreams];
		//! fz, numerator to calculate the sample rate.
		nsr_int32 vnSampleRateZ[nMaxSimultaneousStreams];
		//! fn, denominator to calculate the sample rate.
		nsr_int32 vnSampleRateN[nMaxSimultaneousStreams];
		//! IF frequency for each stream.
		double vdIntermediateFrequency[nMaxSimultaneousStreams];
		//! Carrier frequency for each virtual stream.
		double vdCarrierFrequency[nMaxSimultaneousStreams];
		//! Size of a packet. 
		nsr_int32 vnPacketSize[nMaxSimultaneousStreams];
		//! if true, then vpnSamples contains compressed samples (e.g. in 2-bit, 4-bit or 8-bit format). No of bits is given by DSamplePacketInfo::vnNoBits
		bool vbCompressed[nMaxSimultaneousStreams];
};


/**
 * Loads a metadata file.   
 */
Metadata ReadXmlFile(const char* pszFilename)
{
    printf("\nReading GNSS Metadata from XML file: %s\n", pszFilename);

	Metadata md;
    XmlProcessor xproc;

    try
    {
        if( xproc.Load( pszFilename, false, md) )
        {
            printf("Xml Processed successfully.\n");


        }
    }
    catch( ApiException& e)
    {
        printf("An error occurred while saving the xml file: %s\n", e.what() );
    }
    catch( std::exception& ge)
    {
        printf("Unknown Exception Occured: %s\n", ge.what() );
    }

	return md;
}



/**
 * Writes a metadata file.   
 */
void WriteXmlFile( const Metadata md, const char* pszFilename)
{
    printf("\nWriting GNSS Metadata to xml file: %s\n", pszFilename);

	XmlProcessor proc;

	try
	{
		proc.Save( pszFilename,  md);
	}
	catch( ApiException& e)
	{
		printf("An error occurred while saving the xml file: %s\n", e.what() );
	}
}



/**
 * Converts metadata from IFEN structure to ION data structure
 */
Metadata convertFromIfen( const DSamplePacketInfo mySampInfo )
{
	Metadata md;

	return md;
}



/**
 * Converts metadat from ION data structure to IFEN structure
 */
DSamplePacketInfo convertToIfen( const Metadata md )
{
	DSamplePacketInfo mySampInfo;

	return mySampInfo;
}




/**
 * main routine (see beginning of file for description)
 */
int main(int argc, char** argv)
{
	DSamplePacketInfo mySamples1, mySamples2; // IFEN struct
	Metadata md1, md2, md3;
	char *file1 = "iter1.datx";
	char *file2 = "iter2.datx";

	printf("GNSS Metadata XML <-> IFEN conversion test\n");
	printf("Test successful, if output file 'iter1.datx' matches 'iter2.datx'\n" );
    printf("\n");

	md1 = convertFromIfen( mySamples1 );

    WriteXmlFile( md1, file1 );
    md2 = ReadXmlFile( file1 );
	mySamples2 = convertToIfen( md2 );
	md3 = convertFromIfen( mySamples2 );
    WriteXmlFile( md3, file2 );

	return 0;
}

