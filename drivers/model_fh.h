* model_fh.h
* declarations for model_fh.F
* this file is part of FormCalc
* last modified 18 May 11 th


#include "FHRecord.h"

	RecordDecl(record)
	common /rec/ record

	double precision Alfa0
	parameter (Alfa0 = 1/137.0359895D0)

	double complex CKM(3,3)
	double precision Mf(4,3), Mf2(4,3)
	double precision MZ, MZ2, MW, MW2, MH, MH2, MBatMB
	double precision CW, CW2, SW, SW2
	double precision ELMZ, AlfaMZ, GF, AlfaGF, AlfasMZ
	double precision EL, Alfa, Alfa2, GS, Alfas, Alfas2
	double precision CKMlambda, CKMA, CKMrhobar, CKMetabar

	common /sm_para/ CKM
	common /sm_para/ Mf, Mf2
	common /sm_para/ MZ, MZ2, MW, MW2, MH, MH2, MBatMB
	common /sm_para/ CW, CW2, SW, SW2
	common /sm_para/ ELMZ, AlfaMZ, GF, AlfaGF, AlfasMZ
	common /sm_para/ EL, Alfa, Alfa2, GS, Alfas, Alfas2
	common /sm_para/ CKMlambda, CKMA, CKMrhobar, CKMetabar

#ifndef CKMC
#define CKMC(i,j) DCONJG(CKM(i,j))
#endif

	double precision ME, ME2, MM, MM2, ML, ML2
	double precision MU, MU2, MC, MC2, MT, MT2
	double precision MD, MD2, MS, MS2, MB, MB2
	equivalence (Mf(2,1), ME), (Mf2(2,1), ME2)
	equivalence (Mf(2,2), MM), (Mf2(2,2), MM2)
	equivalence (Mf(2,3), ML), (Mf2(2,3), ML2)
	equivalence (Mf(3,1), MU), (Mf2(3,1), MU2)
	equivalence (Mf(3,2), MC), (Mf2(3,2), MC2)
	equivalence (Mf(3,3), MT), (Mf2(3,3), MT2)
	equivalence (Mf(4,1), MD), (Mf2(4,1), MD2)
	equivalence (Mf(4,2), MS), (Mf2(4,2), MS2)
	equivalence (Mf(4,3), MB), (Mf2(4,3), MB2)


	double complex UCha(2,2), VCha(2,2), ZNeu(4,4)
	double complex XHiggs(3,3,2)
	double complex deltaSf(6,6,4), UASf(6,6,4)
	double complex MSS2(3,3,5), Afd(2:4,3), Kf(3,3,2:4)
	double complex MUE, Mino1, Mino2, Mino3, SqrtEGl, Deltab
	double precision MCha(2), MCha2(2), MNeu(4), MNeu2(4)
	double precision MSS(5,3), MASf(6,4), MASf2(6,4)
	double precision MHiggs(4), MHiggs2(4), MHtree(4), MHtree2(4)
	double precision MGl, MGl2
	double precision CB, SB, TB, CB2, SB2, TB2, C2B, S2B
	double precision CA, SA, CA2, SA2, C2A, S2A
	double precision CAB, SAB, CBA, SBA, CBA2, SBA2, SAeff
	integer nmfv

	common /mssm_para/ UCha, VCha, ZNeu
	common /mssm_para/ XHiggs
	common /mssm_para/ deltaSf, UASf
	common /mssm_para/ MSS2, Afd, Kf
	common /mssm_para/ MUE, Mino1, Mino2, Mino3, SqrtEGl, Deltab
	common /mssm_para/ MCha, MCha2, MNeu, MNeu2
	common /mssm_para/ MSS, MASf, MASf2
	common /mssm_para/ MHiggs, MHiggs2, MHtree, MHtree2
	common /mssm_para/ MGl, MGl2
	common /mssm_para/ CB, SB, TB, CB2, SB2, TB2, C2B, S2B
	common /mssm_para/ CA, SA, CA2, SA2, C2A, S2A
	common /mssm_para/ CAB, SAB, CBA, SBA, CBA2, SBA2, SAeff
	common /mssm_para/ nmfv

#ifndef USfC
#define MSf(s,t,g) MASf(g+3*(s-1),t)
#define MSf2(s,t,g) MASf2(g+3*(s-1),t)
#define USf(i,j,t,g) UASf(g+3*(i-1),g+3*(j-1),t)
#define USfC(i,j,t,g) DCONJG(USf(i,j,t,g))
#define UASfC(i,j,t) DCONJG(UASf(i,j,t))

#define deltaSf_LL(i,j,t) deltaSf(i,j,t)
#define deltaSf_LR(i,j,t) deltaSf(i,j+3,t)
#define deltaSf_RL(i,j,t) deltaSf(j,i+3,t)
#define deltaSf_RR(i,j,t) deltaSf(i+3,j+3,t)

#define VChaC(i,j) DCONJG(VCha(i,j))
#define UChaC(i,j) DCONJG(UCha(i,j))
#define ZNeuC(i,j) DCONJG(ZNeu(i,j))

#define UHiggsC(i,j) DCONJG(UHiggs(i,j))
#define ZHiggsC(i,j) DCONJG(ZHiggs(i,j))

#define Af(t,g1,g2) Mf(t,g1)*Kf(g1,g2,t)
#define AfC(t,g1,g2) DCONJG(Af(t,g1,g2))
#define KfC(g1,g2,t) DCONJG(Kf(g1,g2,t))
#define Mino3C DCONJG(Mino3)
#define MUEC DCONJG(MUE)
#define SqrtEGlC DCONJG(SqrtEGl)
#endif

	double precision Mh0, Mh02, MHH, MHH2, MA0, MA02, MHp, MHp2
	equivalence (MHiggs(1), Mh0), (MHiggs2(1), Mh02)
	equivalence (MHiggs(2), MHH), (MHiggs2(2), MHH2)
	equivalence (MHiggs(3), MA0), (MHiggs2(3), MA02)
	equivalence (MHiggs(4), MHp), (MHiggs2(4), MHp2)

	double precision Mh0tree, Mh0tree2, MHHtree, MHHtree2
	double precision MA0tree, MA0tree2, MHptree, MHptree2
	equivalence (MHtree(1), Mh0tree), (MHtree2(1), Mh0tree2)
	equivalence (MHtree(2), MHHtree), (MHtree2(2), MHHtree2)
	equivalence (MHtree(3), MA0tree), (MHtree2(3), MA0tree2)
	equivalence (MHtree(4), MHptree), (MHtree2(4), MHptree2)

	double complex UHiggs(3,3), ZHiggs(3,3)
	equivalence (XHiggs(1,1,1), UHiggs)
	equivalence (XHiggs(1,1,2), ZHiggs)

	double complex Atau, At, Ab
	equivalence (Afd(2,3), Atau)
	equivalence (Afd(3,3), At)
	equivalence (Afd(4,3), Ab)

	double precision MASf_flat(6*4), MASf2_flat(6*4)
	equivalence (MASf, MASf_flat)
	equivalence (MASf2, MASf2_flat)

	double complex deltaLRuc, deltaLRct, deltaLRut
	equivalence (deltaSf_LR(1,2,3), deltaLRuc)
	equivalence (deltaSf_LR(2,3,3), deltaLRct)
	equivalence (deltaSf_LR(1,3,3), deltaLRut)

	double complex deltaRLuc, deltaRLct, deltaRLut
	equivalence (deltaSf_RL(1,2,3), deltaRLuc)
	equivalence (deltaSf_RL(2,3,3), deltaRLct)
	equivalence (deltaSf_RL(1,3,3), deltaRLut)

	double complex deltaRRuc, deltaRRct, deltaRRut
	equivalence (deltaSf_RR(1,2,3), deltaRRuc)
	equivalence (deltaSf_RR(2,3,3), deltaRRct)
	equivalence (deltaSf_RR(1,3,3), deltaRRut)

	double complex deltaLL12, deltaLL23, deltaLL13
	equivalence (deltaSf_LL(1,2,4), deltaLL12)
	equivalence (deltaSf_LL(2,3,4), deltaLL23)
	equivalence (deltaSf_LL(1,3,4), deltaLL13)

	double complex deltaLRds, deltaLRsb, deltaLRdb
	equivalence (deltaSf_LR(1,2,4), deltaLRds)
	equivalence (deltaSf_LR(2,3,4), deltaLRsb)
	equivalence (deltaSf_LR(1,3,4), deltaLRdb)

	double complex deltaRLds, deltaRLsb, deltaRLdb
	equivalence (deltaSf_RL(1,2,4), deltaRLds)
	equivalence (deltaSf_RL(2,3,4), deltaRLsb)
	equivalence (deltaSf_RL(1,3,4), deltaRLdb)

	double complex deltaRRds, deltaRRsb, deltaRRdb
	equivalence (deltaSf_RR(1,2,4), deltaRRds)
	equivalence (deltaSf_RR(2,3,4), deltaRRsb)
	equivalence (deltaSf_RR(1,3,4), deltaRRdb)
