//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#ifndef _STATICARRAYS_H_
#define _STATICARRAYS_H_ 1

#pragma once

/* 
	Static Array Macro Templates
	----------------------------

    The standard static array macro is passed a type, length, and class name.
	This class always pins the index value to the array extents and breaks
	into the debugger when BUG is turned on if an out of range value is passed.
	IndexInRange allows you to check if an index is in range while looping
	through the array.
*/

//---------------------------------------------------------------------------------------
template <class T, ptrdiff_t elems> class StaticArray
{
	public:
		StaticArray()				{ }

		T& operator[](ptrdiff_t i)		{ 
			#if BUG
				DSTOPIF(!IndexInRange(i), (kStaticArrayToWhom | kNoNetDebug, "Array index %Id out of bounds (0..%d)!\n", i, elems-1)); 
			#else
				DSTOPIF(!IndexInRange(i), (kEveryone, "Array index %Id out of bounds (0..%d)!\n", i, elems-1)); 
			#endif
			return fBuf[PIN(i, 0, elems-1)]; 
		}

		const T& operator[](ptrdiff_t i) const { 
			#if BUG
				DSTOPIF(!IndexInRange(i), (kStaticArrayToWhom | kNoNetDebug, "Array index %Id out of bounds (0..%d)!\n", i, elems-1)); 
			#else
				DSTOPIF(!IndexInRange(i), (kEveryone, "Array index %Id out of bounds (0..%d)!\n", i, elems-1)); 
			#endif
			return fBuf[PIN(i, 0, elems-1)]; 
		}

		bool IndexInRange(ptrdiff_t i) const { return i >= 0 && i < elems; }

	private:
		T			fBuf[elems];
};

#define STATIC_ARRAY(DataType, elems, ClassName) \
	typedef StaticArray<DataType, elems>  ClassName

#define STATIC_ARRAY_DEBUGONLY(DataType, elems, ClassName) \
	typedef StaticArray<DataType, elems>  ClassName

//---------------------------------------------------------------------------------------
template <class T> struct List
{
	T v;
	T& operator[](ptrdiff_t i)				{ return (&v)[i]; }
	const T& operator[](ptrdiff_t i) const	{ return (&v)[i]; }
};

#define DEFINE_LISTSTRUCT(T)  typedef List<T> T##List


#endif // _STATICARRAYS_H_
