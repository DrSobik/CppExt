/* 
 * File:   WritableReadable.h
 * Author: DrSobik
 *
 * Created on July 17, 2014, 2:47 PM
 */

#ifndef WRITABLEREADABLE_H
#define	WRITABLEREADABLE_H

namespace Common {

	namespace Interfaces {

		/**********************************************************************/
		
		template<class T> class WritableTo {
		public:

			virtual T& operator>>(T&) const = 0; // Must be overridden for writing
			
			friend T& operator<<(T& destination, const WritableTo& writable) {
				return writable >> destination;
			}
			
		private:

			/** We do not need a copy constructor for the interface. */
			WritableTo(const WritableTo&) {
			}

		protected:

			WritableTo() {
			}

			virtual ~WritableTo() {
			}
		};

		/**********************************************************************/
		
		/**********************************************************************/
		
		template<class T> class ReadableFrom {
		public:

			virtual T& operator<<(T&) = 0; // Must be overridden for reading
			
			friend T& operator>>(T& source, ReadableFrom& readable){
				return readable << source;
			}

		private:

			/** We do not need a copy constructor for the interface. */
			ReadableFrom(const ReadableFrom&) {
			}

		protected:

			ReadableFrom() {
			}

			virtual ~ReadableFrom() {
			}
		};

		/**********************************************************************/
		
		/**********************************************************************/
		
		template<class dstT, class srcT> class WritableToReadableFrom : public WritableTo<dstT>, public ReadableFrom<srcT> {
		public:
			
			// Implicitly defines << and >>
			
		private:

			/** We do not need a copy constructor for the interface. */
			WritableToReadableFrom(const WritableToReadableFrom&) : WritableTo<dstT>(), ReadableFrom<srcT>() {}

		protected:

			WritableToReadableFrom() : WritableTo<dstT>(), ReadableFrom<srcT>(){}

			virtual ~WritableToReadableFrom(){}
		};
		
		/**********************************************************************/

	}

}

#endif	/* WRITABLEREADABLE_H */

