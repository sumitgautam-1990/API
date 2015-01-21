/**
 * File: Source.h
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

#ifndef SOURCE_H_H
#define SOURCE_H_H

#include "BaseTypes.h"
#include "AttributedObject.h"
#include "Position.h"


namespace GnssMetadata
{
	/**
	 * Class defines a source.
	 */
	class Source: public AttributedObject
	{
	public:
		enum SourcePolarization 
		{
			UndefinedPolarization,
			RHCP,
			Linear,
			Horizontal,
			Vertical
		};

		enum SourceType
		{
			UndefinedType,
			Patch,
			Dipole,
			Helical,
			Quadrifilar,
			Simulator
		};
	public:
		/**
		 * Default constructor.
		 */
		Source( )
		{
			
		}

		Source( const Source& rhs) : 
			_type(rhs._type),
			_polarization(rhs._polarization),
			_origin( rhs._origin),
			_idCluster( rhs._idCluster)

		{
			
		}

		const Source& operator=( const Source& rhs)
		{
			if( &rhs == this)
				return *this;
			AttributedObject::operator =(rhs);
			_type = rhs._type;
			_polarization = rhs._polarization;
			_origin = rhs._origin;
			_idCluster = rhs._idCluster;
			return *this;
		}


		/**
		 * Returns a string representation of the object.
		 */
		virtual String toString( const String & sFormat = DefaultFormat );

	private:
		SourceType _type;
		SourcePolarization _polarization;
		GnssMetadata::Position _origin;
		// TODO Rotation _rotation;
		String  _idCluster;

	};

	typedef std::list<Source> SourceList;	
	
}


#endif