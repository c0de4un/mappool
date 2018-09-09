/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: Apache 2.0 (see "LICENSE" file)
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef _C0DE4UN_MAP_POOL_HXX_
#define _C0DE4UN_MAP_POOL_HXX_

#include <mutex>
#include <map>
#include <vector>

namespace c0de4un
{

	/*
	 * MapPool - pool (cache) based on map & vector.
	 *
	 * Unlikely static-based type generation (ECS), this class using fixed type as
	 * key for collection of objects.
	 *
	 * @USAGE
	 * - to retrieve cached item call #getItem. Item will be removed from pool.
	 * Don't forget to return it the pool ;
	 * - to put item in pool (cache), use #putItem.
	 *
	 * @thread_safety
	 * Thread-safe, synchronization (thread-lock) used.
	 *
	 * @note
	 * - smart-pointer are more preferred ;
	 * - instead of erasing (removing) from collection of specific type,
	 * it could be better to reset pointer-value instead, which can give
	 * better performance if get/put called often ;
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
			itemsMutex( )
		{
		}

		/* MapPool Destructor */
		~MapPool( ) noexcept
		{
			// Release Collections
			for ( map_t::iterator position_ = itemsMap.begin( ); position_ != itemsMap.end( ); position_++ )
			{
				// Delete Items Collection
				if ( position_->second != nullptr )
					delete position_->second;
			}
		}

		// ===========================================================
		// Getter & Setter
		// ===========================================================

		/*
		 * Searches item of given type
		 *
		 * @thread_safety - thread-safe, synchronization (thread-lock) used.
		 * @param pKey - Item-Type.
		 * @return item or null, if none found.
		*/
		V getItem( const K & pType ) noexcept
		{
			// Lock
			std::unique_lock<std::mutex> lock_( itemsMutex );

			// Get Items Collection
			vector_t & itemsVector_ = getItems( pType );

			// Return null
			return( getAnyItem( itemsVector_ ) );
		}

		/*
		 * Adds item.
		 *
		 * @thread_safety - thread-safe, synchronization (thread-lock) used.
		 * @param pKey - Item-Type.
		 * @param pItem - item.
		*/
		void putItem( const K & pType, V pItem ) noexcept
		{
			// Lock
			std::unique_lock<std::mutex> lock_( itemsMutex );

			// Get Items Collection
			vector_t & itemsVector_ = getItems( pType );

			// Add Item to Collection
			itemsVector_.push_back( pItem );
		}

		// -------------------------------------------------------- \\

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Types
		// ===========================================================

		/* Type-Alias for vector */
		using vector_t = std::vector<V>;

		/* Type-Alias for map */
		using map_t = std::map<K, vector_t*>;

		// ===========================================================
		// Fields
		// ===========================================================

		/* Items map */
		map_t itemsMap;

		/* Mutex to synchronize access */
		std::mutex itemsMutex;

		// ===========================================================
		// Constructors & Destructor
		// ===========================================================

		/* @deleted MapPool const copy constructor */
		explicit MapPool( const MapPool & ) = delete;

		/* @deleted MapPool const copy '=' operator */
		MapPool operator=( const MapPool & ) = delete;

		// ===========================================================
		// Getter & Setter
		// ===========================================================

		/*
		 * Searches for any stored (cached) item.
		 *
		 * @thread_safety - must be called only from synchronization-block (thread-lock).
		 * @return Item
		*/
		static V getAnyItem( vector_t & pItems ) noexcept
		{
			// Cancel
			if ( pItems.empty( ) )
				return( nullptr ); // V - must be convertible from null.

			// Get Last Item from vector
			V item_ = pItems.back( );

			// Remove Last Item from vector
			pItems.pop_back( );

			// Return Item
			return( item_ );
		}

		/*
		 * Searches and, if required, allocates (creates 'new') collection
		 * for items of given type.
		 *
		 * @param pType - Item-Type.
		 * @return - 'reference' to collection of items.
		*/
		inline vector_t & getItems( const K & pType ) noexcept
		{
			// Search
			const map_t::iterator position_ = itemsMap.find( pType );

			// Return result
			if ( position_ != itemsMap.end( ) )
				return( * position_->second );
			else
			{// Not found
				// Create new collection for given type
				vector_t *const itemsVector_lp = new vector_t( );

				// Register (add, insert) new collection
				itemsMap.insert( map_t::value_type( pType, itemsVector_lp ) );

				// Return Collection
				return( * itemsVector_lp );
			}

		}

		// -------------------------------------------------------- \\

	};

}

#endif // !_C0DE4UN_MAP_POOL_HXX_