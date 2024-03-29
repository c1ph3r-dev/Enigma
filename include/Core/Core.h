#pragma once
#ifndef CORE_H_
#define CORE_H_

#include <Core/GenericInclude.h>
#include <Pair/Pair.h>
#include <Rotor/Rotor.h>

#include <string>

namespace Enigma
{
	class Core
	{
		// Member variables for Pair module and Three Rotor modules
		Pair m_PairModule;
		Rotor m_RotorF, m_RotorS, m_RotorT;

		std::string m_RotPath;

		void InternalEncrypt(char& letter); // Function to encrypt character. This contains the actual encryption logic
	public:
		Core(); // Default constructor
		Core(Core& obj); // Overloaded Copy Constructor
		Core& operator=(const Core& obj); // Overloaded Copy Assignment
		Core(Core&& obj) noexcept; // Overloaded Move Constructor
		Core& operator=(Core&& obj) noexcept;// Overloaded Move Assignment
		~Core() = default; // Destructor

		void GenNewPairModule(); // Generate Pair Module with default pairs
#ifdef ENIGMA_USE_STD_PAIR
		void GenNewPairModule(std::array<std::pair<char, char>, 13> pairs);
#else
		void GenNewPairModule(std::array<s_Pairs, 13> pairs); // Generate Pair Module with user set pairs
#endif

		inline void SetRotorDataPath(std::string path) { m_RotPath = path; }
		inline void SetNumberOfRotorModules(Enigma_64 NumberOfModules) const { Rotor::SetNumberOfModules(NumberOfModules); } // Sets number of Rotor modules that are available to choose from.
		void GenNewRotorsModules(Enigma_64 Rot1, Enigma_64 Rot2, Enigma_64 Rot3); // Generates Rotors using 3 different seed values
		void SwitchRotorModule(Enigma_Short RotModuleNo, Enigma_64 Rot); // Switches a specific rotor with a new one with a user determined seed
		void OffsetRotor(uint64_t offset); // Offsets Rotor for continued use of machine from a previous state

		std::string Encrypt(const std::string& word); // Encryption code for a string that returns a string
		void Encrypt(const std::string& word, std::string& output); // Encryption code for a string that takes a reference to a user string to write the output to

		char* Encrypt(const char* word);
	};
}

#endif
