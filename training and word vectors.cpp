#include "training and word vectors.h"
#include <iomanip>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <fstream>
#include "args.h"
#include "autotune.h"
#include "fasttext.h"
using namespace fasttext;
using namespace std;

void trainmodel() {
    vector<string> args;
    args.push_back("fasttext");
    args.push_back("cbow");
    args.push_back("-input");
    args.push_back("trainingdata.txt");
    args.push_back("-output");
    args.push_back("cbowmodel");
    args.push_back("-minn");
    args.push_back("2");
    args.push_back("-maxn");
    args.push_back("6");
    train(args);
}

void loadwordvectors() {

    vector<string> args;
    args.push_back("fasttext");
    args.push_back("print-word-vectors");
    args.push_back("cbowmodel.bin");
    printWordVectors(args);
}



void train(const vector<string> args)
{
    Args a = Args();
    a.parseArgs(args);
    std::shared_ptr<FastText> fasttext = std::make_shared<FastText>();
    std::string outputFileName;

    if (a.hasAutotune() &&
        a.getAutotuneModelSize() != Args::kUnlimitedModelSize) {
        outputFileName = a.output + ".ftz";
    }
    else {
        outputFileName = a.output + ".bin";
    }
    std::ofstream ofs(outputFileName);
    if (!ofs.is_open()) {
        throw std::invalid_argument(
            outputFileName + " cannot be opened for saving.");
    }
    ofs.close();
    if (a.hasAutotune()) {
        Autotune autotune(fasttext);
        autotune.train(a);
    }
    else {
        fasttext->train(a);
    }
    fasttext->saveModel(outputFileName);
    fasttext->saveVectors(a.output + ".vec");
    if (a.saveOutput) {
        fasttext->saveOutput(a.output + ".output");
    }
}


void printWordVectors(const std::vector<std::string> args) {
    std::ofstream f1("listofmoviewordvectors.txt");
    std::ifstream f2("movielist.txt");
    FastText fasttext;
    fasttext.loadModel(std::string(args[2]));
    std::string word;
    Vector vec(fasttext.getDimension());
    while (f2 >> word) {
        fasttext.getWordVector(vec, word);
        f1 << vec << std::endl; //word
    }

    f1.close();
    f2.close();
   
}
