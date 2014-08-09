/* 
 * File:   Savable.h
 * Author: DrSobik
 *
 * Created on July 16, 2014, 8:08 PM
 * 
 * Description : Class Savable is an interface to the objects which can be saved using the save method. Class Restorable is the counterpart of Savable
 *				 which uses the restore method. Class SavableRestorable is provided for convenience.
 * 
 *				 The SavableTo, ReadableFrom and SavableToReadableFrom are provided for convenience
 * 
 */

#ifndef SAVABLE_RESTORABLE_H
#define	SAVABLE_RESTORABLE_H

namespace Common {

	namespace Interfaces {

		/**********************************************************************/
		
		class Savable {
		public:

			virtual void save() = 0; // Must be overridden in order to save the object
			
		private:

			/** We do not need a copy constructor for the interface. */
			Savable(const Savable&){}

		protected:

			Savable(){}

			virtual ~Savable(){}
		};

		/**********************************************************************/
		
		/**********************************************************************/
		
		template<class T> class SavableTo {
		public:

			virtual void saveTo(T&) = 0; // Must be overridden in order to save the object
			
		private:

			/** We do not need a copy constructor for the interface. */
			SavableTo(const SavableTo&){}

		protected:

			SavableTo(){}

			virtual ~SavableTo(){}
		};
		
		/**********************************************************************/
		
		/**********************************************************************/
		
		class Restorable {
		public:

			virtual void restore() = 0; // Must be overridden in order to restore the object
			
		private:

			/** We do not need a copy constructor for the interface. */
			Restorable(const Restorable&){}

		protected:

			Restorable(){}

			virtual ~Restorable(){}
		};
		
		/**********************************************************************/
		
		/**********************************************************************/
		
		template<class T> class RestorableFrom {
		public:

			virtual void restoreFrom(const T&) = 0; // Must be overridden in order to restore the object
			
		private:

			/** We do not need a copy constructor for the interface. */
			RestorableFrom(const RestorableFrom&){}

		protected:

			RestorableFrom(){}

			virtual ~RestorableFrom(){}
		};
		
		/**********************************************************************/
		
		/**********************************************************************/
		
		class SavableRestorable : public Savable, public Restorable {
		public:
			
			// Implicitly defines save() and restore()
			
		private:

			/** We do not need a copy constructor for the interface. */
			SavableRestorable(const SavableRestorable&) : Savable(), Restorable() {}

		protected:

			SavableRestorable() : Savable(), Restorable(){}

			virtual ~SavableRestorable(){}
		};
		
		/**********************************************************************/
		
		/**********************************************************************/
		
		template<class saveT, class restoreT> class SavableToRestorableFrom : public SavableTo<saveT>, public RestorableFrom<restoreT> {
		public:
			
			// Implicitly defines saveTo() and restoreFrom()
			
		private:

			/** We do not need a copy constructor for the interface. */
			SavableToRestorableFrom(const SavableToRestorableFrom&) : SavableTo<saveT>(), RestorableFrom<restoreT>() {}

		protected:

			SavableToRestorableFrom() : SavableTo<saveT>(), RestorableFrom<restoreT>(){}

			virtual ~SavableToRestorableFrom(){}
		};
		
		/**********************************************************************/
		
	}

}
#endif	/* SAVABLERESTORABLE_H */

