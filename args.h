/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <istream>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>

namespace fasttext {
	
enum class model_name : int { cbow = 1, sg, sup };
enum class loss_name : int { hs = 1, ns, softmax, ova };
enum class metric_name : int {
  f1score = 1,
  f1scoreLabel,
  precisionAtRecall,
  precisionAtRecallLabel,
  recallAtPrecision,
  recallAtPrecisionLabel
};

class Args {
 protected:

  
  std::unordered_set<std::string> manualArgs_;

 public:
  Args();
  std::string input;
  std::string output;
  std::string label;
  int minCountLabel;
  int autotuneDuration;
  std::string pretrainedVectors;
  int neg;
  int wordNgrams;
  loss_name loss;
  model_name model;
  int bucket;
  int minn;
  bool retrain;
  bool qnorm;
  size_t cutoff;
  int maxn;
  int verbose;
  int autotunePredictions;
  int dim;
  int ws;
  int epoch;
  int minCount;
  int lrUpdateRate;
  bool saveOutput;
  bool qout;
  double lr;
  int thread;
  int seed;
  size_t dsub;
  double t;
  std::string autotuneMetric;
  std::string autotuneValidationFile;
  bool isManual(const std::string& argName) const;
  double getAutotuneMetricValue() const;
  std::string autotuneModelSize;
  metric_name getAutotuneMetric() const;
  std::string lossToString(loss_name) const;
  void parseArgs(const std::vector<std::string>& args);
  std::string getAutotuneMetricLabel() const;
  void save(std::ostream&);
  bool hasAutotune() const;

  void load(std::istream&);


  int64_t getAutotuneModelSize() const;

  static constexpr double kUnlimitedModelSize = -1.0;
};
} // namespace fasttext
