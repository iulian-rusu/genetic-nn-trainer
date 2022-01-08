#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <gnnt/mlp/activations.hpp>
#include <array>
#include <cstdlib>
#include  <numbers>

TEST_CASE("Softmax function testing", "[functions]") {
    std::array<double, 4> rawValues = {0,1,2,3};
    std::array<double, 4> calculatedValues = {0.03205,0.08714,0.23688,0.64391};
    double eps = 0.00001;

    SECTION("Sum of softmax results array equal to 1") {
        auto sum = 0.0;
        gnnt::mlp::softmax softmax;
        softmax(rawValues);
        for (auto val = std::begin(rawValues); val != std::end(rawValues); val++) {
            std::cout << *val << std::endl;
            sum += *val;
        }
        REQUIRE(sum == 1);
    }

    SECTION("Correct results of the probability distribution") {
        gnnt::mlp::softmax softmax;
        softmax(rawValues);
        //testing 1st element result value compared to given calculated value
        REQUIRE(std::abs(rawValues[0] - calculatedValues[0]) < eps);
        //testing 2nd element result value compared to given calculated value
        REQUIRE(std::abs(rawValues[1] - calculatedValues[1]) < eps);
        //testing 3rd element result value compared to given calculated value
        REQUIRE(std::abs(rawValues[2] - calculatedValues[2]) < eps);
        //testing 4th element result value compared to given calculated value
        REQUIRE(std::abs(rawValues[3] - calculatedValues[3]) < eps);
    }
}

TEST_CASE("Sigmoid function testing", "[functions]") {
    std::array<double, 3> rawValues = {3,20,-20};
    double calculatedValue3 = 0.9525741;
    double eps = 0.0000001;

    SECTION("Result of sigmoid function with x = 3 ") {
        gnnt::mlp::sigmoid sigmoid;
        sigmoid(rawValues);
        REQUIRE(std::abs(rawValues[0] - calculatedValue3) < eps);
    }

    SECTION("Result of sigmoid function with x = 20 between 0 and 1 ") {
        gnnt::mlp::sigmoid sigmoid;
        sigmoid(rawValues);
        REQUIRE(rawValues[1] < 1);
        REQUIRE(rawValues[1] > 0);
    }

    SECTION("Result of sigmoid function with x = -20 between 0 and 1 ") {
        gnnt::mlp::sigmoid sigmoid;
        sigmoid(rawValues);
        REQUIRE(rawValues[2] < 1);
        REQUIRE(rawValues[2] > 0);
    }
}

TEST_CASE("PReLU function testing", "[functions]") {
    std::array<double, 3> rawValues = {74, -17, -136};
    std::array<double, 3> calculatedValues =  {74, -17, -136};
    gnnt::mlp::prelu<0.2> prelu;
    prelu(calculatedValues);

    SECTION("Result of PReLU function ") {
        for (int i = 0; i < 3; i++) {
            if (rawValues[i] > 0) {
                REQUIRE(calculatedValues[i] == rawValues[i]);
            } else {
                REQUIRE(calculatedValues[i] == rawValues[i] * 0.2 );
            }
        }
    }
}