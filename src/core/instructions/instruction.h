#pragma once

namespace Mikan {
	class CPU;

	/**
	 * @brief A single callable instruction
	 */
    class Instruction {
	public:
        const char* name;
		const int size;
		const int cycles;
		const int (*call)(CPU&);
		
		Instruction(const char* name, int size, int cycles, const int (*call)(CPU&)) 
			: name(name), size(size), cycles(cycles), call(call) {}
    };
}