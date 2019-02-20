#ifndef analysis_FCNCt331_h
#define analysis_FCNCt331_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"
#include "SampleAnalyzer/Interfaces/root/RootMainHeaders.h"

namespace MA5
{
class FCNCt331 : public AnalyzerBase
{
  INIT_ANALYSIS(FCNCt331,"FCNCt331")

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private:
 TH1F* myHisto1;
 TH1F* myHisto2;
 TH1F* myHisto3;
 TH1F* myHisto4;
};
}

#endif
