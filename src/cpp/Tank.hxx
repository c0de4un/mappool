/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: Apache 2.0 (see "LICENSE" file)
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef _C0DE4UN_TANK_HXX_
#define _C0DE4UN_TANK_HXX_

// Include BaseObject
#ifndef _C0DE4UN_BASE_OBJECT_HXX_
#include "BaseObject.hxx"
#endif // !_C0DE4UN_BASE_OBJECT_HXX_

namespace c0de4un
{

	/*
	 * Tank - Tank object.
	*/
	class Tank final : public BaseObject
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructors & Destructor
		// ===========================================================

		/*
		 * Tank Constructor
		 *
		 * @param pType - Object-Type.
		*/
		explicit Tank( ) noexcept
			: BaseObject( TANK )
		{
		}

		/* Tank Destructor */
		virtual ~Tank( ) noexcept
		{
		}

		// -------------------------------------------------------- \\

	};

}

#endif // !_C0DE4UN_TANK_HXX_