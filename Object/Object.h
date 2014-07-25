/* 
 * File:   Object.h
 * Author: DrSobik
 *
 * Created on July 15, 2014, 6:31 PM
 * 
 * Description : The basic class for all objects. It cannot be created.
 * 
 */

#ifndef OBJECT_H
#define	OBJECT_H

namespace Common {

	/** A basic object class. */
	class BasicObject {
		
	public:

	private:
		
	protected:

		BasicObject(){}
		BasicObject(const BasicObject&){}
		virtual ~BasicObject() {}
		
	};
	
	/** Parameters Ts specifies the base classes >=0. */	
	template<class... Ts> class Object : virtual public BasicObject, public Ts... {
	public:

	private:
		
	protected:

		Object() : BasicObject(), Ts()... {}
		
		Object(const Object& other) : BasicObject(), Ts((Object*)&other)... {}

		virtual ~Object() {}

	};

}

#endif	/* OBJECT_H */

