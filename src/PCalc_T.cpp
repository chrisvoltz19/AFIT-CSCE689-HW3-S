#include <cstring>
#include <stdexcept>
#include <fstream>
#include <iostream>

// added 
#include <PCalc_T.h>
#include <cmath>
#include <chrono>


/************************************************************************************************
 * PCalc_T (constructor) - Creates an array of primelist boolean objects with the size of
 *                       array_size and initializes them all to true 
 ************************************************************************************************/

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads):PCalc(array_size), tSize(array_size), threadNum(num_threads) 
{   
   // create a vector to hold the primes for thread use
   primes.reserve(sqrt(tSize)/2); 
   // clean primes out of garbage
   primes.clear();

   // create thread pool
   createPool(threadNum - 1); // use one less because one thread needs to be in charge 
   
}


/************************************************************************************************
 * PCalc_T (destructor) - deletes the primelist array
 ************************************************************************************************/

PCalc_T::~PCalc_T() {
   cleanup();
}

/************************************************************************************************
 * markNonPrimes - Goes through the array and marks out all nonprimes
 *                       
 ************************************************************************************************/

void PCalc_T::markNonPrimes()
{
   for(int i = 2; i < sqrt(tSize); i++) // each number at array
   {
	if(this->at(i) == true) // found prime, get rid of everything that is divisible by it
	{
		// check to see if a thread is available, and assign to work if it is
		// put prime in primes list TODO: does this need to be mutex protected?
		primes.emplace_back(i);
	}
   }
   // put 1 in primes so threads know they are done
   primes.emplace_back(1); 

   std::this_thread::sleep_for(std::chrono::seconds(3));
}

/************************************************************************************************
 * oneRound - Goes through the array and marks out multiples of passed in number
 * 		
 * 			num: the prime that was discovered and needs to be marked out
 *                       
 ************************************************************************************************/

void PCalc_T::oneRound(int num)
{
   for(int i = pow(num, 2); i < tSize; i += num)
   {
	this->at(i) = false;
   }
}


/************************************************************************************************
 * Cleanup - cleans up the threads (deleting primelist handled by parent?)
 ************************************************************************************************/

void PCalc_T::cleanup() {
   // clean up the threadpool
   std::cout << "Deleting threads" << std::endl;
   while(!tPool.empty())
   {
	tPool.at(0).join();
   }
   // delete the vector
   //delete tPool;
   
}


/************************************************************************************************
 * createPool - creates a thread pool 
 * 
 * num is the number of threads created in the pool
 ************************************************************************************************/

void PCalc_T::createPool(int num) 
{
   // reserve space for vector
   tPool.reserve(threadNum);
   
   // fill tPool with threads 
   for(int i = 0; i < num; i++)
   {
	// use a lambda to pass in this and run the tRun function with parameter 0
	//tPool.emplace_back(std::thread([this]{tRun(2);})); 
	tPool.emplace_back(std::thread([this]{tRun();}));

   }
}


/************************************************************************************************
 * tRun - function for threads to link to and runs them while they wait  
 * 
 * num is the number of threads created in the pool
 ************************************************************************************************/

//void PCalc_T::tRun(int num) 
void PCalc_T::tRun()
{
   int num = 0;
   while(num != 1) 
   {
        if(this->primes.empty())
	{
		num = 0; 
	}
	else
	{
		num = this->getPrime();
	}
   	// received a prime so process it
   	if(num > 1)
   	{
   	 	this->oneRound(num);
		std::cout << "Did one round :)" << std::endl;
		//num = 0; // reset to waiting for thread
   	}
   	else if(num == 0) // no work case 
   	{
		std::this_thread::sleep_for(std::chrono::microseconds(10));
		std::cout << "Waited" << std::endl;
   	}
   	else if(num == 1) // TODO:time to join thread to kill it
   	{
		//std::this_thread::join();
   	}
   	else //catch garbage case
   	{
   		std::cout << "Thread reached processed unexpected value" << std::endl;
   	}
   }
   //std::this_thread.join();   
}


/************************************************************************************************
 * getPrime - function for threads get the next available prime  
 * 
 *	returns the next prime for a thread to use 
 *
 ************************************************************************************************/
int PCalc_T::getPrime()
{
	std::lock_guard<std::mutex> lock(primesMutex);
	int first_prime = this->primes.at(0);
	if(first_prime != 1)
	{
		this->primes.erase(primes.begin()); 
	}
	return first_prime;
}

 
