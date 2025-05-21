//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "FeedbackDispatcher.h"

using namespace VectorworksMVR;

std::function<void(const std::string&)>& FeedbackDispatcher::GetCallbackRef()
{
	static std::function<void(const std::string&)> callback;
	return callback;
}

void*& FeedbackDispatcher::GetContextRef()
{
	static void* context = nullptr;
	return context;
}

void FeedbackDispatcher::SetCallback( std::function<void(const std::string&)> cb, void* context )
{
	GetCallbackRef() = cb;
}

void FeedbackDispatcher::Send( const TXString& msg )
{
	std::function<void(const std::string&)>& cb = GetCallbackRef();
	void* ctx = GetContextRef();
	if ( cb ) cb( msg.GetStdString() );
}

