#pragma once

#include <memory>
#include <vector>
#include <string>

std::vector<std::vector<float>> LoadDataset(const std::string& path);

struct Rule {
    int index;
    double threshold;
    double value;
};

typedef std::vector<Rule> Model;

Model LoadModel(const std::string& path);

double ApplyModel(const Model& model, const std::vector<float>& features);

struct OptimizedModel;

std::shared_ptr<OptimizedModel> Optimize(const Model& model);

double ApplyOptimizedModel(const OptimizedModel& model, const std::vector<float>& features);
