#ifndef PCALC_SP_H
#define PCALC_SP_H

#include "PCalc.h"

// Add your PCalc_SP class definition here as a child class of PCalc
// Be sure to overload the right methods from PCalc or it won't compile

// This class should manage the single process implementation of the prime number generator. I'd recommend
// getting this working first, then tackling multithreaded

class PCalc_SP : public PCalc { 
   public:
      virtual ~PCalc_SP();
      PCalc_SP(unsigned int array_size); 

      // Overload me!
      virtual void markNonPrimes();

      // if you overload, don't forget to call me
      virtual void cleanup();

   protected:


   private:

      // Stuff to be left alone
      unsigned int sSize;
};

#endif
