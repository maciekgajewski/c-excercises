#include <iostream>
#include <cstdlib>
#include <cmath>

const int MAX_DEPTH = 10000;

struct NewtonMetadata {
        unsigned int recursionDepth = 0;
        unsigned long firstStackTop = 0;
        unsigned long lastStackTop = 0;
};

float newtonSqrtStep(float input, float oldApproximation, struct NewtonMetadata& metadata)
{
        metadata.recursionDepth++;
        if (metadata.recursionDepth >= MAX_DEPTH)
        {
                return oldApproximation;
        }
        auto newApproximation = oldApproximation - ((oldApproximation * oldApproximation - input) / (2 * oldApproximation));
        if (metadata.firstStackTop == 0) {
                metadata.firstStackTop = reinterpret_cast<unsigned long>(&newApproximation);
        }
        metadata.lastStackTop = reinterpret_cast<unsigned long>(&newApproximation);
        if (newApproximation == oldApproximation) {
                return newApproximation;
        } else {
                return newtonSqrtStep(input, newApproximation, metadata);
        }
}

float newtonSqrt(float input, struct NewtonMetadata& metadata)
{
        return newtonSqrtStep(input, input, metadata);
}

int main(int argc, char** argv)
{
        for (auto i = 1; i < argc; i++)
        {
                auto input = std::atof(argv[i]);
                struct NewtonMetadata metadata;
                float newtonResult = newtonSqrt(input, metadata);
                std::cout << "newtonSqrt(" << argv[i] << ")=" << newtonResult << "; recursion depth: " <<
                        metadata.recursionDepth << "; stack growth between first and last recursion: " <<
                        metadata.firstStackTop - metadata.lastStackTop << std::endl;
        }
}
