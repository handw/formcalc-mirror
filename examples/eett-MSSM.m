(*
	eett-MSSM.m
		generates the Fortran code for
		e^+ e^- -> t-bar t in the MSSM
		this file is part of FormCalc
		last modified 11 Jun 03 th

Reference: W. Hollik, C. Schappacher,
           Nucl. Phys. B545 (1999) 98 [hep-ph/9807427].

Note: the QED contributions are not taken into account. To plug
the QED part back in, comment out the parts in DiagramSelect that
eliminate a V[1].

*)


Needs["FeynArts`"]

Needs["FormCalc`"]


time1 = SessionTime[]

CKM = IndexDelta

Small[ME] = Small[ME2] = 0


process = {-F[2, {1}], F[2, {1}]} -> {-F[3, {3}], F[3, {3}]}

name = "eett-MSSM"

SetOptions[InsertFields, Model -> "MSSM", Restrictions -> NoLightFHCoupling]


SetOptions[Paint, PaintLevel -> {Classes}, ColumnsXRows -> {4, 5}]

(* take the comments out if you want the diagrams painted
DoPaint[diags_, file_] := Paint[diags, DisplayFunction ->
  (Display[ToFileName[MkDir[name <> ".diagrams"], file <> ".ps"], #]&)]
*)


Print["Counter terms"]

tops = CreateCTTopologies[1, 2 -> 2,
  ExcludeTopologies -> {TadpoleCTs, WFCorrectionCTs}];
	(* this is because there are no counter terms in MSSM.mod yet: *)
ins = InsertFields[tops, process, Model -> "SMc"];
ins = DiagramSelect[ins, FreeQ[#, Field[5|6] -> S]&];
DoPaint[ins, "counter"];
counter = CreateFeynAmp[ins] /. SW -> -SW


Print["Born"]

tops = CreateTopologies[0, 2 -> 2];
ins = InsertFields[tops, process];
DoPaint[ins, "born"];
born = CalcFeynAmp[CreateFeynAmp[ins]]


Print["Self energies"]

tops = CreateTopologies[1, 2 -> 2, SelfEnergiesOnly];
ins = InsertFields[tops, process];
ins = DiagramSelect[ins, FreeQ[#, Field[5|6] -> S]&];
DoPaint[ins, "self"];
self = CalcFeynAmp[
  CreateFeynAmp[ins],
  Select[counter, DiagramType[#] == 2 &]]


Print["Vertices"]

tops = CreateTopologies[1, 2 -> 2, TrianglesOnly];
ins = InsertFields[tops, process];
ins = DiagramSelect[ins,
  FreeQ[#, Field[5] -> S] && FreeQ[#, Field[6|8] -> V[1]] &];
DoPaint[ins, "vert"];
vert = CalcFeynAmp[
  CreateFeynAmp[ins],
  Select[counter, DiagramType[#] == 1 &]]


Print["Boxes"]

tops = CreateTopologies[1, 2 -> 2, BoxesOnly];
ins = InsertFields[tops, process];
ins = DiagramSelect[ins, FreeQ[#, Field[6|7] -> V[1]]&];
DoPaint[ins, "box"];
box = CalcFeynAmp[
  CreateFeynAmp[ins],
  Select[counter, DiagramType[#] == 0 &]]


col = ColourME[All, born]

abbr = OptimizeAbbr[Abbr[]]


dir = SetupCodeDir[name <> ".fortran", Drivers -> name <> ".drivers"]

WriteSquaredME[born, {self, vert, box}, col, abbr, dir]


InsertFieldsHook[tops_, f1_F -> f2_F] :=
  InsertFields[tops, f1 -> f2, ExcludeParticles -> V[1]]

WriteRenConst[{self, vert, box}, dir]


Print["time used: ", SessionTime[] - time1]
