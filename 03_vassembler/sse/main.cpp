#include <sse.h>
#include <string.h>
#include <math.h>

void DoNotOptimize(double value) {
    volatile double v = value;
    asm volatile("": : :"memory");
}

constexpr int N = 30000000;

static std::vector<std::vector<float>> dataset;
static std::vector<double> answers;
constexpr int index_mask = 0xfff;

static Model model;
static std::shared_ptr<OptimizedModel> optimized_model;

void BenchmarkModel() {
    for (int i = 0; i < N; ++i) {
        DoNotOptimize(ApplyModel(model, dataset[i % index_mask]));
    }
}

void BenchmarkOptimizedModel() {
    for (int i = 0; i < N; ++i) {
        auto result = ApplyOptimizedModel(*optimized_model, dataset[i % index_mask]);
        DoNotOptimize(result);

        if (i < index_mask && fabs(result - answers[i]) > 0.0001) {
            fprintf(stderr, "%lf != %lf\n", result, answers[i % index_mask]);
            abort();
        }
    }
}

int main(int argc, char* argv[]) {
    bool optimized = (argc == 2) && !strcmp(argv[1], "--sse");

    model = LoadModel("model.txt");
    dataset = LoadDataset("dataset.txt");
    for (int i = 0; dataset.size() < index_mask; ++i) {
        dataset.push_back(dataset[i]);
    }

    for (const auto& features : dataset) {
        answers.push_back(ApplyModel(model, features));
    }

    if (optimized) {
        optimized_model = Optimize(model);

        BenchmarkOptimizedModel();
    } else {
        BenchmarkModel();
    }

    return 0;
}
