#!/usr/bin/env python

##
#  Retrieve the latlons form the original data txt file and
#  and retrieve the material properties from binary vp.dat file 
#

import getopt
import sys
import subprocess
import struct
import numpy as np

dimension_x = 101 
dimension_y = 91
dimension_z = 19

lon_origin = -116.7
lat_origin = 33.3

lon_upper = -115.7
lat_upper = 34.2

delta_lon = (lon_upper - lon_origin )/(dimension_x-1)
delta_lat = (lat_upper - lat_origin)/(dimension_y-1)

def usage():
    print("\n./query_data_files.py\n\n")
    sys.exit(0)

def main():

    count =0

    f_lonlat = open("./CV_3D_Model.txt")

    f_vp = open("./cv/vp.dat")

    vp_arr = np.fromfile(f_vp, dtype=np.float32)

    f_vp.close()

    lon_start = lon_origin
    lat_start = lat_origin
    depth_start = 0.0;

    count =0
    for line in f_lonlat:
        arr = line.split()
        lon_v = float(arr[0])
        lat_v = float(arr[1])
        depth_v = float(arr[2])/500
        fvp = arr[3]

        y_pos = int(round((lat_v - lat_origin) / delta_lat))
        x_pos = int(round((lon_v - lon_origin) / delta_lon))
        z_pos = int(depth_v)

        offset=z_pos * (dimension_y * dimension_x) + (y_pos * dimension_x) + x_pos
        vp=vp_arr[offset];

        if((fvp != "NaN") & (count < 10)) :
          count = count + 1
          print "xyz:", x_pos," ",y_pos," ",z_pos," >> ", lon_v, " ",lat_v, " ", float(depth_v) , "-->vp", vp, "->fvp", fvp
          print "offset ",offset

        if((float(vp) != -1) & ( (float(vp) > 8000) | (float(vp)<1500))) :
          print lon_v, " ",lat_v, " ", float(depth_v) , "-->vp", vp

    f_lonlat.close()
    print("\nDone!")

if __name__ == "__main__":
    main()


