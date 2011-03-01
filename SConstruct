# -*- python -*-
#
# Setup our environment
#
import glob, os.path, sys, traceback
import lsst.SConsUtils as scons

try:
    scons.ConfigureDependentProducts
except AttributeError:
    import lsst.afw.scons.SconsUtils
    scons.ConfigureDependentProducts = lsst.afw.scons.SconsUtils.ConfigureDependentProducts

env = scons.makeEnv(
    "solvetansip",
    r"$HeadURL$",
    scons.ConfigureDependentProducts("solvetansip"),
    )

env.libs["solvetansip"] += env.getlibs("pex_exceptions afw boost utils daf_base daf_data daf_persistence pex_logging pex_policy security")

for d in (
#    "etc",
    "lib",
    "python/hsc/meas/tansip",
    "example",
):
    SConscript(os.path.join(d, "SConscript"))

Alias("install", [
    #env.Install(env['prefix'], "doc"),
    env.Install(env['prefix'], "etc"),
    env.Install(env['prefix'], "examples"),
    env.Install(env['prefix'], "include"),
    env.Install(env['prefix'], "lib"),
    env.Install(env['prefix'], "policy"),
    env.Install(env['prefix'], "python"),
    env.Install(env['prefix'], "src"),
    #env.Install(env['prefix'], "tests"),
    env.InstallEups(os.path.join(env['prefix'], "ups")),
    ])
scons.CleanTree(r"*~ core *.so *.os *.o *.pyc config.log")

env['IgnoreFiles'] = r"(~$|\.pyc$|^\.svn$|\.o$)"

env.Declare()
env.Help("""
LSST Application Framework packages
""")
