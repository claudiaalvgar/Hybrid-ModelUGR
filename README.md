# Work Essay
* LightSimulation_Hybrid.  

The main idea about the Hybrid model is doing the propagation of photons not only inside the active volume of SBND but also in the Cryostat volume that contains the active volume and that it is also made of liquid argon.  
Previously, SBND used just the semianalytic model for propagating photons inside the active volume. This model uses corrections to the geometric efficiencies and it is based on the solid angle from the energy depositions to each PMT. Because of this solid angle dependence, it is not a valid approach outside the active volume.  

The other option that we have available for propagating photons is using a library that stores visibilities, but using a library in the whole volume isn’t the most advisable method for large detectors like DUNE because of the memory required and the computing time.  

For all this reason the Hybrid model for SBND does the propagation of photons using the semianalytic model inside the active volume and it uses an Optical Library for propagating photons outside the active volume.  
Also, in order to solve memory problems with the loading of a complete library, a new scaled-down library which just stores visibilities outside the active volume was implemented -It has no visibilities stored inside the active volume and therefore it is less heavy-.  
This way, the Hybrid Nodel need to use two modules in larsim: the library module outside the active volume (PDFastSimPVS_module.cc) and the semianalytic module (PDFastSimPAR_module.cc) inside the active volume, so its implementation is trivial using the New LarG4 because of its modular structure, that’s why the modifications have been done in the New LArg4 (This implementation can be found in the Repository claudiaalvgar/larsim in the branch called Hybrid-ModelUGR with the commit "Updates for Hybrid Model").  
By using this repository you will be able to obtain a complete analysis of light simulation using the Hybrid Model.  
List of .fcl and .C needed for running the complete simulation using the New Hybrid Model for Light Simulation in SBND.  
  - prodsingle_mu_NewGeom.fcl
  - OpHybrid_g4_refactored_sbnd.fcl
  - AnalyzeEvents_module.cc
  - run_analyseEvents.fcl
  - EnergyDepositionsTest.C
  - LightYield_Hybrid_with_without_LArQL.C
  - PhotsDetected_Hybrid_with_without_LarQL.C

* MichelElectrons_GH.  

The geometric propagation of the Semianalytic Model is not model dependent but the GH correction is strongly dependent on the model, because it is based on the Montecarlo simulation and depends on parameters that we dont know exactly its values like the Rayleigh Scattering length and the SBND refelectivities, that’s why calibrating this curves with data-driven corrections is so important.
The main idea of this analysis is to obtain this correction by using real data, so ideally, we need point-like energy depositions. A possible good sample for this purpose is a Michel electron sample because electrons coming from the muon decay have a little energy range, little than 50 MeV and this sample will be almost point-like and close to the ideal case.
So as a proof of concept our choice is a low-energy electron sample with a gaussian energy distribution, similar to the Michel electrons energy distribution. And in order to reduce borders effects in the simulation we launch our sample with a position distribution in the centre of the detector, in particular we are using the positive tpc. 
With this analysis we have been able to demonstrate that:
- We are able to calibrate the Semi-Analytic Model with data-driven corrections.
- Michel electrons, in principle, allow to generate the GH corrections by using cuts proposed.
- Finally, we have done this study using PMTs but conclusions can be extrapolated to the arapucas.  

List of .fcl and .C needed for calibrating the SemiAnalytic Model (GH curves) for Light Simulation in SBND using real data (using a Michel electron-like sample).  
   - prodsingle_NewLarG4.fcl
   - standard_g4_semi_claudia.fcl
   - run_flashfinder_claudia.fcl
   - AnalyzeEvents_FlashVUV.cc
   - AnalyzeEvents_FlashVUVVIS.cc
   - run_analyseEvents_claudia.fcl
   - PMTs.txt
   - makePMTvector.C
   - MichelElectronGraphs_LiteVUV.C
   - MichelelectronGraphs_FlashVUV.C
   - MichelElectronGraphs_FlashVUVVIS.C
   - CutDistanceandPhots.C
   - StandardDeviation.C
   - Nphots-distance-profile2D.C
   - ErrorDistribution.C
   

