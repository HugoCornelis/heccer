setclock 0 2e-5
create compartment c1
setfield c1 \
	Cm 4.57537e-11 \
	Em -0.08 \
	initVm -0.068 \
	Ra 360502 \
	Rm 3.58441e8
copy c1 c2

setfield c1 \
	inject 1e-8

setfield c2 \
	Cm 5.755329373e-12 \
	Ra 772813.4375 \
	Rm 8.548598272e9

addmsg c1 c2 AXIAL Vm
addmsg c2 c1 RAXIAL Ra Vm

create hsolve h
setmethod h 11
setfield h \
	chanmode 4 \
	path /c1,/c2
call h SETUP
reset

function showfields

	showfield h \
		results[0] \
		results[1] \
		results[2] \
		results[3] \
		vm[0] \
		vm[1]
end
