#ifndef analysis_FCNCReco_h
#define analysis_FCNCReco_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"
#include "SampleAnalyzer/Interfaces/root/RootMainHeaders.h"

namespace MA5
{
class FCNCReco : public AnalyzerBase
{
  INIT_ANALYSIS(FCNCReco,"FCNCReco")

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private:
 TH1F* myHisto1;
 TH1F* myHisto2;
 TH1F* myHisto3;
 TH1F* myHisto4;
 TH1F* myHisto5;
 TH1F* myHisto6;
 TH1F* myHisto7;
 TH1F* myHisto8; 
};
}

#endif
