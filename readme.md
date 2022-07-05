# Background
The project attempts to create a communication system between three Tiva’s through
CAN protocol while complying to the AUTOSAR standardized software architecture
and level of abstraction.

# Description
The proect is comprised of three TivaC MCUs. Each one of them representing an ECU and all of them communicating via a
CAN bus. ECU 1 should send commands two the other and they respectively should perform certain tasks based on these commands.
The tasks are controlled by a state machine which represents the changing of a state based on the change of the LED color.

ECU 1 has the following functionality: 
   * Read the input switches (the on-board switches). 
   * Send a command on the CAN network based on the switch's states. 
   * SW1 controls ECU2 and SW2 controls ECU3. 
   * ECU 1 sends a message each 500 ms 

ECU 2/3 has the following functionality 
   * ECU 2/3 State machines are periodic tasks with 10ms periodicities
   * Read the commands from the CAN networks. 
   * Execute the state machine as the following: 
      - Move to the next state (clockwise) whenever the SW is pressed
      - If both are pressed. The output on both ECUs will return to default (RED)
      - Only switch states with periodicity of one second

Timing requirements for ECUs 2 and 3 can be seen below
![timing](img/timing.jpg)