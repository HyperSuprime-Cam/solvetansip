# -*- python -*-
#
# Setup our environment
#
import glob, os.path, sys, traceback
import lsst.SConsUtils as scons

env = scons.makeEnv(
    "solvetansip",
#    r"$HeadURL: FILL IN PATH /hscAstrom/trunk/SConstruct $",
    r"$HeadURL: FILL IN PATH /scons_dir/trunk/SConstruct $",
    [
#        ["boost", "boost/version.hpp", "boost_system:C++"],
#        ["boost", "boost/version.hpp", "boost_filesystem:C++"],
#        ["boost", "boost/regex.hpp", "boost_regex:C++"],
#        ["boost", "boost/filesystem.hpp", "boost_system:C++"],
#        ["boost", "boost/serialization/base_object.hpp", "boost_serialization:C++"],
#        ["boost", "boost/test/unit_test.hpp", "boost_unit_test_framework:C++"],
        ["python", "Python.h"],
        ["gsl", "gsl/gsl_linalg.h", "gslcblas gsl"],
        ["boost", "boost/shared_ptr.hpp", "boost_system:C++"],
        ["daf_base", "lsst/daf/base/Citizen.h", "daf_base:C++"],
        ["utils", "lsst/utils/ieee.h", "utils:C++"],
        ["pex_exceptions", "lsst/pex/exceptions.h", "pex_exceptions:C++"],
        ["pex_policy", "lsst/pex/policy/Policy.h", "pex_policy:C++"],
        ["pex_logging", "lsst/pex/logging/Trace.h", "pex_logging:C++"],
        ["daf_persistence", "lsst/daf/persistence.h", "daf_persistence:C++"],
        ["security", "lsst/security/Security.h", "security:C++"],
        ["daf_data", "lsst/daf/data.h", "daf_data:C++"],
        ["eigen", "Eigen/Core.h"],
        ["afw", "lsst/afw/detection/Source.h", "afw"],
    ],
)

env.libs["solvetansip"] += env.getlibs("pex_exceptions afw boost utils daf_base daf_data daf_persistence pex_logging pex_policy security")

for d in (
    "lib",
    "python/hsc/meas/tansip",
    "example",
):
    SConscript(os.path.join(d, "SConscript"))

scons.CleanTree(r"*~ core *.so *.os *.o *.pyc config.log")

env['IgnoreFiles'] = r"(~$|\.pyc$|^\.svn$|\.o$)"

for d in ('example', 'include', 'lib', 'policy', 'python', 'src'):
    Alias("install", env.Install(env['prefix'], d))
Alias("install", env.InstallEups(os.path.join(env['prefix'], "ups")))

env.Declare()
env.Help("""
LSST Application Framework packages
""")
