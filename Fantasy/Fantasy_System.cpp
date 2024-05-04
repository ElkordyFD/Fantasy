
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include "TeamMgr.h"
#include "PlayerMgr.h"





using namespace std;





int main()
{/*
     TeamMgr teamMgr;
     teamMgr.loadDatabase();
     teamMgr.Match(0);*/

    Player p(1 , "Mooaz" , "1234");
    PlayerMgr pg(p);
    pg.loadFootballersFromDatabase();

    pg.menuOfOrders();
        
}
