EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:formula
LIBS:odysseusShield-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L SSM3K333R Q2
U 1 1 5A063FB1
P 2350 2950
F 0 "Q2" H 2550 3025 50  0000 L CNN
F 1 "SSM3K333R" H 2550 2950 50  0000 L CNN
F 2 "footprints:SOT-23F" H 2550 2875 50  0001 L CIN
F 3 "https://drive.google.com/drive/folders/0B-V-iZf33Y4GNzhDQTJZanJRbVk" H 2550 3025 50  0001 L CNN
F 4 "https://www.digikey.com/product-detail/en/toshiba-semiconductor-and-storage/SSM3K333RLF/SSM3K333RLFCT-ND/3522391" H 2650 3125 60  0001 C CNN "PurchasingLink"
F 5 "SSM3K333RLFCT-ND" H 2750 3225 60  0001 C CNN "MPN"
F 6 "Digi-Key" H 2850 3325 60  0001 C CNN "MFN"
F 7 "SOT-23-3 Flat Leads" H 2950 3425 60  0001 C CNN "Package"
	1    2350 2950
	1    0    0    -1  
$EndComp
$Comp
L SSM3K333R Q1
U 1 1 5A064039
P 2050 3150
F 0 "Q1" H 2250 3225 50  0000 L CNN
F 1 "SSM3K333R" H 2250 3150 50  0000 L CNN
F 2 "footprints:SOT-23F" H 2250 3075 50  0001 L CIN
F 3 "https://drive.google.com/drive/folders/0B-V-iZf33Y4GNzhDQTJZanJRbVk" H 2250 3225 50  0001 L CNN
F 4 "https://www.digikey.com/product-detail/en/toshiba-semiconductor-and-storage/SSM3K333RLF/SSM3K333RLFCT-ND/3522391" H 2350 3325 60  0001 C CNN "PurchasingLink"
F 5 "SSM3K333RLFCT-ND" H 2450 3425 60  0001 C CNN "MPN"
F 6 "Digi-Key" H 2550 3525 60  0001 C CNN "MFN"
F 7 "SOT-23-3 Flat Leads" H 2650 3625 60  0001 C CNN "Package"
	1    2050 3150
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x32 J1
U 1 1 5A064289
P 1300 3150
F 0 "J1" H 1300 4750 50  0000 C CNN
F 1 "Conn_01x32" H 1300 1450 50  0000 C CNN
F 2 "odysseus:Header_Arduino_Shield" H 1300 3150 50  0001 C CNN
F 3 "" H 1300 3150 50  0001 C CNN
	1    1300 3150
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x07 J2
U 1 1 5A0643BB
P 1800 1950
F 0 "J2" H 1800 2350 50  0000 C CNN
F 1 "Conn_01x07" H 1800 1550 50  0000 C CNN
F 2 "odysseus:Header_P2.54mm_7" H 1800 1950 50  0001 C CNN
F 3 "" H 1800 1950 50  0001 C CNN
	1    1800 1950
	-1   0    0    1   
$EndComp
Text Label 2000 1650 0    60   ~ 0
HE_GND
Text Label 2000 1750 0    60   ~ 0
HE_Out
Text Label 2000 1850 0    60   ~ 0
HE_VCC
Text Label 2000 1950 0    60   ~ 0
Relay+
Text Label 2000 2050 0    60   ~ 0
Relay-
Text Label 2000 2150 0    60   ~ 0
Estop+
Text Label 2000 2250 0    60   ~ 0
Estop-
$Comp
L GND #PWR01
U 1 1 5A064597
P 2450 3150
F 0 "#PWR01" H 2450 2900 50  0001 C CNN
F 1 "GND" H 2450 3000 50  0000 C CNN
F 2 "" H 2450 3150 50  0001 C CNN
F 3 "" H 2450 3150 50  0001 C CNN
	1    2450 3150
	1    0    0    -1  
$EndComp
Text Label 2450 2750 0    60   ~ 0
Estop-
Text Label 1500 4050 0    60   ~ 0
Relay+
Wire Wire Line
	2000 2050 2000 2150
$Comp
L VCC #PWR02
U 1 1 5A0645FB
P 2500 1750
F 0 "#PWR02" H 2500 1600 50  0001 C CNN
F 1 "VCC" H 2500 1900 50  0000 C CNN
F 2 "" H 2500 1750 50  0001 C CNN
F 3 "" H 2500 1750 50  0001 C CNN
	1    2500 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5A064617
P 3350 1950
F 0 "#PWR03" H 3350 1700 50  0001 C CNN
F 1 "GND" H 3350 1800 50  0000 C CNN
F 2 "" H 3350 1950 50  0001 C CNN
F 3 "" H 3350 1950 50  0001 C CNN
	1    3350 1950
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR04
U 1 1 5A064633
P 2850 1750
F 0 "#PWR04" H 2850 1600 50  0001 C CNN
F 1 "+12V" H 2850 1890 50  0000 C CNN
F 2 "" H 2850 1750 50  0001 C CNN
F 3 "" H 2850 1750 50  0001 C CNN
	1    2850 1750
	1    0    0    -1  
$EndComp
Text Label 2850 1750 3    60   ~ 0
Relay+
Text Label 3350 1950 0    60   ~ 0
HE_GND
Text Label 2500 1750 3    60   ~ 0
HE_VCC
$Comp
L R_10k R1
U 1 1 5A0646A5
P 1850 3000
F 0 "R1" V 1930 3000 50  0000 C CNN
F 1 "R_10k" V 1750 3000 50  0000 C CNN
F 2 "footprints:R_0805_OEM" H 1780 3000 50  0001 C CNN
F 3 "http://www.bourns.com/data/global/pdfs/CRS.pdf" H 1930 3000 50  0001 C CNN
F 4 "CRS0805-FX-1002ELFCT-ND" H 1850 3000 60  0001 C CNN "MPN"
F 5 "Digi-Key" H 1850 3000 60  0001 C CNN "MFN"
F 6 "Value" H 1850 3000 60  0001 C CNN "Package"
F 7 "https://www.digikey.com/products/en?keywords=CRS0805-FX-1002ELFCT-ND" H 2330 3400 60  0001 C CNN "PurchasingLink"
	1    1850 3000
	1    0    0    -1  
$EndComp
$Comp
L R_10k R2
U 1 1 5A0646D8
P 2150 2800
F 0 "R2" V 2230 2800 50  0000 C CNN
F 1 "R_10k" V 2050 2800 50  0000 C CNN
F 2 "footprints:R_0805_OEM" H 2080 2800 50  0001 C CNN
F 3 "http://www.bourns.com/data/global/pdfs/CRS.pdf" H 2230 2800 50  0001 C CNN
F 4 "CRS0805-FX-1002ELFCT-ND" H 2150 2800 60  0001 C CNN "MPN"
F 5 "Digi-Key" H 2150 2800 60  0001 C CNN "MFN"
F 6 "Value" H 2150 2800 60  0001 C CNN "Package"
F 7 "https://www.digikey.com/products/en?keywords=CRS0805-FX-1002ELFCT-ND" H 2630 3200 60  0001 C CNN "PurchasingLink"
	1    2150 2800
	1    0    0    -1  
$EndComp
Text Label 1850 2850 1    60   ~ 0
HE_VCC
Text Label 1850 3150 3    60   ~ 0
HE_Out
$Comp
L VCC #PWR05
U 1 1 5A064869
P 2150 2650
F 0 "#PWR05" H 2150 2500 50  0001 C CNN
F 1 "VCC" H 2150 2800 50  0000 C CNN
F 2 "" H 2150 2650 50  0001 C CNN
F 3 "" H 2150 2650 50  0001 C CNN
	1    2150 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5A064A3D
P 2150 3350
F 0 "#PWR06" H 2150 3100 50  0001 C CNN
F 1 "GND" H 2150 3200 50  0000 C CNN
F 2 "" H 2150 3350 50  0001 C CNN
F 3 "" H 2150 3350 50  0001 C CNN
	1    2150 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5A064AC3
P 1900 4150
F 0 "#PWR07" H 1900 3900 50  0001 C CNN
F 1 "GND" H 1900 4000 50  0000 C CNN
F 2 "" H 1900 4150 50  0001 C CNN
F 3 "" H 1900 4150 50  0001 C CNN
	1    1900 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4250 1500 4150
Wire Wire Line
	1500 4150 1900 4150
$Comp
L VCC #PWR08
U 1 1 5A064B08
P 1600 4350
F 0 "#PWR08" H 1600 4200 50  0001 C CNN
F 1 "VCC" H 1600 4500 50  0000 C CNN
F 2 "" H 1600 4350 50  0001 C CNN
F 3 "" H 1600 4350 50  0001 C CNN
	1    1600 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4350 1600 4350
$Comp
L PWR_FLAG #FLG09
U 1 1 5A064E0D
P 2850 2500
F 0 "#FLG09" H 2850 2575 50  0001 C CNN
F 1 "PWR_FLAG" H 2850 2650 50  0000 C CNN
F 2 "" H 2850 2500 50  0001 C CNN
F 3 "" H 2850 2500 50  0001 C CNN
	1    2850 2500
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG010
U 1 1 5A064E2D
P 2550 2400
F 0 "#FLG010" H 2550 2475 50  0001 C CNN
F 1 "PWR_FLAG" H 2550 2550 50  0000 C CNN
F 2 "" H 2550 2400 50  0001 C CNN
F 3 "" H 2550 2400 50  0001 C CNN
	1    2550 2400
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG011
U 1 1 5A064E69
P 3150 2400
F 0 "#FLG011" H 3150 2475 50  0001 C CNN
F 1 "PWR_FLAG" H 3150 2550 50  0000 C CNN
F 2 "" H 3150 2400 50  0001 C CNN
F 3 "" H 3150 2400 50  0001 C CNN
	1    3150 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5A064E89
P 2550 2400
F 0 "#PWR012" H 2550 2150 50  0001 C CNN
F 1 "GND" H 2550 2250 50  0000 C CNN
F 2 "" H 2550 2400 50  0001 C CNN
F 3 "" H 2550 2400 50  0001 C CNN
	1    2550 2400
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR013
U 1 1 5A064EA9
P 2850 2500
F 0 "#PWR013" H 2850 2350 50  0001 C CNN
F 1 "+12V" H 2850 2640 50  0000 C CNN
F 2 "" H 2850 2500 50  0001 C CNN
F 3 "" H 2850 2500 50  0001 C CNN
	1    2850 2500
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR014
U 1 1 5A064EC9
P 3150 2400
F 0 "#PWR014" H 3150 2250 50  0001 C CNN
F 1 "VCC" H 3150 2550 50  0000 C CNN
F 2 "" H 3150 2400 50  0001 C CNN
F 3 "" H 3150 2400 50  0001 C CNN
	1    3150 2400
	-1   0    0    1   
$EndComp
NoConn ~ 1500 4750
NoConn ~ 1500 4650
NoConn ~ 1500 4550
NoConn ~ 1500 4450
NoConn ~ 1500 3650
NoConn ~ 1500 3550
NoConn ~ 1500 3450
NoConn ~ 1500 3350
NoConn ~ 1500 3250
NoConn ~ 1500 3150
NoConn ~ 1500 3050
NoConn ~ 1500 2950
NoConn ~ 1500 2850
NoConn ~ 1500 2750
NoConn ~ 1500 2650
NoConn ~ 1500 2550
NoConn ~ 1500 2450
NoConn ~ 1500 2350
NoConn ~ 1500 2250
NoConn ~ 1500 2150
NoConn ~ 1500 2050
NoConn ~ 1500 1950
NoConn ~ 1500 1850
NoConn ~ 1500 1750
NoConn ~ 1500 1650
NoConn ~ -2000 2550
$Comp
L Conn_01x07 J3
U 1 1 5A0F7574
P 2300 4000
F 0 "J3" H 2300 4400 50  0000 C CNN
F 1 "Conn_01x07" H 2300 3600 50  0000 C CNN
F 2 "odysseusWindows:Header_P2.54mm_7" H 2300 4000 50  0001 C CNN
F 3 "" H 2300 4000 50  0001 C CNN
	1    2300 4000
	-1   0    0    1   
$EndComp
Text Label 2500 3700 0    60   ~ 0
Fan+
Text Label 2500 3800 0    60   ~ 0
Fan-
Text Label 2500 3900 0    60   ~ 0
Joy+
Text Label 2500 4000 0    60   ~ 0
Joy-
Text Label 2500 4100 0    60   ~ 0
Joy1
Text Label 2500 4200 0    60   ~ 0
Joy2
Text Label 2500 4300 0    60   ~ 0
Joy3
Text Label 2850 1750 0    60   ~ 0
Fan+
Text Label 3350 1950 1    60   ~ 0
Fan-
Text Label 3350 1850 0    60   ~ 0
Joy-
Wire Wire Line
	3350 1950 3350 1850
Text Label 2500 1750 0    60   ~ 0
Joy+
Text Label 1500 3750 0    60   ~ 0
Joy3
Text Label 1500 3850 0    60   ~ 0
Joy2
Text Label 1500 3950 0    60   ~ 0
Joy1
$Comp
L LED_0805 D1
U 1 1 5A11F581
P 3265 3450
F 0 "D1" H 3265 3350 50  0000 C CNN
F 1 "LED_0805" H 3265 3550 50  0000 C CNN
F 2 "footprints:LED_0805_OEM" H 3165 3450 50  0001 C CNN
F 3 "http://www.osram-os.com/Graphics/XPic9/00078860_0.pdf" H 3265 3550 50  0001 C CNN
F 4 "475-1410-1-ND" H 3265 3450 60  0001 C CNN "MPN"
F 5 "Digi-Key" H 3265 3450 60  0001 C CNN "MFN"
F 6 "Value" H 3265 3450 60  0001 C CNN "Package"
F 7 "https://www.digikey.com/products/en?keywords=475-1410-1-ND" H 3665 3950 60  0001 C CNN "PurchasingLink"
	1    3265 3450
	0    -1   -1   0   
$EndComp
$Comp
L LED_0805 D2
U 1 1 5A11F61C
P 3545 3450
F 0 "D2" H 3545 3350 50  0000 C CNN
F 1 "LED_0805" H 3545 3550 50  0000 C CNN
F 2 "footprints:LED_0805_OEM" H 3445 3450 50  0001 C CNN
F 3 "http://www.osram-os.com/Graphics/XPic9/00078860_0.pdf" H 3545 3550 50  0001 C CNN
F 4 "475-1410-1-ND" H 3545 3450 60  0001 C CNN "MPN"
F 5 "Digi-Key" H 3545 3450 60  0001 C CNN "MFN"
F 6 "Value" H 3545 3450 60  0001 C CNN "Package"
F 7 "https://www.digikey.com/products/en?keywords=475-1410-1-ND" H 3945 3950 60  0001 C CNN "PurchasingLink"
	1    3545 3450
	0    -1   -1   0   
$EndComp
$Comp
L R_200 R3
U 1 1 5A11F67F
P 3265 3150
F 0 "R3" V 3345 3150 50  0000 C CNN
F 1 "R_200" V 3165 3150 50  0000 C CNN
F 2 "footprints:R_0805_OEM" H 3195 3150 50  0001 C CNN
F 3 "https://www.seielect.com/Catalog/SEI-RMCF_RMCP.pdf" H 3345 3150 50  0001 C CNN
F 4 "Digi-Key" H 3265 3150 60  0001 C CNN "MFN"
F 5 "RMCF0805JT200RCT-ND" H 3265 3150 60  0001 C CNN "MPN"
F 6 "Value" H 3265 3150 60  0001 C CNN "Package"
F 7 "https://www.digikey.com/products/en?keywords=RMCF0805JT200RCT-ND" H 3745 3550 60  0001 C CNN "PurchasingLink"
	1    3265 3150
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR015
U 1 1 5A11F88C
P 3545 3000
F 0 "#PWR015" H 3545 2850 50  0001 C CNN
F 1 "+12V" H 3545 3140 50  0000 C CNN
F 2 "" H 3545 3000 50  0001 C CNN
F 3 "" H 3545 3000 50  0001 C CNN
	1    3545 3000
	1    0    0    -1  
$EndComp
$Comp
L R_1k R4
U 1 1 5A11F938
P 3545 3150
F 0 "R4" V 3625 3150 50  0000 C CNN
F 1 "R_1k" V 3445 3150 50  0000 C CNN
F 2 "footprints:R_0805_OEM" H 3475 3150 50  0001 C CNN
F 3 "https://www.seielect.com/Catalog/SEI-rncp.pdf" H 3625 3150 50  0001 C CNN
F 4 "Digi-Key" H 3545 3150 60  0001 C CNN "MFN"
F 5 "RNCP0805FTD1K00CT-ND" H 3545 3150 60  0001 C CNN "MPN"
F 6 "Value" H 3545 3150 60  0001 C CNN "Package"
F 7 "https://www.digikey.com/products/en?keywords=RNCP0805FTD1K00CT-ND" H 4025 3550 60  0001 C CNN "PurchasingLink"
	1    3545 3150
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR016
U 1 1 5A11F995
P 3265 3000
F 0 "#PWR016" H 3265 2850 50  0001 C CNN
F 1 "VCC" H 3265 3150 50  0000 C CNN
F 2 "" H 3265 3000 50  0001 C CNN
F 3 "" H 3265 3000 50  0001 C CNN
	1    3265 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5A11F9BF
P 3265 3600
F 0 "#PWR017" H 3265 3350 50  0001 C CNN
F 1 "GND" H 3265 3450 50  0000 C CNN
F 2 "" H 3265 3600 50  0001 C CNN
F 3 "" H 3265 3600 50  0001 C CNN
	1    3265 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5A11F9E9
P 3545 3600
F 0 "#PWR018" H 3545 3350 50  0001 C CNN
F 1 "GND" H 3545 3450 50  0000 C CNN
F 2 "" H 3545 3600 50  0001 C CNN
F 3 "" H 3545 3600 50  0001 C CNN
	1    3545 3600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
