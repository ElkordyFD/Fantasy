
#include <iostream>
#include "fantasy.h"


using namespace std;


int main()
{
	PlayerMgr PM;
	PM.loadDatabase();

	Team t = PM.loadTeam(0);
	for (auto it : t.getFootballers())
		cout << it.getName() << " ";


	 
	/*Fantasy fantasyGamePlay; 
	fantasyGamePlay.Run();*/
}
