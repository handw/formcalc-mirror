	double precision function CompAZ(x, E, icase)
	implicit none
	double precision x, E
	integer icase

* Input parameters:
* -----------------
*
*   x             Fraction of beam energy carried by photon  ( 0 < x < 1 )
*
*   E             Electron beam energy [GeV]
*
*   icase         Choice of output distribution:
*
*   icase = 0     Full spectra - sum of three contributions
*           1     Main contribution from direct Compton process
*           2     Contribution from scattering with 2 photons
*           3     Contribution from scattering on secondary electrons
*
*          10     Polarization of the full spectra
*          11     Polarization of the 1st component (direct Compton)
*          12     Polarization of the 2nd component (two photon)
*          13     Polarization of the 3rd component (secondary electron)
*
*          20     Effective z parameter
*          21     maximum x value for direct Compton
*          22     maximum x value for scattering with 2 photons

* Parameters of the distribution, partly fitted to the spectra from V. Telnov
	double precision par(14)
	data Par /
     &    18.08800D0    ,                         ! Laser parameter
     &      .06594662D0 ,    .7060851D0 ,         ! Nonlinear corrections
     &      .7115863D0  ,   -.6776124D0 ,  0D0 ,  ! Total normalization
     &      .5540019D0  ,  37.38912D0   ,         ! 2nd component fraction
     &      .7257064D0  ,    .517959D0  ,         ! 3rd component fraction
     &     3.315865D0   ,    .387423D0  ,         ! Corrections
     &      .85D0       ,   1.00D0        /       ! Polarizations

	double precision Ee, z0, xi, z
	double precision Tot, Tot2, Tot3
	double precision Br2, gpow, pole, poll, pol, pole2

	double precision xmax, xmax2, g
	double precision gflux1, gflux2, gflux3, gflux
	double precision Pol1, Pol2, Pol3, Ptot
	double precision g1, g2, dg, p1, p2, dp
	double precision ymin, ymin2, ymax, y1, y2, dy

	logical DoPolar

	integer iy, ny
	parameter (ny = 100)

	double precision CompAZc, CompAZp
	external CompAZc, CompAZp

* Check input flag
	if( .NOT. ((icase .GE. 0  .and. icase .LE. 3 ) .or.
     &             (icase .GE. 10 .and. icase .LE. 13) .or.
     &             (icase .GE. 20 .and. icase .LE. 22)) ) then
	   print *, "CompAZ: Invalid distribution flag ", icase
	   CompAZ = 0
	   return
	 endif

* Check input energy
	if( E .lt. 50 .or. E .gt. 500 ) then
	  print *, "CompAZ: Beam energy outside range 50..500: ", E
	  CompAZ = 0
	  return
	endif

* Polarisation calculation flag

	DoPolar = (icase .GE. 10 .and. icase .LE. 13) 

* Set parameter values for given energy
* -------------------------------------

* Beam energy in TeV
	Ee = e/1000D0

* Nominal value of z = 4*Ee*El/me^2
	z0 = par(1)*ee

* correction nonlinear effects
	xi = par(2) + par(3)*ee

* effective z
	z = z0/(1 + xi)

* Maximum x values for different contributions
	xmax = z/(1 + z)
	xmax2 = 2*z/(1 + 2*z)

	if( icase .eq. 20 ) then
	  CompAZ = z
	  return
	else if( icase .eq. 21 ) then
	  CompAZ = xmax
	  return
	else if( icase .eq. 22 ) then
	  CompAZ = xmax2
	  return
	endif

* normalization of main compton component
	Tot = par(4) + ee*(par(5) + ee*par(6))

* normalization of additional contributions
	Tot2 = Tot*par(7)*(1 - exp(-xi*xi*par(8)))
	Tot3 = Tot*(par(9) + ee*par(10))

* Corrections to Compton spectra
	Br2 = par(11)
	gpow = par(12)

* Electron/laser polarisation
	Pole = par(13)
	poll = par(14)

	Pol = Pole*poll

* Leading Compton term
* --------------------

	gflux1 = 0
	pol1 = 0

	if( x .gt. 0 .and. x .le. xmax .and. Tot .gt. 0 ) then
	  gflux1 = CompAZc(x, z, Pol)
	  g = (z/x - z - 1)
	  if( g .gt. 0 ) then
	    g = sqrt(g)
	  else
	    g = 0
	  endif

	  gflux1 = gflux1*exp( -Br2 * g*g/8D0 )

	  if( DoPolar ) pol1 = CompAZp(x, poll, Pole, z)

	EndIf

	if( icase .eq. 1 ) then
	   CompAZ = Tot*gflux1
	   return
	else if( icase .eq. 11) then
	   CompAZ = pol1
	   return
	endif

* Scattering on 2 photons
* -----------------------

	gflux2 = 0
	pol2 = 0
	
	if( x .gt. 0 .and. x .lt. xmax2 .and. Tot2 .gt. 0 ) then
	  gflux2 = CompAZc(x, 2*z, Pol)
	  g = 2*z/x - 2*z - 1
	  if( g .gt. 0 ) then
	    g = sqrt(g)
	  else
	    g = 0
	  endif

	  gflux2 = gflux2*exp( -Br2 * g*g/8D0 )* g**gpow

	  if( DoPolar .and. x .gt. xmax ) then
	     Pol2 = CompAZp(x, poll, Pole, 2*z)
	  else if( DoPolar ) then
	     Pol2 = CompAZp(xmax, poll, Pole, 2*z)
	  endif
	EndIf

	if( icase .eq. 2 ) then
	   CompAZ = Tot2*gflux2
	   return
	else if( icase .eq. 12 ) then
	   CompAZ = pol2
	   return
	endif

* Electron rescattering
* ---------------------

	gflux3 = 0
	pol3 = 0
	
	if( x .gt. 0 .and. x .le. xmax .and. Tot3 .gt. 0 ) then
	  ymin = .5D0*x*(1 + sqrt(4/x/z + 1))

	  ymin2 = 1/(z + 1)
	  if( ymin2 .gt. ymin ) ymin = ymin2

	  ymax = 1

	  if( ymax .gt. ymin ) then
	    pole2 = 0

	    y1 = ymin
	    y2 = y1

* To avoid numerical problems
	    y1 = y1*1.0001D0

	    g1 = log(y1*z + 1)/log(z + 1)/y1 *
     &        CompAZc(x/y1, y1*z, pole2*poll)*CompAZc(1 - y1, z, Pol)

	    if( DoPolar ) p1 = CompAZp(x/y1, poll, pole2, y1*z)

	    dy = (ymax - ymin)/ny

	    do iy = 1, ny       
	      y2 = y2 + dy
	      g2 = log(y2*z + 1)/log(z + 1)/y2 *
     &          CompAZc(x/y2, y2*z, pole2*poll)*CompAZc(1 - y2, z, Pol)
	      
	      dg = .5D0*(g1 + g2)*dy
	      dp = .5D0*(g1*p1 + g2*p2)*dy

	      gflux3 = gflux3 + dg

	      if( DoPolar ) then
	        p2 = CompAZp(x/y2, poll, pole2, y2*z)
	        dp = .5D0*(g1*p1 + g2*p2)*dy
	        Pol3 = Pol3 + dp
	        p1 = p2
	      endif

	      y1 = y2
	      g1 = g2
	    enddo
	  endif
	endif

	if( icase .eq. 3 ) then
	  CompAZ = Tot3*gflux3
	  return
	else if( icase .eq. 13 .and. gflux3 .gt. 0 ) then
	  CompAZ = pol3/gflux3
	  return
	else if( icase .eq. 13 ) then
	  CompAZ = 0
	  return
	endif

	Gflux = Tot*gflux1 + Tot2*gflux2 + Tot3*gflux3

	if( icase .eq. 0 ) then
	  CompAZ = Gflux
	else if( Gflux .gt. 0 .and. icase .eq. 10 ) then
	  Ptot = Tot*gflux1*pol1 + Tot2*gflux2*pol2 + Tot3*pol3
	  CompAZ = Ptot/Gflux
	else
	  CompAZ = 0
	endif
	end


************************************************************************
** 'Ideal' spectrum of compton backscattered photons

	double precision function CompAZc(x, z, Pol)
	implicit none
	double precision x, z, Pol

	double precision xmax, l, r, y, gflux, norm

	xmax = z/(1 + z)

	if( x .lt. 0 .or. x .gt. xmax ) then
	  CompAZc = 0
	  return
	endif

* Flux normalisation (corrected!  formula in paper is wrong)
	l = log(1 + z)
	norm = (16 + z*(32 + z*(18 + z)))/(2*z*(z + 1)**2) +
     &    (1 - 4/z - 8/z**2)*l +
     &    Pol*(2 + z*z/(2*(z + 1)**2) - (1 + 2/z)*l)

* Additional variables, for easier calculation
	r = x/(1 - x)
	y = 1 - x + 1/(1 - x)

* Photon flux, as given in hep-ph/9508397
	gflux = y + 4*r/z*(r/z - 1) + Pol*r*(2 - x)*(2*r/z - 1)

	CompAZc = gflux/norm
	end


************************************************************************
** Calculate spectrum of compton backscattered photons

	double precision function CompAZp(x, Pl, Pb, z)
	Implicit none
	double precision x, Pl, Pb, z

	double precision xmax, r, y, gflux, gpol, Pol

	xmax = z/(1 + z)

	if( x .lt. 0 .or. x .gt. xmax ) then
	  CompAZp = 0
	  return
	EndIf

	Pol = Pl*Pb
	r = x/(1 - x)
	y = 1 - x + 1/(1 - x)

* Photon polarized flux
	gpol = Pb*r*(1 + (1 - x)*(2*r/z - 1)**2) + Pl*y*(2*r/z - 1)

* Photon flux
	gflux = y + 4*r/z*(r/z - 1) + Pol*r*(2 - x)*(2*r/z - 1)

	CompAZp = gpol/gflux
	end
