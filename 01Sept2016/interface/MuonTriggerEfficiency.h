#ifndef __MuonTriggerEfficiency__hh
#define __MuonTriggerEfficiency__hh

#include "configana.h"

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

#include "TLorentzVector.h"
#include "TVector.h"
#include "TVector3.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"

#include "PhysicsObjects.h"
#include "AnaBase.h"

class MuonTriggerEfficiency : public AnaBase {
    
public:

  MuonTriggerEfficiency();
  virtual ~MuonTriggerEfficiency();
    
  void eventLoop();  // the main analysis 
  bool beginJob();
  void endJob();

  bool readJob(const std::string& jobFile, int& nFiles);
  void printJob(std::ostream& os=std::cout) const;

  void selectEvent();
  void initializeHistograms();
  void bookHistograms();
  void bookTriggerPrescaleHistograms(std::string tname);
  void fillTriggerTPHistograms();
  void fillTriggerPrescaleHistograms(int run, int lumi); 
  void fillTriggerEfficiencies(std::map<TH1F*, TH1F*> & histo_map);
  void clearCollection();

public:
  struct TriggerHistos {
    TProfile* prescaleHist;
    TH1F*     firstMuPtAcc;
    TH1F*     secondMuPtAcc;
    TH1F*     firstMuEff;
    TH1F*     secondMuEff;
    int       eventPassed;
  };
  
  // Histograms
  std::map<std::string, TriggerHistos> _triggerHistoMap;

  TH1F* _firstMuPt; 
  TH1F* _secondMuPt; 

  TH1F* _firstElPt; 
  TH1F* _secondElPt; 

  TH1F* _invMass;
  TH1F* _invMassPass;
  TH1F* _invMassFail;
  TH1F* _invMassTrigPass;
  TH1F* _invMassTrigFail;
  TH1F* _deltaVtx;
  TH2F* _invMassVsPtPass;
  TH2F* _invMassVsPtFail;

  TH1F* _tagPt;
  TH1F* _tagPtv;
  TH1F* _tagEta;
  TH1F* _tagPhi;
  TH1F* _tagDeltaR;
  TH1F* _trigTagPt;
  TH1F* _trigTagEta;
  TH1F* _trigTagPhi;
  TH1F* _tagDeltaPt;
  TH1F* _probePt;
  TH1F* _probePtv;
  TH1F* _probeEta;
  TH1F* _probePhi;
  TH1F* _probeDeltaR;
  TH1F* _matchedProbePt;
  TH1F* _matchedProbePtv;
  TH1F* _matchedProbeEta;
  TH1F* _matchedProbePhi;
  TH1F* _probeDeltaRFail;
  TH1F* _probeTrigDeltaPtFail;
  TH1F* _probeDeltaPt;

  TH2F* _tagVsTrigPt;
  TH2F* _tagVsTrigEta;
  TH2F* _tagVsTrigPhi;
  TH2F* _tagDRVsPt;
  TH2F* _tagDRVsInvMass;
  TH2F* _probeVsTrigPt;
  TH2F* _probeVsTrigEta;
  TH2F* _probeVsTrigPhi;
  TH2F* _probeDRVsPt;
  TH2F* _probeDRVsInvMass;
  TH2F* _probeVsTagDz;
  TH2F* _probeVsTagDR;
  TH2F* _probeVsTagDRFail;
  TH2F* _probeVsTrigPtFail;
  TH2F* _probeVsTrigEtaFail;
  TH2F* _probeVsTrigPhiFail;

  TH1F* _singleTrigPt;
  TH1F* _singleTrigPtv;
  TH1F* _singleTrigEta;
  TH1F* _singleTrigPhi;

  TH1F* _multiTrigPt;
  TH1F* _multiTrigPtv;
  TH1F* _multiTrigEta;
  TH1F* _multiTrigPhi;

public:
  std::vector<std::string> _triggerPathLeg1;
  std::vector<std::string> _triggerPathLeg2;
  int _iFlagL1, _iFlagL2;
  int _iPreScaleL1, _iPreScaleL2;
  int _neventsMuTrig;  
  int _runSave, _lumiSave;
  bool _dumpEvent;

  std::vector<vhtm::Vertex> vertexVec;
  std::vector<vhtm::Muon> muonVec;
  std::vector<vhtm::Electron> electronVec;
  std::vector<vhtm::Tau> tauVec;
  std::vector<vhtm::Jet> jetVec;
  std::vector<vhtm::TriggerObject> trigObjVec;

  std::map<std::string, double> _evselCutMap;
};
#endif
