// MUON tracking efficiency + (mother hadron):(daughter muon) kinematic relation + x_F analysis
// Author : Saehanseul Oh


#ifndef AliMuonEffMC_h
#define AliMuonEffMC_h

class TH1F;
class TH1D;
class TH2F;
class TH3F;
class THn;
class TList;
class TObjArray;
class TObject;
class AliStack;

class AliAODEvent;
class AliESDEvent;
class AliESDtrackCuts;
class AliEvtPoolManager;
class AliMCEvent;
class AliESDMuonTrack;
class AliAODTrack;
#include "AliAnalysisTaskSE.h"


class AliMuonEffMC : public AliAnalysisTaskSE {
 public:
  AliMuonEffMC();
  AliMuonEffMC(const char *name);
  virtual ~AliMuonEffMC();
 
  void         UserCreateOutputObjects();
  void         UserExec(Option_t *option);
  void         Terminate(Option_t *);
  virtual Bool_t    Notify();

  void         SetMcAna(Bool_t IsMc)               { fIsMc = IsMc;               }
  void         SetIsPYTHIA(Bool_t IsPythia)        { fIsPythia = IsPythia;       }
  void         SetMDProcess(Bool_t kMDProcess)     { fMDProcess = kMDProcess;    }
  void         SetFeynmanXProcess(Bool_t kFeynmanX){ fFeynmanX = kFeynmanX;      }
  void         SetScatFX(Bool_t kScatFX)           { fScatFX = kScatFX;          }
  void         SetZvProcess(Bool_t kZvProcess)     { fZvProcess = kZvProcess;    }
  void         SetCentEstimator(TString Cent)      { fCentralityEstimator = Cent;}
  void         SetNEtaBins(Int_t NEtaBins)         { fNEtaBins = NEtaBins;       }
  void         SetNpTBins(Int_t NpTBins)           { fNpTBins = NpTBins;         }
  void         SetNCentBins(Int_t NCentBins)       { fNCentBins = NCentBins;     }
  void         SetNZvtxBins(Int_t NZvtxBins)       { fNZvtxBins = NZvtxBins;     }
  void         SetNPhiBins(Int_t NPhiBins)         { fNPhiBins = NPhiBins;       }
  void         SetNPBins(Int_t NPBins)             { fNPBins = NPBins;           }
  void         MDProcess(Int_t motherpdg, Double_t mcpt, Double_t mcphi, Double_t mceta, Double_t trackpt, Double_t trackphi, Double_t tracketa, Double_t motherpt, Double_t motherphi, Double_t mothereta, Double_t dcavalue);
  Double_t     deltaphi(Double_t phi);
  Int_t        GetMotherBin(Int_t motherpdg);
  void         FeynmanX();
  void         ScatFX();

 protected:
  Bool_t       VertexOk(TObject* obj) const;
  Int_t       IsGoodMUONtrack(AliESDMuonTrack &track);
  Int_t       IsGoodMUONtrack(AliAODTrack &track);

 private:
  AliESDEvent *fESD;               //! ESD object
  AliAODEvent *fAOD;               //! AOD object
  AliMCEvent  *fMC;                //! MC object
  AliStack    *fStack;             //! MC stack
  Double_t     fCentrality;        //! Of current event
  Double_t     fZVertex;           //! Of current event
  TList       *fOutputList;        //! Output list
  TH1D        *fHEventStat;        //! statistics histo
  TH1F        *fHXsec;             //! sum of cross section value for hard bins
  TH1F        *fHTrials;           //! N_trial
  TH2F        *fHEvt;              //! Cent, vtx

  Bool_t       fIsMc;              //
  Bool_t       fIsPythia;          //
  Bool_t       fMDProcess;         // (mother hadron) : (daughter muon) QA
  Bool_t       fFeynmanX;          //
  Bool_t       fScatFX;            //
  Bool_t       fZvProcess;         //

  TString      fCentralityEstimator;//
  Int_t        fNEtaBins;          // number of eta bins
  Int_t        fNpTBins;           // number of p_T bins
  Int_t        fNCentBins;         // number of centrality bins
  Int_t        fNZvtxBins;         // number of Z-vertex bins
  Int_t        fNPhiBins;          // number of phi bins
  Int_t        fNPBins;            // number of P bins

  THn         *fHMuonParGen;       //! truth muon track eta, p_T, Centrality, Z-vertex, phi, charge
  THn         *fHMuonParGenSec;    //! secondary truth muon track eta, p_T, Centrality, Z-vertex, phi, charge
  THn         *fHMuonDetGen[5];    //! detector level muon track generated eta, p_T, Centrality, Z-vertex, phi, charge
  THn         *fHMuonDetRec[5];    //! reconstructed muon track eta, p_T, Centrality, Z-vertex, phi, charge
  THn         *fHHadDetRec[5];     //! particle reconstructed at MUON detector, but not muon
  THn         *fHSecDetRec[5];     //! particle reconstructed at MUON detector, but secondary muon

  TH2F        *fHCutSpecies;       //!

  THn         *fHMuonParGenP;      //! truth muon track eta, p_T, Centrality, Z-vertex, phi, charge
  THn         *fHMuonDetGenP;      //! detector level muon track generated eta, p_T, Centrality, Z-vertex, phi, charge
  THn         *fHMuonDetRecP;      //! reconstructed muon track eta, p_T, Centrality, Z-vertex, phi, charge

  TH2F        *fHMuMotherGenPt[4]; //! particle-level muon p_T vs. mother p_T
  TH2F        *fHMuMotherRecPt[4]; //! detector-level muon p_T vs. mother p_T
  TH2F        *fHMuMotherGenPhi[4];//! particle-level muon phi vs. mother phi
  TH2F        *fHMuMotherRecPhi[4];//! detector-level muon phi vs. mother phi
  TH2F        *fHMuMotherGenEta[4];//! particle-level muon eta vs. mother eta
  TH2F        *fHMuMotherRecEta[4];//! detector-level muon eta vs. mother eta
  TH1F        *fHMuDCA[4];         //! muon DCA

  TH1F        *fHMuMohterPhiDifGen[4][3]; //!
  TH1F        *fHMuMohterPhiDifRec[4][3]; //!
  TH1F        *fHMuMohterEtaDifGen[4][3]; //!
  TH1F        *fHMuMohterEtaDifRec[4][3]; //!

  TH1F        *fHFXu;              //!
  TH1F        *fHFXantiu;          //!
  TH1F        *fHFXd;              //!
  TH1F        *fHFXantid;          //!
  TH1F        *fHFXg;              //!
  TH1F        *fHFXetc;            //!
  TH1F        *fHFXmuonP[2][3];    //!
  TH1F        *fHFXmuonM[2][3];    //!

  TH1F        *fHaFx;              //!
  TH1F        *fHbFx;              //!
  TH2F        *fHabFxMu[3];        //!
  TH1F        *fHabFxRatio;        //!
  TH1F        *fHabFxRatioMu[3];   //!
  TH1F        *fHabDeltaFx;        //!
  TH1F        *fHabDeltaFxMu[3];   //!
  TH1F        *fHabRelDeltaFx;     //!
  TH1F        *fHabRelDeltaFxMu[3];//!

  TH1F        *fHMuZv[4];          //! Z-vertex of muon divided into mother species
  TH1F        *fHMuRelZv[4];       //! (Z-vertex of muon - z-vertex) divided into mother species

  AliMuonEffMC(const AliMuonEffMC&);            // not implemented
  AliMuonEffMC &operator=(const AliMuonEffMC&); // not implemented

  ClassDef(AliMuonEffMC, 8);
};

#endif
