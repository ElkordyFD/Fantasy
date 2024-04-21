
#include <iostream>
#include <sstream>
#include "TeamMgr.h"
using namespace std;
int main()
{
    cout << "Hello World!\n";
    TeamMgr teamMgr;
    teamMgr.loadDatabase();
    teamMgr.Match(0);
    
        
}
