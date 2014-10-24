FeynAmpList[Model -> "SM", GenericModel -> "Lorentz", 
   InsertionLevel -> Classes, ExcludeParticles -> {}, LastSelections -> {}, 
   ExcludeFieldPoints -> {}, Restrictions -> 
    ExcludeFieldPoints -> 
     {FieldPoint[0][-F[4, {1}], F[3, {2}], S[3]], 
      FieldPoint[0][-F[4, {1}], F[3, {2}], V[3]], 
      FieldPoint[0][-F[4, {1}], F[3, {3}], S[3]], 
      FieldPoint[0][-F[4, {1}], F[3, {3}], V[3]], 
      FieldPoint[0][-F[4, {2}], F[3, {1}], S[3]], 
      FieldPoint[0][-F[4, {2}], F[3, {1}], V[3]], 
      FieldPoint[0][-F[4, {2}], F[3, {3}], S[3]], 
      FieldPoint[0][-F[4, {2}], F[3, {3}], V[3]], 
      FieldPoint[0][-F[4, {3}], F[3, {1}], S[3]], 
      FieldPoint[0][-F[4, {3}], F[3, {1}], V[3]], 
      FieldPoint[0][-F[4, {3}], F[3, {2}], S[3]], 
      FieldPoint[0][-F[4, {3}], F[3, {2}], V[3]]}, VertexFunctions -> False, 
   ProcessName -> "S1", Process -> {{S[1], p1, MH}} -> {}][FeynAmp[
   GraphName["S1", T1, I1], q1, 
   -(RelativeCF*DiracTrace[DiracSlash[-q1] + Mass[F[Index[Generic, 2]]], 
        ChiralityProjector[-1]*
          G[1][0][-F[Index[Generic, 2]], F[Index[Generic, 2]], S[1]][
           ChiralityProjector[-1]] + 
         ChiralityProjector[1]*
          G[1][0][-F[Index[Generic, 2]], F[Index[Generic, 2]], S[1]][
           ChiralityProjector[1]]]*
       FeynAmpDenominator[PropagatorDenominator[q1, 
         Mass[F[Index[Generic, 2]]]]])/(32*Pi^4), 
   {Mass[F[Index[Generic, 2]]], 
     G[1][0][-F[Index[Generic, 2]], F[Index[Generic, 2]], S[1]][
      ChiralityProjector[-1]], 
     G[1][0][-F[Index[Generic, 2]], F[Index[Generic, 2]], S[1]][
      ChiralityProjector[1]], RelativeCF} -> 
    Insertions[Classes][{MLE[Index[Generation, 1]], 
      (-I/2*EL*MLE[Index[Generation, 1]])/(MW*SW), 
      (-I/2*EL*MLE[Index[Generation, 1]])/(MW*SW), 
      2*SumOver[Index[Generation, 1], 3]}, 
     {MQU[Index[Generation, 1]], 
      (-I/2*EL*MQU[Index[Generation, 1]])/(MW*SW), 
      (-I/2*EL*MQU[Index[Generation, 1]])/(MW*SW), 
      6*SumOver[Index[Generation, 1], 3]}, 
     {MQD[Index[Generation, 1]], 
      (-I/2*EL*MQD[Index[Generation, 1]])/(MW*SW), 
      (-I/2*EL*MQD[Index[Generation, 1]])/(MW*SW), 
      6*SumOver[Index[Generation, 1], 3]}]], 
  FeynAmp[GraphName["S1", T1, I2], q1, 
   (RelativeCF*FeynAmpDenominator[PropagatorDenominator[q1, 
        Mass[S[Index[Generic, 2]]]]]*
      G[1][0][S[1], -S[Index[Generic, 2]], S[Index[Generic, 2]]][1])/
    (32*Pi^4), {Mass[S[Index[Generic, 2]]], 
     G[1][0][S[1], -S[Index[Generic, 2]], S[Index[Generic, 2]]][1], 
     RelativeCF} -> 
    Insertions[Classes][{MH, ((-3*I)/2*EL*MH^2)/(MW*SW), 1}, 
     {MZ, (-I/2*EL*MH^2)/(MW*SW), 1}, {MW, (-I/2*EL*MH^2)/(MW*SW), 2}]], 
  FeynAmp[GraphName["S1", T1, I3], q1, 
   -(RelativeCF*FeynAmpDenominator[PropagatorDenominator[q1, 
         Mass[U[Index[Generic, 2]]]]]*
       G[1][0][S[1], -U[Index[Generic, 2]], U[Index[Generic, 2]]][1])/
    (32*Pi^4), {Mass[U[Index[Generic, 2]]], 
     G[1][0][S[1], -U[Index[Generic, 2]], U[Index[Generic, 2]]][1], 
     RelativeCF} -> 
    Insertions[Classes][{MZ, (-I/2*EL*MW)/(CW^2*SW), 2}, 
     {MW, (-I/2*EL*MW)/SW, 2}, {MW, (-I/2*EL*MW)/SW, 2}]], 
  FeynAmp[GraphName["S1", T1, I4], q1, 
   -(RelativeCF*FeynAmpDenominator[PropagatorDenominator[q1, 
         Mass[V[Index[Generic, 2]]]]]*MetricTensor[li1, li2]^2*
       G[1][0][S[1], -V[Index[Generic, 2]], V[Index[Generic, 2]]][
        MetricTensor[KI1[2], KI1[3]]])/(32*Pi^4), 
   {Mass[V[Index[Generic, 2]]], 
     G[1][0][S[1], -V[Index[Generic, 2]], V[Index[Generic, 2]]][
      MetricTensor[KI1[2], KI1[3]]], RelativeCF} -> 
    Insertions[Classes][{MZ, (I*EL*MW)/(CW^2*SW), 1}, {MW, (I*EL*MW)/SW, 2}]]]