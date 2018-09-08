/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: Apache 2.0 (see "LICENSE" file)
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// Include STL
#include <iostream>
#include <cstdlib>

// Include Vehicle
#include "Vehicle.hxx"

// Include Tank
#include "Tank.hxx"

// Include MapPool
#include "MapPool.hxx"

/* MAIN */
int main( int argC, char** argV )
{

	// Print Hello to Console
	std::cout << "MapPool Example Started" << std::endl;

	// Create MapPool with ObjectTypes
	c0de4un::MapPool<c0de4un::ObjectTypes, c0de4un::BaseObject> objectsPool;

	// Create Vehicle & Add to the Pool
	objectsPool.putItem( c0de4un::ObjectTypes::VEHICLE, std::make_shared<c0de4un::Vehicle>( ) );

	// Create Tank & Add to the Pool
	objectsPool.putItem( c0de4un::ObjectTypes::TANK, std::make_shared<c0de4un::Tank>( ) );

	// Get Vehicle
	std::shared_ptr<c0de4un::Vehicle> vehicle_sp = std::static_pointer_cast<c0de4un::Vehicle, c0de4un::BaseObject>( objectsPool.getItem( c0de4un::ObjectTypes::VEHICLE ) );

	// Check if Vehicle Pointer is valid
	if ( vehicle_sp == nullptr )
		std::cout << "Vehicle is null ! This is wrong." << std::endl;
	else
		std::cout << "Vehicle retrieved & removed from pool (cache)." << std::endl;

	// Get Vehicle again
	vehicle_sp = std::static_pointer_cast<c0de4un::Vehicle, c0de4un::BaseObject>( objectsPool.getItem( c0de4un::ObjectTypes::VEHICLE ) );

	// Check if Pool has Vehicle
	if ( vehicle_sp != nullptr )
		std::cout << "Vehicle found. This is wrong behavior." << std::endl;
	else
		std::cout << "No vehicles in the pool." << std::endl;

	// Print Bye to Console
	std::cout << "MapPool Example Finished" << std::endl;

	// Pause Console-Window
	std::cin.get( );

	// Return OK
	return( 0 );

}