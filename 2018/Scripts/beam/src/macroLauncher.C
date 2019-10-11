{

    using namespace URANIE::DataServer;
    using namespace URANIE::Sampler;
    using namespace URANIE::Launcher;

    TDataServer *tds = new TDataServer("tdsPoutreSolution", "Solution for the Poutre useacse");
    tds->addAttribute ( new TBetaDistribution("E", 0.93, 2.27, 2.8e7, 4.8e7));

    Double_t F_mu = 3e4;
    Double_t F_sigma = 9e3;
    Double_t F_min =15e3;

    Double_t F_A = F_sigma*F_sigma/((F_mu-F_min)*(F_mu-F_min));
    Double_t F_ErrorFactor = exp(1.645*sqrt(log(F_A+1)));
    cout << " ** F_A(" << F_A << ") F_ErrorFactor("<<F_ErrorFactor<<")"<<endl;
    tds->addAttribute ( new TLogNormalDistribution( "F", F_mu, F_ErrorFactor, F_min));
    tds->addAttribute ( new TUniformDistribution("L", 250.0, 260.0));
    tds->addAttribute ( new TBetaDistribution("I", 2.5, 1.5, 310., 450.));

    TString sJDD = TString("beam.xml");
    tds->getAttribute("E")->setFileKey(sJDD, "//inputs/@E", "%.9e", URANIE::DataServer::TAttributeFileKey::kXMLAttribute);
    tds->getAttribute("F")->setFileKey(sJDD, "//inputs/@F", "%.9e", URANIE::DataServer::TAttributeFileKey::kXMLAttribute);
    tds->getAttribute("L")->setFileKey(sJDD, "//inputs/@L", "%.9e", URANIE::DataServer::TAttributeFileKey::kXMLAttribute);
    tds->getAttribute("I")->setFileKey(sJDD, "//inputs/@I", "%.9e", URANIE::DataServer::TAttributeFileKey::kXMLAttribute);

    // Sampling
    Int_t nS = 1000;
    TSampling *ts = new TSampling(tds, "lhs", nS);
    ts->generateSample();

    // Launcher
    TOutputFileXML * fout = new TOutputFileXML("_beam_outputs_.xml");
    fout->addAttribute("y", "//outputs/@deviation", URANIE::DataServer::TAttributeFileKey::kXMLAttribute);

    // the TCode object
    TCode *mycode = new TCode(tds, "beam -x beam.xml"); // option verbose : -v
    mycode->addOutputFile( fout );

    // Lanceur de code
    TLauncher *lanceur = new TLauncher(tds, mycode);
    lanceur->setClean();
    lanceur->run("");
    tds->exportData("_launcher_code_.dat");

    tds->drawPairs();
}
