#ifndef __FakeRate__HH
#define __FakeRate__HH

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

using namespace vhtm;

class MVASkim_SigkNN; // forward declaration
class MVASkim_BkgkNN; // forward declaration
namespace TMVA {
  class Reader;
}


class FakeRate : public AnaBase {
    
public:

  FakeRate();
  virtual ~FakeRate();
    
  void eventLoop();  // the main analysis 
  bool beginJob();
  void endJob();
  void selectEvent();

  bool readJob(const std::string& jobFile, int& nFiles);
  void printJob(std::ostream& os=std::cout) const;
  
  void clearLists();

  virtual void bookHistograms();
  void JetToFakeDYJets();
  void JetToTauFakeWJets();
  void selectTau();
  void selectTightMuon();
  void selectTightElectron();
  void selectLooseMuon();
  void ApplyFR();
  void MuMuTauApplyFR();
  void investigateFake();
  void MuMuTauFakeWJets();
  void MuMuTauFakeQCD();
  void MuMuTauFakeZJets();
  void EleMuTauFakeWJets();
  void EleMuTauFakeZJets();
  void skimForKNN(const Muon& probeMuon, const bool& probeTID, const float& nJet);

public:

  std::vector<vhtm::Vertex> vtxList;
  std::vector<vhtm::Muon> muoList;
  std::vector<vhtm::Electron> eleList;
  std::vector<vhtm::Tau> tauList;
  std::vector<vhtm::Jet> bjetList;
  std::vector<vhtm::Tau> selectTauList;
  std::vector<vhtm::Muon> selectTightMuonList;
  std::vector<vhtm::Muon> selectLooseMuonList;
  std::vector<vhtm::Electron> selectTightElectronList;

public:
  std::map<std::string, double> _tau1CutMap;
  std::map<std::string, double> _tau2CutMap;
  bool _createMVATree;
  bool _readMVA;
  bool _readMVAFK;
  std::string _mvaInputFileSigkNN;
  std::string _mvaInputFileBkgkNN;
  std::string _MVAdisFile;
  std::string _MVAFKdisFile;
  float vz;

  // MVA input variables while reading
  float muEta;
  float muPt;
  float tau1Eta;
  float tau1Pt;
  float tau2Eta;
  float tau2Pt;
  float diTaudR;
  float dphiMuTau1;
  float dphiMuDiTau;
  float met;
  float ptRatio;
  
  // for fake mva
  float leadPt;
  float subPt;
  float deltaRDiTau;

  MVASkim_SigkNN* _skimSig;
  MVASkim_BkgkNN* _skimBkg;

  TMVA::Reader* reader;
  TMVA::Reader* reader1;
};
#endif
