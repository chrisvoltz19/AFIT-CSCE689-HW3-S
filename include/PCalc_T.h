#ifndef PCALC_T_H
#define PCALC_T_H

#include "PCalc.h"
//added 
#include <vector>
#include <thread>
#include <mutex>

// Your implementation of PCalc_T class should go here. 
// Make sure your constructor takes in two parameters:

// PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads);

// Call the parent constructor when initializing your constructor and pass in array_size. Then
// use num_threads to cap off how many threads you use to calculate all prime numbers

// I referenced stackoverflow.com/questions/15752659/thread-pooling-in-c11 and talked general threading concepts with Josh Larson to better understand as well as threading different paradigms, at a more general level, threading 
// I referenced stackoverflow.com/questions/50175002/invalid-use-of-non-static-member-function-c-thread-linux for an idea of how to use a lambda to pass in the function and this to my thread

class PCalc_T : public PCalc { 
   public:
      virtual ~PCalc_T();

      // Overload me!
      virtual void markNonPrimes();
      // added 
      PCalc_T(unsigned int array_size, unsigned int num_threads); 
      void createPool(int num);
      void oneRound(int num); 
      void tRun(int index);
      int getPrime();
      

      // if you overload, don't forget to call me
      virtual void cleanup();

   protected:


   private:
 
      PCalc_T();

      // Stuff to be left alone
      int threadNum; // int to hold the number of threads desired 
      std::vector<std::thread> tPool; // vector to hold threads that have been created 
      std::vector<unsigned int> primes; // vector to hold the primes for the threads
      std::mutex primesMutex; // mutex to guard the prime vector


      
      unsigned int tSize;

};

#endif
