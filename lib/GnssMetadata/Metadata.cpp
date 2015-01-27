/**
 * File: Metadata.cpp
 * Author: M.B. Mathews
 *  
 * Copyright(c) 2014 Institute of Navigation
 * http://www.ion.org
 *  
 * This Metadata API is free software; you can redistribute it and/or
 * modify it under the terms of the Lesser GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Metadata API.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <GnssMetadata/Metadata.h>
using namespace GnssMetadata;


/**
 * Returns a string representation of the object.
 */
String Metadata::toString( const String & /*sFormat*/ )
{
	return "Metadata Object";
}


/**
 * Method combines one metadata object with another. It does not 
 * override local id.  Only collections are combined.
 */
void  Metadata::Splice( Metadata& rhs)
{
	//Splice baseclass collections.
	Comments().splice( Comments().end(), rhs.Comments());
	Artifacts().splice( Artifacts().end(), rhs.Artifacts());

	//splice all the collections.
	_includes.splice( _includes.end(), rhs._includes);
	_files.splice(_files.end(), rhs._files);
	_filesets.splice(_filesets.end(), rhs._filesets);
	_bands.splice(_bands.end(), rhs._bands);
	_streams.splice(_streams.end(), rhs._streams);
	_lumps.splice(_lumps.end(), rhs._lumps);
	_chunks.splice(_chunks.end(), rhs._chunks);
	_blocks.splice(_blocks.end(), rhs._blocks);
	_lanes.splice(_lanes.end(), rhs._lanes);
	_sessions.splice( _sessions.end(), rhs._sessions);
	_systems.splice(_systems.end(), rhs._systems);
}
