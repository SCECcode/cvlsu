#!/usr/bin/env python


##
#  Builds the data files in the expected format from CV_3D_Model.txt
#
# from >> lon lat depth(m) vp(km/s)
#
# to >>  /** P-wave velocity in km/s per second */
#        double vp;
# depth is in increment of 500m,
#
 

import getopt
import sys
import subprocess
import struct
import array

## at hypocenter  LSU/CV_3D_Model.txt

model = "LSU"

#174629
dimension_x = 101
dimension_y = 91
dimension_z = 19

lon_origin = -116.7
lat_origin = 33.3

lon_upper = -115.7
lat_upper = 34.2


delta_lon = (lon_upper - lon_origin )/(dimension_x-1)
delta_lat = (lat_upper - lat_origin)/(dimension_y-1)

for ycoord in xrange(dimension_y):
   yloc = lat_origin + (ycoord * delta_lat)
#  print "yloc - ",yloc
for xcoord in xrange(dimension_x):
   xloc = lon_origin + (xcoord * delta_lon)
#   print  "xloc - ",xloc

def usage():
    print("\n./make_data_files.py -u [uid]\n\n")
    print("-u - username to use to do the dataset retrieval.\n")
    sys.exit(0)

def main():

    # Set our variable defaults.
    username = ""
    path = "/var/www/html/research/ucvmc/" + model 

    try:
        opts, args = getopt.getopt(sys.argv[1:], "u:", ["user="])
    except getopt.GetoptError as err:
        print(str(err))
        usage()
        sys.exit(1)

    for o, a in opts:
        if o in ("-u", "--user"):
            username = str(a) + "@"

##
##    subprocess.check_call(["scp", username +
##                           "hypocenter.usc.edu:" + path + "/CV_3D_Model.txt",
##                           "."])
##

    # Now we need to go through the data files and put them in the correct
    # format for LSUCV. More specifically, we need a Vp.dat

    print("\nWriting out LSUCV data files\n")

    f = open("./CV_3D_Model.txt")

    f_vp = open("./cv/vp.dat", "wb")

#    print("size of model, ",dimension_x * dimension_y * dimension_z)

    vp_arr = array.array('f', (-1.0,) * (dimension_x * dimension_y * dimension_z))

    nan_cnt = 0
    total_cnt =0;
    for line in f:
        arr = line.split()
        lon_v = float(arr[0])
        lat_v = float(arr[1])
        depth_v = float(arr[2])/500
        vp = -1.0;
        tmp = arr[3]
        total_cnt = total_cnt + 1
        if( tmp != "NaN" ):
          vp = float(arr[3])
          vp = vp * 1000.0;
        else:
          nan_cnt = nan_cnt + 1

        y_pos = int(round((lat_v - lat_origin) / delta_lat))
        x_pos = int(round((lon_v - lon_origin) / delta_lon))
        z_pos = int(depth_v)

        loc =z_pos * (dimension_y * dimension_x) + (y_pos * dimension_x) + x_pos

        vp_arr[loc] = vp
#        if( tmp != "NaN" ):
#          print x_pos," ",y_pos," ",z_pos," >> ",lon_v," ",lat_v," ",depth_v," ",vp 
#        else:
#          print "NAN", x_pos," ",y_pos," ",z_pos," >> ",lon_v," ",lat_v," ",depth_v," ",vp 

    vp_arr.tofile(f_vp)

    f.close()
    f_vp.close()

    print("Done! with NaN", nan_cnt, "total", total_cnt)

if __name__ == "__main__":
    main()

