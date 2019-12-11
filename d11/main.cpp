#include <computer/Computer.h>
#include <computer/Instructionset.h>

int main() {
    InstructionSet iss;
    iss.enable_all();
    Computer com{iss.get()};
    com.load_from_file("inputs/d11.txt");
    com.execute();
}