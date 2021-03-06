* NJCcut.F
* the FormCalc wrapper for the Ninja three-point function
* this file is part of FormCalc
* last modified 27 Oct 15 th

#include "types.h"


	subroutine NJCmas(mi, p1, p2, p1p2, m1, m2, m3)
	implicit none
	ComplexType mi(*)
	RealType p1, p2, p1p2, m1, m2, m3
	end


************************************************************************

	ComplexType function NJCcut(mi, hdelta, rank,
     &    num, muexp, t3exp, t2exp,
     &	  k1, k2, m1, m2, m3)
	implicit none
	ComplexType mi(*)
	external num, muexp, t3exp, t2exp
	integer hdelta, rank
	integer*8 k1, k2
	RealType m1, m2, m3

#include "NJ.h"

	RealType kj(0:3,3), mj(3)
	ComplexType res(-2:0)

	NJCcut = 0
	if( hdelta .eq. 0 ) return

	kj(0,1) = 0
	kj(1,1) = 0
	kj(2,1) = 0
	kj(3,1) = 0
	call NJMomDecode(k1, kj(0,2))
	call NJMomDecode(k2, kj(0,3))

	mj(1) = m1
	mj(2) = m2
	mj(3) = m3

#if NJDEBUG >= 3
	print *, "  rank =", rank
	print '("   k1: ",Z8.8)', k1
	print *, "  k1 =", kj(0,2)
	print *, "      ", kj(1,2)
	print *, "      ", kj(2,2)
	print *, "      ", kj(3,2)
	print '("   k2: ",Z8.8)', k2
	print *, "  k2 =", kj(0,3)
	print *, "      ", kj(1,3)
	print *, "      ", kj(2,3)
	print *, "      ", kj(3,3)
	print *, "  m1 =", mj(1)
	print *, "  m2 =", mj(2)
	print *, "  m3 =", mj(3)
	call flush(6)
#endif

	call ninjaformcalc(num, muexp, t3exp, t2exp, 3, rank,
     &    kj, mj, mudim, res)
	NJCcut = res(-epsi)

#if NJDEBUG
	print *, "  NJCcut =", NJCcut
	call flush(6)
#endif
	end

