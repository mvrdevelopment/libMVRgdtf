//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------
#include "mvrxchange_prefix.h"
namespace MVRxchangeNetwork
{
    class MVRxchangeServer
    {
    public:
        MVRxchangeServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint);

        public:
            virtual void Deliver(const MVRxchangeMessage& msg);
        private:
            void DoAccept();

            tcp::acceptor       fAcceptor;

    }
}