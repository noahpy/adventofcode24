
#include "../lib/nutils.h"
#include "../lib/parseutils.h"
#include "../lib/regexutils.h"
#include <cmath>
#include <iostream>

typedef size_t Acc;

struct Computer {
    int A;
    int B;
    int C;

    int ip = 0;
    bool jumpAfter = true;
    bool firstOutput = true;
    std::vector<int> ops;

    void init(std::vector<std::string>& lines)
    {
        A = std::stoi(reutils::getMatch(lines[0], "(\\d+)").value());
        B = std::stoi(reutils::getMatch(lines[1], "(\\d+)").value());
        C = std::stoi(reutils::getMatch(lines[2], "(\\d+)").value());

        auto matches = reutils::getMatches(lines[4], "(\\d+)");

        ops.clear();
        for (auto& match : matches) {
            ops.push_back(std::stoi(match));
        }

        std::cout << "Initialized: " << A << " " << B << " " << C << " " << std::endl;
    }

    int getComboOperand(int operand)
    {
        if (operand <= 3)
            return operand;
        if (operand == 4)
            return A;
        if (operand == 5)
            return B;
        if (operand == 6)
            return C;
        else
            return 0;
    }

    void adv(int operand)
    {
        operand = getComboOperand(operand);
        A = A / pow(2, operand);
    }

    void bxl(int operand) { B = B ^ operand; }

    void bst(int operand) { B = nutils::modulo(getComboOperand(operand), 8); }

    void jnz(int operand)
    {
        if (!A)
            return;
        ip = operand;
        jumpAfter = false;
    }

    void bxc(int operand) { B = B ^ C; }

    void out(int operand)
    {
        if (firstOutput) {
            std::cout << nutils::modulo(getComboOperand(operand), 8);
            firstOutput = false;
        } else {
            std::cout << "," << nutils::modulo(getComboOperand(operand), 8);
        }
    }

    void bdv(int operand)
    {
        operand = getComboOperand(operand);
        B = A / pow(2, operand);
    }

    void cdv(int operand)
    {
        operand = getComboOperand(operand);
        C = A / pow(2, operand);
    }

    void applyOperation(int op, int operand)
    {
        std::cout << "Apply: " << op << " " << operand << std::endl;
        switch (op) {
        case 0:
            adv(operand);
            break;
        case 1:
            bxl(operand);
            break;
        case 2:
            bst(operand);
            break;
        case 3:
            jnz(operand);
            break;
        case 4:
            bxc(operand);
            break;
        case 5:
            out(operand);
            break;
        case 6:
            bdv(operand);
            break;
        case 7:
            cdv(operand);
            break;
        default:
            std::cout << "Invalid op: " << op << std::endl;
            break;
        }
        std::cout << "State : " << A << " " << B << " " << C << " " << std::endl;
        if (jumpAfter) {
            ip += 2;
        }
        jumpAfter = true;
    }

    void run()
    {
        while (ip < ops.size()) {
            applyOperation(ops[ip], ops[ip + 1]);
        }
        std::cout << std::endl;
    }
};


int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Missing positional argument: input file" << std::endl;
        return 1;
    }
    auto lines = pautils::getLineVector(argv[1]);
    Computer computer;
    computer.init(lines);
    computer.run();
}
