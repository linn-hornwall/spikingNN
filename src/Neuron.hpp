/*! \class Neuron
 *
 *  \author Neuro-1
 * 
 *  \date 19.10.2016
 *
 *  \brief The class Neuron receives input spikes from the Cortex and sends output spikes to the Cortex.
 *
 *  \details Neuron calculates its potential depending on the inputs from the Cortex and according to the differential equation presented by the Brunel paper (2000).
 * 	\details The vector of Neurons, neurons_ (private attribut of Cortex),
 * 	\details has indexes for each Neuron contained in the network. When a Neuron fires a spike,
 *  \details the index of this Neuron is saved. The Cortex is in charge to send the spikes to the neurons the spiking Neuron is connected to.
 */

#ifndef NEURON_H
#define NEURON_H

#include <vector>
#ifdef TEST
#include <gtest/gtest.h>
#endif

class Cortex; //prédéclaration
/*! θ [V] */
constexpr double THRESHOLD_POTENTIAL (20);
/*! Vr [V] */
constexpr double RESET_POTENTIAL (10);
/*! Vr [V] */
constexpr double RESTING_POTENTIAL (0);
/*! tau = membrane resistance * capacitor [ms] */
constexpr double TAU (20.0);
/*! Refractory period [ms] */
constexpr double REFRACTORY_PERIOD(20);
/*! Transmission delay [ms] */
constexpr double TRANSMISSION_DELAY(15);

class Neuron
{
	private :
                #ifdef TEST
		FRIEND_TEST (Neuron_Test, update );
		FRIEND_TEST (Neuron_Test, sum_input);
		FRIEND_TEST (Neuron_Test, calculate_potential);
		FRIEND_TEST (Neuron_Test, reset_input); 
		FRIEND_TEST (Neuron_Test, initialize_neuron);
		FRIEND_TEST (Neuron_Test, reset);
		FRIEND_TEST (Neuron_Test, activate_neuron);
		FRIEND_TEST (Cortex_Test, update);
		FRIEND_TEST (Cortex_Test, send_spike);
		FRIEND_TEST (Cortex_Test, initialize_neuron_types);
                #endif

		/*!  \brief The potential in the neuron's membrane */
		double potential_;

		/*! The input received from the Cortex in the previous time step. */
		double current_input_;
		
		/*! The input received from the Cortex in the current time step.
		 * Won't be used until the next step. */
		double next_input_;

		/*!  \brief The indexes of the neurons this Neuron is connected to */
		std::vector<unsigned short int> connection_indexes_;

		/*!  \brief The amplitude of the spike a Neuron sends */
		double amplitude_;

		/*!  \brief The time at which the Neuron last reached the threshold potential and thus sent a spike */
		int last_spike_;
		
		/*! Constant used to update potential, = exp(-timestep/tau) where tau = membrane resistance * capacitor
		 */
		static double exponential_const;
		
		/*! Tells if this instance is a neuron that is going to be observed. */
		bool is_observed_;

		/*! \brief Whether the Neuron's potential is above the threshold potential.
		 *  \return True if the \a potential_ has reached the threshold and false if not.
		 */
		bool is_activated() const;

		/*! \brief It resets the Neuron.
		 *  \details The \a potential_ is set to the resting potential and the \a last_spike_ is set to the current time t.
		 *  @param[in] t the current time
		 */
		void reset(int t);

		/*! \brief Send a spike to the Cortex.
		 * 	\details The Cortex sends on the spike to the neurons according to the connections.
		 */
		void send_spike();
		
		/*! \brief Updates the neuron's potential 
		 * According to differential equation described in the Brunel paper.
		 */
		void update_potential() ;


	public :

		/*! \brief Constructor
		 *  \details Initializes a Neuron.
		 * 			 The connections vector should not be empty.
		 */
		Neuron(double amplitude, std::vector<unsigned short int> const& connections);

		/*! \brief Constructor of copy
		 *  \details It copies the value of \a potential_ and \a connexion_number_ but not the value of \a input_ nor \a last_spike_.
		 */
		Neuron(Neuron const& neuron);

		/*! \brief Returns the value \a amplitude_ of a given neuron */
		double get_amplitude() const;

		/*! \brief Destructor */
		~Neuron();

		/*! \brief Update of the neuron
		 * 	\details The Neuron sends a spike if the current time t equals \a last_spike_ + \a TRANSMISSION_DELAY,
		 * 			 where last_spike_ is the time at which the Neuron last reached the threshold potential.
		 * 			 If the current time is larger than  \a last_spike_ + \a REFRACTORY_PERIOD:
		 * 			 	If the Neuron reaches the threshold potential, it sets the potential to \a RESTING_POTENTIAL.
		 * 			 	If it cannot be activated, it recalculcates its potential
		 *  @param[in] t the current time
		 *  \throw invalid_argument detects an error if the time is negative.
		 */
		void update(int t);

		/*! \brief Sums the inputs from the Cortex */
		void sum_input(double input_from_cortex);

		/*! \brief Notifies Cortex when the Neuron spikes
		 * \details This is useful when a Neuron is observed
		 */
		void notify_cortex(bool spike_send);
		
		/*! \brief The Neuron sets its incoming input to that sent in the previous time step
		 * 	\details The attribute current_input is set to the value of next_input, as a new timestep is beginning.
		 * 			 next_input is set to 0.
		 */
		void reset_input();
		
		/*! \brief Getter for whether the neuron is observed */
		bool is_observed() const;
	
		/*! \brief Setter for whether the neuron is observed */
		void set_observed(bool is_observed);
};


#endif /* Neuron_hpp */
