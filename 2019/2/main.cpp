#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

const char *kTestInput1 = "1,9,10,3,2,3,11,0,99,30,40,50";
const char *kTestInput2 = "1,0,0,0,99";  // becomes 2,0,0,0,99 (1 + 1 = 2).
const char *kTestInput3 = "2,3,0,3,99";  // becomes 2,3,0,6,99 (3 * 2 = 6).
const char *kTestInput4 = "2,4,4,5,99,0";  // becomes 2,4,4,5,99,9801 (99 * 99 = 9801).
const char *kTestInput5 = "1,1,1,4,99,5,6,0,99";  // becomes 30,1,1,4,2,5,6,0,99.
const char *kThePuzzle = "1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,9,19,1,19,5,23,2,6,23,27,1,6,27,31,2,31,9,35,1,35,6,39,1,10,39,43,2,9,43,47,1,5,47,51,2,51,6,55,1,5,55,59,2,13,59,63,1,63,5,67,2,67,13,71,1,71,9,75,1,75,6,79,2,79,6,83,1,83,5,87,2,87,9,91,2,9,91,95,1,5,95,99,2,99,13,103,1,103,5,107,1,2,107,111,1,111,5,0,99,2,14,0,0";

const char *kTheInput = kThePuzzle;

using InstructionMap = map<int,int>;

int handle_instruction(int ictr, int op, InstructionMap& instructions) {
    int ret = 1;    // if in doubt, increment by one until a valid opcode is found

    int lhs = instructions[ictr + 1];
    int rhs = instructions[ictr + 2];
    int idx = instructions[ictr + 3];

    switch (op) {
    case 1:  // add
        instructions[idx] = instructions[lhs] + instructions[rhs];
        ret += 3;
        break;

    case 2:  // multiply
        instructions[idx] = instructions[lhs] * instructions[rhs];
        ret += 3;
        break;

    default:
        cerr << "unknown instruction: " << op << endl;
        break;
    }

    return ret;
}

int main() {

    stringstream ss;
    ss << kTheInput;

    InstructionMap instructions;

    string nr;
    nr.resize(100);
    size_t instruction_nr = 0;
    while (ss.getline(const_cast<char *>(nr.data()), nr.size(), ',')) {
        instructions[instruction_nr++] = atoi(nr.data());
    }

    {
        InstructionMap first_solution = instructions;

        first_solution[1] = 12;
        first_solution[2] = 2;

        size_t i = 0;
        bool eoc_found = false;
        for (i = 0; i < instruction_nr;) {
            if (first_solution[i] == 99) {
                eoc_found = true;
                break;
            }
            i += handle_instruction(i, first_solution[i], first_solution);
        }

        if (!eoc_found) {
            cerr << "no eoc found" << endl;
            return 0;
        }
        cerr << "Solution 1: " << first_solution[0] << endl;
    }

    for (int verb = 0; verb <= 99; verb++) {
        for (int noun = 0; noun <= 99; noun++) {
            InstructionMap inst_cpy = instructions;

            inst_cpy[2] = verb;
            inst_cpy[1] = noun;

            size_t i = 0;
            bool eoc_found = false;
            for (i = 0; i < instruction_nr;) {
                if (inst_cpy[i] == 99) {
                    if (19690720 == inst_cpy[0])
                        eoc_found = true;
                    break;
                }
                i += handle_instruction(i, inst_cpy[i], inst_cpy);
            }

            if (eoc_found) {
                cerr << "Solution 2: " << 100 * noun + verb << endl;
                return 0;
            }
        }
    }
    return 1;
}

