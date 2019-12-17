EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 6
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SimpleBci2:ESP32 U10
U 1 1 5DE49C31
P 8400 4500
AR Path="/5E277843/5DE49C31" Ref="U10"  Part="1" 
AR Path="/5DF8D13F/5DE49C31" Ref="U17"  Part="1" 
F 0 "U17" H 8425 5515 50  0000 C CNN
F 1 "ESP32" H 8425 5424 50  0000 C CNN
F 2 "SimpleBciPcb:ESP32" H 7700 3850 50  0001 C CNN
F 3 "" H 7700 3850 50  0001 C CNN
	1    8400 4500
	1    0    0    -1  
$EndComp
Text GLabel 7600 4550 0    50   Input ~ 0
SCLK
Text GLabel 7600 4650 0    50   Input ~ 0
MISO
Text GLabel 7600 5150 0    50   Input ~ 0
MOSI
$Comp
L power:GND #PWR0143
U 1 1 5DE15B40
P 1850 1750
AR Path="/5E277843/5DE15B40" Ref="#PWR0143"  Part="1" 
AR Path="/5DF8D13F/5DE15B40" Ref="#PWR0161"  Part="1" 
F 0 "#PWR0161" H 1850 1500 50  0001 C CNN
F 1 "GND" H 1855 1577 50  0000 C CNN
F 2 "" H 1850 1750 50  0001 C CNN
F 3 "" H 1850 1750 50  0001 C CNN
	1    1850 1750
	-1   0    0    -1  
$EndComp
$Comp
L Reference_Voltage:REF3025 U8
U 1 1 5E279386
P 1950 1450
AR Path="/5E277843/5E279386" Ref="U8"  Part="1" 
AR Path="/5DF8D13F/5E279386" Ref="U14"  Part="1" 
F 0 "U14" H 1721 1496 50  0000 R CNN
F 1 "REF3025" H 1721 1405 50  0000 R CIN
F 2 "Package_TO_SOT_SMD:SOT-23" H 1950 1000 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/ref3033.pdf" H 2050 1100 50  0001 C CIN
	1    1950 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0149
U 1 1 5DE0F14B
P 1850 1000
AR Path="/5E277843/5DE0F14B" Ref="#PWR0149"  Part="1" 
AR Path="/5DF8D13F/5DE0F14B" Ref="#PWR0162"  Part="1" 
F 0 "#PWR0162" H 1850 850 50  0001 C CNN
F 1 "+3V3" H 1850 950 50  0000 C CNN
F 2 "" H 1850 1000 50  0001 C CNN
F 3 "" H 1850 1000 50  0001 C CNN
	1    1850 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1000 1850 1150
$Comp
L Device:C C17
U 1 1 5E2BD3BF
P 1100 1450
AR Path="/5E277843/5E2BD3BF" Ref="C17"  Part="1" 
AR Path="/5DF8D13F/5E2BD3BF" Ref="C18"  Part="1" 
F 0 "C18" H 1215 1496 50  0000 L CNN
F 1 "C" H 1215 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1138 1300 50  0001 C CNN
F 3 "~" H 1100 1450 50  0001 C CNN
	1    1100 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0146
U 1 1 5DEE1681
P 7000 3750
AR Path="/5E277843/5DEE1681" Ref="#PWR0146"  Part="1" 
AR Path="/5DF8D13F/5DEE1681" Ref="#PWR0163"  Part="1" 
F 0 "#PWR0163" H 7000 3600 50  0001 C CNN
F 1 "+3V3" V 7100 3800 50  0000 C CNN
F 2 "" H 7000 3750 50  0001 C CNN
F 3 "" H 7000 3750 50  0001 C CNN
	1    7000 3750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0150
U 1 1 5DEE1E89
P 7000 3850
AR Path="/5E277843/5DEE1E89" Ref="#PWR0150"  Part="1" 
AR Path="/5DF8D13F/5DEE1E89" Ref="#PWR0164"  Part="1" 
F 0 "#PWR0164" H 7000 3600 50  0001 C CNN
F 1 "GND" V 6900 3750 50  0000 C CNN
F 2 "" H 7000 3850 50  0001 C CNN
F 3 "" H 7000 3850 50  0001 C CNN
	1    7000 3850
	0    1    -1   0   
$EndComp
Wire Wire Line
	7000 3750 7600 3750
Wire Wire Line
	7000 3850 7600 3850
Wire Wire Line
	1100 1300 1100 1150
Wire Wire Line
	1100 1150 1850 1150
Connection ~ 1850 1150
Wire Wire Line
	1100 1600 1100 1750
Wire Wire Line
	1100 1750 1850 1750
Connection ~ 1850 1750
$Comp
L Diode:1N5819 D25
U 1 1 5DF34C12
P 1250 2600
AR Path="/5E277843/5DF34C12" Ref="D25"  Part="1" 
AR Path="/5DF8D13F/5DF34C12" Ref="D32"  Part="1" 
F 0 "D32" H 1250 2816 50  0000 C CNN
F 1 "1N5819" H 1250 2725 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" H 1250 2425 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 1250 2600 50  0001 C CNN
	1    1250 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2600 1600 2600
$Comp
L power:+5V #PWR0153
U 1 1 5DF3BE74
P 950 2550
AR Path="/5E277843/5DF3BE74" Ref="#PWR0153"  Part="1" 
AR Path="/5DF8D13F/5DF3BE74" Ref="#PWR0165"  Part="1" 
F 0 "#PWR0165" H 950 2400 50  0001 C CNN
F 1 "+5V" H 965 2723 50  0000 C CNN
F 2 "" H 950 2550 50  0001 C CNN
F 3 "" H 950 2550 50  0001 C CNN
	1    950  2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0154
U 1 1 5DF400D9
P 1450 3050
AR Path="/5E277843/5DF400D9" Ref="#PWR0154"  Part="1" 
AR Path="/5DF8D13F/5DF400D9" Ref="#PWR0166"  Part="1" 
F 0 "#PWR0166" H 1450 2800 50  0001 C CNN
F 1 "GND" H 1455 2877 50  0000 C CNN
F 2 "" H 1450 3050 50  0001 C CNN
F 3 "" H 1450 3050 50  0001 C CNN
	1    1450 3050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1450 3050 1450 3000
Wire Wire Line
	1450 3000 1600 3000
$Comp
L power:+5V #PWR0144
U 1 1 5DF88082
P 9350 3700
AR Path="/5E277843/5DF88082" Ref="#PWR0144"  Part="1" 
AR Path="/5DF8D13F/5DF88082" Ref="#PWR0167"  Part="1" 
F 0 "#PWR0167" H 9350 3550 50  0001 C CNN
F 1 "+5V" H 9365 3873 50  0000 C CNN
F 2 "" H 9350 3700 50  0001 C CNN
F 3 "" H 9350 3700 50  0001 C CNN
	1    9350 3700
	1    0    0    -1  
$EndComp
$Comp
L power:+2V5 #PWR0145
U 1 1 5DF9DD40
P 2400 1450
AR Path="/5E277843/5DF9DD40" Ref="#PWR0145"  Part="1" 
AR Path="/5DF8D13F/5DF9DD40" Ref="#PWR0168"  Part="1" 
F 0 "#PWR0168" H 2400 1300 50  0001 C CNN
F 1 "+2V5" H 2415 1623 50  0000 C CNN
F 2 "" H 2400 1450 50  0001 C CNN
F 3 "" H 2400 1450 50  0001 C CNN
	1    2400 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1450 2400 1450
$Comp
L SimpleBci:ADS1256 U9
U 1 1 5DFBC955
P 4800 1650
AR Path="/5E277843/5DFBC955" Ref="U9"  Part="1" 
AR Path="/5DF8D13F/5DFBC955" Ref="U15"  Part="1" 
F 0 "U15" H 4825 2515 50  0000 C CNN
F 1 "ADS1256" H 4825 2424 50  0000 C CNN
F 2 "Package_SO:SSOP-28_5.3x10.2mm_P0.65mm" H 3200 900 50  0001 C CNN
F 3 "" H 3200 900 50  0001 C CNN
	1    4800 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 1250 4000 1250
Wire Wire Line
	4000 1250 4000 1150
Wire Wire Line
	4000 1150 4200 1150
$Comp
L power:GND #PWR0147
U 1 1 5DFBC966
P 4000 1150
AR Path="/5E277843/5DFBC966" Ref="#PWR0147"  Part="1" 
AR Path="/5DF8D13F/5DFBC966" Ref="#PWR0169"  Part="1" 
F 0 "#PWR0169" H 4000 900 50  0001 C CNN
F 1 "GND" V 4005 1022 50  0000 R CNN
F 2 "" H 4000 1150 50  0001 C CNN
F 3 "" H 4000 1150 50  0001 C CNN
	1    4000 1150
	0    1    -1   0   
$EndComp
Connection ~ 4000 1150
Wire Wire Line
	3900 1000 3900 1050
Wire Wire Line
	3900 1050 4200 1050
Text GLabel 5450 1850 2    50   Input ~ 0
CS_1
Text GLabel 5450 1650 2    50   Input ~ 0
MISO
Text GLabel 5450 1550 2    50   Input ~ 0
MOSI
$Comp
L power:+3V3 #PWR0148
U 1 1 5DFBC973
P 5600 2250
AR Path="/5E277843/5DFBC973" Ref="#PWR0148"  Part="1" 
AR Path="/5DF8D13F/5DFBC973" Ref="#PWR0170"  Part="1" 
F 0 "#PWR0170" H 5600 2100 50  0001 C CNN
F 1 "+3V3" V 5600 2500 50  0000 C CNN
F 2 "" H 5600 2250 50  0001 C CNN
F 3 "" H 5600 2250 50  0001 C CNN
	1    5600 2250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0151
U 1 1 5DFBC979
P 5450 2150
AR Path="/5E277843/5DFBC979" Ref="#PWR0151"  Part="1" 
AR Path="/5DF8D13F/5DFBC979" Ref="#PWR0171"  Part="1" 
F 0 "#PWR0171" H 5450 1900 50  0001 C CNN
F 1 "GND" V 5455 2022 50  0000 R CNN
F 2 "" H 5450 2150 50  0001 C CNN
F 3 "" H 5450 2150 50  0001 C CNN
	1    5450 2150
	0    -1   1    0   
$EndComp
Wire Wire Line
	5450 2250 5600 2250
$Comp
L power:+5V #PWR0152
U 1 1 5DFBC980
P 3900 1000
AR Path="/5E277843/5DFBC980" Ref="#PWR0152"  Part="1" 
AR Path="/5DF8D13F/5DFBC980" Ref="#PWR0172"  Part="1" 
F 0 "#PWR0172" H 3900 850 50  0001 C CNN
F 1 "+5V" H 3915 1173 50  0000 C CNN
F 2 "" H 3900 1000 50  0001 C CNN
F 3 "" H 3900 1000 50  0001 C CNN
	1    3900 1000
	1    0    0    -1  
$EndComp
$Comp
L power:+2V5 #PWR0155
U 1 1 5DFBC993
P 4050 1350
AR Path="/5E277843/5DFBC993" Ref="#PWR0155"  Part="1" 
AR Path="/5DF8D13F/5DFBC993" Ref="#PWR0173"  Part="1" 
F 0 "#PWR0173" H 4050 1200 50  0001 C CNN
F 1 "+2V5" V 4065 1478 50  0000 L CNN
F 2 "" H 4050 1350 50  0001 C CNN
F 3 "" H 4050 1350 50  0001 C CNN
	1    4050 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4050 1350 4200 1350
Text GLabel 4200 2350 0    50   Input ~ 0
SYNC
Text GLabel 5450 2350 2    50   Input ~ 0
RESET
Text GLabel 5450 1950 2    50   Input ~ 0
CLK
Text GLabel 5450 1750 2    50   Input ~ 0
READY_1
Text GLabel 5450 1450 2    50   Input ~ 0
SCLK
$Comp
L SimpleBci:ADS1256 U12
U 1 1 5DEE65D8
P 8200 1650
AR Path="/5E277843/5DEE65D8" Ref="U12"  Part="1" 
AR Path="/5DF8D13F/5DEE65D8" Ref="U16"  Part="1" 
F 0 "U16" H 8225 2515 50  0000 C CNN
F 1 "ADS1256" H 8225 2424 50  0000 C CNN
F 2 "Package_SO:SSOP-28_5.3x10.2mm_P0.65mm" H 6600 900 50  0001 C CNN
F 3 "" H 6600 900 50  0001 C CNN
	1    8200 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 1250 7400 1250
Wire Wire Line
	7400 1250 7400 1150
Wire Wire Line
	7400 1150 7600 1150
$Comp
L power:GND #PWR0156
U 1 1 5DEE65E9
P 7400 1150
AR Path="/5E277843/5DEE65E9" Ref="#PWR0156"  Part="1" 
AR Path="/5DF8D13F/5DEE65E9" Ref="#PWR0174"  Part="1" 
F 0 "#PWR0174" H 7400 900 50  0001 C CNN
F 1 "GND" V 7405 1022 50  0000 R CNN
F 2 "" H 7400 1150 50  0001 C CNN
F 3 "" H 7400 1150 50  0001 C CNN
	1    7400 1150
	0    1    -1   0   
$EndComp
Connection ~ 7400 1150
Wire Wire Line
	7300 1000 7300 1050
Wire Wire Line
	7300 1050 7600 1050
Text GLabel 8850 1850 2    50   Input ~ 0
CS_2
Text GLabel 8850 1650 2    50   Input ~ 0
MISO
Text GLabel 8850 1550 2    50   Input ~ 0
MOSI
$Comp
L power:+3V3 #PWR0157
U 1 1 5DEE65F5
P 9000 2250
AR Path="/5E277843/5DEE65F5" Ref="#PWR0157"  Part="1" 
AR Path="/5DF8D13F/5DEE65F5" Ref="#PWR0175"  Part="1" 
F 0 "#PWR0175" H 9000 2100 50  0001 C CNN
F 1 "+3V3" V 9000 2500 50  0000 C CNN
F 2 "" H 9000 2250 50  0001 C CNN
F 3 "" H 9000 2250 50  0001 C CNN
	1    9000 2250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0158
U 1 1 5DEE65FB
P 8850 2150
AR Path="/5E277843/5DEE65FB" Ref="#PWR0158"  Part="1" 
AR Path="/5DF8D13F/5DEE65FB" Ref="#PWR0176"  Part="1" 
F 0 "#PWR0176" H 8850 1900 50  0001 C CNN
F 1 "GND" V 8855 2022 50  0000 R CNN
F 2 "" H 8850 2150 50  0001 C CNN
F 3 "" H 8850 2150 50  0001 C CNN
	1    8850 2150
	0    -1   1    0   
$EndComp
Wire Wire Line
	8850 2250 9000 2250
$Comp
L power:+5V #PWR0159
U 1 1 5DEE6602
P 7300 1000
AR Path="/5E277843/5DEE6602" Ref="#PWR0159"  Part="1" 
AR Path="/5DF8D13F/5DEE6602" Ref="#PWR0177"  Part="1" 
F 0 "#PWR0177" H 7300 850 50  0001 C CNN
F 1 "+5V" H 7315 1173 50  0000 C CNN
F 2 "" H 7300 1000 50  0001 C CNN
F 3 "" H 7300 1000 50  0001 C CNN
	1    7300 1000
	1    0    0    -1  
$EndComp
$Comp
L power:+2V5 #PWR0160
U 1 1 5DEE660E
P 7450 1350
AR Path="/5E277843/5DEE660E" Ref="#PWR0160"  Part="1" 
AR Path="/5DF8D13F/5DEE660E" Ref="#PWR0178"  Part="1" 
F 0 "#PWR0178" H 7450 1200 50  0001 C CNN
F 1 "+2V5" V 7465 1478 50  0000 L CNN
F 2 "" H 7450 1350 50  0001 C CNN
F 3 "" H 7450 1350 50  0001 C CNN
	1    7450 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7450 1350 7600 1350
Text GLabel 7600 2350 0    50   Input ~ 0
SYNC
Text GLabel 8850 2350 2    50   Input ~ 0
RESET
Text GLabel 8850 1950 2    50   Input ~ 0
CLK
Text GLabel 8850 1750 2    50   Input ~ 0
READY_2
Text GLabel 8850 1450 2    50   Input ~ 0
SCLK
Wire Wire Line
	9150 3750 9350 3750
Wire Wire Line
	9350 3750 9350 3700
$Comp
L SimpleBci:chargerTH U11
U 1 1 5DEF3CCA
P 1900 2800
AR Path="/5E277843/5DEF3CCA" Ref="U11"  Part="1" 
AR Path="/5DF8D13F/5DEF3CCA" Ref="U13"  Part="1" 
F 0 "U13" H 2128 2846 50  0000 L CNN
F 1 "chargerTH" H 2128 2755 50  0000 L CNN
F 2 "SimpleBciPcb:chargerTH" H 1900 2800 50  0001 C CNN
F 3 "" H 1900 2800 50  0001 C CNN
	1    1900 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 1450 3550 2700
Wire Wire Line
	3550 1450 4200 1450
Wire Wire Line
	3450 1550 3450 2800
Wire Wire Line
	3450 1550 4200 1550
Wire Wire Line
	3350 1650 3350 2900
Wire Wire Line
	3350 1650 4200 1650
Wire Wire Line
	3250 1750 3250 3000
Wire Wire Line
	3250 1750 4200 1750
Wire Wire Line
	3150 1850 3150 3100
Wire Wire Line
	3150 1850 4200 1850
Wire Wire Line
	3050 1950 3050 3200
Wire Wire Line
	3050 1950 4200 1950
Wire Wire Line
	2950 2050 2950 3300
Wire Wire Line
	2950 2050 4200 2050
Wire Wire Line
	2850 2150 2850 3400
Wire Wire Line
	2850 2150 4200 2150
Wire Wire Line
	2750 2250 2750 3500
Wire Wire Line
	2750 2250 4200 2250
Wire Wire Line
	5850 2700 6100 2700
Wire Wire Line
	6100 2700 6100 1450
Wire Wire Line
	6100 1450 7600 1450
Wire Wire Line
	5850 2800 6200 2800
Wire Wire Line
	6200 2800 6200 1550
Wire Wire Line
	6200 1550 7600 1550
Wire Wire Line
	6300 2900 6300 1650
Wire Wire Line
	6300 1650 7600 1650
Wire Wire Line
	5850 3000 6400 3000
Wire Wire Line
	6400 3000 6400 1750
Wire Wire Line
	6400 1750 7600 1750
Wire Wire Line
	5850 3100 6500 3100
Wire Wire Line
	6500 3100 6500 1850
Wire Wire Line
	6500 1850 7600 1850
Wire Wire Line
	5850 3200 6600 3200
Wire Wire Line
	6600 3200 6600 1950
Wire Wire Line
	6600 1950 7600 1950
Wire Wire Line
	5850 3300 6700 3300
Wire Wire Line
	6700 3300 6700 2050
Wire Wire Line
	6700 2050 7600 2050
Wire Wire Line
	6800 3400 6800 2150
Wire Wire Line
	6800 2150 7600 2150
Wire Wire Line
	5850 3500 6900 3500
Wire Wire Line
	6900 3500 6900 2250
Wire Wire Line
	6900 2250 7600 2250
Wire Wire Line
	3050 3200 5350 3200
Wire Wire Line
	2950 3300 5350 3300
Wire Wire Line
	2750 3500 5350 3500
Wire Wire Line
	3550 2700 5350 2700
Wire Wire Line
	3450 2800 5350 2800
Wire Wire Line
	3250 3000 5350 3000
Wire Wire Line
	3150 3100 5350 3100
Wire Wire Line
	5850 3400 6800 3400
Wire Wire Line
	2850 3400 5350 3400
Wire Wire Line
	3350 2900 5350 2900
Wire Wire Line
	5850 2900 6300 2900
$Comp
L Connector_Generic:Conn_02x09_Top_Bottom J8
U 1 1 5DEF7276
P 5550 3100
AR Path="/5E277843/5DEF7276" Ref="J8"  Part="1" 
AR Path="/5DF8D13F/5DEF7276" Ref="J9"  Part="1" 
F 0 "J9" H 5600 3717 50  0000 C CNN
F 1 "Conn_02x09_Top_Bottom" H 5600 3626 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x18_P2.54mm_Vertical" H 5550 3100 50  0001 C CNN
F 3 "~" H 5550 3100 50  0001 C CNN
	1    5550 3100
	1    0    0    -1  
$EndComp
Text GLabel 7600 4050 0    50   Input ~ 0
READY_2
Text GLabel 7600 4750 0    50   Input ~ 0
CS_1
Text GLabel 7600 5050 0    50   Input ~ 0
READY_1
Text GLabel 7600 3950 0    50   Input ~ 0
CS_2
Text GLabel 7600 4150 0    50   Input ~ 0
SYNC
Text GLabel 7600 4350 0    50   Input ~ 0
CLK
Text GLabel 7600 4250 0    50   Input ~ 0
RESET
$Comp
L Mechanical:MountingHole H1
U 1 1 5DEDAA9C
P 4650 4450
F 0 "H1" H 4750 4496 50  0000 L CNN
F 1 "MountingHole" H 4750 4405 50  0000 L CNN
F 2 "MountingHole:MountingHole_2mm" H 4650 4450 50  0001 C CNN
F 3 "~" H 4650 4450 50  0001 C CNN
	1    4650 4450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H5
U 1 1 5DEE31F5
P 4650 4650
F 0 "H5" H 4750 4696 50  0000 L CNN
F 1 "MountingHole" H 4750 4605 50  0000 L CNN
F 2 "MountingHole:MountingHole_2mm" H 4650 4650 50  0001 C CNN
F 3 "~" H 4650 4650 50  0001 C CNN
	1    4650 4650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H6
U 1 1 5DEE3440
P 4650 4850
F 0 "H6" H 4750 4896 50  0000 L CNN
F 1 "MountingHole" H 4750 4805 50  0000 L CNN
F 2 "MountingHole:MountingHole_2mm" H 4650 4850 50  0001 C CNN
F 3 "~" H 4650 4850 50  0001 C CNN
	1    4650 4850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H7
U 1 1 5DEE367E
P 4650 5050
F 0 "H7" H 4750 5096 50  0000 L CNN
F 1 "MountingHole" H 4750 5005 50  0000 L CNN
F 2 "MountingHole:MountingHole_2mm" H 4650 5050 50  0001 C CNN
F 3 "~" H 4650 5050 50  0001 C CNN
	1    4650 5050
	1    0    0    -1  
$EndComp
$Comp
L KiCadSimpleQcw:switch U8
U 1 1 5DEE7C18
P 1400 3900
F 0 "U8" H 1400 4265 50  0000 C CNN
F 1 "switch" H 1400 4174 50  0000 C CNN
F 2 "KiCadSimpleQcw:switch" H 1300 3750 50  0001 C CNN
F 3 "" H 1300 3750 50  0001 C CNN
	1    1400 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 3800 1100 2600
Wire Wire Line
	1100 3900 950  3900
Wire Wire Line
	950  2550 950  3900
$Comp
L Connector:Conn_01x02_Male J8
U 1 1 5DF32FC7
P 2500 4450
F 0 "J8" H 2608 4631 50  0000 C CNN
F 1 "Conn_01x02_Male" H 2608 4540 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2500 4450 50  0001 C CNN
F 3 "~" H 2500 4450 50  0001 C CNN
	1    2500 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5DF33D39
P 3100 4250
AR Path="/5E277843/5DF33D39" Ref="#PWR?"  Part="1" 
AR Path="/5DF8D13F/5DF33D39" Ref="#PWR0143"  Part="1" 
F 0 "#PWR0143" H 3100 4100 50  0001 C CNN
F 1 "+5V" H 3115 4423 50  0000 C CNN
F 2 "" H 3100 4250 50  0001 C CNN
F 3 "" H 3100 4250 50  0001 C CNN
	1    3100 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5DF34503
P 3100 4600
AR Path="/5E277843/5DF34503" Ref="#PWR?"  Part="1" 
AR Path="/5DF8D13F/5DF34503" Ref="#PWR0144"  Part="1" 
F 0 "#PWR0144" H 3100 4450 50  0001 C CNN
F 1 "+3V3" H 3100 4550 50  0000 C CNN
F 2 "" H 3100 4600 50  0001 C CNN
F 3 "" H 3100 4600 50  0001 C CNN
	1    3100 4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	2700 4450 3100 4450
Wire Wire Line
	3100 4450 3100 4250
Wire Wire Line
	2700 4550 3100 4550
Wire Wire Line
	3100 4550 3100 4600
$EndSCHEMATC