#ifndef __MVASkim_SigkNN__h
#define __MVASkim_SigkNN__h

#include <fstream>
#include <string>

class TTree;
class TFile;

typedef struct  
{
  float muEta;
  float muPt;
  float nJet;
} SigVariables;

class MVASkim_SigkNN {
    
public:

  MVASkim_SigkNN(const std::string& filename);
  virtual ~MVASkim_SigkNN();

  void fill(const SigVariables& varList);
  void close();

  TFile* _mvaFile;
  TTree* _tree;

  SigVariables _varList;
};
#endif
