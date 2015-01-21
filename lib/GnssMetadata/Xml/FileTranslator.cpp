/**
 * File: FileTranslator.cpp
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


#include "FileTranslator.h"
#include <GnssMetadata/File.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

//// Endian Values
//static const char* _szEndian[] = {"Big","Little", "Undefined"};
//Lump::WordEndian ToEndian( const char* pszFmt)
//{
//    for( unsigned int i = 0; i < sizeof( _szEndian); i++)
//	{
//		if( strcmp( _szEndian[i], pszFmt) == 0)
//			return (Lump::WordEndian)i;
//	}
//	return (Lump::WordEndian)2;
//}
//
//// Sample Format Values
//static const char* _szWordAlignment[] = {"Left","Right","Unspecified"};
//Lump::WordAlignment ToWordAlignment( const char* pszFmt)
//{
//    for( unsigned int i = 0; i < sizeof( _szWordAlignment); i++)
//	{
//		if( strcmp( _szWordAlignment[i], pszFmt) == 0)
//			return (Lump::WordAlignment)i;
//	}
//	return (Lump::WordAlignment)2;
//}

NODELIST_BEGIN(_FileNodes)
	NODELIST_ENTRY( "url",			TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "timestamp",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "offset",		TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "owner",		TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "copyright",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "next",		TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "previous",	TE_SYSTEM)
	NODELIST_ENTRY( "comment",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "artifact", TE_SIMPLE_TYPE)
NODELIST_END

FileTranslator::FileTranslator() 
: Translator( (NodeEntry*) _FileNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool FileTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	const XMLElement* pchild;
	if( pAdaptor == NULL)
		return false;
	File file;

	bool bRetVal = true;

	//Parse the AttributedObject Elements.
	if( !ReadAttributedObject( file, ctxt, elem, false))
		return false;

	//Done processing element, if	 children, meaning this is 
	//an element referencing another element.
	if( elem.NoChildren())
		file.IsReference(true);
	else
	{
		//Parse url [1]
		file.Url().Value( ReadFirstElement("url", elem, true, ""));

		//Parse timestamp [1]
		pchild = elem.FirstChildElement("timestamp");
		file.TimeStamp( Date(pchild->GetText()));

		//Parse offset [0..1]
		file.Offset( ReadFirstElement("offset", elem, false, (size_t)0));

		//Parse owner [0..1]
		file.Owner( ReadFirstElement( "owner", elem, false, ""));

        //Parse copyright [0..1]
		file.Copyright( ReadFirstElement( "copyright", elem, false, ""));

		//Parse next [0..1]
		file.Next().Value( ReadFirstElement("next", elem, false, ""));
		
		//Parse previous [0..1]
		file.Previous().Value( ReadFirstElement("previous", elem, false, ""));

		//TODO Parse Lane [1]
	}

	//Lastly set the datafile on the specified object.
	if( bRetVal)
		pAdaptor->set( &file);
	return bRetVal;
}
/**
 * Write the current object 
 */
void FileTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem )
{
	const File* pdatafile = dynamic_cast< const File*>(pObject);
	if( pdatafile == NULL) 
		throw TranslationException("FileTranslator cannot cast File object");

	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	if( !pdatafile->IsReference())
	{
		XMLElement* pelem;

		//Write url [1]
		WriteElement( "url", pdatafile->Url().Value().c_str(), pelemc, true);

		//Write timestamp [1]
		pelem = elem.GetDocument()->NewElement( "timestamp");
		pelem->SetText( pdatafile->TimeStamp().toString().c_str());
		pelemc->InsertEndChild( pelem);

		//Write offset [0..1]
		WriteElement( "offset", pdatafile->Offset(), pelemc, false, 0);

		//Write owner [0..1]
		WriteElement("owner", pdatafile->Owner().c_str(), pelemc, false, "");

		//Write copyright [0..1]
		WriteElement("owner", pdatafile->Copyright().c_str(), pelemc, false, "");

		//Write next [0..1]
		WriteElement("next", pdatafile->Next().Value().c_str(), pelemc, false, "");

		//Write previous [0..1]
		WriteElement("previous", pdatafile->Previous().Value().c_str(), pelemc, false, "");

		//TODO Write Lane [1]
	}
	
	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *pdatafile, ctxt, *pelemc, false);
	elem.InsertEndChild( pelemc);
}
