#pragma once

#include <string>
#include <vector>
#include <stdint.h>
#include <cstring>
#include <memory>

// ---------------------------------------------------------------------------------------------------
// Support
namespace VectorworksMVR
{
	// ---------------------------------------------------------------------------------------------------
	#ifdef _WIN32
		#ifdef EXPORT_STATIC
			#define EXPORT_MVR_CLASS
		#else
			#ifdef EXPORT_SYMBOLS
				#define EXPORT_MVR_CLASS			__declspec(dllexport)
			#else
				#define EXPORT_MVR_CLASS			__declspec(dllimport)
			#endif
		#endif
	#elif _LINUX
		#define EXPORT_MVR_CLASS			__attribute__((visibility("default")))
	#else
		#define EXPORT_MVR_CLASS			__attribute__((visibility("default")))
	#endif
	
	// ---------------------------------------------------------------------------------------------------
	struct VWIID
	{
		uint32_t	data1;
		uint16_t	data2;
		uint16_t	data3;
		uint8_t		data4[8];

		VWIID& operator = (const VWIID& iid) {
#if _LINUX
			std::memcpy( this, &iid, sizeof(VWIID) );
#else
			memcpy( this, &iid, sizeof(VWIID) );
#endif
			return *this;
		}

		bool operator == (const VWIID& iid) const {
#if _LINUX
			return std::memcmp( this, &iid, sizeof(VWIID) ) == 0;
#else
			return memcmp( this, &iid, sizeof(VWIID) ) == 0;
#endif
		}

		bool operator < (const VWIID& iid) const {
			bool	isLess	= true;
			bool	isEqual	= true;

			// data1
			if ( isEqual ) {
				isEqual		= isEqual && data1 == iid.data1;
				if ( ! isEqual ) { isLess	= (data1 < iid.data1); }

				// data2
				if ( isEqual ) {
					isEqual		= isEqual && data2 == iid.data2;
					if ( ! isEqual ) { isLess	= (data2 < iid.data2); }

					// data3
					if ( isEqual ) {
						isEqual		= isEqual && data3 == iid.data3;
						if ( ! isEqual ) { isLess	= (data3 < iid.data3); }

						// data4
						for(uint32_t i=0; i<8 && isEqual; i++) {
							isEqual		= isEqual && data4[i] == iid.data4[i];
							if ( ! isEqual ) { isLess	= (data4[i] < iid.data4[i]); }
						}
					}
				}
			}

			return isLess && ! isEqual;
		}
		void SetToNULL(void) { memset(this, 0, sizeof(VWIID)); }
		bool IsNULL(void) const { VWIID compare; compare.SetToNULL(); return(*this == compare);}
	};

	// ---------------------------------------------------------------------------------------------------
	#ifdef _WIN32
	# define VCOM_CALLTYPE			__stdcall
	#else
	# define VCOM_CALLTYPE
	#endif

	// ---------------------------------------------------------------------------------------------------
	// We define Dynamic Attribute modificator so VCOM and other C++ interfaces
	//		could participate in static_cast operator on Mac.
	// This is a bug (or issue) in Mac compiler that causes static_cast operator to fail
	//		if the interface instance is from local memory of a DLL!
	#ifdef _WIN32
	# define DYNAMIC_ATTRIBUTE
	#else
	# define DYNAMIC_ATTRIBUTE __attribute__((visibility("default")))
	#endif

	// ---------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IVWUnknown
	{
	public:
		virtual								~IVWUnknown( void )		{}
		virtual uint32_t VCOM_CALLTYPE		AddRef() = 0;
		virtual uint32_t VCOM_CALLTYPE		Release() = 0;
	
	};

	// ---------------------------------------------------------------------------------------------------
	// VCOM errors
	typedef	uint32_t		VCOMError;

	const VCOMError		kVCOMError_NoError			= 0;
	const VCOMError		kVCOMError_Failed			= 1;
	const VCOMError		kVCOMError_False			= 2;
	const VCOMError		kVCOMError_OutOfMemory		= 3;
	const VCOMError		kVCOMError_NotInitialized	= 4;
	const VCOMError		kVCOMError_NoInterface		= 5;
	const VCOMError		kVCOMError_NotImplemented	= 6;
	const VCOMError		kVCOMError_InvalidArg		= 15;
	const VCOMError		kVCOMError_NoInstance		= 16;

	const VCOMError		kVCOMError_NoProjectorObj				= 455;	
	const VCOMError		kVCOMError_NoVideoScreenObj				= 456;
	const VCOMError		kVCOMError_NoValidContainerObj	      	= 457;
	const VCOMError		kVCOMError_NoLayerObj			      	= 458;
	const VCOMError		kVCOMError_NoFixtureObj			      	= 459;
    const VCOMError		kVCOMError_OutOfBounds                	= 460;
	
	const VCOMError		kVCOMError_NotSet				      	= 461;
	const VCOMError		kVCOMError_WrongGeometryType	      	= 462;
    const VCOMError     kVCOMError_WrongRDMParameterValueType 	= 463;
	const VCOMError     kVCOMError_SlaveMasterNotInSameMode   	= 464;
    const VCOMError     kVCOMError_NoObj                      	= 465;

	// ---------------------------------------------------------------------------------------------------
	extern "C" VCOMError VWQueryInterface(const VWIID& iid, IVWUnknown** outInterface);

	// ---------------------------------------------------------------------------------------------------
	template<class T> class VCOMPtr
	{
	public:
					VCOMPtr()						{ fPtr = NULL; }
					VCOMPtr(T* ptr)					{ fPtr = ptr;						if ( fPtr ) { fPtr->AddRef(); } }
					VCOMPtr(const VWIID& iid)		{ fPtr = NULL;						this->Query( iid ); }
					VCOMPtr(const VCOMPtr& p)		{ fPtr = p.fPtr;					if ( fPtr ) { fPtr->AddRef(); } }
					~VCOMPtr()						{ this->Release(); }

		VCOMError	Query(const VWIID& iid)			{ 
														this->Release();
														IVWUnknown*	pInterface		= NULL;
														VCOMError err = VectorworksMVR::VWQueryInterface( iid, & pInterface );
														if ( err == kVCOMError_NoError ) {
															// Vlado: Temporally removed 'static_cast'
															// because on new Mac OS it is failing to cast properly
															//fPtr = static_cast<T*>( pInterface );
															fPtr = (T*)( pInterface );
															if ( fPtr == NULL ) {
																if ( pInterface ) {
																	pInterface->Release();
																	pInterface	= NULL;
																}
																// the passed 'iid' is not from the extected type 'T'
																err			= kVCOMError_InvalidArg;
															}
														}
														return err;
													}
		void		AddRef()						{ if ( fPtr ) { fPtr->AddRef(); } }
		uint32_t	Release()						{ uint32_t res = 0; if ( fPtr ) { res = fPtr->Release(); } fPtr = NULL; return res; }

		VCOMPtr&	operator=(T* ptr)				{ T* pOld = fPtr; fPtr = ptr;						if ( fPtr ) { fPtr->AddRef(); } if ( pOld ) { pOld->Release(); } return *this; }
		VCOMPtr&	operator=(const VCOMPtr& p)		{ T* pOld = fPtr; fPtr = p.fPtr;					if ( fPtr ) { fPtr->AddRef(); } if ( pOld ) { pOld->Release(); } return *this; }

		T*			operator->() const				{ return fPtr; }
		T**			operator&()						{ return & fPtr; }
					operator T*() const 			{ return fPtr; }

	protected:
		T*			Get() const	{ return fPtr; }
		void		Set(T* p)	{ fPtr = p; }

	private:
		T*		fPtr;
	};
}

// ---------------------------------------------------------------------------------------------------
// Interfaces
#include "IMediaRessourceVectorInterface.h"

