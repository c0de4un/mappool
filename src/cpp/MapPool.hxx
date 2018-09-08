/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: Apache 2.0 (see "LICENSE" file)
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef _C0DE4UN_MAP_POOL_HXX_
#define _C0DE4UN_MAP_POOL_HXX_

#include <mutex>
#include <memory>
#include <map>
#include <vector>

namespace c0de4un
{

	/*
	 * MapPool - simple map-based cache (pool) to store objects of same base type.
	 *
	 * @thread_safety
	 * Thread-safe, synchronization (thread-lock) used.
	 *
	 * @USAGE:
	 * - get item with #getItem. Item will be removed from pool (cache).
	 * Returns null if no items found ;
	 * - put item back in the pool with #putItem ;
	 *
	 * @note
	 * - instead of shared_ptr, raw-pointer can be used for better performance ;
	 * - instead of erasing (removing) from collection of specific type,
	 * it could be better to reset pointer-value instead, which can give
	 * better performance if get/put called often ;
	 * - instead of references for item-type, copy-constructor can be used, if
	 * given value is small (char, enum, etc).
	*/
	template<typename K, typename V>
	class MapPool final
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructors & Destructor
		// ===========================================================

		/*
		 * MapPool Constructor
		*/
		explicit MapPool( ) noexcept
			: itemsMap( ),
			accessMutex( )
		{
		}

		/* MapPool Destructor */
		~MapPool( ) noexcept
		{
		}

		// ===========================================================
		// Getter & Setter
		// ===========================================================

		/*
		 * Searches item of given type
		 *
		 * @thread_safety - thread-safe, synchronization (thread-lock) used.
		 * @param pKey - Item-Type.
		 * @return item or null.
		*/
		std::shared_ptr<V> getItem( const K & pKey ) noexcept
		{

			// Lock
			

			// Get Items
			std::shared_ptr<vector_t> itemsVector_sp( getItems( pKey, false ) );

			// Get Item
			std::shared_ptr<V> item_sp( getItem( itemsVector_sp ) );

			// Return Item & Unlock
			return( item_sp );

		}

		// -------------------------------------------------------- \\

	};

}

#endif // !_C0DE4UN_MAP_POOL_HXX_