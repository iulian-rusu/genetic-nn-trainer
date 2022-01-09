#define CATCH_CONFIG_MAIN

#include <array>
#include <cstdlib>
#include <numbers>
#include <catch.hpp>
#include <gnnt/mlp/activations.hpp>

TEST_CASE("Softmax function testing", "[functions]")
{
    std::array<double, 4> raw_values = {0, 1, 2, 3};
    std::array<double, 4> calculated_values = {0.03205, 0.08714, 0.23688, 0.64391};
    double eps = 0.00001;

    SECTION("Sum of softmax results array equal to 1")
    {
        auto sum = 0.0;
        gnnt::mlp::softmax softmax;
        softmax(raw_values);
        for (auto val : raw_values)
        {
            std::cout << val << std::endl;
            sum += val;
        }
        REQUIRE(sum == 1);
    }

    SECTION("Correct results of the probability distribution")
    {
        gnnt::mlp::softmax softmax;
        softmax(raw_values);
        REQUIRE(std::abs(raw_values[0] - calculated_values[0]) < eps);
        REQUIRE(std::abs(raw_values[1] - calculated_values[1]) < eps);
        REQUIRE(std::abs(raw_values[2] - calculated_values[2]) < eps);
        REQUIRE(std::abs(raw_values[3] - calculated_values[3]) < eps);
    }
}

TEST_CASE("Sigmoid function testing", "[functions]")
{
    std::array<double, 3> raw_values = {3, 20, -20};
    double calculated = 0.9525741;
    double eps = 0.0000001;

    SECTION("Result of sigmoid function with x = 3 ")
    {
        gnnt::mlp::sigmoid sigmoid;
        sigmoid(raw_values);
        REQUIRE(std::abs(raw_values[0] - calculated) < eps);
    }

    SECTION("Result of sigmoid function with x = 20 between 0 and 1 ")
    {
        gnnt::mlp::sigmoid sigmoid;
        sigmoid(raw_values);
        REQUIRE(raw_values[1] < 1);
        REQUIRE(raw_values[1] > 0);
    }

    SECTION("Result of sigmoid function with x = -20 between 0 and 1 ")
    {
        gnnt::mlp::sigmoid sigmoid;
        sigmoid(raw_values);
        REQUIRE(raw_values[2] < 1);
        REQUIRE(raw_values[2] > 0);
    }
}

TEST_CASE("PReLU function testing", "[functions]")
{
    std::array<double, 3> raw_values = {74, -17, -136};
    std::array<double, 3> calculated_values = {74, -17, -136};
    gnnt::mlp::prelu<0.2> prelu;
    prelu(calculated_values);

    SECTION("Result of PReLU function ")
    {
        for (int i = 0; i < 3; ++i)
        {
            if (raw_values[i] > 0)
            {
                REQUIRE(calculated_values[i] == raw_values[i]);
            }
            else
            {
                REQUIRE(calculated_values[i] == raw_values[i] * 0.2);
            }
        }
    }
}