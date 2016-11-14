#ifndef __ElectronTriggerEfficiency_hh
#define __ElectronTriggerEfficiency_hh

#define NEL(x) (sizeof((x))/sizeof((x)[0]))

#include "configana.h"

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

class ElectronTriggerEfficiency : public AnaBase {
    
public:
  
  ElectronTriggerEfficiency();
  virtual ~ElectronTriggerEfficiency();
    
  void eventLoop();  // the main analysis 
  bool beginJob();
  void endJob();

  bool readJob(const std::string& jobFile, int& nFiles);
  void printJob(std::ostream& os=std::cout) const;
  
  void clearLists();
  
  virtual void selectEvent();
  virtual void bookHistograms();

  void fillTriggerFlags(bool check_prescale=false, bool verbose=false);

public:
  std::vector<vhtm::Vertex> vtxList;
  std::vector<vhtm::Muon> muoList;
  std::vector<vhtm::Electron> eleList;
  std::vector<vhtm::Tau> tauList;
  std::vector<vhtm::Jet> bjetList;
  std::vector<vhtm::TriggerObject> trigObjList;

public:
  std::map<std::string, double> _evselCutMap;
  std::vector<std::string> _tagTrigPathList;
  std::string _prbTrigPath;
  bool _dumpEvent;
  bool _matchTau;

  int _iFlagL1, _iFlagL2;
};
#endif
