===================
Roadmap for the Training 2021
===================

The goal of this document is to present the roadmap for the 2021 Training. This text is a map from the programme to the files: slides or scripts. 

Day 1 : Methodology of Uncertainty Treatment – Basics of Probability and Statistics
-----------------------------------------------------------------------------------

- General Uncertainty Methodology (30’): A. Dutfoy.

    https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Courses/Intro/1-PRACE_D1-IntroStage.ppt

    https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Courses/Intro/2-PRACE_D1-MethodoIncertitudes.ppt

- Probability and Statistics: Basics (45’): G. Blondet.

    https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Courses/Probability/PRACE_D1_Probability_theory_basics_2021.pdf

- General introduction to Open TURNS and Uranie (2 * 30’): G. Blondet, J.B. Blanchard.

    https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Courses/Intro_OT/PRACE_D1_OpenTURNS_introduction_2021.pdf

- General overview of the Uranie platform:

    https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Courses/Intro/05._PRACE_D1_UranieGeneralIntroduction.pdf

- Introduction to Python and Jupyter (45’): Hands-on session on distributions manipulations.

    https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Scripts/Python/TP0_Introduction_Python_Jupyter.ipynb

- Lunch 
- Uncertainty Quantification (45’): J.B. Blanchard.

    https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Courses/Intro/06._PRACE_D1_UncertaintyQuantification.pdf

- Hands-on session 1 with OpenTURNS and Uranie: sections 1, 2 (1h): G. Blondet,  J.B. Blanchard,  A. Dutfoy.
Hands-on session 1 on the beam example with OpenTURNS.

    https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Scripts/Uncertainty_Quantification/TP1_Uncertainty_Quantification.ipynb

- Sensitivity analysis (1h): A. Dutfoy.

    https://github.com/mbaudin47/hpcuqtraining/blob/master/2021/Courses/Sensitivity/AnaSensibilite_PRACE_english.pdf

Day 2 : Quantification, Propagation and Ranking of Uncertainties
----------------------------------------------------------------

- Hands-on session 2 with OpenTURNS and Uranie, section 3 (1h): M. Baudin, G. Blondet, F. Gaudier, J.B. Blanchard. 
Hands-on session 2 on the beam example with OpenTURNS: central tendency and sensitivity.

    https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Scripts/Central_tendency/TP2_wrapper_Central_dispersion.ipynb

- Estimation of probability of rare events (1h): G. Blondet.

    https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Courses/Rare_event/PRACE_D2_Rare_events_probability_estimation_2021.pdf

- Hands-on session 3 with OpenTURNS and Uranie (1h): G. Blondet, F. Gaudier, J.B. Blanchard, M. Baudin. 
Hands-on session 3 with OpenTURNS: rare event probability estimation based on beam example.

        https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Scripts/Rare_Event/TP3_Rare_event.ipynb

- Lunch 

- Distributed computing (1h): Uranie (15’, F. Gaudier, J.B. Blanchard), OpenTURNS (15’, G. Blondet), Salome et OpenTURNS (30’, O. Mircescu).

    - Batch Submission with Uranie: https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Courses/DistributedComputing/11.PRACE_D3_BatchUranie.pdf

    - Otwrappy: https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Courses/DistributedComputing/PRACE_D2_OtWraPy/Distributing_OpenTURNS_OtWraPy.pdf

    - SALOME Course: https://github.com/mbaudin47/hpcuqtraining/blob/master/2021/Courses/Salome/Salome.pptx

- Optimization and Calibration (1h): J.B. Blanchard, M. Baudin.

    - Numerical Optimisation: A broad introduction:  https://github.com/mbaudin47/hpcuqtraining/blob/master/2021/Courses/Calibration/14._PRACE_D2_Optimisation_introduction.pdf

    - Calibration Course: https://github.com/mbaudin47/hpcuqtraining/blob/master/2021/Courses/Calibration/Calibration_PRACE_english.pdf

- Hands-on session with OpenTURNS and Uranie (1h): J.B. Blanchard, M. Baudin.

    - Calibration Scripts Deterministic (30min): https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Scripts/Calibration/Exercise-calage-deterministic-Chaboche.ipynb)
    - Calibration Scripts Bayesian: https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Scripts/Calibration/Exercise-calage-bayesian-Chaboche.ipynb

TODO : Optimization Application

Day 3 : HPC and Meta modeling
-----------------------------

- HPC aspects specific to the Uncertainty treatment (1h): K. Delamotte

    https://github.com/mbaudin47/hpcuqtraining/tree/master/2021/Courses/LinearAlgebra/HMat-PRACE-2021.pdf

- Introduction to Meta models (validation, over-fitting) – Polynomial chaos expansion (1h): M.Baudin, C. Mai.

    - Course: https://github.com/mbaudin47/hpcuqtraining/blob/master/2021/Courses/Metamodel/Introduction/steps-C-surrogate.pdf

- Kriging meta model (1h): C. Mai

    - Kriging Course: https://github.com/mbaudin47/hpcuqtraining/blob/master/2021/Courses/Metamodel/slides_GP/Latex/Metamodel_Kriging.pdf

    - Chaos Course: https://github.com/mbaudin47/hpcuqtraining/blob/master/2021/Courses/Metamodel/slides_PCEs/Latex/Metamodel_PCEs.pdf

- Hands-on session with OpenTURNS (it time allows)

    - Over-fitting and model selection: https://github.com/mbaudin47/hpcuqtraining/blob/master/2021/Scripts/Metamodel/Over_fitting_model_selection.ipynb
    - Application of the polynomial chaos to the cantilever beam: validation of a metamodel. https://github.com/mbaudin47/hpcuqtraining/blob/master/2021/Scripts/Metamodel/Validation-Chaos-cantilever-beam.ipynb

- Lunch 

- Hands-on session 4 with OpenTURNS and Uranie (2h): C. Mai, G. Blondet, J.B. Blanchard.

    - Hands-on session 4 (a) with OpenTURNS: polynomial chaos metamodel on the beam example.

    https://github.com/mbaudin47/hpcuqtraining/blob/master/2021/Scripts/Metamodel/TP4_Cantilever_beam_polynomial_chaos.ipynb

    - Hands-on session 4 (b) with OpenTURNS: kriging metamodel on the beam example.

    https://github.com/mbaudin47/hpcuqtraining/blob/master/2021/Scripts/Metamodel/TP4b_Kriging.ipynb

- Discussion /  Participants projects

