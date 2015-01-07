/**
 * File: TestApp.cpp
 * Author: M.B. Mathews
 *  
 * Copyright(c) 2014 Institute of Navigation
 * http://www.ion.org
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
#include<GnssMetadata/Metadata.h>
#include<GnssMetadata/Xml/XmlProcessor.h>

using namespace GnssMetadata;

void ReadXmlFile(const char* pszFilename);
void WriteXmlFile(const char* pszFilename);


int main(int argc, char** argv)
{
    //Get the filename if specified.
    const char* pszFilename = "141230-gps-4msps.xml";
    if( argc > 1) pszFilename = argv[1];

    printf("GNSS Metadata XML file translation test\n");
    printf("\n");
    printf("Application demonstrates writing and reading an XML file\n");
    printf("Program creates an metadata file using the API and then parses it.\n");
    printf("\n");
    printf("Command line\n");
    printf("GnssMetadataTestApp [xmlfile (default: '14230-gps-4msps.xml')]\n");

    WriteXmlFile(pszFilename);
    ReadXmlFile(pszFilename);
	return 0;
}

/**
 * Loads and saves a metadata file.   
 */
 void ReadXmlFile(const char* pszFilename)
{
    printf("\nReading GNSS Metadata to xml file: %s\n", pszFilename);

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


}

void WriteXmlFile(const char* pszFilename)
{
    printf("\nWriting GNSS Metadata to xml file: %s\n", pszFilename);

    ////////////////////////////////
	//Define information about the datafile.

	//UTC:    30-Dec-2014 22:38:54
	//GPS:    1825/254334.906
	Date dt0( 254334.906, 1825);
	size_t offset = 588;
    String sfile = "141230-gps-4msps.bds";
    String sfilemd = pszFilename;

	////////////////////////////////
	//Define the Session and System.
	Session sess("0");
	sess.Scenario("Example 2");
	sess.Campaign("GNSS Metadata API Testing");
	sess.Contact("J. Doe");
	sess.Location( Location(47.76471300, -122.15612900, 25.610));
	sess.AddComment("This is an example metadata specification with two interleaved streams.");

	System sys("A2300-1");
	sys.Model("ASR-2300");
	sys.AddComment( "ASR-2300 configured with standard firmware and FPGA id=1, version=1.18.");

	////////////////////////////////
	//Define Channel 1 and L1 C/A Stream.
	Channel ch1("L1External");
	ch1.CenterFrequency(Frequency( 1575.42, Frequency::GHz));
	ch1.TranslatedFrequency(Frequency( 38400, Frequency::Hz));
	ch1.System(System("A2300-1", true));

	Stream sm1("L1ca");
	sm1.RateFactor(1);
	sm1.Quantization(8);
	sm1.Encoding("INT8");
	sm1.Format(Stream::IQ);
	sm1.Channel( ch1);

	////////////////////////////////
	//Define Channel 2 and L2 C Stream.
	Channel ch2("L2cExternal");
	ch2.CenterFrequency(Frequency( 1227.6, Frequency::GHz));
	ch2.TranslatedFrequency(Frequency( 38400, Frequency::Hz));
	ch2.System(System("A2300-1", true));

	Stream sm2("L2C");
	sm2.RateFactor(1);
	sm2.Quantization(8);
	sm2.Encoding("INT8");
	sm2.Format(Stream::IQ);
	sm2.Channel( ch2);

	////////////////////////////////
	//Define the Datafile
	DataFile df;
	df.Url( sfile);
	df.CreateDate( dt0);
	df.Session (sess);
	df.Rate( Frequency( 4, Frequency::MHz));
	df.Offset( offset);
	df.SubFrame(SubFrame(32,SubFrame::Little, 1, SubFrame::Left));
	df.Frame( Frame(4000, 96,0));
	df.Streams().push_back( sm1);
	df.Streams().push_back( sm2);
	//Note: we aren't specifying copyright or owner.


	////////////////////////////////
	//Assemble the Metadata object and write XML 
	Metadata md;
	XmlProcessor proc;
	md.DataFiles().push_back( df);
	md.Systems().push_back(sys);

	try
	{
		proc.Save( sfilemd.c_str(),  md);
	}
	catch( ApiException& e)
	{
		printf("An error occurred while saving the xml file: %s\n", e.what() );
	}
}

