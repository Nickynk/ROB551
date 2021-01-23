/**
 * @file rc_project_template.c
 *
 * This is meant to be a skeleton program for Robot Control projects. Change
 * this description and file name before modifying for your own purpose.
 */

#include <stdio.h>
#include <robotcontrol.h> // includes ALL Robot Control subsystems

// function declarations


/**
 * This template contains these critical components
 * - ensure no existing instances are running and make new PID file
 * - start the signal handler
 * - initialize subsystems you wish to use
 * - while loop that checks for EXITING condition
 * - cleanup subsystems at the end
 *
 * @return     0 during normal operation, -1 on error
 */
int main()
{
	// make sure another instance isn't running
	// if return value is -3 then a background process is running with
	// higher privaledges and we couldn't kill it, in which case we should
	// not continue or there may be hardware conflicts. If it returned -4
	// then there was an invalid argument that needs to be fixed.
	if(rc_kill_existing_process(2.0)<-2) return -1;

	// start signal handler so we can exit cleanly
	if(rc_enable_signal_handler()==-1){
		fprintf(stderr,"ERROR: failed to start signal handler\n");
		return -1;
	}

	// make PID file to indicate your project is running
	// due to the check made on the call to rc_kill_existing_process() above
	// we can be fairly confident there is no PID file already and we can
	// make our own safely.
	rc_make_pid_file();


	printf("\nSquare motion of the robot\n");
    rc_motor_init();
	// Keep looping until state changes to EXITING
	// Baisc form not working well on non-uniform floor
	// For carpet at home 
	for (int i=0;i<4;i++){
		rc_motor_set(1,-0.25);
		rc_motor_set(2,0.25);
		rc_nanosleep(8E9); 
		rc_motor_set(1,0.25);
		rc_motor_set(2,0.25);
		rc_nanosleep(1.8E9);
	}

	rc_motor_set(1,0);
	rc_motor_set(2,0);

	// close file descriptors
	rc_remove_pid_file();	// remove pid file LAST
	return 0;
}
