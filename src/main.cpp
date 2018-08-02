#include <iostream>
#include <stdexcept>
#include "CortexInitializer.hpp"
#include "Cortex.hpp"
#include <random>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <chrono>

#define RED "\033[1m\033[31m"
#define ORANGE "\033[38;5;214m"
#define YELLOW "\033[1m\033[33m"
#define GREEN_YELLOW "\033[38;5;190m"
#define GREEN "\033[1m\033[32m"
#define BOLD "\033[1m\033[37m"
#define RESET "\033[0m"
#define ESCAPE "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
#define SPACE "                             "

// Units: ms
const int MAX_TIME(2000);
const double TIME_STEP(0.1);

int main (int argc, char** argv) {

	auto start = std::chrono::system_clock::now();
	if(initialize_cortex(argc, argv, TIME_STEP, MAX_TIME)) {
		Cortex::initialize_neurons();
	
		auto after_init = std::chrono::system_clock::now();
		auto elapsed =  std::chrono::duration_cast<std::chrono::seconds>(after_init - start);
		std::cout << "Initialization time: " << elapsed.count() << " seconds" << std::endl;
	
		// initializing of the parameters and the connections between neurons */
		try {
		
			int progress(0);
			std::cout << "Simulating : " << std::endl;
			std::cout << "[  0%] [--------------------]" << std::flush;
	
			for (int t(0); t < (MAX_TIME / TIME_STEP); ++t) {

				Cortex::update(t);

				//loading bar animation
				if (progress != ((t * 100)/(MAX_TIME / TIME_STEP - 1))) {
					progress = (t * 100)/(MAX_TIME / TIME_STEP -1 );
					std::cout << ESCAPE << std::flush;
					std::cout << SPACE << std::flush;
					std::cout << ESCAPE << std::flush;

					//color animation
					if (progress < 20){
						std::cout << RED;
					} else if (progress < 40){
						std::cout << ORANGE;
					} else if (progress < 60){
						std::cout << YELLOW;
					} else if (progress < 80){
						std::cout << GREEN_YELLOW;
					} else {
						std::cout << GREEN;
					}

					if (progress < 10) {
						std::cout << "[  " << progress << "%] [" << std::flush;
					} else if(progress < 100) {
						std::cout << "[ " << progress << "%] [" << std::flush;
					} else {
						std::cout << "[" << progress << "%] [" << std::flush;
					}
					
					for (int i(0); i < 20; ++i){
						if (i < progress/5) {
							std::cout << '=' << std::flush;
						} else {
							std::cout << '-' << std::flush;
						}
					}
					
					std::cout << ']' << std::flush;
				}

				if (progress == 100){
					std::cout << " DONE" << RESET << std::endl;
				}
			}
		
			auto end = std::chrono::system_clock::now();
			auto elapsed =  std::chrono::duration_cast<std::chrono::seconds>(end - start);
			std::cout << "Total execution time: " << elapsed.count() << " seconds" << std::endl;
		
			} 
			catch (std::runtime_error error) {
				std::cerr << error.what();
				Cortex::reset();
				return -1;
			}
	
			Cortex::reset();
		}
	return 0;
}
