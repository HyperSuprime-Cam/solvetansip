#! /bin/csh -f

@ ID = 0
if(-f ../pair/matchlist_price-101541.dat) then
rm ../pair/matchlist_price-101541.dat
endif
while({$ID}<10)
	set DIR = ../Pauldata/price-101541{$ID}.matches
	set ODIR = ../pair/matchlist_price-101541.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $1, $2, $11, $5}' > ../pair/temp.dat
	sed -e "1,1d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end
@ ID = 0
if(-f ../pair/matchlist_price-101542.dat) then
rm ../pair/matchlist_price-101542.dat
endif
while({$ID}<10)
	set DIR = ../Pauldata/price-101542{$ID}.matches
	set ODIR = ../pair/matchlist_price-101542.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $1, $2, $11, $5}' > ../pair/temp.dat
	sed -e "1,1d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end
@ ID = 0
if(-f ../pair/matchlist_price-101543.dat) then
rm ../pair/matchlist_price-101543.dat
endif
while({$ID}<10)
	set DIR = ../Pauldata/price-101543{$ID}.matches
	set ODIR = ../pair/matchlist_price-101543.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $1, $2, $11, $5}' > ../pair/temp.dat
	sed -e "1,1d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end
@ ID = 0
if(-f ../pair/matchlist_price-101544.dat) then
rm ../pair/matchlist_price-101544.dat
endif
while({$ID}<10)
	set DIR = ../Pauldata/price-101544{$ID}.matches
	set ODIR = ../pair/matchlist_price-101544.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $1, $2, $11, $5}' > ../pair/temp.dat
	sed -e "1,1d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end
@ ID = 0
if(-f ../pair/matchlist_price-101545.dat) then
rm ../pair/matchlist_price-101545.dat
endif
while({$ID}<10)
	set DIR = ../Pauldata/price-101545{$ID}.matches
	set ODIR = ../pair/matchlist_price-101545.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $1, $2, $11, $5}' > ../pair/temp.dat
	sed -e "1,1d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end
@ ID = 0
if(-f ../pair/matchlist_price-101546.dat) then
rm ../pair/matchlist_price-101546.dat
endif
while({$ID}<10)
	set DIR = ../Pauldata/price-101546{$ID}.matches
	set ODIR = ../pair/matchlist_price-101546.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $1, $2, $11, $5}' > ../pair/temp.dat
	sed -e "1,1d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end
@ ID = 0
if(-f ../pair/matchlist_price-101547.dat) then
rm ../pair/matchlist_price-101547.dat
endif
while({$ID}<10)
	set DIR = ../Pauldata/price-101547{$ID}.matches
	set ODIR = ../pair/matchlist_price-101547.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $1, $2, $11, $5}' > ../pair/temp.dat
	sed -e "1,1d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end
@ ID = 0
if(-f ../pair/matchlist_price-101548.dat) then
rm ../pair/matchlist_price-101548.dat
endif
while({$ID}<10)
	set DIR = ../Pauldata/price-101548{$ID}.matches
	set ODIR = ../pair/matchlist_price-101548.dat
	setenv IID {$ID}
#	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $15, $16, $25, $19}' > pair/temp.dat
	cat {$DIR} | awk '{print $16 , ENVIRON["IID"], $1, $2, $11, $5}' > ../pair/temp.dat
	sed -e "1,1d" ../pair/temp.dat >> {$ODIR}
	@ ID ++
end

