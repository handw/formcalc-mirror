* num.h
* headers for the computation of the numerators
* this file is part of FormCalc
* last modified 17 Jul 12 th


#ifndef NUM_H
#define NUM_H

#define q1 0

#ifdef SAMURAI
#define NumeratorFunction(f) function f(ncut, q1in, MuTildeSq)
#define Result(f) f
#else
#define NumeratorFunction(f) subroutine f(q1in, res)
#define Result(f) res
#endif

#else

#ifdef SAMURAI
	integer ncut
	ComplexType q1in(4)
	RealType MuTildeSq
#include "inline.h"
	vec(1,1,q1) = q1in(4) + q1in(3)
	vec(2,2,q1) = q1in(4) - q1in(3)
	vec(2,1,q1) = q1in(1) + cI*q1in(2)
	vec(1,2,q1) = q1in(1) - cI*q1in(2)
	muscale = MuTildeSq
#else
	ComplexType q1in(0:3)
#include "inline.h"
	vec(1,1,q1) = q1in(0) + q1in(3)
	vec(2,2,q1) = q1in(0) - q1in(3)
	vec(2,1,q1) = q1in(1) + cI*q1in(2)
	vec(1,2,q1) = q1in(1) - cI*q1in(2)
#endif

#endif

