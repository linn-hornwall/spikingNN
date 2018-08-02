#include "CortexInitializer.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <tclap/CmdLine.h>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "Cortex.hpp"
#include "Neuron.hpp"

#define BOLD "\033[1m\033[37m"
#define RESET "\033[0m"

static const double NUMBER_OF_NEURONS(12500);
static const double VERBOSE(true);

static const double DEFAULT_RELATIVE_AMPLITUDE(5.0);
static const double DEFAULT_RATIO(2.0);
static const double DEFAULT_AMPLITUDE(0.1);

bool initialize_cortex (int argc, char** argv, double timestep, int max_time){

	

	try{
		TCLAP::CmdLine cmd ("Variables");
		TCLAP::ValueArg<bool> launchProgram ("r", "Run", "Enables to run the programm", false, false, "bool");
		cmd.add (launchProgram);
		TCLAP::ValueArg<double> relAmplitudeArg("g", "Relative_inhibitory_amplitude", "Inhibitory amplitude (default: 5)", false, DEFAULT_RELATIVE_AMPLITUDE, "double");
		cmd.add (relAmplitudeArg);
		TCLAP::ValueArg<double> ratioArg("f","Ratio_Vext_divide_by_Vthr", "Ratio between External frequency (Vext) and Threshold frequency (Vthr) (default: 2", false, DEFAULT_RATIO, "double");
		cmd.add (ratioArg);
		TCLAP::ValueArg<double> amplitudeArg("j", "Excitatory_amplitude", "Amplitude of the spike of an excitatory neuron (default: 0.1 mV)", false, DEFAULT_AMPLITUDE, "double");
		cmd.add (amplitudeArg);
		cmd.parse(argc, argv);
		
		if (relAmplitudeArg.getValue() < 0){
			
			std::cout << "Error, relative inhibitory amplitude must be larger than 0" << std::endl;
			std::cout << "Try again !" << std::endl;
			return false;
		}
		
		else if (ratioArg.getValue() < 0){
			
			std::cout << "Error, ratio between external and threshold frequency must be larger than 0" << std::endl;
			std::cout << "Try again !" << std::endl;
			return false;
		}
		
		else if (amplitudeArg.getValue() < 0){
			
			std::cout << "Error, the excitatory amplitude must be larger than 0" << std::endl;
			std::cout << "Try again !" << std::endl;
			return false;
		}

				
		if (!launchProgram.getValue()){
			
			//"-r" flag was not set to true --> don't run program
			
			std::cout << "Welcome to our "<< BOLD << "NeuronSimulation program" << RESET << " ! Its purpose is to simulate a neural network" << std::endl;
			std::cout << "Execute the program with different flags to change its behavior :" << std::endl;
			std::cout << "     '" << BOLD << "-r " << RESET << "1' to run the program" << std::endl;
			std::cout << "     '" << BOLD << "-h" << RESET << "' to display all the available flags" << std::endl;
			std::cout << "Please refer to the README for further details and for an example executions" << std::endl;
			
		} else if (launchProgram.getValue()){
			
			//"-r" set to true --> run the program
			
			// display parameters
			std::cout << "The following parameters will be used for the simulation :" << std::endl;
			std::cout.setf(std::ios::left);
			std::cout << std::setw(40) << "     Relative inhibitory amplitude: ";
			std::cout.unsetf(std::ios::left);
			std::cout << std::setw(10) << BOLD << relAmplitudeArg.getValue() << RESET << std::endl;
	
			std::cout.setf(std::ios::left);
			std::cout << std::setw(40) << "     Ratio Vext/Vthr: ";
			std::cout.unsetf(std::ios::left);
			std::cout << std::setw(10) << BOLD << ratioArg.getValue() << RESET << std::endl;

			std::cout.setf(std::ios::left);
			std::cout << std::setw(40) << "     Excitatory amplitude: ";
			std::cout.unsetf(std::ios::left);
			std::cout << std::setw(10) << BOLD << amplitudeArg.getValue() << " mV" << RESET << std::endl;
		
			std::cout.setf(std::ios::left);
			std::cout << std::setw(40) << "     Time Step: ";
			std::cout.unsetf(std::ios::left);
			std::cout << std::setw(10) << BOLD << timestep << " ms" << RESET << std::endl;
			
			std::cout.setf(std::ios::left);
			std::cout << std::setw(40) << "     Simulation Time: ";
			std::cout.unsetf(std::ios::left);
			std::cout << std::setw(10) << BOLD << max_time << " ms" << RESET << std::endl;
			
			
			//---------------------- initialize cortex -------------------------------				
			
			//seed based on time
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::default_random_engine generator(seed);
			// calculate external input frequency
			double external_input_frequency = ratioArg.getValue() * timestep * THRESHOLD_POTENTIAL/(amplitudeArg.getValue() * TAU);
			std::poisson_distribution<int> distribution(external_input_frequency);
			
			Cortex(relAmplitudeArg.getValue(), amplitudeArg.getValue(), NUMBER_OF_NEURONS, VERBOSE, timestep, distribution, generator);
		}
		
		//simulation will only run if this is true
		return launchProgram.getValue();
		
	} catch (TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::flush;
		return false;

	} catch (std::runtime_error error) {
		std::cerr << error.what() << std::flush;
		return false;
	}
}

