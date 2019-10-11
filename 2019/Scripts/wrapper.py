import openturns as ot
from openturns import coupling_tools
import otwrapy as otw
import os
from xml.dom import minidom
from time import time
from time import sleep
import socket

ot.Log.Show(ot.Log.USER)
ot.Log.SetFile('host.log')

def define_distribution():
    """
    Define the distribution of the training example (beam).
    Return a ComposedDistribution object from openTURNS
    """
    sample_E = ot.Sample.ImportFromCSVFile("sample_E.csv")
    kernel_smoothing = ot.KernelSmoothing(ot.Normal())
    bandwidth = kernel_smoothing.computeSilvermanBandwidth(sample_E)
    E = kernel_smoothing.build(sample_E, bandwidth)
    E.setDescription(['Young modulus'])

    F = ot.LogNormal()
    F.setParameter(ot.LogNormalMuSigma()([30000, 9000, 15000]))
    F.setDescription(['Load'])

    L = ot.Uniform(250, 260)
    L.setDescription(['Length'])

    I = ot.Beta(2.5, 4, 310, 450)
    I.setDescription(['Inertia'])

    marginal_distributions = [F, E, L, I]
    SR_cor = ot.CorrelationMatrix(len(marginal_distributions))
    SR_cor[2, 3] = -0.2
    copula = ot.NormalCopula(ot.NormalCopula.GetCorrelationFromSpearmanCorrelation(SR_cor))

    return(ot.ComposedDistribution(marginal_distributions, copula))

class Wrapper(ot.OpenTURNSPythonFunction):
    """
    Wrapper of the beam code
    """
    def __init__(self):
        # initialize the OpenTURNSPythonFunction
        # number of inputs = 4
        # number of outputs = 1
        super(Wrapper, self).__init__(4, 1)
        # define attributes for the template file and the executable
        cwd = os.getcwd()
        self.template = cwd + os.sep + 'beam' + os.sep + 'beam_input_template.xml'
        self.executable = cwd + os.sep + 'beam' + os.sep + 'beam -v -x beam.xml'

    def _exec(self, X):

        with otw.TempWorkDir(cleanup=False, prefix='ot-beam-'):
            sleep(5)
            # create input
            self._create_input_file(X)
            # run executable
            self._run()
            # parse output
            Y = self._parse_output()
            ot.Log.User(socket.gethostname())
            #ot.Log.Flush()
        return [Y]

    def _create_input_file(self, X):
        coupling_tools.replace(
              self.template,
              'beam.xml',
              ['@F','@E','@L','@I'],
             X)

    def _run(self):
        coupling_tools.execute(self.executable)

    def _parse_output(self):
        xmldoc = minidom.parse('_beam_outputs_.xml')
        itemlist = xmldoc.getElementsByTagName('outputs')
        deviation = float(itemlist[0].attributes['deviation'].value)
        return deviation

if __name__=='__main__':
    import argparse
    parser = argparse.ArgumentParser(description="Python wrapper example.")
    parser.add_argument('-X', nargs=4, metavar=('X1', 'X2', 'X3', 'X4'),
                        help='Vector on which the model will be evaluated')
    parser.add_argument('-N', nargs=1, type=int,
                        help='Number of samples to evaluate')
    parser.add_argument('-n_cpus', nargs=1, type=int,
                        help='Number of jobs to use')
    args = parser.parse_args()

    #model = ot.Function(Wrapper())
    if args.n_cpus:
        n_cpus=args.n_cpus[0]
    else:
        n_cpus=-1

    model = otw.Parallelizer(Wrapper(), backend='joblib', n_cpus=n_cpus)
    X_distribution = define_distribution()
    if args.X:
        X = ot.Point([float(x) for x in args.X])
    elif args.N:
        X = X_distribution.getSample(args.N[0])
    starttime = time()
    Y = model(X)
    fulltime = ot.Sample([[time() - starttime]])
    fulltime.exportToCSVFile('time.csv')
    Y.exportToCSVFile('result.csv')
