#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include <memory>

#include "../Socket.hpp"


class ConnectionManager
{
    public:
        void init();


    private:
        struct sockaddr_in _seraddr{};





};

extern std::unique_ptr<ConnectionManager> connMgr;


#endif 