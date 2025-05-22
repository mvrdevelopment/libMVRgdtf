//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once

namespace VectorworksMVR
{
    class FeedbackDispatcher 
    {

    public:
        static void SetCallback(std::function<void(const FixtureFeedback&)> cb, void* context);
        static void Send(const FixtureFeedback& msg);

    private:
        static std::function<void(const FixtureFeedback&)>& GetCallbackRef();
        static void*& GetContextRef();

    };
}
