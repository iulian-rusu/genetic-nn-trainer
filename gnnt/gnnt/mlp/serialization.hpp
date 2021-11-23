#ifndef GENETIC_NN_TRAINER_SERIALIZATION_HPP
#define GENETIC_NN_TRAINER_SERIALIZATION_HPP

#include <fstream>

namespace gnnt::mlp
{
    template<typename R>
    static void write_range(std::ostream &os, R const &range)
    {
        std::streamsize sz = sizeof(range[0]) * range.size();
        os.write(reinterpret_cast<const char *>(&range[0]), sz);
    }

    template<typename R>
    static void read_range(std::istream &is, R &range)
    {
        std::streamsize sz = sizeof(range[0]) * range.size();
        is.read(reinterpret_cast<char *>(&range[0]), sz);
    }
}
#endif //GENETIC_NN_TRAINER_SERIALIZATION_HPP
