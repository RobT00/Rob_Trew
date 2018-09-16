setMode -bs
setMode -bs
setCable -port auto
Identify 
identifyMPM 
assignFile -p 1 -file "C:/EDPGA/Chapter 3/bargraphtest/s3ebargraphtest/bargraphtest.bit"
Program -p 1 -defaultVersion 0 
Program -p 1 -defaultVersion 0 
Program -p 1 -defaultVersion 0 
Program -p 1 -defaultVersion 0 
Program -p 1 -defaultVersion 0 
saveProjectFile -file "C:/EDPGA/Chapter 3/bargraphtest/s3ebargraphtest/s3ebargraphtest.ipf"
setMode -bs
deleteDevice -position 3
deleteDevice -position 2
deleteDevice -position 1
setMode -bs
setMode -bs
setCable -port auto
Identify 
identifyMPM 
assignFile -p 1 -file "C:/EDPGA/Chapter 3/pbsswtest/s3epbsswtest/pbsswtest.bit"
Program -p 1 -defaultVersion 0 
saveProjectFile -file "C:/EDPGA/Chapter 3/pbsswtest/s3epbsswtest/s3epbsswtest.ipf"
setMode -bs
deleteDevice -position 3
deleteDevice -position 2
deleteDevice -position 1
