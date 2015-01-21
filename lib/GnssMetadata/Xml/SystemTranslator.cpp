/**
 * File: SystemTranslator.cpp
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


#include "SystemTranslator.h"
#include <GnssMetadata/System.h>
#include <GnssMetadata/RfConfiguration.h>
#include <GnssMetadata/Oscillator.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_SystemNodes)
	NODELIST_ENTRY( "freqbase",      TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "equipment",      TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "type",      TE_SIMPLE_TYPE)
	//TODO Add source element
	//TODO Add cluster element
//	NODELIST_ENTRY( "rfconfig",   TE_RFCONFIG)
//	NODELIST_ENTRY( "oscillator", TE_OSCILLATOR)
	NODELIST_ENTRY( "comment",	  TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "artifact",	  TE_SIMPLE_TYPE)
NODELIST_END

static const char* _szTypes[] = {"Processor","Receiver", "Simulator", "Undefined"};
System::SystemType ToSystemType( const char* pszFmt)
{
    for( unsigned int i = 0; i < sizeof( _szTypes); i++)
	{
		if( strcmp( _szTypes[i], pszFmt) == 0)
			return (System::SystemType)i;
	}
	return (System::SystemType)3;
}


SystemTranslator::SystemTranslator() 
: Translator( (NodeEntry*) _SystemNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool SystemTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	const XMLElement* pchild;
	if( pAdaptor == NULL)
		return false;
	System system;

	bool retval = false;

	//Parse the AttributedObject Elements.
	if( !ReadAttributedObject( system, ctxt, elem))
		return false;

	//Done processing element, if no children, meaning this is 
	//an element referencing another element.
	if( elem.NoChildren())
		system.IsReference(true);
	else
	{
		//Parse freqbase [0..1]
		pchild = elem.FirstChildElement("freqbase");
		AccessorAdaptor<System, Frequency> adpt( &system, &System::BaseFrequency);
		retval = ReadElement( system, ctxt, *pchild, &adpt);

		//Parse Equipment [0..1]
		system.Equipment(ReadFirstElement( "equipment", elem, false, ""));

		//Parse Type Attribute. [0..1]
		System::SystemType stype = ToSystemType( ReadFirstElement("type", elem, false, ""));
		system.Type( stype);

		//TODO Read source elements
		//TODO Read cluster elements
	}

	//Lastly set the channel on the specified object.
	pAdaptor->set( &system);
	return true;
}
/**
 * Write the current object 
 */
void SystemTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem )
{
	const System* psystem = dynamic_cast< const System*>(pObject);
	if( psystem == NULL) 
		throw TranslationException("SystemTranslator cannot cast System object");

	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	if( !psystem->IsReference())
	{
		//Write Frequency Base.
		WriteElement( &psystem->BaseFrequency(), "freqbase", ctxt, *pelemc);
	
		//Write Equipment [0..1]
		WriteElement("equipment", psystem->Equipment().c_str(),  pelemc, false, "");

		//Write Type Attribute [0..1]
		WriteElement( "types", _szTypes[psystem->Type()], pelemc, false, "");

		//TODO Write source elements
		//TODO Write cluster elements
	}
	
	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *psystem, ctxt, *pelemc);
	elem.InsertEndChild( pelemc);
}
