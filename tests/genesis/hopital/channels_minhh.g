// ======================================================
// Channels for minimum HH models 
// ======================================================
// modified from genesis/scripts/neuron/channels.g

// note: included l'hopital rule on tabchannel defs to avoid
// singularity giving genesis error (returns -inf, breaks code)

// this script is a validation script for when this makes it to the
// tabulator of heccer.  Contributed by Nathan Lepora.

// ======================================================
// Parameters - Channel Conductancies 
// ======================================================
 
float ENa = 0.050
float EK = -0.090
float V_T = -65e-3

//=================================================
//           NA CHANNEL (Traub, Miles 1991)
//=================================================
function make_Na
     create tabchannel Na
     setfield ^ Ek {ENa} Gbar {500} Xpower 3 Ypower 1 Zpower 0
    
	 int   xdivs=5000
	 float xmin=-0.100, xmax=0.050, dx={(xmax-xmin)/xdivs}
	 call Na TABCREATE X {xdivs} {xmin} {xmax}
	 call Na TABCREATE Y {xdivs} {xmin} {xmax}

	 float valX_A, valX_B, valY_A, valY_B, Vm

	 int i		 

	 for (i=0; i<={xdivs}; i=i+1)

		 Vm = xmin + i*dx

		 valX_A = -0.32e6*(Vm-V_T-13e-3)/({exp {(Vm-V_T-13e-3)/-4e-3}}-1)
		 valX_B = 0.28e6*(Vm-V_T-40e-3)/({exp {(Vm-V_T-40e-3)/5e-3}}-1)
		 valY_A = 0.128e3*{exp {(Vm-V_T-17e-3)/-18e-3}} 
		 valY_B = 4e3/({exp {(Vm-V_T-40e-3)/-5e-3}}+1)
/*
		 if ({({exp {(Vm-V_T-13e-3)/-4e-3}}-1)}==0)
		    	 valX_A = -0.32e6/(1/-4e-3*{exp {(Vm-V_T-13e-3)/-4e-3}})
		 end

		 if ({({exp {(Vm-V_T-40e-3)/5e-3}}-1)}==0)
		    	 valX_B = 0.28e6/(1/5e-3*{exp {(Vm-V_T-40e-3)/5e-3}})
		 end
*/
		 setfield Na X_A->table[{i}] {valX_A} X_B->table[{i}] {valX_B}
		 setfield Na Y_A->table[{i}] {valY_A} Y_B->table[{i}] {valY_B}
	 end

	 tweakalpha Na X
	 tweakalpha Na Y
end

//=================================================
//           Kd CHANNEL (Traub, Miles 1991)
//=================================================
function make_Kd 
    create tabchannel Kd
    setfield ^ Ek {EK} Gbar {50} Xpower 4 Ypower 0 Zpower 0

	int   xdivs=5000
	float xmin=-0.100, xmax=0.050, dx={(xmax-xmin)/xdivs}
	call Kd TABCREATE X {xdivs} {xmin} {xmax}

	float valX_A, valX_B, Vm
	int i		 
	for (i=0; i<={xdivs}; i=i+1)
		Vm = xmin + i*dx
		valX_A = -0.032e6*(Vm-V_T-15e-3)/({exp {(Vm-V_T-15e-3)/-5e-3}}-1)
		valX_B = 0.5e3*{exp {(Vm-V_T-10e-3)/-40e-3}} 
		if ({({exp {(Vm-V_T-15e-3)/-5e-3}}-1)}==0)
		    	 valX_A = -0.032e6/(1/-5e-3*{exp {(Vm-V_T-15e-3)/-5e-3}})
		end
		setfield Kd X_A->table[{i}] {valX_A} X_B->table[{i}] {valX_B}
	end
	tweakalpha Kd X
end
