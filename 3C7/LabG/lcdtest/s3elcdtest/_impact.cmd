setMode -bs
setMode -bs
setCable -port auto
Identify 
identifyMPM 
assignFile -p 1 -file "C:/EDPGA/Chapter 3/lcdtest/s3elcdtest/lcdtest.bit"
Program -p 1 -defaultVersion 0 
saveProjectFile -file "C:\EDPGA\Chapter 3\lcdtest\s3elcdtest/s3elcdtest.ipf"
saveProjectFile -file "C:/EDPGA/Chapter 3/lcdtest/s3elcdtest/s3elcdtest.ipf"
setMode -bs
deleteDevice -position 3
deleteDevice -position 2
deleteDevice -position 1
setMode -bs
setMode -bs
setCable -port auto
Identify 
identifyMPM 
assignFile -p 1 -file "C:/EDPGA/Chapter 3/elapsedtime/s3eelapsedtime/s3eelapsedtime.bit"
Program -p 1 -defaultVersion 0 
saveProjectFile -file "C:/EDPGA/Chapter 3/elapsedtime/s3eelapsedtime/s3eelapsedtime.ipf"
setMode -bs
deleteDevice -position 1
deleteDevice -position 1
deleteDevice -position 1
setMode -ss
setMode -sm
setMode -hw140
setMode -spi
setMode -acecf
setMode -acempm
setMode -pff
setMode -bs
