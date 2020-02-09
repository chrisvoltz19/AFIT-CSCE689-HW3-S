#include <cstring>
#include <stdexcept>
#include <fstream>
#include <iostream>

// added 
#include <PCalc_SP.h>
#include <cmath>

/************************************************************************************************
 * PCalc_SP (constructor) - Creates an array of primelist boolean objects with the size of
 *                       array_size and initializes them all to true 
 ************************************************************************************************/

PCalc_SP::PCalc_SP(unsigned int array_size):PCalc(array_size), sSize(array_size)
{
   // set 1 and 0 to false if supposed to 
   //this->at(0) = false;
   //this->at(1) = false;
   
}


/************************************************************************************************
 * PCalc_SP (destructor) - deletes the primelist array
 ************************************************************************************************/

PCalc_SP::~PCalc_SP() {
}

/************************************************************************************************
 * markNonPrimes - Goes through the array and marks out all nonprimes
 *                        
 ************************************************************************************************/

void PCalc_SP::markNonPrimes()
{
   for(int i = 2; i < sqrt(sSize); i++)
   {
	if(this->at(i) == true)
	{
		for(int j = pow(i, 2); j < sSize; j += i)
		{
			this->at(j) = false;
		}			
	}
   }

}

/************************************************************************************************
 * Cleanup - deletes the primelist array
 ************************************************************************************************/

void PCalc_SP::cleanup() {
   //free(primelist);
   std::cout << "Single Thread Cleaned Up" << std::endl;
}



