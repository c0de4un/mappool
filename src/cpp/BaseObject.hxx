/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: Apache 2.0 (see "LICENSE" file)
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef _C0DE4UN_BASE_OBJECT_HXX_
#define _C0DE4UN_BASE_OBJECT_HXX_

// Include ObjectTypes
#ifndef _C0DE4UN_OBJECTS_HXX_
#include "ObjectTypes.hxx"
#endif // !_C0DE4UN_OBJECTS_HXX_

namespace c0de4un
{

	/*
	 * BaseObject - base object class (interface).
	*/
	class BaseObject
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructors & Destructor
		// ===========================================================

		/*
		 * BaseObject Constructor
		 *
		 * @param pType - Object-Type.
		*/
		explicit BaseObject( const ObjectTypes pType ) noexcept
			: objectType( pType )
		{
		}

		/*
		 * BaseObject virtual Destructor.
		 * Allows deletion of derived instance through this interface (class).
		*/
		virtual ~BaseObject( ) noexcept
		{
		}

		// ===========================================================
		// Getter & Setter
		// ===========================================================

		/* Returns Object-Type */
		const ObjectTypes getType( ) const noexcept
		{ return( objectType ); }

		// -------------------------------------------------------- \\

	protected:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constants
		// ===========================================================

		/* Object-Type */
		const ObjectTypes objectType;

		// ===========================================================
		// Constructors & Destructor
		// ===========================================================

		/* @delete BaseObject const copy constructor */
		explicit BaseObject( const BaseObject & ) = delete;

		// -------------------------------------------------------- \\

	};

}

#endif // !_C0DE4UN_BASE_OBJECT_HXX_