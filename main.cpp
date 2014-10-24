#include <iostream>
#include <vector>
#include <iomanip>

using std::cout;
using std::setw;
using std::vector;
using namespace std::chrono;


#define DUPLICATION(x) x x
#define MIN_SHIFT 10
#define MAX_SHIFT 28
#define NUMBER_OF_TESTS 16
#define NUMBER_OF_TESTS_IN_ONE_ITERATION 16
#define NUMBER_OF_STEPS 256
#define COUNT_OF_OUTPUT_CHARACTERS 10

template <size_t N>
struct el {
    el *next;
    long payload[N];
    el(): next(nullptr) { }
};

template <size_t N>
void create_linear_sequence(vector<el<N>> &elements);

template <size_t N>
void create_random_sequence(vector<el<N>> &elements);

template <size_t N>
double test_cache(el<N> *element);

template <size_t N>
void test();


int main(int argc, char** argv) {
    srand((unsigned int) time(NULL));

    test<31>();
    return 0;
}

template <size_t N>
void create_linear_sequence(vector<el<N>> &elements) {
    for(int i = 0; i < elements.size() - 1; i++) {
        elements[i].next = &elements[i + 1];
    }
    elements[elements.size() - 1].next = &elements[0];
}

template <size_t N>
void create_random_sequence(vector<el<N>> &elements) {
    for(int i = 0; i < elements.size(); i++) {
        elements[i].next = &elements[rand() % (elements.size() - 1)];
    }
}

template <size_t N>
double test_cache(el<N> *first_element) {
    auto element = first_element;
    long t_start = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
    for (int i = 0; i < NUMBER_OF_TESTS_IN_ONE_ITERATION; i++) {
        DUPLICATION(
                DUPLICATION(
                        DUPLICATION(
                                DUPLICATION(
                                        DUPLICATION(
                                                DUPLICATION(
                                                        DUPLICATION(
                                                                DUPLICATION(
                                element = element->next;
        ))))))))
    }
    long t_stop = duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
    double duration = double(t_stop - t_start) / (NUMBER_OF_STEPS * NUMBER_OF_TESTS_IN_ONE_ITERATION);
    return duration;
}

template <size_t N>
void test() {
    for (unsigned i = MIN_SHIFT; i <= MAX_SHIFT; i++) {
        size_t el_size = sizeof(el<N>);
        unsigned long array_size = ((unsigned long) 1 << i) / el_size;
        vector<el<N>> elements(array_size);
        double linear_sum_time = 0;
        double random_sum_time = 0;

        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            create_linear_sequence(elements);
            linear_sum_time += test_cache(&elements[0]);
        }
        //
        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            create_random_sequence(elements);
            random_sum_time += test_cache(&elements[0]);
        }
        cout << setw(COUNT_OF_OUTPUT_CHARACTERS) << i;
        cout << setw(COUNT_OF_OUTPUT_CHARACTERS) << linear_sum_time / double(NUMBER_OF_TESTS);
        cout << setw(COUNT_OF_OUTPUT_CHARACTERS) << random_sum_time / double(NUMBER_OF_TESTS);
        cout << std::endl;
    }
}