/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: Apache 2.0 (see "LICENSE" file)
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef _C0DE4UN_VEHICLE_HXX_
#define _C0DE4UN_VEHICLE_HXX_

// Include BaseObject
#ifndef _C0DE4UN_BASE_OBJECT_HXX_
#include "BaseObject.hxx"
#endif // !_C0DE4UN_BASE_OBJECT_HXX_

namespace c0de4un
{

	/*
	 * Vehicle - vehicle object.
	*/
	class Vehicle final : public BaseObject
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructors & Destructor
		// ===========================================================

		/*
		 * Vehicle Constructor
		 *
		 * @param pType - Object-Type.
		*/
		explicit Vehicle( ) noexcept
			: BaseObject( VEHICLE )
		{
		}

		/* Vehicle Destructor */
		virtual ~Vehicle( ) noexcept
		{
		}

		// -------------------------------------------------------- \\

	};

}

#endif // !_C0DE4UN_VEHICLE_HXX_