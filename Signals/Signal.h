/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Signal.h
 * Author: DrSobik
 *
 * Created on December 25, 2015, 11:06 PM
 */

#ifndef SIGNAL_H
#define SIGNAL_H

#include <iostream>
#include <map>
#include <functional>
#include <mutex>

#include "Functor"
#include "MathExt"

using namespace Common;
using namespace Common::Interfaces;

namespace Common {

	namespace Signals {

		template<class resT = void, class...argT> class Signal : public Functor<void, argT...> {
		private:

			typedef std::function<void(const argT&...) > FunctionPtr;

		protected:

			std::map<void*, FunctionPtr> fSlots; // Functions/Functors that will be called on signal
			std::map<void*, std::map<Math::uint64, FunctionPtr>> mSlots; // Object methods that will be called on signal

			std::mutex fSlotsMutex; // For locking fSlots
			std::mutex mSlotsMutex; // For locking mSlots

			static std::map<void*, std::map<Math::uint64, Math::uint16>> mSlotsUsages; // How many times which mSlot is used

			std::mutex mSlotUsagesMutex; // For locking mSlotsUsages

		public:

			Signal() { }

			Signal(const Signal& other) : Functor<void, argT...>() {
				std::lock_guard<std::mutex> curFSlotsLock(fSlotsMutex); // Lock the fSlots so that noone modifies it in parallel
				std::lock_guard<std::mutex> curMSlotsLock(mSlotsMutex); // Lock the mSlots so that noone modifies it in parallel
				std::lock_guard<std::mutex> curMSlotUsagesLock(mSlotUsagesMutex); // Lock the mSlotUsagess so that noone modifies it in parallel

				fSlots = other.fSlots;
				mSlots = other.mSlots;

				// Adopt the number of usages for each mslot
				for (auto curMSlotIter : mSlots) {
					for (auto curMSlotUsageIter : curMSlotIter.second) {
						mSlotsUsages[curMSlotIter.first][curMSlotUsageIter.first]++;
					}
				}

			}

			virtual ~Signal() {

				std::lock_guard<std::mutex> curMSlotUsagesLock(mSlotUsagesMutex); // Lock the mSlots so that noone modifies it in parallel

				// Adopt the number of usages for each mslot
				for (auto curMSlotIter : mSlots) {
					for (auto curMSlotUsageIter : curMSlotIter.second) {
						mSlotsUsages[curMSlotIter.first][curMSlotUsageIter.first]--;

						if (mSlotsUsages[curMSlotIter.first][curMSlotUsageIter.first] == 0) {
							mSlotsUsages[curMSlotIter.first].erase(curMSlotUsageIter.first);
						}

					}

					if (mSlotsUsages[curMSlotIter.first].size() == 0) {
						mSlotsUsages.erase(curMSlotIter.first);
					}

				}

			}

			/** Connect method slot. */
			template<class receiverT, class methodT> void connect(receiverT* obj, methodT mPtr, bool establish = true) {

				static std::map<void*, std::map < Math::uint64, methodT>> obj2MethodsMap;
				static std::mutex obj2MethodsMapMutex;

				std::lock_guard<std::mutex> curObj2MethodsMapLock(obj2MethodsMapMutex); // To avoid multiple threads making connections at once. Will be released directly after one thread is done
				std::lock_guard<std::mutex> curMSlotsLock(mSlotsMutex); // Lock the mSlots so that noone modifies it in parallel
				std::lock_guard<std::mutex> curMSlotUsagesLock(mSlotUsagesMutex); // Lock the mSlots so that noone modifies it in parallel

				void* objPtr = (void*) obj;

				if (establish) {

					FunctionPtr curFunctionPtr = std::bind(mPtr, obj, std::placeholders::_1); // Wrap the method

					auto curIterMap = std::find_if(obj2MethodsMap[objPtr].begin(), obj2MethodsMap[objPtr].end(), [&mPtr](typename std::map <Math::uint64, methodT>::value_type & curPair) {
						return curPair.second == mPtr;
					});

					if (curIterMap == obj2MethodsMap[objPtr].end()) { // This entry is not present => add it

						Math::uint64 curMapKey = (obj2MethodsMap[objPtr].size() > 0) ? (--obj2MethodsMap[objPtr].end())->first + 1 : 1; // Take the last entry ref + 1

						mSlots[objPtr][curMapKey] = curFunctionPtr;

						obj2MethodsMap[objPtr][curMapKey] = mPtr;
						mSlotsUsages[objPtr][curMapKey] = 1;

					} else { // Just increase the number of connections to this slot

						Math::uint64 curMapKey = curIterMap->first;

						mSlotsUsages[objPtr][curMapKey]++;

					}


					/*
					auto curIter = std::find(obj2Methods[(void*) obj].begin(), obj2Methods[(void*) obj].end(), mPtr);

					if (curIter == obj2Methods[(void*) obj].end()) { // Only if the method is not present => add it

						obj2Methods[(void*) obj].push_back(mPtr);
						curIter = --obj2Methods[(void*) obj].end();

					}

					mSlots[(void*) obj][curIter - obj2Methods[(void*) obj].begin()] = curFunctionPtr;
					 */


				} else {

					auto curIterMap = std::find_if(obj2MethodsMap[(void*) obj].begin(), obj2MethodsMap[objPtr].end(), [&mPtr](typename std::map <Math::uint64, methodT>::value_type & curPair) {
						return curPair.second == mPtr;
					});

					if (curIterMap != obj2MethodsMap[objPtr].end()) { // This entry exists => delete it, provided there are no more usages

						Math::uint64 curMapKey = curIterMap->first;

						if (mSlots[objPtr].find(curMapKey) != mSlots[objPtr].end()) { // It exists for this object => delete it

							mSlots[objPtr].erase(curMapKey); // Erase the usage for this object
							mSlotsUsages[objPtr][curMapKey]--;

						}

						if (mSlotsUsages[objPtr][curMapKey] == 0) { // No more objects connected to this method => erase it to release memory

							obj2MethodsMap[objPtr].erase(curMapKey);
							mSlotsUsages[objPtr].erase(curMapKey);

							if (obj2MethodsMap[objPtr].size() == 0) {
								obj2MethodsMap.erase(objPtr);
							}

							if (mSlotsUsages[objPtr].size() == 0) {
								mSlotsUsages.erase(objPtr);
							}

						}

					}

					/*
					typename std::vector<methodT>::iterator curIter = std::find(obj2Methods[(void*) obj].begin(), obj2Methods[(void*) obj].end(), mPtr);

					if (curIter != obj2Methods[(void*) obj].end()) { // Only if the method is present => remove it

						mSlots[(void*) obj].erase(curIter - obj2Methods[(void*) obj].begin());

					}
					 */

					// Do not remove the static element under curIter in order to preserve the indices

				}

			}

			/** Disconnect method slot. */
			template<class receiverT, class methodT> void disconnect(receiverT* obj, methodT mPtr) {

				connect(obj, mPtr, false);

			}

			template<class objectT> void connect(objectT& obj) {

				std::lock_guard<std::mutex> curFSlotsLock(fSlotsMutex); // Lock the fSlots so that noone modifies it in parallel

				std::cout << "Connecting: " << std::flush;

				obj(10);

				FunctionPtr curFunctionPtr = std::ref(obj); // Create the function using the reference to the object

				fSlots[(void*) &obj] = curFunctionPtr;

			}

			/** Disconnect function/functor/methods based on the given object. */
			template<class objectT> void disconnect(objectT& obj) {

				{
					std::lock_guard<std::mutex> curFSlotsLock(fSlotsMutex); // Lock the fSlots so that noone modifies it in parallel
					fSlots.erase((void*) &obj);
				}

				{
					std::lock_guard<std::mutex> curMSlotsLock(mSlotsMutex); // Lock the mSlots so that noone modifies it in parallel
					std::lock_guard<std::mutex> curMSlotUsagesLock(mSlotUsagesMutex); // Lock the mSlotUsages so that noone modifies it in parallel
					// Adopt the number of usages for each mslot

					for (auto curMSlotUsageIter : mSlots[(void*) &obj]) {
						mSlotsUsages[(void*) &obj][curMSlotUsageIter.first]--;

						if (mSlotsUsages[(void*) &obj][curMSlotUsageIter.first] == 0) {
							mSlotsUsages[(void*) &obj].erase(curMSlotUsageIter.first);
						}

					}

					if (mSlotsUsages[(void*) &obj].size() == 0) {
						mSlotsUsages.erase((void*) &obj);
					}

					mSlots.erase((void*) &obj);

				}

			}

			virtual void operator()(const argT&... args) {

				// Call all function slots
				FunctionPtr curFunctionPtr;

				// Execute the fSlots
				for (auto curFSlot : fSlots) {

					curFunctionPtr = curFSlot.second;

					curFunctionPtr(args...);

				}

				// Execute the mSlots
				for (auto curIterObj : mSlots) {

					for (auto curIterMethod : curIterObj.second) {

						curFunctionPtr = curIterMethod.second;

						curFunctionPtr(args...);

					}

				}

			}

		};
		
		template<class resT, class...argT> std::map<void*, std::map<Math::uint64, Math::uint16>> Signal<resT, argT...>::mSlotsUsages;

	}

}



#endif /* SIGNAL_H */

