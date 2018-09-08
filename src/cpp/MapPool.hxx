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
			itemsMutex( )
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
			std::unique_lock<std::mutex> lock_l( itemsMutex );

			// Get Items
			std::shared_ptr<vector_t> itemsVector_sp( getItems( pKey, false ) );

			// Get Item
			std::shared_ptr<V> item_sp( getItem( itemsVector_sp ) );

			// Return Item & Unlock
			return( item_sp );

		}

		/*
		 * Puts item of given type.
		 *
		 * @thread_safety - thread-safe, synchronization (thread-lock) used.
		 * @param pKey - Item-Type.
		 * @param pItem - Item.
		*/
		void putItem( const K & pKey, std::shared_ptr<V> pItem ) noexcept
		{

			// Lock
			std::unique_lock<std::mutex> lock_l( itemsMutex );

			// Get Items
			std::shared_ptr<vector_t> itemsVector_sp( getItems( pKey, true ) ); // Create new vector_t if needed.

			// Add Item to Collection
			itemsVector_sp->push_back( pItem ); // For better performance, reusing shared_ptr without deletion can be better.

		}

		// -------------------------------------------------------- \\

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Types
		// ===========================================================

		/* Type-Alias for vector */
		using vector_t = std::vector<std::shared_ptr<V>>;

		/* Type-Alias for map */
		using map_t = std::map<K, std::shared_ptr<vector_t>>;

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
		 * Searches for items collection of given type.
		 *
		 * @thread_safety - not thread-safe, must be called inside of
		 * the synchronization block (thread-lock).
		 * @param pKey - Item-Type.
		 * @param pAllocate - true to create new collection for given type, if none where found.
		 * @return collection or null.
		*/
		std::shared_ptr<vector_t> getItems( const K & pKey, const bool pAllocate ) noexcept
		{

			// Items Collection
			std::shared_ptr<vector_t> items_sp( nullptr );

			// Search position
			const map_t::iterator position = itemsMap.find( pKey );

			// Get
			if ( position == itemsMap.end( ) )
			{
				// Add new type
				if ( pAllocate )
				{
					// Allocate using std::make_shared
					items_sp = std::make_shared<vector_t>( );

					// Register collection
					itemsMap.insert( map_t::value_type( pKey, items_sp ) );
				}
			}
			else
				items_sp = position->second; // Copy-Constructor of smart-pointer

			// Return items
			return( items_sp );

		}

		/*
		 * Searches for item within collection.
		 *
		 * @thread_safety - not thread-safe, must be called inside of
		 * the synchronization block (thread-lock).
		 * @param itemsVector_sp - pointer to collection.
		 * @return pointer to item or null if none found.
		*/
		std::shared_ptr<V> getItem( std::shared_ptr<vector_t> & itemsVector_sp ) noexcept
		{

			// Cancel
			if ( itemsVector_sp->empty( ) )
				return( nullptr );

			// Get Back (Last) Item
			std::shared_ptr<V> item_sp = itemsVector_sp->back( ); // Get reference

			// Copy pointer-value
			std::shared_ptr<V> result_sp = std::move( item_sp ); // Transfer ownership

			// Remove Item from Collection
			itemsVector_sp->pop_back( );

			// Return Item
			return( result_sp );

		}

		// -------------------------------------------------------- \\

	};

}

#endif // !_C0DE4UN_MAP_POOL_HXX_