#include "Neuron.hpp"
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <cmath>
#include "Cortex.hpp"

double Neuron::exponential_const;

Neuron::Neuron(double amplitude, std::vector<unsigned short int> const& connections)
	: potential_(RESTING_POTENTIAL), current_input_(0), next_input_(0), connection_indexes_(connections), 
	  amplitude_(amplitude), last_spike_(-100), is_observed_(false)
{
	assert(!connections.empty());
	exponential_const = exp(-Cortex::timestep_/(TAU));
}

Neuron::Neuron (Neuron const& neuron)
	:potential_(neuron.potential_), current_input_(neuron.current_input_), next_input_(neuron.next_input_), 
	connection_indexes_(neuron.connection_indexes_), amplitude_(neuron.amplitude_), last_spike_(neuron.last_spike_), 
	is_observed_(neuron.is_observed_)
	
{}

Neuron::~Neuron() {}

void Neuron::reset_input() {
	// new timestep is beginning --> look at spikes sent in previous time-step
	current_input_ = next_input_;
	// no spikes sent in this timestep yet.
	next_input_ = 0;
}

void Neuron::update (int t)
{
	assert(t >= 0);

	bool sent_spike(false);

	// It is time for the neuron to actually send (in the code) its spike to its connected neurons
	if (t == (last_spike_ + TRANSMISSION_DELAY - 1)) {
		// due to the management of incoming spikes using next_input and current_input 
		// (spikes sent in the previous timestep are received in the current timestep),
		// the spike won't be received until the next timestep, so we subtract the transmission delay by 1
		send_spike();
		sent_spike = true;
	}

	// Neuron is not in the refractory period
	if (t >= (last_spike_ + REFRACTORY_PERIOD)) {
		if (is_activated()) {
			// reached threshold potential in the previous timestep
			reset(t);
		} else {
			// didn't reach threshold potential --> update potential normally
			update_potential();
		}
	}
	
	// If the neuron is one of the 50 observed neurons, it will notify the Cortex whether it sent a spike or not
	notify_cortex(sent_spike);
}

void Neuron::update_potential() {
	// multiply by exp(-timestep/TAU)
	potential_ *= exponential_const; 
	// add incoming inputs (both background and cortical)
	potential_ += current_input_ ;
}

bool Neuron::is_activated () const
{
	// has reached the threshold potential
	return (potential_ >= THRESHOLD_POTENTIAL);
}

void Neuron::reset (int t)
{
	assert(t >= 0);
	potential_ = RESET_POTENTIAL;
	
	// mark the time at which the threshold potential was reached
	last_spike_ = t;
}



double Neuron::get_amplitude() const
{
	return amplitude_;
}

void Neuron::send_spike()
{
	Cortex::send_spike(connection_indexes_, amplitude_);
	// notify the cortex that a spike was sent
	Cortex::increment_spike_sum();
}

void Neuron::sum_input (double input_from_cortex)
{
	// add to input that will be treated in the next timestep
	next_input_ += input_from_cortex;
}

void Neuron::notify_cortex(bool spike_send)
{
   if(is_observed_ ) {
	   // if it is one of the observed neurons, it should notify the 
	   // cortex whether it spiked or not in this timestep
		Cortex::save_to_file(spike_send);
	}
}

bool Neuron::is_observed() const {
	return is_observed_;
}


void Neuron::set_observed(bool observe) {
	is_observed_ = observe;
}
