Group No.1 : Nobike by ปลากระป๋อง
สมาชิกประกอบด้วย
นายคุณานนต์ บุรเทพ 5910500121
นายชาญชัย ชนาเทพาพร 5910503707
ชั้นปีที่ 2 ปีการศึกษา 2560 คณะ วิศวกรรมศาสตร์ ภาควิชาคอมพิวเตอร์ มหาวิทยาลัย เกษตรศาสตร์ บางเขน

โฟลเดอร์ : nobike_website
เก็บโค้ดในการทำ mobile app ทั้งหมด โดยเริ่มต้นที่ไฟล์ index.html

โฟลเดอร์ : practicum_board_input
เก็บโค้ดสำหรับการควบคุมการส่งค่าจาก GPS ไปหา  Wifi เพื่ออัพขึ้น server
ภายในไฟล์ practicum_board_1 ประกอบไปด้วย 2 โฟลเดอร์หลักๆ
ไฟล์โค้ด gps_to_esp : เป็นโค้ดสำหรับรับค่าและแปลงค่าของ GPS บนบอร์ด practicum และ ส่งค่าที่รับมาได้จาก GPS ไปยัง WiFi module
ไฟล์โค้ด esp_to_server : เป็น โค้ดสำหรับการส่งค่าของ WiFi module ไปยัง Web Server

โฟลเดอร์ : practicum_board_output
เก็บโค้ดสำหรับการควบคุมไฟ บัสเซอร์ และ รับคำสั่งเปิด/ปิดจาก server
ไฟล์โค้ด practicum_nobike.c : เป็นโค้ด set การเปิด/ปิด ไฟและบัสเซอร์
ไฟล์โค้ด esp8266_module.ino : เป็นโค้ดในการรับคำสั่งจาก server


อุปกรณ์ที่ใช้
Practicum Board 2 ชิ้น
GPS Module neo6mv2 1 ชิ้น
ESP WiFi Module 2 ชิ้น
Bi-directional Logic Level Converter 3V to 5V 2 ชิ้น
AMS1117 3.3V Power Supply Module (Voltage Regulator 3.3 V) 2 ชิ้น
LED 2 หลอด 
Buzzer 1 ชิ้น
ตัวต้านทาน(ขนาด) 3 ตัว

ไลบรารีที่ใช้
ESP8266WiFi.h

Link สำหรับการเลือก Board เป็น WiFi module ใน Arduino ide
http://arduino.esp8266.com/stable/package_esp8266com_index.json

SoftwareSerial.h