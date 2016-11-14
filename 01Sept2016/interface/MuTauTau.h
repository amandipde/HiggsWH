#ifndef __MuTauTau__hh
#define __MuTauTau__hh

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include "TLorentzVector.h"
#include "TVector.h"
#include "TProfile.h"

#include "PhysicsObjects.h"
#include "AnaBase.h"

class MVASkim;

class MuTauTau : public AnaBase {
    
public:

  MuTauTau();
  virtual ~MuTauTau();
    
  void eventLoop();  // the main analysis 
  bool beginJob();
  void endJob();
  void selectEvent();

  bool readJob(const std::string& jobFile, int& nFiles);
  void printJob(std::ostream& os=std::cout) const;
  
  void clearLists();
  virtual void bookHistograms();

public:
  std::vector<vhtm::Vertex> vtxList;
  std::vector<vhtm::Muon> muoList;
  std::vector<vhtm::Electron> eleList;
  std::vector<vhtm::Tau> tauList;
  std::vector<vhtm::Jet> bjetList;

public:
  std::map<std::string, double> _evselCutMap;
  bool _createMVATree;
  std::string _mvaInputFile;

  MVASkim* _skimObj;
};
#endif
