import sys, re, os, math
import pyfits
import SWIG.SLVTS_SWIG    as SLVTS

def doTansip_ASCII(APRM,CCD,REF):
	print '--- doTansip_local : start ---'

	print '--- doTansip : get APRM ---'
	APRM=GET_APRM_A(APRM)
	print '--- doTansip : get CCD  ---'
	CCD =GET_CCD_A(CCD)
	KV=SLVTS.VS([])
	KV.append('NUM_CCD')
	KV.append(str(len(CCD)))
	APRM.append(KV)
	print '--- doTansip : get REF ---'
	REF =GET_REF_A(REF)
	KV=SLVTS.VS([])
	KV.append('NUM_REF')
	KV.append(str(len(REF)))
	APRM.append(KV)

	print APRM
	SLVTS_Argvs=SLVTS.VVVS([])
	SLVTS_Argvs.append(APRM)
    	SLVTS_Argvs.append(CCD)
	SLVTS_Argvs.append(REF)

	print '--- doTansip : SOLVE TANSIP ---'
	WCS=SLVTS.SOLVETANSIP(SLVTS_Argvs)
	print '--- doTansip_local :  end  ---'

def doTansip_BINARY(APRM,CCD,REF):
	print '--- doTansip_local : start ---'

	print '--- doTansip : get APRM ---'
	APRM=GET_APRM_B(APRM)
	print '--- doTansip : get CCD ---'
	CCD =GET_CCD_B(CCD)
	print '--- doTansip : get REF ---'
	REF =SLVTS.VVS([])

	SLVTS_Argvs=SLVTS.VVVS([])
	SLVTS_Argvs.append(APRM)
    	SLVTS_Argvs.append(CCD)
	SLVTS_Argvs.append(REF)

	print '--- doTansip : SOLVE TANSIP ---'
	WCS=SLVTS.SOLVETANSIP(SLVTS_Argvs)

	print '--- doTansip_local :  end  ---'

def GET_APRM_A(APRM):
	KVs=SLVTS.VVS([])
	
	FIN=open(APRM, 'r')
	for line in FIN:
		itemList = line[:-1].split()
		for K in ['INSTR','MODE_CR','MODE_CCDPOS','PRECISION_POS','ORDER_ASIP','ORDER_PSIP','MODE_REJ','CRPIX1','CRPIX2','CRVAL1','CRVAL2','BASISPOSX','BASISPOSY','BASISPOST','CLIPSIGMA','FLAG_STD','FLAG_OUT','DIR_OUT']:
			if(itemList[0][:-1]==K):
#				print itemList[0][:-1],K,str(itemList[1])
				KV=SLVTS.VS([])
				KV.append(str(itemList[0][:-1]))
				KV.append(str(itemList[1]))
				KVs.append(KV)
	return KVs

def GET_APRM_B(APRM):
	KVs=SLVTS.VVS([])
	
	return KVs

def GET_CCD_A(CCD):
	KVs=SLVTS.VVS([])
	
	FIN=open(CCD, 'r')
	for line in FIN:
		itemList = line[:-1].split()
		KV=SLVTS.VS([])
		KV.append(str(itemList[0]))
		KV.append(str(itemList[1]))
		KV.append(str(itemList[2]))
		KV.append(str(itemList[3]))
		KV.append(str(itemList[4]))
		KV.append(str(itemList[5]))
		KVs.append(KV)

	return KVs

def GET_CCD_B(CCD):
	KVs=SLVTS.VVS([])
	return KVs

def GET_REF_A(REF):
	KVs=SLVTS.VVS([])
	
	FIN=open(REF, 'r')
	for line in FIN:
		itemList = line[:-1].split()
		KV=SLVTS.VS([])
		KV.append(str(itemList[0]))
		KV.append(str(itemList[1]))
		KV.append(str(itemList[2]))
		KV.append(str(itemList[3]))
		KV.append(str(itemList[4]))
		KV.append(str(itemList[5]))
		KVs.append(KV)

	return KVs


def ERROR():
	print("usage : doTansip_local.py [FILE TYPE] [APRM FILE] [CCD FILE] [REF FILE]")
	print("FILE TYPE : A = ASCII")
	print("FILE TYPE : B = BINARY")

if __name__== '__main__':
	argvs=sys.argv
	argc=len(argvs)
	
	if(os.path.exists(argvs[2]) == False):
		ERROR()
		sys.exit("Could not be found APRM FILE : "+argvs[2])
	if(os.path.exists(argvs[3]) == False):
		ERROR()
		sys.exit("Could not be found CCD  FILE : "+argvs[3])
	if(os.path.exists(argvs[4]) == False):
		ERROR()
		sys.exit("Could not be found REF  FILE : "+argvs[4])

	if(argc==5):
		if(     argvs[1]=="A"):
			doTansip_ASCII (argvs[2],argvs[3],argvs[4])
		elif(argvs[1]=="B"):
			doTansip_BINARY(argvs[2],argvs[3],argvs[4])
		else:
			ERROR()
	else:
		ERROR()





