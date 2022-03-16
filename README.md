# SdCard-Rfid

Scan Rfid, save the UID to a string and then the UID string saved to a SdCard.

There are two types of rfid present in the merket

if you use this funtion after rfid initialization, "   rfid.PCD_DumpVersionToSerial();  "  then it shows the firmware version to serial monitor.

as like >>>>> Firmware Version: 0x92 = v2.0 , so with this version rfid 0x92 = v2.0 , i am abel to run SD Card and RFID both at same time.

but with other version like >>>>> Firmware Version: 0x12 = counterfeit chip , SD Card is not initializing !!! but RFID is working fine.

I think this " 0x12 = counterfeit chip " is fake chinese copy , this my observation.


