// genesis - minimum hodgkin huxley spiking neuron 

// Create library of prototype elements
include protodefs_minhh		

// Stepsize for sim
float dt = 1e-5

//===============================
// Main Script
//===============================

// Build the cell using the cell reader
readcell cell_minhh.p /cell 

// Initialise sim 
check
reset 
setclock 0 {100*dt}
step 100 -t 

// Save initial state 
save /cell/## mycell.save 

// Run sim
reset
setclock 0 {dt}
restore mycell.save

setfield /cell/soma inject {0} 
step 0.1 -t 
setfield /cell/soma inject {1e-9} 
step 0.2 -t 

