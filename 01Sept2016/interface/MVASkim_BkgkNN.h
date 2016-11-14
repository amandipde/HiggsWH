#ifndef __MVASkim_BkgkNN__h
#define __MVASkim_BkgkNN__h

#include <fstream>
#include <string>

class TTree;
class TFile;

typedef struct  
{
  float muEta;
  float muPt;
  float nJet;
} BkgVariables;

class MVASkim_BkgkNN {
    
public:

  MVASkim_BkgkNN(const std::string& filename);
  virtual ~MVASkim_BkgkNN();

  void fill(const BkgVariables& varList);
  void close();

  TFile* _mvaFile;
  TTree* _tree;

  BkgVariables _varList;
};
#endif
