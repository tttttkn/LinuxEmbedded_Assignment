#include "ConnectionManager/ConnectionManager.hpp"

int main()
{
    connMgr = std::make_unique<ConnectionManager>();
    connMgr->init();
    
    return 0; 
}