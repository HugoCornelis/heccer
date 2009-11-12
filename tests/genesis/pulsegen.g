//genesis - demonstration of pulsegen object

//- still working on adapting this to heccer. 
create pulsegen /pulse0
setfield ^ level1 50.0 width1 3.0 delay1 5.0 level2 -20.0 width2 5.0  \
    delay2 8.0 baselevel 10.0 trig_mode 0

create pulsegen /trig
setfield ^ level1 20.0 width1 1.0 delay1 5.0 width2 30.0

create pulsegen /pulse1
setfield ^ level1 50.0 width1 3.0 delay1 5.0 level2 -20.0 width2 5.0  \
    delay2 8.0 baselevel 10.0 trig_mode 1

addmsg /trig /pulse1 INPUT output

create pulsegen /gate
setfield ^ level1 20.0 width1 30.0 delay1 15.0 width2 30.0

create pulsegen /pulse2
setfield ^ level1 50.0 width1 3.0 delay1 5.0 level2 -20.0 width2 5.0  \
    delay2 8.0 baselevel 10.0 trig_mode 2

addmsg /gate /pulse2 INPUT output



create asc_file /pulse0_out 
setfield /pulse0_out    filename "pulse0.txt" flush 1  leave_open 1 append 1  float_format %0.9g
addmsg       /pulse0     /pulse0_out       SAVE output
call /pulse0_out OUT_OPEN
call /pulse0_out OUT_WRITE "pulse0 output"        // Write a header



create asc_file /pulse1_out 
setfield /pulse1_out    filename "pulse1.txt" flush 1  leave_open 1 append 1  float_format %0.9g
addmsg       /pulse1     /pulse1_out       SAVE output
call /pulse1_out OUT_OPEN
call /pulse1_out OUT_WRITE "pulse1 output"        // Write a header



create asc_file /pulse2_out 
setfield /pulse2_out    filename "pulse2.txt" flush 1  leave_open 1 append 1  float_format %0.9g
addmsg       /pulse2     /pulse2_out       SAVE output
call /pulse2_out OUT_OPEN
call /pulse2_out OUT_WRITE "pulse2 output"        // Write a header


reset
setclock 0 0.5
step 200
 