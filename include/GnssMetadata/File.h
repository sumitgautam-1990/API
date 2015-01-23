/**
 * File: File.h
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

#ifndef GNSSMETADATAFILE_H_H
#define GNSSMETADATAFILE_H_H

#include "BaseTypes.h"
#include "AnyUri.h"
#include "Lane.h"
#include "Date.h"

namespace GnssMetadata
{
	/**
	 * Class defines metadata for a specific data file. 
	 */
	class File  : public AttributedObject
	{
		
	public:
		File( const String& id = "", bool bIsReference = false)
			: AttributedObject( id, bIsReference), _offset(0)
		{}

		File(const File& rhs) 
			: AttributedObject( rhs), 
			_url(rhs._url), 
			_timestamp( rhs._timestamp),
			_offset(rhs._offset), 
			_owner(rhs._owner), 
			_copyright(rhs._copyright),
			_next( rhs._next),
			_previous( rhs._previous), 
			_lane(rhs._lane)
		{}	
	
		const File& operator=( const File& rhs)
		{
			if( &rhs == this)
				return *this;
			AttributedObject::operator =(rhs);

			_url = rhs._url;
			_timestamp= rhs._timestamp;
			_offset = rhs._offset;
			_owner = rhs._owner;
			_copyright = rhs._copyright;
			_next = rhs._next;
			_previous = rhs._previous;
			_lane = rhs._lane; 
			return *this;
		}


		const AnyUri& Url( ) const
		{
			return _url;
		}
		AnyUri& Url( ) 
		{
			return _url;
		}
		void Url( const AnyUri& url )
		{
			_url = url;
		}


		
		Date TimeStamp( ) const
		{
			return _timestamp;
		}
		void TimeStamp( const Date& timestamp )
		{
			_timestamp = timestamp;
		}

		size_t Offset( ) const
		{
			return _offset;
		}
		void Offset( const size_t offset )
		{
			_offset = offset;
		}

		String Owner( ) const
		{
			return _owner;
		}
		void Owner( const String& owner )
		{
			_owner = owner;
		}

		String Copyright( ) const
		{
			return _copyright;
		}
		void Copyright( const String& copyright )
		{
			_copyright = copyright;
		}

		const AnyUri& Next( ) const
		{
			return _next;
		}
		AnyUri& Next( )
		{
			return _next;
		}
		void Next( const AnyUri& next )
		{
			_next = next;
		}

		const AnyUri& Previous( ) const
		{
			return _previous;
		}
		AnyUri& Previous( )
		{
			return _previous;
		}
		void Previous( const AnyUri& previous )
		{
			_previous = previous;
		}

		const GnssMetadata::Lane& Lane( ) const
		{
			return _lane;
		}
		GnssMetadata::Lane& Lane( ) 
		{
			return _lane;
		}
		void Lane( const GnssMetadata::Lane& lane)
		{
			_lane = lane;
		}
		void Lane( const GnssMetadata::Lane& lane, bool bReferenceOnly)
		{
			if( bReferenceOnly)
			{
				GnssMetadata::Lane rln( lane.Id(), true);
				_lane = rln;
			}
			else
				_lane = lane;
		}

		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );
		
	private:
		/**
		 * url points to the file 
		 */
		AnyUri _url;

		
		Date _timestamp;

		/**
		 * Byte offset into file for start of stream.
		 */
		size_t _offset;
		

		String _owner;

		
		String _copyright;
		
		/**
		 * Previous file URI in the sequence.
		 */
		AnyUri _next;
		
		/**
		 * Previous file URI in the sequence.
		 */
		AnyUri _previous;

		GnssMetadata::Lane _lane;	
	};

	typedef std::list<File> FileList;


	/**
	 * Class defines metadata for a specific a file set. 
	 */
	class FileSet  : public AttributedObject
	{
		
	public:
		FileSet( const String& id) : AttributedObject( id){}
		FileSet() {}
		FileSet(const FileSet& rhs) 
			: AttributedObject( rhs), _files(rhs._files)
		{}	
	
		const FileSet& operator=( const FileSet& rhs)
		{
			if( &rhs == this)
				return *this;
			AttributedObject::operator =(rhs);
	
			_files = rhs._files;
			return *this;
		}

		const AnyUriList& FileUrls( ) const
		{
			return _files;
		}
		AnyUriList& FileUrls( )
		{
			return _files;
		}


		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual String toString( const String & sFormat = DefaultFormat );
		
	private:
		AnyUriList _files;

	};

	typedef std::list<FileSet> FileSetList;


}


#endif
