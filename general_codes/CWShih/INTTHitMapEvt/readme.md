# The module for making the INTT half-ladder by half-ladder, event-by-event HitMap
* You will need to compile the module
  * you will have to do the `autogen.sh --prefix=$MYINSTALL` first.
* The module makes the hitmap based on the `INTT bco_full` you save in the `std::vector<long long> input_bcofull_vec`, and passed to the class by the member function of `int INTTHitMapEvt::SetCheckEventBCOFULLs`.
* There is one more new function if you want to just check the specific half-ladders with the given INTT_bco_full, you can use the function of `int SetCheckEventBCOFULLsHalfLadder(std::vector<std::tuple<long long, int, int>> input_bcofull_halfladder_vec);`.
  * The three variables in the `std::tuple<long long, int, int>` are `INTT_bcofull`, `FELIX (0 ~ 7)`, `FELIX channel (0 ~ 13)`.

* The module reads the `INTTRAWHIT`
* The module applies the bad channels based on the map directory you offer.
* If you have the tag of `ApplyBcoDiff_in = true`, it basically assumes that the `bco_diff` peaks of all the half-ladders are the same, which is the case for most of the run 2024 data. But may not be applicable to the data taken in run 2023.
  * If you have the tag of `ApplyBcoDiff_in = true`, it will only accept the hits with the `bco_diff` within `plus and minus 1 bco of bco_diff_peak_in`.
* You can remove the clone hits by having the `clone_hit_remove_BCO_tag_in = true`.
  * Here the definition of clone hits is, you have at least two hits with the same `FELIX ID`, `FELIX_channel_ID`, `chip_id`, `channel_id`, `hit_bco`.
* You can have the hit quality assurance by having the `ApplyHitQA_in = true`.
  * What it does is, it checks the `FELIX ID`, `FELIX_channel_ID`, `chip_id`, `channel_id`, `hit_bco` and `adc`. They should have to be within the regions we expect.
  * Such as the `hit_bco` should be `0 ~ 127`.
  * Such as the `hit adc` should be `0 ~ 7`
* If you wish to have the adc values of the hits to also be shown in the Z axis of the TH2D, you can do `setADCinZaxis_tag_in = true`.
  * The way how it works is by `TH2D_hitmap->Fill(chip_id,channel_id,hit_adc)`. In order to avoid filling the hit with zero weight due to the `hit_adc = 0`. The new feature is to have the adc converted. 
  * The vector of the adc conversion is required now.

* The module saves the 112 TH2D (the hitmaps) for each event into the root file with the name given by `std::string output_directory_in`.
  * You can use the `MakePlot.C` in the `./macro/MakePlot/` to make the pdf plots.

* The inputs
``` C++

INTTHitMapEvt(
    const std::string &name = "INTTHitMapEvt",
    const int process_id_in = 0,
    const int runnumber_in = 0,
    const std::string output_directory_in = "output.root",
    const bool isBadChannelMask_in = true,
    const std::string hotchannel_full_directory_in = "",
    const bool ApplyBcoDiff_in = true,
    const int bco_diff_peak_in = 0,
    const bool ApplyHitQA_in = true,
    const bool clone_hit_remove_BCO_tag_in = true,
    const bool setADCinZaxis_tag_in = false,
    const std::vector<int> adc_conversion_vec_in = {35, 45, 60, 90, 120, 150, 180, 210}
  );

```
