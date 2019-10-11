
void poutreModel(Double_t *x, Double_t *y)
{
    Double_t dE = x[0];
    Double_t dF = x[1];
    Double_t dL = x[2];
    Double_t dI = x[3];

    //  cout << " *** dE[" << dE << "] dF[" << dF << "] dL(" << dL << ") dI(" << dI << ") ..." << endl;

    y[0] = ( dF * dL**3) / (3.0*dE*dI);

}


void validateExternalCode()
{
    using namespace URANIE::DataServer;
    using namespace URANIE::Sampler;
    using namespace URANIE::Launcher;

    TDataServer *tds = new TDataServer("tdsPoutreExternalCode", "PATC Training session");
    tds->fileDataRead("_launcher_code_.dat");

    TLauncherFunction *tl = new TLauncherFunction(tds, poutreModel, "E:F:L:I", "yFA");
    tl->run();

    TCanvas *c = new TCanvas("c1", "c1",12,42,1200,750);
    tds->drawPairs("E:F:L:I:y:yFA");
//    tds->draw("yFA-y:y");
    c->SaveAs("images/beamExternalCodeDrawPairs.png");

}
