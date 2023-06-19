//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------namespace LightRightNetwork
#include "mvrxchange_prefix.h"
namespace MVRxchangeNetwork
{
    class MVRxchangeClient
    {
    public:
    MVRxchangeClient(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints);

    virtual void Deliver(const MVRxchangeMessage& msg);
    void         Close();

    private:
    void DoConnect(const tcp::resolver::results_type& endpoints);
    void DoReadHeader();
    void DoReadBody();
    void DoWrite();

    private:
    boost::asio::io_context&  fIo_context;
    tcp::socket               fSocket;
    LRNetMessage              fRead_msg;
    LRNetMessageQueue         fWrite_msgs;
    };
}