#include <vector>
#include <stdexcept>
#include <iostream>
#include <chrono>

#include <gtest/gtest.h>
#include "../src/Cortex.hpp"
#include "../src/Neuron.hpp"

double excitatory_amplitude (0.1);
double relative_inhibitory_amplitude (5.0);
unsigned int number_of_neurons (100);
double external_input_frequency (2);
double time_step(0.1);
bool verbose(false);

// Test constants
TEST (Main_Test, constants) {
	// Neuron constants
	EXPECT_EQ(20, THRESHOLD_POTENTIAL);
	EXPECT_EQ(10, RESET_POTENTIAL);
	EXPECT_EQ(0, RESTING_POTENTIAL);
	EXPECT_EQ(20.0, TAU);
	EXPECT_EQ(20, REFRACTORY_PERIOD);
	EXPECT_EQ(15, TRANSMISSION_DELAY);
	
	// Cortex constants
	EXPECT_EQ(0.2, INHIBITORY_PROPORTION);
	EXPECT_EQ(0.1, CONNECTION_PROBABILITY);
}


// ------------------------ Cortex Tests--------------------------------

// Test Cortex constructor
TEST(Cortex_Test, initialize_cortex) {
	
	// Test initialization of the fields in Cortexs
	EXPECT_EQ(excitatory_amplitude, Cortex::excitatory_amplitude_);
	EXPECT_EQ(relative_inhibitory_amplitude, Cortex::relative_inhibitory_amplitude_);
	EXPECT_EQ(verbose, Cortex::verbose_);
	EXPECT_EQ(number_of_neurons, Cortex::number_of_neurons_);
	EXPECT_EQ(time_step, Cortex::timestep_);
	
	// Test calculation of inhibitory amplitude
	double inhibitory_amplitude(- Cortex::relative_inhibitory_amplitude_ * Cortex::excitatory_amplitude_);
	EXPECT_EQ(inhibitory_amplitude, Cortex::inhibitory_amplitude_);
}


// Test Cortex::update
TEST(Cortex_Test, update) {
	Cortex::update(1);
	for(size_t i(0); i < Cortex::number_of_neurons_; ++i) {
		// verify that each neuron receives a positive input
		EXPECT_LE(0.0, Cortex::neurons_[i]->current_input_);
	}
}

// Test Cortex::increment_spike_sum()
TEST(Cortex_Test, increment_spike_sum) {
	double spike_sum(2);
	Cortex::set_spike_sum (spike_sum);
	EXPECT_EQ(spike_sum, Cortex::get_spike_sum());
	Cortex::increment_spike_sum();
	EXPECT_EQ(++spike_sum, Cortex::get_spike_sum());
}

// Test Cortex::send_spike
TEST(Cortex_Test, send_spike) {
	short unsigned int index1(0), index2(15), index3(30), index4(45), index5(50), index6(70), index7(99);
	std::vector<short unsigned int> vector = { index1, index2, index3, index4, index5, index6, index7};
	
	// take the excitator amplitude of the Cortex
	double exc_amplitude = Cortex::excitatory_amplitude_;
	
	Cortex::send_spike(vector, exc_amplitude);
	
	// Make sure each neuron receives the input
	EXPECT_EQ(exc_amplitude, Cortex::neurons_[index1]->next_input_);
	EXPECT_EQ(exc_amplitude, Cortex::neurons_[index2]->next_input_);
	EXPECT_EQ(exc_amplitude, Cortex::neurons_[index3]->next_input_);
	EXPECT_EQ(exc_amplitude, Cortex::neurons_[index4]->next_input_);
	EXPECT_EQ(exc_amplitude, Cortex::neurons_[index5]->next_input_);
	EXPECT_EQ(exc_amplitude, Cortex::neurons_[index6]->next_input_);
	EXPECT_EQ(exc_amplitude, Cortex::neurons_[index7]->next_input_);
}
	
// Test Cortex::initialize_neurons	
TEST(Cortex_Test, initialize_neuron_types) {
	EXPECT_EQ(Cortex::number_of_neurons_, Cortex::neurons_.size());
	
	// Test that the amplitude was initialized correctly
	
	unsigned int inhib_number (Cortex::number_of_neurons_ * INHIBITORY_PROPORTION);
	// Assuming inhibitory neurons are first in the set of neurons
	for(size_t index(0); index < inhib_number; ++index) {
		EXPECT_EQ(Cortex::inhibitory_amplitude_, Cortex::neurons_[index]->amplitude_);
	}
	
	for(size_t index(inhib_number); index < Cortex::number_of_neurons_; ++index) {
		EXPECT_EQ(Cortex::excitatory_amplitude_, Cortex::neurons_[index]->amplitude_);
	}
	
}

// Test Cortex::choose_50_random_neurons	
TEST(Cortex_Test, choose_50_random_neurons) {
	int nbr(0);
	
	std::vector<Neuron*> neurons (Cortex::neurons_);
	for(Neuron* neuron: neurons) {
		if(neuron->is_observed()) {
			++nbr;
		}
	}
	
	// Test that we choose exactly 50 neurons
	EXPECT_EQ(NUMBER_OF_CHOSEN_NEURONS, nbr);
}

// Test Cortex::save_to_file
TEST(Cortex_Test, save_to_file){
	// Test that save_to_file doesn't throw anything
	EXPECT_NO_THROW(Cortex::save_to_file(false));
	EXPECT_NO_THROW(Cortex::save_to_file(true));
}

// Test Cortex::write_spike_sum_file
TEST(Cortex_Test, write_spike_sum_file) {
	// Test that write_spike_sum_file doesn't throw anything
	Cortex::set_spike_sum (123);
	EXPECT_NO_THROW(Cortex::write_spike_sum_file());
	
	// Test that spike_sum is 0 after calling write_spike_sum_file
	EXPECT_EQ(0, Cortex::get_spike_sum());
}

// Test Cortex::reset
TEST(Cortex_Test, reset_neurons) {
	Cortex::reset();
	EXPECT_EQ(0, Cortex::neurons_.size());
}


// ------------------------ Neuron Tests--------------------------------

// Test Neuron constructor
TEST(Neuron_Test, initialize_neuron) {
	std::vector<short unsigned int> tab = {2, 10};
	Neuron neuron (Cortex::get_excitatory_amplitude(), tab);
	EXPECT_EQ(tab, neuron.connection_indexes_);
	EXPECT_DOUBLE_EQ(exp(-Cortex::timestep_/TAU), neuron.exponential_const);
}

// Test Neuron::is_activated
TEST(Neuron_Test, activate_neuron) {
	std::vector<short unsigned int> tab = {2, 10};
	Neuron neuron(Cortex::get_excitatory_amplitude(), tab);
	
	// Test that the neuron will spike correctly
	neuron.potential_ = 20.0;
	EXPECT_EQ(neuron.potential_, THRESHOLD_POTENTIAL);
	EXPECT_TRUE(neuron.is_activated());
	
	neuron.potential_ = 19.9999;
	EXPECT_LT(neuron.potential_, THRESHOLD_POTENTIAL);
	EXPECT_FALSE(neuron.is_activated());
	
	neuron.potential_ = -1000.0;
	EXPECT_LT(neuron.potential_, THRESHOLD_POTENTIAL);
	EXPECT_FALSE(neuron.is_activated());
	
	neuron.potential_ = 1000.0;
	EXPECT_GT (neuron.potential_, THRESHOLD_POTENTIAL);
	EXPECT_TRUE (neuron.is_activated());
}

// Test Neuron::reset
TEST(Neuron_Test, reset) {
	std::vector<short unsigned int> tab = {2, 10};
	Neuron neuron(Cortex::get_excitatory_amplitude(), tab);
	
	// Test that potential and last_spike are updated
	neuron.reset(0);
	EXPECT_EQ (RESET_POTENTIAL, neuron.potential_);
	EXPECT_EQ (0, neuron.last_spike_);

	neuron.potential_ = 1000.0;
	constexpr int TIME(100);
	neuron.reset (TIME);
	EXPECT_EQ (RESET_POTENTIAL, neuron.potential_);
	EXPECT_EQ (TIME, neuron.last_spike_);
}

// Test Neuron::update_potential
TEST(Neuron_Test, calculate_potential) {	
	std::vector<short unsigned int> tab = {2, 10};
	Neuron neuron(Cortex::get_excitatory_amplitude(), tab);
	
	constexpr double PRECISION(0.0001);
	
	// Test the potential exactitude
	neuron.current_input_ = 0.0;
	neuron.potential_ = THRESHOLD_POTENTIAL;
	neuron.update_potential();
	double expected_value (THRESHOLD_POTENTIAL * neuron.exponential_const);
	EXPECT_NEAR(expected_value, neuron.potential_, PRECISION);
	
	constexpr double POTENTIAL_1(40.0);
	neuron.current_input_ = 0.0;
	neuron.potential_ = POTENTIAL_1;
	neuron.update_potential();
	expected_value = POTENTIAL_1 * neuron.exponential_const;
	EXPECT_NEAR(expected_value, neuron.potential_, PRECISION);
	
	// Test that potential is higher or lower depending on the input 
	constexpr double POTENTIAL_2(10.0);
	neuron.current_input_ = -0.5;
	neuron.potential_ = POTENTIAL_2;
	neuron.update_potential();
	EXPECT_GT (POTENTIAL_2, neuron.potential_);
	
	neuron.current_input_ = 0.5;
	neuron.potential_ = POTENTIAL_2;
	neuron.update_potential();
	EXPECT_LT (POTENTIAL_2, neuron.potential_);
	
} 

// Test Neuron::sum_input
TEST(Neuron_Test, sum_input) {
	std::vector<short unsigned int> tab = {2, 10};
	Neuron neuron(Cortex::get_excitatory_amplitude(), tab);
	constexpr double PRECISION(1.0e-14);
	
	// Test that sum_input works correctly
	constexpr double INPUT_1(0.0);
	neuron.sum_input(INPUT_1);
	EXPECT_NEAR (INPUT_1, neuron.next_input_, PRECISION);
	
	constexpr double INPUT_2(100.0);
	neuron.sum_input(INPUT_2);
	EXPECT_NEAR (INPUT_1 + INPUT_2, neuron.next_input_, PRECISION);
	
	constexpr double INPUT_3(-12.4567);
	neuron.sum_input (INPUT_3);
	EXPECT_NEAR  (INPUT_1 + INPUT_2 + INPUT_3, neuron.next_input_, PRECISION);
	
	constexpr double INPUT_4(-100.0);
	neuron.sum_input (INPUT_4);
	EXPECT_NEAR  (INPUT_1 + INPUT_2 + INPUT_3 + INPUT_4, neuron.next_input_, PRECISION);
	
}

// Test Neuron::update
TEST(Neuron_Test, update) {
	std::vector<short unsigned int> tab = {2, 10};
	Neuron neuron(Cortex::get_excitatory_amplitude(), tab);
	
	// Test that the neuron spikes
	neuron.potential_ = THRESHOLD_POTENTIAL;
	neuron.current_input_ = 1;	
	
	constexpr int TIME(1000);												
	neuron.update(TIME);
	EXPECT_EQ(TIME, neuron.last_spike_);
}


// Test Neuron::reset_input
TEST(Neuron_Test, reset_input) {
	std::vector<short unsigned int> tab = {2, 10};
	Neuron neuron (Cortex::get_excitatory_amplitude(), tab);
	
	constexpr double NEXT_INPUT(10);
	constexpr double CURRENT_INPUT(20);
	
	neuron.next_input_ = NEXT_INPUT;
	neuron.current_input_ = CURRENT_INPUT;
	
	neuron.reset_input();
	EXPECT_EQ(NEXT_INPUT, neuron.current_input_);
	EXPECT_EQ(0, neuron.next_input_);
	
	neuron.reset_input();
	EXPECT_EQ(neuron.next_input_, neuron.current_input_);
}

int main(int argc, char **argv) { 
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::poisson_distribution<int> distribution(external_input_frequency);
	
	Cortex(relative_inhibitory_amplitude, excitatory_amplitude, number_of_neurons, verbose, time_step, distribution, generator);
	Cortex::initialize_neurons();
	
	::testing::InitGoogleTest(&argc, argv); 
	return RUN_ALL_TESTS();
}

