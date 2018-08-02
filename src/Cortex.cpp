#include "Cortex.hpp"
#include <vector>
#include <iostream>
#include <cassert>
#include <fstream>
#include <stdexcept>
#include <random>
#include <chrono>

// various strings used for terminal animations
#define BOLD "\033[1m\033[37m"
#define RESET "\033[0m"
#define ESCAPE "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
#define SPACE "                               "

#define SPIKE_SUM_FILE "sum_spikes.txt"
#define SPIKE_DETAIL_FILE "spikes.txt"

std::vector<Neuron*> Cortex::neurons_;
int Cortex::spike_sum_;
int Cortex::spikes_saved_to_file_;
double Cortex::relative_inhibitory_amplitude_;
double Cortex::excitatory_amplitude_;
double Cortex::inhibitory_amplitude_;
unsigned int Cortex::number_of_neurons_ (12500);
std::ofstream Cortex::outputFile;
std::default_random_engine Cortex::generator_;
std::poisson_distribution<int> Cortex::distribution_; 
bool Cortex::verbose_(true);
double Cortex::timestep_;

Cortex::Cortex(double relative_inhibitory_amplitude, double excitatory_amplitude, unsigned int number_of_neurons, 
				bool verbose, double time_step, std::poisson_distribution<int> distribution, std::default_random_engine generator)
{
	relative_inhibitory_amplitude_ = relative_inhibitory_amplitude;
	excitatory_amplitude_ = excitatory_amplitude;
	verbose_ = verbose;
	inhibitory_amplitude_ = (- relative_inhibitory_amplitude * excitatory_amplitude);
	number_of_neurons_ = number_of_neurons;
	spike_sum_ = 0;
	timestep_ = time_step;
	distribution_ = distribution;
	generator_ = generator;
	
	// empty existing output files
	reset_output_files();
}

void Cortex::update(int t)
{	
	for (auto& neuron : neurons_) {
		// add background input to the incoming spikes of the neuron
		neuron->sum_input(excitatory_amplitude_ * distribution_(generator_));
		// neuron knows it's a new time step, knows to receive spikes sent in the previous timestep
		neuron->reset_input();
    }
    
    for (auto& neuron : neurons_) {
		neuron->update(t);
    }
	
	// write the sum of spikes (from our 12500 neurons) in this timestep into a file
	write_spike_sum_file();
}

void Cortex::increment_spike_sum() {
	++spike_sum_;
}

void Cortex::send_spike(std::vector<short unsigned int> const& connection_indexes, double amplitude)
{
	// sends a spike to all neurons with indexes inside connection_indexes
	for (auto const index : connection_indexes) {
		neurons_[index]->sum_input(amplitude);
	}
}

void Cortex::initialize_neurons()
{
	// Check that the amplitudes have been initialized correctly
	assert(inhibitory_amplitude_ <= 0.0);
	assert(excitatory_amplitude_ >= 0.0);


	// First initializes the inhibitory neurons then the excitatory,
	// creating their lists of connections at the same time

	std::vector<short unsigned int> connection_indexes;
	// select indices with a certain connection probability
	std::default_random_engine generator;
	std::bernoulli_distribution distribution(CONNECTION_PROBABILITY);

	// ---------- initialize inhibitory neurons -----------

	if(verbose_) {
		std::cout << "Generating inhibitory neurons..."<<std::flush;
	}
	
	// number of inhibitory neurons
	int inhibitory_amount(number_of_neurons_ * INHIBITORY_PROPORTION);
	
	for (short unsigned int i(0); i < inhibitory_amount; ++i) {

		for (short unsigned int j(0); j < number_of_neurons_ ; ++j) {

			if (distribution(generator) and (j != i)) { // can't have connection to itself
				// add connection to other neuron with a certain probability
				connection_indexes.push_back(j);
			}
		}

		neurons_.push_back(new Neuron(inhibitory_amplitude_, connection_indexes));

		connection_indexes.clear();
	}
	
	
	// console animation
	if(verbose_) {
		std::cout << BOLD << "  COMPLETE" << RESET << std::endl;
		std::cout << "Generating excitatory neurons..." << std::flush;
	}


	//------------ initialize excitatory neurons --------------

	// number of excitatory neurons
    double excitatory_amount(number_of_neurons_ * (1.0 - INHIBITORY_PROPORTION));

	for (short unsigned int i(0) ; i < excitatory_amount ; ++i) {

		for(short unsigned int j(0); j < number_of_neurons_ ; ++j) {

			if (distribution(generator) and (j != i)) { // can't have connection to itself
				connection_indexes.push_back(j);
			}
		}

		neurons_.push_back(new Neuron(excitatory_amplitude_, connection_indexes));

		connection_indexes.clear();
		
	}

	// terminal animation
	if(verbose_) {
		std::cout << BOLD << "  COMPLETE" << RESET << std::endl;
	}
	
	// choose 50 random neurons to track
	Cortex::choose_50_random_neurons();
}

void Cortex::reset()
{
	// delete neurons
	for (auto& neuron : neurons_) {
		delete neuron;
		neuron = nullptr;
	}
	neurons_.clear();
}

void Cortex::write_spike_sum_file ()
{
    std::ofstream output_file(SPIKE_SUM_FILE, std::ofstream::out | std::ofstream::app);

    if (output_file.fail()) {
		// circumvent issue when using SPIKE_SUM_FILE in the error constructor
		std::string file_name(SPIKE_SUM_FILE);
        throw std::runtime_error("file " + file_name + " couldn't be opened");
    } else {
			output_file << spike_sum_ << std::endl;
    }
    output_file.close();
    
    // reset sum of spikes in current time step
    spike_sum_ = 0;
}

void Cortex::save_to_file(bool spiked)
{
	std::ofstream output_file(SPIKE_DETAIL_FILE, std::ofstream::out | std::ofstream::app);

    if (output_file.fail()) {
		// circumvent issue when using SPIKE_SUM_FILE in the error constructor
		std::string file_name(SPIKE_DETAIL_FILE);
        throw std::runtime_error("file " + file_name + " couldn't be opened");

    } else if (spiked) {
		// the neuron spiked --> write 1
		output_file << "1 ";
    } else {
		// the neuron didn't spike --> write 0
		output_file << "0 ";
    }
    ++spikes_saved_to_file_;

    if (spikes_saved_to_file_ >= 50) {
		// the spikes from this time step have been written into the file
		output_file << std::endl;
		spikes_saved_to_file_ = 0;
	}

    output_file.close();
}

void Cortex::reset_output_files()
{
	// erase the content of the two output files
	
	std::ofstream overwrite_sums;
	overwrite_sums.open(SPIKE_SUM_FILE);
	overwrite_sums << "";
	overwrite_sums.close();

	std::ofstream overwrite_spike;
	overwrite_spike.open(SPIKE_DETAIL_FILE);
	overwrite_spike << "";
	overwrite_spike.close();
}

void Cortex::choose_50_random_neurons() {
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	
	std::uniform_int_distribution<> distribution(0, number_of_neurons_ - 1);
	spikes_saved_to_file_ = 0;
	int n(0);
	int index;
	
	// choose 50 random neurons and let them know they are observed
	do{
		index = distribution(generator);
		if (!neurons_[index]->is_observed()){
				neurons_[index]->set_observed(true);
				++n;
		}

	} while (n < NUMBER_OF_CHOSEN_NEURONS);
}

void Cortex::set_spike_sum (int nbr)
{
	spike_sum_ = nbr;
}

int Cortex::get_spike_sum()
{
	return spike_sum_;
}

Cortex::~Cortex()
{
	reset();
}

double Cortex::get_excitatory_amplitude(){
	return excitatory_amplitude_;
}
