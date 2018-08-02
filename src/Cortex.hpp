/*! \class Cortex
 *
 *  \author Neuro-1
 *
 *  \date 22.10.2016
 *
 * 	\brief The class Cortex contains a neuronal network that consists of indivuals of the class Neuron.
 * 	\details Cortex has all the neurons and organise the connections between them.
 *  \details Cortex print also the number of spike to do the graphic.
 */
#ifndef CORTEX_H
#define CORTEX_H

#include <vector>
#include <memory>
#include <fstream>
#include <random>
#include "Neuron.hpp"

#ifdef TEST
#include <gtest/gtest_prod.h>
#endif

/*! The proportion of inhibitory neurons out of total neurons */
constexpr double INHIBITORY_PROPORTION (0.2);

/*! The probability of connection between two neurons */
constexpr double CONNECTION_PROBABILITY (0.1);

/*! Number of neurons chosen randomly to be observed during the simulation */
constexpr double NUMBER_OF_CHOSEN_NEURONS(50);

class Cortex
{
	private:

        // Add Tests as friend so they can access private members
        	#ifdef TEST
		FRIEND_TEST(Cortex_Test, initialize_cortex);
		FRIEND_TEST(Cortex_Test, update);
		FRIEND_TEST(Cortex_Test, increment_spike_sum);
		FRIEND_TEST(Cortex_Test, send_spike);
		FRIEND_TEST(Cortex_Test, initialize_neuron_types);
		FRIEND_TEST(Cortex_Test, choose_50_random_neurons);
		FRIEND_TEST(Cortex_Test, save_to_file);
		FRIEND_TEST(Cortex_Test, write_spike_sum_file);
		FRIEND_TEST(Cortex_Test, reset_neurons);
       		#endif

		/*! \brief Pointers to all Neurons */
		static std::vector<Neuron*> neurons_;

		/*! \brief The total number of neurons in the Cortex */
		static unsigned int number_of_neurons_;

		/*! \brief Number of total spikes of the current time t */
		static int spike_sum_;

		/*! \brief Number of times that observed neurons have called save_to_file in the current timestep */
		static int spikes_saved_to_file_;

		/*! \brief relative amplitude of inhibitory connection vs. excitatory */
		static double relative_inhibitory_amplitude_;

		/*! \brief The amplitude of a spike from an excitatory neuron */
		static double excitatory_amplitude_;

		/*! \brief The amplitude of a spike from an inhibitory neuron */
		static double inhibitory_amplitude_;

		/*! 
		 */
		static std::default_random_engine generator_;
		
		/*! \brief generates random numbers according to the poisson distribution, by which the "background noise" is simulated.
		 */
		static std::poisson_distribution<int> distribution_; 

		/*! Write the spike sums stored in spike_sum_ into a .txt file for later usage by Matlab */
		static void write_spike_sum_file();

		/*! \brief Boolean to handle the display of comments when running tests.
		 * \details True if you want the messages to be displayed, and false if not.
		 * \details Initialised to true by default.
		 */
		static bool verbose_;
		
		/*! \brief Output file
		 *  \details Only one single output file needs to be generated.
		 * 	\details This file is an attribute of the Cortex 
		 */
		static std::ofstream outputFile;
		
	public :
	
		/*! \brief Timestep used for the simulation */
		static double timestep_;

		/*! \brief Constructor
		 * @param[in] relative_inhibitory_amplitude relative amplitude of inhibitory vs. excitatory connection, a constant entered by the user
		 * @param[in] excitatory_amplitude the amplitude of a spike of an excitatory neuron, a constant entered by the user
		 * @param[in] number_of_neurons the total number of neurons in the network, a fixed constant
		 * @param[in] verbose indicating whether the program should print any output into the terminal
		 * @param[in] time_step the time step (in ms) of the Cortex when updating its neurons
		 * @param[in] distribution the Poisson distribution that will be used to model the background activity
		 * @param[in] generator the generator used for the Poisson distribution
		 */
		Cortex(double relative_inhibitory_amplitude, double excitatory_amplitude, unsigned int number_of_neurons, bool verbose, double time_step, 
				std::poisson_distribution<int> distribution, std::default_random_engine generator);

		/*! \brief Destructor */
		~Cortex();

		/*! \brief Sends spike to other neurons.
		 * @param[in] connection_indexes list of indexes of the neurons it's connected to
		 * @param[in] amplitude amplitude of the spike
		 */
		static void send_spike(std::vector<short unsigned int> const& connection_indexes, double amplitude);

		/*! \brief Initializes the neurons of the Cortex and their connections 
		 * \details Initializes both types of Neurons, excitatory and inhibitory
		 * \details Initializes the connections of each Neuron
		 * */
		static void initialize_neurons();


		/*! \brief Reset the output files.
		 * \details All data in the output files is deleted in order to avoid having the data of several simulations in the same file.
		 */
		static void reset_output_files();

		/*! \brief Update of each neuron
		 * \details updates the sum of spikes it's receiving, updates write_spike_sum_file
		 *  @param[in] t the current time
		 */
		static void update(int t);

		/*! \brief Reset of the Cortex
		 *  \details Deletes all neurons and their connections.
		 */
		static void reset();

		/*! \brief Creates a file with the times of spikes
		 * 	@param[in] spiked a boolean to know whether the neuron spiked in this timestep or not
		 */
    		static void save_to_file(bool spiked);

		/*! \brief Sets spike_sum to nbr
		 *  \details This function is used for testing
		 * @param[in] nbr an int to set the attribute spike_sum_ to nbr for tests
		 */
		static void set_spike_sum (int nbr);

		/*! \brief Returns the value of spike_sum_
		 */
		static int get_spike_sum();

		/*! \brief Increments the value of spike_sum_  */
		static void increment_spike_sum();

	 	/*! \brief this function chooses 50 random neurons from the network.
		 *  \details These neurons are going to be observed, and their spikes tracked and plotted. */
		static void choose_50_random_neurons();
		
		/*! \brief Returns the excitatory amplitude
		 */
		static double get_excitatory_amplitude();
		
};

#endif /* Cortex_hpp */
