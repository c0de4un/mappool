# mappool
Sample project to show usage of pool (cache) with different types.

@porpose
Typical porpose is ECS (Entity Component System), where such caches (pool) required often (entities, systems, events/messages, components, etc). Also helps with many other aspects, like caching different types of Input-Events (Gamepad, Keyboard, Pointer/Mouse, Joystick, Sensors).

@thread_safety
provided with thread-lock (synchronization).

@usage
 - to get prevously cached item, call #getItem. If it returns null, allocate item instance yourself, and put it back in cache
 when job done.
  - for caching item, use #putItem.

@optimization
By default, std::vector used to store values (instances of objects/items), but order not kept. Swaping used to reduce add/remove time. But is pointers used, its recommended to use pointer value reset instead of erase (remove), which will require bit more memory, but increase add/remove (insert/erase) speed.

(?) Note:
Also it is recommended to use smart-pointers to avoid conflicts with ownership (if instance of item deleted while still cached).
