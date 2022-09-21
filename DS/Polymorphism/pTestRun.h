#include <iostream>
#include <vector>                     
#include "pBox.h"                      
#include "pToughPack.h"                
#include "pCarton.h"                   
#include "pCan.h"

namespace Polymorphism
{
	void Run()
	{
		Box box{ 40, 30, 20 };
		Can can{ 10, 3 };
		Carton carton{ 40, 30, 20, "Plastic" };
		ToughPack hardcase{ 40, 30, 20 };

		std::vector<const Vessel*> vessels{ &box, &can, &carton, &hardcase };

		for (const auto* vessel : vessels)
			std::cout << "Volume is " << vessel->volume() << std::endl;
	}
}
