#! /bin/csh

set pafname = $argv[1]
set objname = $argv[2]
set objdir = $objname:r
echo $objdir
if(! -d $objdir) mkdir $objdir
./solvetansip $pafname $objname
