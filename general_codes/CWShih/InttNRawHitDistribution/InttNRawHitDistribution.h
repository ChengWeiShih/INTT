// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef INTTNRAWHITDISTRIBUTION_H
#define INTTNRAWHITDISTRIBUTION_H

#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllReturnCodes.h>

#include <phool/PHCompositeNode.h>
#include <phool/PHIODataNode.h>   // for PHIODataNode
#include <phool/PHNodeIterator.h> // for PHNodeIterator
#include <phool/PHObject.h>       // for PHObject
#include <phool/getClass.h>
#include <phool/phool.h>
#include <phool/recoConsts.h>

#include <ffarawobjects/InttRawHit.h>
#include <ffarawobjects/InttRawHitContainer.h>
#include <ffarawobjects/Gl1Packetv2.h>


#include <limits>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TH2.h>


class PHCompositeNode;
class InttRawHitContainer;
class Gl1Packet;

class TH2;
class TFile;
class TTree;

class InttNRawHitDistribution : public SubsysReco
{
 public:

  InttNRawHitDistribution(
    const std::string &name = "InttNRawHitDistribution",
    const int process_id_in = 0,
    const int runnumber_in = 0,
    const std::string output_directory_in = "output.root",
    const bool isBadChannelMask_in = true,
    const std::string hotchannel_full_directory_in = "",
    const bool ApplyHitQA_in = true,
    const bool clone_hit_remove_BCO_tag_in = true,
    const bool MBDNS_trigger_require_tag_in = true,
    const int  trigger_MBDvtxZ_cm_in = 10 // note : cm
  );

  ~InttNRawHitDistribution() override;

  /** Called during initialization.
      Typically this is where you can book histograms, and e.g.
      register them to Fun4AllServer (so they can be output to file
      using Fun4AllServer::dumpHistos() method).
   */
  int Init(PHCompositeNode *topNode) override;

  /** Called for first event when run number is known.
      Typically this is where you may want to fetch data from
      database, because you know the run number. A place
      to book histograms which have to know the run number.
   */
  int InitRun(PHCompositeNode *topNode) override;

  /** Called for each event.
      This is where you do the real work.
   */
  int process_event(PHCompositeNode *topNode) override;

  /// Clean up internals after each event.
  int ResetEvent(PHCompositeNode *topNode) override;

  /// Called at the end of each run.
  int EndRun(const int runnumber) override;

  /// Called at the end of all processing.
  int End(PHCompositeNode *topNode) override;

  /// Reset
  int Reset(PHCompositeNode * /*topNode*/) override;

  void Print(const std::string &what = "ALL") const override;

  std::string GetOutputFileName() {return output_filename;}

 private:
    struct inttHitstr{
        int hit_server;
        int hit_felix_ch;
        int hit_chip;
        int hit_channel;
        int hit_adc;
        int hit_bco;
        int hit_bco_diff;
    };

    int PrepareHotChannel();

    int process_id;
    int runnumber;
    std::string output_directory;
    bool isBadChannelMask;
    std::string hotchannel_full_directory;
    bool ApplyHitQA;
    bool clone_hit_remove_BCO_tag;
    bool MBDNS_trigger_require_tag;
    int trigger_MBDvtxZ_cm; 

    std::string output_filename;

    // note : -------------------------------- for INTTRawHit ------------------------------
    std::string m_InttRawNodeName = "INTTRAWHIT";
    InttRawHitContainer* inttcont;

    // note : -------------------------------- for output ------------------------------
    TFile * file_out;
    std::map<std::string, TH1D*> h1_nHit_map;

    // note : -------------------------------- used in the analysis ------------------------------
    long long eID_count;
    std::map<std::string, inttHitstr> evt_inttHits_map;
    std::map<std::string, int> evt_nHits_count_map;


    // note : -------------------------------- for gl1 and trigger selection ------------------------------
    Gl1Packet * p_gl1;
    std::string m_gl1NodeName = "GL1RAWHIT";

    long long live_trigger_decimal; 
    std::map<int,int>  live_trigger_map;

    long long scaled_trigger_decimal; 
    std::map<int,int>  scaled_trigger_map;
 
    void GetLiveTrigger(PHCompositeNode *topNode); 
    static std::map<int, int> prepare_trigger_vec(long long trigger_input); 


    const int MBDNS_VtxZ10cm_Id = 12;
    const int MBDNS_VtxZ30cm_Id = 13;

    // note : -------------------------------- The constant values ------------------------------
    const int nBCO = 128;
    const int nFelix = 8;
    const int Felix_offset = 3001;
    const int nFelix_channel = 14; 

    const int inner_barrel_0 = 3;
    const int inner_barrel_1 = 4;
    const int outer_barrel_0 = 5;
    const int outer_barrel_1 = 6;

    const int nLadder_inner = 12;
    const int nLadder_outer = 16;

    const int south_typeB_ZID = 1;
    const int south_typeA_ZID = 0;
    const int north_typeA_ZID = 2;
    const int north_typeB_ZID = 3;

    // note : -------------------------------- Hot channel branch ------------------------------
    TFile * hot_file_in;
    TTree * hot_tree_in;
    std::string hot_tree_name = "Multiple";
    int IID;             
    int Ichannel;        
    int Ichip;           
    int Ifelix_channel;  
    int Ifelix_server;   
    int Iflag;           

    std::map<std::string,std::string> hot_channel_map;

};

#endif // INTTNRAWHITDISTRIBUTION_H
