# Work Essay. 

Little introduction and programs used.  

***File_Task 1: LightSimulation_Hybrid.***  

The main idea about the Hybrid Model is doing the propagation of photons not only inside the active volume of SBND but also in the Cryostat volume that contains the active volume and that it is also made of liquid argon.  
Previously, SBND used just the semianalytic model for propagating photons inside the active volume. This model uses corrections to the geometric efficiencies and it is based on the solid angle from the energy depositions to each PMT. Because of this solid angle dependence, it is not a valid approach outside the active volume.  

The other option that we have available for propagating photons is using a library that stores visibilities, but using a library in the whole volume isn’t the most advisable method for large detectors like DUNE because of the memory required and the computing time.  

For all this reason the Hybrid model for SBND does the propagation of photons using the semianalytic model inside the active volume and it uses an Optical Library for propagating photons just outside the active volume.  
Also, in order to solve memory problems with the loading of a complete library, a new scaled-down library which just stores visibilities outside the active volume was implemented -It has no visibilities stored inside the active volume and therefore it is less heavy-.  
This way, the Hybrid Model need to use two modules in larsim: the library module outside the active volume (PDFastSimPVS_module.cc) and the semianalytic module (PDFastSimPAR_module.cc) inside the active volume, so its implementation is trivial using the New LarG4 because of its modular structure, that’s why the modifications have been done in the New LArg4 (This implementation can be found in the Repository claudiaalvgar/larsim in the branch called Hybrid-ModelUGR with the commit "Updates for Hybrid Model" and the fcls required in sbndcode can be found in claudiaalvgar/sbndcode in the branch called Hybrid-ModelUGR with the commit "Hybrid Model"). 
Inside the active volume the electric field in SBND is 0.5 kV/cm but:  

Warning!: Although the electric is variable on the top and bottom side of the cryostat if we represent the visibilities of the library, the visibilities on the top and bottom side are almost negligible, so including the variable electric field will add little change to the Hybrid Model. Behind PMTs the electric field is zero and in the rest of the cryostat visibilities are negligible, so as first approach using an electric field of 0 in all the cryostat is a good approach (this has been implemented creating the class ISTPC and by modifying the EFieldAtStep function of ISCalcCorrelated module). Nevertheless including the variable field is the next step of the Hybrid Model.

By using this repository you will be able to obtain a complete analysis of light simulation using the Hybrid Model.  
Below is exposed the list of .fcl and .C needed for running the complete simulation using the New Hybrid Model for Light Simulation in SBND.  
  - prodsingle_mu_NewGeom.fcl :  stage gen. Generates a muon sample using the "new geometry" for Hybrid Model (sbnd_v02_00.gdml).  
  - OpHybrid_g4_refactored_sbnd.fcl : stage g4. Propagation of photons using the new library (SBND_OpLibOUT_v2.00.root) and geometry (sbnd_v02_00.gdml). If the  energy deposition is generated inside the active volume (IonAndScintIN) then it propagates photons using the Semianalytic Model (PAR) and if it is generated outside the active volume (IonAndScintOUT), then it uses the library for propagating photons (LIB). We are able to use LArQL model (by using services.LArG4Parameters.UseModLarqlRecomb: true) or not to use it (by using services.LArG4Parameters.UseModLarqlRecomb: false). This stage generates SimPhotonsLite.
  - run_analyseEvents.fcl : fcl for running the Analyzer. 
  - AnalyzeEvents_module.cc : Analyzer that stores: energy depositions in each step for each muon (E and E1, for the semianalytic and the library), positions x (X, X1), y (Y, Y1), z (Z, Z1) of each step (SimEnergyDeposit) and photons detected vuv at a g4 stage (SimPhotonsLite) using the semianalytic model (phot_detected) and the library (phot_detected1) and vis (phot_detectedref and phot_detectedref1). 
  - EnergyDepositionsTest.C : Testing the Hybrid Model. Verify that we have energy depositions in the whole Cryostat volume in X, Y and Z directions.
  - LightYield_Hybrid_with_without_LArQL.C : Launching 50 crossing muons in different x positions in order to calculate the light yield in each x position (covering positions inside and outside the active volume). The light yield is calculated using LArQL model that has into account escaping electrons at low electric fields and without using LArQL model (the difference is important outside the active volume where the Efield= 0 kV/cm).
  - PhotsDetected_Hybrid_with_without_LarQL.C : Same as the previous program but calculating just the number of photons (#PE) instead of the light yield.

***File_Task 2: MichelElectrons_GH.***  

The geometric propagation of the Semianalytic Model is not model dependent but the GH correction is strongly dependent on the model, because it is based on the Montecarlo simulation and depends on parameters that we dont know exactly its values like the Rayleigh Scattering length and the SBND refelectivities, that’s why calibrating this curves with data-driven corrections is so important.
The main idea of this analysis is to obtain this correction by using real data, so ideally, we need point-like energy depositions. A possible good sample for this purpose is a Michel electron sample because electrons coming from the muon decay have a little energy range, little than 50 MeV and this sample will be almost point-like and close to the ideal case.
So as a proof of concept our choice is a low-energy electron sample with a gaussian energy distribution, similar to the Michel electrons energy distribution. And in order to reduce borders effects in the simulation we launch our sample with a position distribution in the centre of the detector, in particular we are using the positive tpc. 
With this analysis we have been able to demonstrate that:
- We are able to calibrate the Semi-Analytic Model with data-driven corrections.
- Michel electrons, in principle, allow to generate the GH corrections by using cuts proposed.
- Finally, we have done this study using PMTs but conclusions can be extrapolated to the ARAPUCAS.  

List of .fcl and .C needed for calibrating the SemiAnalytic Model (GH curves) for Light Simulation in SBND using real data (using a Michel electron-like sample).  
   - prodsingle_NewLarG4.fcl : stage gen. Generates an electron sample using a gaussian distribution for the energy and the positions in x, y, z.
   - standard_g4_semi_claudia.fcl : stage g4. Propagation of photons inside the active volume (launched in the centre of the positive tpc) (IonAndScint) then it propagates photons using the Semianalytic Model (LIB). We are able to simulate just vuv photons (by using DoReflectedLight: false) or vuv+vis photons (by using DoReflectedLight: true). This stage generates SimPhotonsLite.
   - run_flashfinder_claudia.fcl : stage detsim. Running the digitization using the IDEAL response of PMTs. This stage generates OpFlash.
   - run_analyseEvents_claudia.fcl : fcl for running the Analyzer.  
   - AnalyzeEvents_FlashVUV.cc : Analyzer that stores: energy depositions in each step (E), positions x (X), y (Y), z (Z) of each step and photons generated at each step (phot_generated), (using SimEnergyDeposit) and photons detected vuv at a g4 stage (phot_detected) and the optical channel (chanopt) (using SimPhotonsLite). It also stores digitized photons vuv (flash_pe_vuv) at detsim stage (Using OpFlash), for each Michel we have a vector flash_pe_vuv and the entries of the vectors are the number of the optical channel, so we don't need a new variable that stores the optical channels.
   - AnalyzeEvents_FlashVUVVIS.cc : Analyzer that stores: energy depositions in each step (E), positions x (X), y (Y), z (Z) of each step and photons generated at each step (phot_generated), (using SimEnergyDeposit) and photons detected vuv at a g4 stage (phot_detected) and the optical channel (chanopt) (using SimPhotonsLite). It also stores digitized photons vuv+vis (flash_pe_vuvvis) at detsim stage (Using OpFlash), for each Michel we have a vector flash_pe_vuvvis and the entries of the vectors are the number of the optical channel, so we don't need a new variable that stores the optical channels.
   - PMTs.txt : list of the positions of the 320 PMTs of SBND.
   - makePMTvector.C : making a .root file of 320 PMTs and its positions.
   - MichelElectronGraphs_LiteVUV.C : Recovering GH curves using VUV photons at g4 stage.
   - MichelelectronGraphs_FlashVUV.C : Recovering GH curves using VUV photons including digitization. 
   - MichelElectronGraphs_FlashVUVVIS.C : Recovering GH curves using (VUV+VIS at coated)-(VIS at uncoated) in each window with photons including digitization. 
   - StandardDeviation.C : Studying the spread the postions of the energy depositions for each Michel (standard deviation and cumulative).
   - Nphots-distance-profile2D.C : Relative error between VUV photons reco and VUV true photons detected. 
The relative error is shown in the color bar. Result: we need to establish a method in order to cut in photons detected and distances.
   - CutDistanceandPhots.C : quality cuts for VUV digitized photons: if the error between photons reco and lite is deviated from the mean value of the relative error more than a 5% we cut in distance and in number of photons reconstructed.
   - ErrorDistribution.C
   

