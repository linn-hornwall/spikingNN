/*! \class CortexInitializer
 *
 *  \author Neuro-1
 * 
 *  \date 19.10.2016
 *
 *  \brief this is the interface for the user to start the simulation and set the parameters
 *
 *  * \details the user can change the parameters or use the default values by using flags when lauching the simulation
		The flags are: 	-r 1 			to launch the simulation
	 					-g (double) 	to set the inhibitory amplitude 
	 					-f (double) 	to set the Vext/Vthr ratio (ratio between external frequency and threshold frequency)
	 					-j (double) 	to set the amplitude of excitatory spikes 
	 					-h 				for more details about flags and their usage
 */

#ifndef CORTEXINITIALIZER_H
#define CORTEXINITIALIZER_H

/*! 	\brief Function for the user to start the simulation and set the parameters 
		 * @param[in] argc the number of arguments written in command line
		 * @param[in] argv the arguments entered in the command line
         * @param[in] timestep the time step (in ms) to be used in the simulation
         * @param[in] max_time the simulation time in ms 
*/        
bool initialize_cortex (int argc, char** argv, double timestep, int max_time);

#endif
