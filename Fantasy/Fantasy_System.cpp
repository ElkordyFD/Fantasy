
#include <iostream>
#include <unordered_set>
#include "TeamMgr.h"




using namespace std;





int main()
{
    TeamMgr teamMgr;
    teamMgr.loadDatabase();
    for (int i{ 0 }; i < 5; i++) {
        teamMgr.Match(i);
        teamMgr.showFoot("ManUnited");
    }

}
