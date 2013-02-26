#! /bin/csh

set pafname = $argv[1]
set objname = $argv[2]
foreach objname (`cat | awk '{print}' $objname`)
	set objdir = $objname:r
#	echo $objdir
	if(! -d $objdir) mkdir $objdir
#	echo ./solvetansip $pafname $objname
	./solvetansip $pafname $objname
end

