#! /bin/csh -f


@ ID = 0
while({$ID}<10)
if(-f ../pair/matchlist_SUPW0021247{$ID}.dat) then
rm ../pair/matchlist_SUPW0021247{$ID}.dat
endif

if(-f ../pair/matchlist_SUPW0021248{$ID}.dat) then
rm ../pair/matchlist_SUPW0021248{$ID}.dat
endif

if(-f ../pair/matchlist_SUPW0021249{$ID}.dat) then
rm ../pair/matchlist_SUPW0021249{$ID}.dat
endif

if(-f ../pair/matchlist_SUPW0021251{$ID}.dat) then
rm ../pair/matchlist_SUPW0021251{$ID}.dat
endif
	@ ID ++
end
@ ID = 0
while({$ID}<10)
	set DIR = ../pair/tan_flt_oss_SUPW0021247{$ID}_flag0.fits.pair.full
	set ODIR = ../pair/matchlist_SUPW0021247{$ID}.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print 0, ENVIRON["IID"], $2, $4, $14, $16, $34}' > ../pair/temp.dat
	sed -e "1,5d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end
@ ID = 0
while({$ID}<10)
	set DIR = ../pair/tan_flt_oss_SUPW0021248{$ID}_flag0.fits.pair.full
	set ODIR = ../pair/matchlist_SUPW0021248{$ID}.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print 0, ENVIRON["IID"], $2, $4, $14, $16, $34}' > ../pair/temp.dat
	sed -e "1,5d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end
@ ID = 0
while({$ID}<10)
	set DIR = ../pair/tan_flt_oss_SUPW0021249{$ID}_flag0.fits.pair.full
	set ODIR = ../pair/matchlist_SUPW0021249{$ID}.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print 0, ENVIRON["IID"], $2, $4, $14, $16, $34}' > ../pair/temp.dat
	sed -e "1,5d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end
@ ID = 0
while({$ID}<10)
	set DIR = ../pair/tan_flt_oss_SUPW0021251{$ID}_flag0.fits.pair.full
	set ODIR = ../pair/matchlist_SUPW0021251{$ID}.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print 0, ENVIRON["IID"], $2, $4, $14, $16, $34}' > ../pair/temp.dat
	sed -e "1,5d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end


