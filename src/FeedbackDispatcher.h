//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once

namespace VectorworksMVR
{
    class FeedbackDispatcher 
    {

    public:
        static void SetCallback(std::function<void(const std::string&)> cb, void* context);
        static void Send(const TXString& msg);

    private:
        static std::function<void(const std::string&)>& GetCallbackRef();
        static void*& GetContextRef();

    };
}
