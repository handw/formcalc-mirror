* process.h
* defines all process-dependent parameters
* this file is part of FormCalc
* last modified 8 Apr 04 th


* Definition of the external particles.
* The TYPEn may be one of SCALAR, FERMION, PHOTON, or VECTOR.
* (PHOTON is equivalent to VECTOR, except that longitudinal
* modes are not allowed)

#define TYPE1 FERMION
#define MASS1 ME
#define CHARGE1 1

#define TYPE2 FERMION
#define MASS2 ME
#define CHARGE2 -1

#define TYPE3 VECTOR
#define MASS3 MW
#define CHARGE3 1

#define TYPE4 VECTOR
#define MASS4 MW
#define CHARGE4 -1


* When using Dirac fermions (FermionChains -> Chiral|VA) and
* the trace technique (HelicityME), the following flag should be 
* defined to compute unpolarized cross-sections efficiently,
* i.e. without actually summing up the different helicities.
* This has no effect on the result, only on the speed of the
* calculation.
* Note: DIRACFERMIONS must NOT be defined when using Weyl fermions,
* i.e. FermionChains -> Weyl in CalcFeynAmp.

c#define DIRACFERMIONS


* The combinatorial factor for identical particles in the final state:
* 1/n! for n identical particles, 1 otherwise

#define IDENTICALFACTOR 1


* Possibly a colour factor, e.g.
* - an additional averaging factor if any of the incoming particles
*   carry colour,
* - the overall colour factor resulting from the external particles
*   if that cannot computed by FormCalc (e.g. if the model has no
*   colour indices, as SM.mod).

#define COLOURFACTOR 1


* Whether to include soft-photon bremsstrahlung.
* ESOFTMAX is the maximum energy a soft photon may have and may be
* defined in terms of sqrtS, the CMS energy.

#define BREMSSTRAHLUNG
#define ESOFTMAX .1D0*sqrtS


* Possibly some wave-function renormalization
* (e.g. if calculating in the background-field method)

c#define WF_RENORMALIZATION (nW*dWFW1 + nZ*dWFZ1)


* NCOMP is the number of components of the result vector.  Currently
* the components are 1 = tree-level result, 2 = one-loop result.

#define NCOMP 2


* Include the kinematics-dependent part of the code

#include "2to2.F"

