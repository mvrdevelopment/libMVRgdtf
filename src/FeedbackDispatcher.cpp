//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "FeedbackDispatcher.h"

using namespace VectorworksMVR;

std::function<void(const FixtureFeedback&)>& FeedbackDispatcher::GetCallbackRef()
{
	static std::function<void(const FixtureFeedback&)> callback;
	return callback;
}

void*& FeedbackDispatcher::GetContextRef()
{
	static void* context = nullptr;
	return context;
}

void FeedbackDispatcher::SetCallback( std::function<void(const FixtureFeedback&)> cb, void* context )
{
	GetCallbackRef() = cb;
}

void FeedbackDispatcher::Send( const FixtureFeedback& msg )
{
	std::function<void(const FixtureFeedback&)>& cb = GetCallbackRef();
	void* ctx = GetContextRef();
	if ( cb ) cb( msg );
}

