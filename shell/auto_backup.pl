#!/usr/bin/perl

while(1){
    #system "rsync -auz datadir -e ssh emt:/home/mumon-emt/data/daqpc1";
    system "rsync -auz -e ssh emt:/home/mumon-emt/data/daqpc1 ../rawdata";
    system "rsync -auz -e ssh emt:/home/mumon-emt/data/daqpc2 ../rawdata";
    system "rsync -auz -e ssh emt:/home/mumon-emt/data/daqpc3 ../rawdata";
    system "sleep 600";
}
