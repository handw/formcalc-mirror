(*
	AAAA-SM.m  
		generates the Fortran code for
		gamma gamma -> gamma gamma in the electroweak SM
		this file is part of FormCalc
		last modified 11 Jun 03 th

Reference: M. Boehm, R. Schuster, Z. Phys. C63 (1994) 219.

*)


Needs["FeynArts`"]

Needs["FormCalc`"]


time1 = SessionTime[]

CKM = IndexDelta


process = {V[1], V[1]} -> {V[1], V[1]}

name = "AAAA-SM"

SetOptions[InsertFields, Model -> "SM"]


SetOptions[Paint, PaintLevel -> {Classes}, ColumnsXRows -> {4, 5}]

(* take the comments out if you want the diagrams painted
DoPaint[diags_, file_] := Paint[diags, DisplayFunction ->
  (Display[ToFileName[MkDir[name <> ".diagrams"], file <> ".ps"], #]&)]
*)


Print["Boxes"]

tops = CreateTopologies[1, 2 -> 2, BoxesOnly];
ins = InsertFields[tops, process];
DoPaint[ins, "box"];
box = CalcFeynAmp[CreateFeynAmp[ins]]


abbr = OptimizeAbbr[Abbr[]]


dir = SetupCodeDir[name <> ".fortran", Drivers -> name <> ".drivers"]

WriteSquaredME[{}, box, abbr, dir]

WriteRenConst[{}, dir]


Print["time used: ", SessionTime[] - time1]
