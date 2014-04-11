setup hscPipe 2.8.3d_hsc
setup -j -r /data/ana/astrometry_net_data/sdss-dr8

./solvetansip.py /data08b/Subaru/HSC --output /data08b/Subaru/HSC/rerun/ok_test_doTansip --id visit=904410 --doraise -c doWriteNewFits=False  --clobber-config

