/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "args.h"

#include <stdlib.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace fasttext {

Args::Args() {

  loss = loss_name::ns;
  lr = 0.05;
  thread = 12;
  verbose = 2;
  seed = 0;
  minCountLabel = 0;
  dsub = 2;
  wordNgrams = 1;
  autotuneMetric = "f1";
  dim = 100;
  label = "__label__";
  model = model_name::sg;
  bucket = 2000000;
  minn = 3;
  maxn = 6;
  lrUpdateRate = 100;
  retrain = false;
  qnorm = false;
  cutoff = 0;
  autotunePredictions = 1;
  t = 1e-4;
  qout = false;
  saveOutput = false;
  pretrainedVectors = "";
  neg = 5;
  autotuneValidationFile = "";
  ws = 5;
  epoch = 5;
  minCount = 5;
  autotuneModelSize = "";
  autotuneDuration = 60 * 5; // 5 minutes
}

double Args::getAutotuneMetricValue() const {
    metric_name metric = getAutotuneMetric();
    double value = 0.0;
    if (metric == metric_name::precisionAtRecallLabel ||
        metric == metric_name::precisionAtRecall ||
        metric == metric_name::recallAtPrecisionLabel ||
        metric == metric_name::recallAtPrecision) {
        size_t firstSemicolon = 18; // semicolon position in "precisionAtRecall:"
        size_t secondSemicolon = autotuneMetric.find(":", firstSemicolon);
        const std::string valueStr =
            autotuneMetric.substr(firstSemicolon, secondSemicolon - firstSemicolon);
        value = std::stof(valueStr) / 100.0;
    }
    return value;
}


void Args::load(std::istream& in) {
    in.read((char*)&(dim), sizeof(int));
    in.read((char*)&(ws), sizeof(int));
    in.read((char*)&(epoch), sizeof(int));
    in.read((char*)&(minCount), sizeof(int));
    in.read((char*)&(neg), sizeof(int));
    in.read((char*)&(wordNgrams), sizeof(int));
    in.read((char*)&(loss), sizeof(loss_name));
    in.read((char*)&(model), sizeof(model_name));
    in.read((char*)&(bucket), sizeof(int));
    in.read((char*)&(minn), sizeof(int));
    in.read((char*)&(maxn), sizeof(int));
    in.read((char*)&(lrUpdateRate), sizeof(int));
    in.read((char*)&(t), sizeof(double));
}

void Args::save(std::ostream& out) {
    out.write((char*)&(dim), sizeof(int));
    out.write((char*)&(ws), sizeof(int));
    out.write((char*)&(epoch), sizeof(int));
    out.write((char*)&(minCount), sizeof(int));
    out.write((char*)&(neg), sizeof(int));
    out.write((char*)&(wordNgrams), sizeof(int));
    out.write((char*)&(loss), sizeof(loss_name));
    out.write((char*)&(model), sizeof(model_name));
    out.write((char*)&(bucket), sizeof(int));
    out.write((char*)&(minn), sizeof(int));
    out.write((char*)&(maxn), sizeof(int));
    out.write((char*)&(lrUpdateRate), sizeof(int));
    out.write((char*)&(t), sizeof(double));
}

std::string Args::lossToString(loss_name ln) const {
    switch (ln) {
    case loss_name::hs:
        return "hs";
    case loss_name::ns:
        return "ns";
    case loss_name::softmax:
        return "softmax";
    case loss_name::ova:
        return "one-vs-all";
    }
    return "Unknown loss!"; // should never happen
}

bool Args::isManual(const std::string& argName) const {
    return (manualArgs_.count(argName) != 0);
}

void Args::parseArgs(const std::vector<std::string>& args) {
  std::string command(args[1]);
  
  if (command == "cbow") {
    model = model_name::cbow;
  }
  for (int ai = 2; ai < args.size(); ai += 2) {

    try {
        manualArgs_.emplace(args[ai].substr(1));
      
      if (args[ai] == "-input") {
        input = std::string(args.at(ai + 1));
      }
      else if (args[ai] == "-output") {
          output = std::string(args.at(ai + 1));
      } else if (args[ai] == "-minn") {
        minn = std::stoi(args.at(ai + 1));
      } else if (args[ai] == "-maxn") {
        maxn = std::stoi(args.at(ai + 1));
      } 
    } catch (std::out_of_range) {
      std::cerr << args[ai] << " is missing an argument" << std::endl;
    
      exit(EXIT_FAILURE);
    }
  }
  if (input.empty() || output.empty()) {
    std::cerr << "Empty input or output path." << std::endl;

    exit(EXIT_FAILURE);
  }
  if (wordNgrams <= 1 && maxn == 0 && !hasAutotune()) {
    bucket = 0;
  }
}





bool Args::hasAutotune() const {
  return !autotuneValidationFile.empty();
}

metric_name Args::getAutotuneMetric() const {
    if (autotuneMetric.substr(0, 3) == "f1:") {
        return metric_name::f1scoreLabel;
    }
    else if (autotuneMetric == "f1") {
        return metric_name::f1score;
    }
    else if (autotuneMetric.substr(0, 18) == "precisionAtRecall:") {
        size_t semicolon = autotuneMetric.find(":", 18);
        if (semicolon != std::string::npos) {
            return metric_name::precisionAtRecallLabel;
        }
        return metric_name::precisionAtRecall;
    }
    else if (autotuneMetric.substr(0, 18) == "recallAtPrecision:") {
        size_t semicolon = autotuneMetric.find(":", 18);
        if (semicolon != std::string::npos) {
            return metric_name::recallAtPrecisionLabel;
        }
        return metric_name::recallAtPrecision;
    }
    throw std::runtime_error("Unknown metric : " + autotuneMetric);
}


std::string Args::getAutotuneMetricLabel() const {
    metric_name metric = getAutotuneMetric();
    std::string label;
    if (metric == metric_name::f1scoreLabel) {
        label = autotuneMetric.substr(3);
    }
    else if (
        metric == metric_name::precisionAtRecallLabel ||
        metric == metric_name::recallAtPrecisionLabel) {
        size_t semicolon = autotuneMetric.find(":", 18);
        label = autotuneMetric.substr(semicolon + 1);
    }
    else {
        return label;
    }

    if (label.empty()) {
        throw std::runtime_error("Empty metric label : " + autotuneMetric);
    }
    return label;
}






int64_t Args::getAutotuneModelSize() const {
  std::string modelSize = autotuneModelSize;
  if (modelSize.empty()) {
    return Args::kUnlimitedModelSize;
  }
  std::unordered_map<char, int> units = {
      {'k', 1000},
      {'K', 1000},
      {'m', 1000000},
      {'M', 1000000},
      {'g', 1000000000},
      {'G', 1000000000},
  };
  uint64_t multiplier = 1;
  char lastCharacter = modelSize.back();
  if (units.count(lastCharacter)) {
    multiplier = units[lastCharacter];
    modelSize = modelSize.substr(0, modelSize.size() - 1);
  }
  uint64_t size = 0;
  size_t nonNumericCharacter = 0;
  bool parseError = false;
  try {
    size = std::stol(modelSize, &nonNumericCharacter);
  } catch (std::invalid_argument&) {
    parseError = true;
  }
  if (!parseError && nonNumericCharacter != modelSize.size()) {
    parseError = true;
  }
  if (parseError) {
    throw std::invalid_argument(
        "Unable to parse model size " + autotuneModelSize);
  }

  return size * multiplier;
}

} // namespace fasttext
